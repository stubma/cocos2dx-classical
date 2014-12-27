#!/usr/bin/python

import sys
from clang.cindex import *
from clang.cindex import AccessSpecifierKind
from clang.cindex import AvailabilityKind
import ConfigParser
import os
import os.path
import re

type_map = {
    TypeKind.VOID        : "void",
    TypeKind.BOOL        : "bool",
    TypeKind.CHAR_U      : "unsigned char",
    TypeKind.UCHAR       : "unsigned char",
    TypeKind.CHAR16      : "char",
    TypeKind.CHAR32      : "char",
    TypeKind.USHORT      : "unsigned short",
    TypeKind.UINT        : "unsigned int",
    TypeKind.ULONG       : "unsigned long",
    TypeKind.ULONGLONG   : "unsigned long long",
    TypeKind.CHAR_S      : "char",
    TypeKind.SCHAR       : "char",
    TypeKind.WCHAR       : "wchar_t",
    TypeKind.SHORT       : "short",
    TypeKind.INT         : "int",
    TypeKind.LONG        : "long",
    TypeKind.LONGLONG    : "long long",
    TypeKind.FLOAT       : "float",
    TypeKind.DOUBLE      : "double",
    TypeKind.LONGDOUBLE  : "long double",
    TypeKind.NULLPTR     : "NULL",
    TypeKind.OBJCID      : "id",
    TypeKind.OBJCCLASS   : "class",
    TypeKind.OBJCSEL     : "SEL",
}

INVALID_NATIVE_TYPE = "??"

default_arg_type_arr = [
    # An integer literal.
    CursorKind.INTEGER_LITERAL,

    # A floating point number literal.
    CursorKind.FLOATING_LITERAL,

    # An imaginary number literal.
    CursorKind.IMAGINARY_LITERAL,

    # A string literal.
    CursorKind.STRING_LITERAL,

    # A character literal.
    CursorKind.CHARACTER_LITERAL,

    # [C++ 2.13.5] C++ Boolean Literal.
    CursorKind.CXX_BOOL_LITERAL_EXPR,

    # [C++0x 2.14.7] C++ Pointer Literal.
    CursorKind.CXX_NULL_PTR_LITERAL_EXPR,

    # An expression that refers to some value declaration, such as a function,
    # varible, or enumerator.
    CursorKind.DECL_REF_EXPR
]

def build_namespace(cursor, namespaces=[]):
    if cursor:
        parent = cursor.semantic_parent
        if parent:
            if parent.kind == CursorKind.NAMESPACE or parent.kind == CursorKind.CLASS_DECL:
                namespaces.append(parent.displayname)
                build_namespace(parent, namespaces)

    return namespaces

def get_qualified_name(node):
    ns_list = build_namespace(node, [])
    ns_list.reverse()
    ns = "::".join(ns_list)
    if len(ns) > 0:
        return ns + "::" + node.displayname
    return node.displayname

def get_qualified_namespace(node):
    ns_list = build_namespace(node, [])
    ns_list.reverse()
    ns = "::".join(ns_list)
    return ns

def native_name_from_type(ntype, underlying=False):
    kind = ntype.kind
    const = ""
    if not underlying and kind == TypeKind.ENUM:
        decl = ntype.get_declaration()
        return get_qualified_name(decl)
    elif kind in type_map:
        return const + type_map[kind]
    elif kind == TypeKind.RECORD:
        # might be an std::string
        decl = ntype.get_declaration()
        parent = decl.semantic_parent
        cdecl = ntype.get_canonical().get_declaration()
        cparent = cdecl.semantic_parent
        if decl.spelling == "string" and parent and parent.spelling == "std":
            return "std::string"
        elif cdecl.spelling == "function" and cparent and cparent.spelling == "std":
            return "std::function"
        else:
            return const + decl.spelling
    else:
        return INVALID_NATIVE_TYPE

class NativeType(object):
    def __init__(self):
        self.is_class = False
        self.is_function = False
        self.is_enum = False
        self.not_supported = False
        self.param_types = []
        self.ret_type = None
        self.qualified_name = ""
        self.qualified_ns  = ""
        self.name = ""
        self.whole_name = None
        self.is_const = False
        self.is_pointer = False
        self.is_ref = False
        self.canonical_type = None
        self.pointee_name = ""
        self.qualified_pointee_name = ""

    @staticmethod
    def from_type(ntype):
        if ntype.kind == TypeKind.POINTER:
            nt = NativeType.from_type(ntype.get_pointee())

            if nt.canonical_type is not None:
                nt.canonical_type.name += "*"
                nt.canonical_type.qualified_name += "*"
                nt.canonical_type.whole_name += "*"

            nt.name += "*"
            nt.qualified_name += "*"
            nt.whole_name = nt.qualified_name
            nt.is_enum = False
            nt.is_const = ntype.get_pointee().is_const_qualified()
            nt.is_pointer = True

            # const prefix
            if nt.is_const:
                nt.whole_name = "const " + nt.whole_name
                nt.name = "const " + nt.name
        elif ntype.kind == TypeKind.LVALUEREFERENCE:
            nt = NativeType.from_type(ntype.get_pointee())
            nt.is_const = ntype.get_pointee().is_const_qualified()
            nt.is_ref = True
            nt.whole_name = nt.qualified_name + "&"
            nt.name += "&"

            # const prefix
            if nt.is_const:
                nt.whole_name = "const " + nt.whole_name
                nt.name = "const " + nt.name

            if nt.canonical_type is not None:
                nt.canonical_type.whole_name += "&"
                nt.canonical_type.name += "&"
        else:
            nt = NativeType()
            decl = ntype.get_declaration()

            if ntype.kind == TypeKind.RECORD:
                if decl.kind == CursorKind.CLASS_DECL or decl.kind == CursorKind.STRUCT_DECL:
                    nt.is_class = True
                nt.name = decl.displayname
                nt.pointee_name = nt.name
                nt.qualified_name = get_qualified_name(decl)
                nt.qualified_ns  = get_qualified_namespace(decl)
                nt.whole_name = nt.qualified_name
                nt.qualified_pointee_name = nt.whole_name
            else:
                if decl.kind == CursorKind.NO_DECL_FOUND:
                    nt.name = native_name_from_type(ntype)
                else:
                    nt.name = decl.spelling
                nt.pointee_name = nt.name
                nt.qualified_name = get_qualified_name(decl)
                nt.qualified_ns  = get_qualified_namespace(decl)

                if nt.qualified_name == "std::string":
                    nt.name = nt.qualified_name

                if nt.qualified_name.startswith("std::function"):
                    nt.name = "std::function"

                if len(nt.qualified_name) == 0 or nt.qualified_name.find("::") == -1:
                    nt.qualified_name = nt.name

                nt.whole_name = nt.qualified_name
                nt.qualified_pointee_name = nt.whole_name
                nt.is_const = ntype.is_const_qualified()

                # const prefix
                if nt.is_const:
                    nt.whole_name = "const " + nt.whole_name

                # Check whether it's a std::function typedef
                cdecl = ntype.get_canonical().get_declaration()
                if None != cdecl.spelling and 0 == cmp(cdecl.spelling, "function"):
                    nt.name = "std::function"

                if nt.name != INVALID_NATIVE_TYPE and nt.name != "std::string" and nt.name != "std::function":
                    if ntype.kind == TypeKind.UNEXPOSED or ntype.kind == TypeKind.TYPEDEF:
                        ret = NativeType.from_type(ntype.get_canonical())
                        if ret.name != "":
                            if decl.kind == CursorKind.TYPEDEF_DECL:
                                ret.canonical_type = nt
                            return ret

                nt.is_enum = ntype.get_canonical().kind == TypeKind.ENUM

                if nt.name == "std::function":
                    nt.qualified_name = get_qualified_name(cdecl)
                    r = re.compile('function<(.+) .*\((.*)\)>').search(cdecl.displayname)
                    (ret_type, params) = r.groups()
                    params = filter(None, params.split(", "))

                    nt.is_function = True
                    nt.ret_type = NativeType.from_string(ret_type)
                    nt.param_types = [NativeType.from_string(string) for string in params]

        # mark argument as not supported
        if nt.name == INVALID_NATIVE_TYPE:
            nt.not_supported = True

        return nt

    @staticmethod
    def from_string(displayname):
        displayname = displayname.replace(" *", "*")

        nt = NativeType()
        nt.name = displayname.split("::")[-1]
        nt.qualified_name = displayname
        nt.whole_name = nt.qualified_name
        nt.is_class = True
        return nt

class NativeEnum(object):
    def __init__(self, node):
        self.node = node
        self.enum_name = node.displayname
        self.qualified_name = get_qualified_name(node)
        self.constants = []

        # visit
        self.visit_node(self.node)

    def generate_tolua(self, indent_level=0):
        # indent
        tolua = "\t" * indent_level

        # enum
        tolua += "enum " + self.enum_name + " {\n"

        # constants
        first_constant = True
        for c in self.constants:
            if first_constant is False:
                tolua += ",\n"
            tolua += "\t" * (indent_level + 1)
            tolua += c
            first_constant = False

        # close
        tolua += "\n"
        tolua += "\t" * indent_level
        tolua += "};\n"

        # final string
        return tolua

    def visit_node(self, node):
        # visit all children
        for c in node.get_children():
            self.process_node(c)
            self.visit_node(c)

    def process_node(self, node):
        if node.kind == CursorKind.ENUM_CONSTANT_DECL:
            self.constants.append(node.spelling)

class NativeOverloadedFunction(object):
    def __init__(self, func_array):
        self.implementations = func_array
        self.func_name = func_array[0].func_name
        self.signature_name = self.func_name
        self.min_args = sys.maxint
        self.is_constructor = False
        for m in func_array:
            self.min_args = min(self.min_args, m.min_args)

    def append(self, func):
        self.min_args = min(self.min_args, func.min_args)
        self.implementations.append(func)

    def generate_tolua(self, indent_level=0):
        tolua = ""
        for f in self.implementations:
            tolua += f.generate_tolua(indent_level)
        return tolua

class NativeFunction(object):
    def __init__(self, node):
        self.node = node
        self.is_constructor = False
        self.is_destructor = False
        self.func_name = node.spelling
        self.signature_name = self.func_name
        self.arguments = []
        self.argumtntTips = [arg.spelling for arg in node.get_arguments()]
        self.static = node.kind == CursorKind.CXX_METHOD and node.is_static_method()
        self.implementations = []
        self.not_supported = False
        self.is_override = False
        self.ret_type = NativeType.from_type(node.result_type)

        # mark the function as not supported if at least one argument is not supported
        for arg in node.type.argument_types():
            nt = NativeType.from_type(arg)
            self.arguments.append(nt)
            if nt.not_supported:
                self.not_supported = True

        # parse arguments
        self.min_args = len(self.arguments)
        index = -1
        for arg_node in self.node.get_children():
            if arg_node.kind == CursorKind.CXX_OVERRIDE_ATTR:
                self.is_override = True
            if arg_node.kind == CursorKind.PARM_DECL:
                index += 1
                if self.has_default_arg(arg_node):
                    self.min_args = index
                    break

    def has_default_arg(self, param_node):
        for node in param_node.get_children():
            if node.kind in default_arg_type_arr:
                return True
            if self.has_default_arg(node):
                return True
        return False

    def get_enums(self):
        e = []
        if self.ret_type.is_enum:
            e.append(self.ret_type)
        for arg in self.arguments:
            if arg.is_enum:
                e.append(arg)
        return e

    def generate_tolua(self, indent_level=0):
        # returned string
        tolua = ""

        # if override, no return
        if self.is_override:
            return tolua

        # indent
        tolua = "\t" * indent_level

        # constructor or not
        if self.is_constructor or self.is_destructor:
            tolua += self.func_name
        else:
            # static
            if self.static:
                tolua += "static "

            # return type
            tolua += self.ret_type.name

            # name
            tolua += " " + self.func_name

        # args
        tolua += "("
        first_arg = True
        for (arg_type, arg_name) in zip(self.arguments, self.argumtntTips):
            if first_arg is False:
                tolua += ", "
            tolua += arg_type.name + " " + arg_name
            first_arg = False
        tolua += ");\n"

        # final string
        return tolua

class NativeField(object):
    def __init__(self, node):
        cnode = node.canonical
        self.node = cnode
        self.name = cnode.displayname
        self.type = NativeType.from_type(cnode.type)
        self.location = cnode.location

    def generate_tolua(self, indent_level=0):
        tolua = ""

        # if type is not support, return
        if self.type.not_supported:
            return tolua

        # indent
        tolua = "\t" * indent_level

        # type
        tolua += self.type.name

        # name
        tolua += " " + self.name + ";\n"

        # final string
        return tolua

class NativeClass(object):
    def __init__(self, node, generator):
        self.node = node
        self.generator = generator
        self.class_name = node.displayname
        self.qualified_name = get_qualified_name(node)
        self.parents = []
        self.fields = []
        self.methods = {}
        self.static_methods = {}
        self.is_struct = False
        self.current_access_specifier = AccessSpecifierKind.PRIVATE
        if node.kind == CursorKind.STRUCT_DECL:
            self.current_access_specifier = AccessSpecifierKind.PUBLIC
            self.is_struct = True
        self.override_methods = {}
        self.has_constructor = False
        self.qualified_ns = get_qualified_namespace(node)
        self.enums = {}
        self.generated_enums = {}
        self.structs = {}
        self.generated_structs = {}

        # visit
        self.visit_node(self.node)

    def is_method_in_parents(self, method_name):
        if len(self.parents) > 0:
            if method_name in self.parents[0].methods:
                return True
            return self.parents[0].is_method_in_parents(method_name)
        return False

    def use_any_non_public_enums(self, nf):
        for e in nf.get_enums():
            if not self.generator.enums.has_key(e.qualified_name) and not self.enums.has_key(e.qualified_name):
                return True
        return False

    def use_any_non_public_structs(self, nf):
        for arg in nf.arguments:
            if arg.is_class and not self.generator.structs.has_key(arg.qualified_name) and not self.structs.has_key(arg.qualified_name):
                return True
        return False

    def record_function_enums(self, nf):
        for e in nf.get_enums():
            if self.enums.has_key(e.qualified_name):
                self.generated_enums[e.qualified_name] = self.enums[e.qualified_name]
            elif self.generator.enums.has_key(e.qualified_name):
                self.generator.generated_enums[e.qualified_name] = self.generator.enums[e.qualified_name]

    def record_function_structs(self, nf):
        for arg in nf.arguments:
            if arg.is_class:
                if self.structs.has_key(arg.qualified_name):
                    self.generated_structs[arg.qualified_name] = self.structs[arg.qualified_name]
                elif self.generator.structs.has_key(arg.qualified_name):
                    self.generator.generated_structs[arg.qualified_name] = self.generator.structs[arg.qualified_name]

    def record_field_enums(self, nf):
        if self.enums.has_key(nf.type.qualified_name):
            self.generated_enums[nf.type.qualified_name] = self.enums[nf.type.qualified_name]
        elif self.generator.enums.has_key(nf.type.qualified_name):
            self.generator.generated_enums[nf.type.qualified_name] = self.generator.enums[nf.type.qualified_name]

    def record_field_structs(self, nf):
        if self.structs.has_key(nf.type.qualified_name):
            self.generated_structs[nf.type.qualified_name] = self.structs[nf.type.qualified_name]
        elif self.generator.structs.has_key(nf.type.qualified_name):
            self.generator.generated_structs[nf.type.qualified_name] = self.generator.structs[nf.type.qualified_name]

    def generate_tolua(self, indent_level=0):
        # buf
        tolua = "\t" * indent_level

        # write class
        if self.is_struct:
            tolua += "struct "
        else:
            tolua += "class "
        tolua += self.class_name

        # parent
        if len(self.parents) > 0:
            first_parent = True
            for p in self.parents:
                if first_parent is False:
                    tolua += ", public " + p.class_name
                else:
                    tolua += " : public " + p.class_name
                    first_parent = False
        tolua += " {\n"

        # fields
        for f in self.fields:
            if f.type.is_enum:
                if self.generator.enums.has_key(f.type.qualified_name) or self.enums.has_key(f.type.qualified_name):
                    tolua += f.generate_tolua(indent_level + 1)
                    self.record_field_enums(f)
            elif f.type.is_class:
                if self.generator.structs.has_key(f.type.qualified_pointee_name) or self.structs.has_key(f.type.qualified_pointee_name):
                    tolua += f.generate_tolua(indent_level + 1)
                    self.record_field_structs(f)
                elif self.generator.classes.has_key(f.type.qualified_pointee_name):
                    tolua += f.generate_tolua(indent_level + 1)
            else:
                tolua += f.generate_tolua(indent_level + 1)

        # write static methods
        mlist = []
        for name, m in self.static_methods.items():
            del mlist[:]
            if isinstance(m, NativeOverloadedFunction):
                mlist += m.implementations
            else:
                mlist.append(m)
            for f in mlist:
                if not self.use_any_non_public_enums(f) and not self.use_any_non_public_structs(f):
                    tolua += f.generate_tolua(indent_level + 1)
                    self.record_function_enums(f)
                    self.record_function_structs(f)

        # write methods
        for name, m in self.methods.items():
            del mlist[:]
            if isinstance(m, NativeOverloadedFunction):
                mlist += m.implementations
            else:
                mlist.append(m)
            for f in mlist:
                if not self.use_any_non_public_enums(f) and not self.use_any_non_public_structs(f):
                    tolua += f.generate_tolua(indent_level + 1)
                    self.record_function_enums(f)
                    self.record_function_structs(f)

        # write override methods
        for name, m in self.override_methods.items():
            del mlist[:]
            if isinstance(m, NativeOverloadedFunction):
                mlist += m.implementations
            else:
                mlist.append(m)
            for f in mlist:
                if not self.use_any_non_public_enums(f) and not self.use_any_non_public_structs(f):
                    tolua += f.generate_tolua(indent_level + 1)
                    self.record_function_enums(f)
                    self.record_function_structs(f)

        # write class enums
        for name, e in self.generated_enums.items():
            tolua += e.generate_tolua(indent_level + 1)

        # write class structs
        for name, s in self.generated_structs.items():
            tolua += s.generate_tolua(indent_level + 1)

        # end of class
        tolua += "\t" * indent_level
        tolua += "};\n"

        # final string
        return tolua

    def visit_node(self, node):
        # visit all children
        for c in node.get_children():
            self.process_node(c)
            self.visit_node(c)

    def process_node(self, node):
        if node.kind == CursorKind.CXX_BASE_SPECIFIER:
            parent = node.get_definition()
            if parent is not None:
                parent_qn = get_qualified_name(parent)
                if not self.generator.classes.has_key(parent_qn):
                    parent = NativeClass(parent, self.generator)
                    self.generator.classes[parent_qn] = parent
                else:
                    parent = self.generator.classes[parent_qn]
                self.parents.append(parent)
        elif node.kind == CursorKind.FIELD_DECL:
            if node.semantic_parent == self.node and self.current_access_specifier == AccessSpecifierKind.PUBLIC:
                self.fields.append(NativeField(node))
        elif node.kind == CursorKind.ENUM_DECL:
            if node.semantic_parent == self.node and self.current_access_specifier == AccessSpecifierKind.PUBLIC:
                ne = NativeEnum(node)
                self.enums[get_qualified_name(node)] = ne
        elif node.kind == CursorKind.STRUCT_DECL:
            if node.semantic_parent == self.node and self.current_access_specifier == AccessSpecifierKind.PUBLIC:
                st = NativeClass(node, self.generator)
                self.structs[st.qualified_name] = st
        elif node.kind == CursorKind.CXX_ACCESS_SPEC_DECL:
            if node.semantic_parent == self.node:
                self.current_access_specifier = node.get_access_specifier()
        elif node.kind == CursorKind.CXX_METHOD and node.get_availability() != AvailabilityKind.DEPRECATED:
            if node.semantic_parent == self.node and self.current_access_specifier == AccessSpecifierKind.PUBLIC and not node.type.is_function_variadic():
                nf = NativeFunction(node)

                # if function is not supported, skip it
                # not supported means at least one argument type is not supported
                if nf.not_supported:
                    return

                # if function is override, need confirm it is defined in parents
                if nf.is_override:
                    if self.is_method_in_parents(nf.func_name):
                        if not self.override_methods.has_key(nf.func_name):
                            self.override_methods[nf.func_name] = nf
                        else:
                            previous_nf = self.override_methods[nf.func_name]
                            if isinstance(previous_nf, NativeOverloadedFunction):
                                previous_nf.append(nf)
                            else:
                                self.override_methods[nf.func_name] = NativeOverloadedFunction([nf, previous_nf])
                        return False

                # non-override function
                if nf.static:
                    if not self.static_methods.has_key(nf.func_name):
                        self.static_methods[nf.func_name] = nf
                    else:
                        previous_nf = self.static_methods[nf.func_name]
                        if isinstance(previous_nf, NativeOverloadedFunction):
                            previous_nf.append(nf)
                        else:
                            self.static_methods[nf.func_name] = NativeOverloadedFunction([nf, previous_nf])
                else:
                    if not self.methods.has_key(nf.func_name):
                        self.methods[nf.func_name] = nf
                    else:
                        previous_nf = self.methods[nf.func_name]
                        if isinstance(previous_nf, NativeOverloadedFunction):
                            previous_nf.append(nf)
                        else:
                            self.methods[nf.func_name] = NativeOverloadedFunction([nf, previous_nf])
        elif node.kind == CursorKind.CONSTRUCTOR and self.current_access_specifier == AccessSpecifierKind.PUBLIC:
            nf = NativeFunction(node)
            nf.is_constructor = True
            self.has_constructor = True
            if not self.methods.has_key('constructor'):
                self.methods['constructor'] = nf
            else:
                previous_nf = self.methods['constructor']
                if isinstance(previous_nf, NativeOverloadedFunction):
                    previous_nf.append(nf)
                else:
                    nf = NativeOverloadedFunction([nf, previous_nf])
                    nf.is_constructor = True
                    self.methods['constructor'] = nf
        elif node.kind == CursorKind.DESTRUCTOR:
            nf = NativeFunction(node)
            nf.is_destructor = True
            self.methods['destructor'] = nf

class Generator(object):
    def __init__(self, conf):
        config = ConfigParser.SafeConfigParser()
        config.read(conf)
        ndk_root = os.getenv("NDK_ROOT")
        self.conf = conf
        self.clang = Index.create()
        self.current_ns = ""
        self.clang_args = [
            "-x", "c++-header",
            "-nostdinc",
            "-std=c++11",
            "-I" + ndk_root + "/platforms/android-14/arch-arm/usr/include",
            "-I" + ndk_root + "/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a/include",
            "-I" + ndk_root + "/sources/cxx-stl/gnu-libstdc++/4.9/include",
            "-I" + ndk_root + "/toolchains/llvm-3.4/prebuilt/darwin-x86_64/lib/clang/3.4/include",
            "-I../../cocos2dx/include",
            "-I../../cocos2dx",
            "-I../../cocos2dx/platform/android",
            "-I../../cocos2dx/platform/android/jni",
            "-I../../cocos2dx/kazmath/include",
            "-DANDROID",
            "-D_SIZE_T_DEFINED_"
        ]
        self.target_ns = config.get("DEFAULT", "target_ns").split(" ") if config.has_option("DEFAULT", "target_ns") else None
        self.src_dir = config.get("DEFAULT", "src_dir") if config.has_option("DEFAULT", "src_dir") else "."
        self.dst_dir = config.get("DEFAULT", "dst_dir") if config.has_option("DEFAULT", "dst_dir") else "."
        exclude_classes = config.get("DEFAULT", "exclude_classes").split(" ") if config.has_option("DEFAULT", "exclude_classes") else None
        self.exclude_classes_regex = [re.compile(x) for x in exclude_classes]
        include_classes = config.get("DEFAULT", "include_classes").split(" ") if config.has_option("DEFAULT", "include_classes") else None
        self.include_classes_regex = [re.compile(x) for x in include_classes]
        self.classes = {}
        self.generated_classes = {}
        self.generated_enums = {}
        self.generated_structs = {}
        self.enums = {}
        self.structs = {}

    def is_class_excluded(self, name):
        for r in self.exclude_classes_regex:
            if r.match(name):
                return True
        return False

    def is_class_included(self, name):
        for r in self.include_classes_regex:
            if r.match(name):
                return True
        return False

    def process_node(self, node):
        if node.kind == CursorKind.CLASS_DECL:
            # check namespace for found class
            if node == node.type.get_declaration() and len(node.get_children_array()) > 0:
                # add class


                # check class is target or not
                is_targeted_class = False
                ns = get_qualified_namespace(node)
                if len(ns) <= 0 or ns in self.target_ns:
                    is_targeted_class = True

                # if it is target class, process it
                if is_targeted_class and not self.generated_classes.has_key(node.displayname):
                    if self.is_class_included(node.displayname) or not self.is_class_excluded(node.displayname):
                        klass = NativeClass(node, self)
                        self.classes[klass.qualified_name] = klass
                        self.generated_classes[node.displayname] = klass
        elif node.kind == CursorKind.ENUM_DECL:
            if node == node.type.get_declaration() and len(node.get_children_array()) > 0 and len(node.displayname) > 0:
                ne = NativeEnum(node)
                self.enums[get_qualified_name(node)] = ne
        elif node.kind == CursorKind.STRUCT_DECL:
            if node == node.type.get_declaration() and len(node.get_children_array()) > 0:
                if not self.structs.has_key(node.displayname):
                    st = NativeClass(node, self)
                    self.structs[st.qualified_name] = st

    def visit_node(self, node):
        # visit all children
        for c in node.get_children():
            self.process_node(c)
            self.visit_node(c)

    @staticmethod
    def process_dir(args, dirname, filenames):
        _self = args
        for f in filenames:
            # if file is header, and not hidden, process it
            filepath = os.path.join(dirname, f)
            if os.path.isfile(filepath) and not os.path.basename(filepath).startswith("."):
                ext = os.path.splitext(filepath)[1][1:]
                if ext == "h":
                    tu = _self.clang.parse(filepath, _self.clang_args)
                    print 'parsing file:', filepath

                    # verify source file
                    if not _self.verify_source(tu):
                        print "%s contains errors, skip it" % filepath
                        continue

                    # visit from top node
                    _self.visit_node(tu.cursor)

    def generate_tolua(self):
        # ensure dst dir existence
        if not os.path.exists(self.dst_dir):
            os.makedirs(self.dst_dir)

        # recursively visit all headers
        os.path.walk(self.src_dir, self.process_dir, self)

        # generate tolua file
        confname = os.path.basename(self.conf)
        dstpath = os.path.join(self.dst_dir, os.path.splitext(confname)[0] + ".tolua")
        dstfile = open(dstpath, "w")

        # write classes
        for name, c in self.generated_classes.items():
            dstfile.write(c.generate_tolua())

        # write global enums
        for name, e in self.generated_enums.items():
            dstfile.write(e.generate_tolua())

        # write global structs
        for name, s in self.generated_structs.items():
            dstfile.write(s.generate_tolua())

        # close
        dstfile.close()

    def print_diag(self, diagnostics):
        print("====\nErrors in parsing headers:")
        severities=['Ignored', 'Note', 'Warning', 'Error', 'Fatal']
        for idx, d in enumerate(diagnostics):
            print "%s. <severity = %s,\n    location = %r,\n    details = %r>" % (
                idx+1, severities[d.severity], d.location, d.spelling)
        print("====")

    def verify_source(self, tu):
        syntax_ok = True
        if len(tu.diagnostics) > 0:
            for d in tu.diagnostics:
                if d.severity >= Diagnostic.Error:
                    self.print_diag(tu.diagnostics)
                    syntax_ok = False
                    break
        return syntax_ok

def main():
    # set libclang path
    Config.set_library_file("libclang/libclang.dylib")

    # check ndk root env
    ndk_root = os.getenv("NDK_ROOT")
    if not ndk_root:
        print "Please set NDK_ROOT environment"
        return

    # generate
    g = Generator(sys.argv[1])
    g.generate_tolua()

if __name__ == '__main__':
    main()