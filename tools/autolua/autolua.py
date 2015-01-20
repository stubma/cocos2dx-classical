#!/usr/bin/python

import sys
from clang.cindex import *
from clang.cindex import AccessSpecifierKind
from clang.cindex import AvailabilityKind
import ConfigParser
import os
import os.path
import re
from Cheetah.Template import Template
import yaml

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

def dict_has_key_re(dict, real_key_list):
    for real_key in real_key_list:
        for (k, v) in dict.items():
            if k.startswith('@'):
                k = k[1:]
                match = re.match("^" + k + "$", real_key)
                if match:
                    return True
            else:
                if k == real_key:
                    return True
    return False

def dict_get_value_re(dict, real_key_list):
    for real_key in real_key_list:
        for (k, v) in dict.items():
            if k.startswith('@'):
                k = k[1:]
                match = re.match("^" + k + "$", real_key)
                if match:
                    return v
            else:
                if k == real_key:
                    return v
    return None

def dict_replace_value_re(dict, real_key_list):
    for real_key in real_key_list:
        for (k, v) in dict.items():
            if k.startswith('@'):
                k = k[1:]
                match = re.match('.*' + k, real_key)
                if match:
                    return re.sub(k, v, real_key)
            else:
                if k == real_key:
                    return v
    return None

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
    if len(ns) > 0:
        ns += "::"
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
        self.is_struct = False
        self.is_union = False
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
        self.pointer_level = 0

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
            nt.is_const = ntype.get_pointee().is_const_qualified()
            nt.is_pointer = True
            nt.pointer_level += 1

            # const prefix
            if nt.is_const:
                nt.whole_name = "const " + nt.whole_name

            # don't support non-object pointer
            if not nt.is_class and nt.name != "char*":
                nt.not_supported = True
        elif ntype.kind == TypeKind.LVALUEREFERENCE:
            nt = NativeType.from_type(ntype.get_pointee())
            nt.is_const = ntype.get_pointee().is_const_qualified()
            nt.is_ref = True
            nt.whole_name = nt.qualified_name + "&"

            # const prefix
            if nt.is_const:
                nt.whole_name = "const " + nt.whole_name

            if nt.canonical_type is not None:
                nt.canonical_type.whole_name += "&"
        elif ntype.kind == TypeKind.RECORD:
            nt = NativeType()
            decl = ntype.get_declaration()
            if decl.kind == CursorKind.CLASS_DECL or decl.kind == CursorKind.STRUCT_DECL:
                nt.is_class = True
            nt.name = decl.displayname
            nt.qualified_name = get_qualified_name(decl)
            nt.qualified_ns  = get_qualified_namespace(decl)
            nt.whole_name = nt.qualified_name
        else:
            nt = NativeType()
            decl = ntype.get_declaration()
            ctype = ntype.get_canonical()
            cdecl = ctype.get_declaration()

            # find name
            if decl.kind == CursorKind.TYPEDEF_DECL:
                decl_type = None
                if len(decl.get_children_array()) > 0:
                    decl_type = decl.get_children_array()[0]
                if ctype.kind == TypeKind.MEMBERPOINTER:
                    nt.name = decl.displayname
                    nt.not_supported = True
                elif decl_type is None:
                    if ctype.kind == TypeKind.POINTER or ctype.kind == TypeKind.LVALUEREFERENCE or ctype.kind == TypeKind.RECORD:
                        nt = NativeType.from_type(ctype)
                    else:
                        nt.name = native_name_from_type(ctype)
                        nt.qualified_name = get_qualified_name(decl)
                        nt.qualified_ns  = get_qualified_namespace(decl)
                elif decl_type.kind == CursorKind.STRUCT_DECL:
                    nt.is_struct = True
                    nt.name = decl.displayname
                    nt.qualified_name = get_qualified_name(decl)
                    nt.qualified_ns  = get_qualified_namespace(decl)
                elif decl_type.kind == CursorKind.UNION_DECL:
                    nt.is_union = True
                    nt.name = decl.displayname
                    nt.qualified_name = get_qualified_name(decl)
                    nt.qualified_ns  = get_qualified_namespace(decl)
                elif decl_type.kind == CursorKind.ENUM_DECL:
                    nt.is_enum = True
                    nt.name = decl.displayname
                    nt.qualified_name = get_qualified_name(decl)
                    nt.qualified_ns  = get_qualified_namespace(decl)
                else:
                    if ctype.kind == TypeKind.POINTER or ctype.kind == TypeKind.LVALUEREFERENCE or ctype.kind == TypeKind.RECORD:
                        nt = NativeType.from_type(ctype)
                    else:
                        nt.name = native_name_from_type(ctype)
                        nt.qualified_name = get_qualified_name(decl)
                        nt.qualified_ns  = get_qualified_namespace(decl)
            elif decl.kind == CursorKind.NO_DECL_FOUND:
                nt.name = native_name_from_type(ntype)
                nt.qualified_name = get_qualified_name(decl)
                nt.qualified_ns  = get_qualified_namespace(decl)
            elif decl.kind == CursorKind.CLASS_DECL:
                nt.name = decl.displayname
                nt.qualified_name = get_qualified_name(decl)
                nt.qualified_ns = get_qualified_namespace(decl)
                nt.is_class = True
            else:
                nt.name = decl.spelling
                nt.qualified_name = get_qualified_name(decl)
                nt.qualified_ns = get_qualified_namespace(decl)

            # special checking for std::string and std::function
            decl_qn = get_qualified_name(decl)
            if decl_qn == "std::string":
                nt.name = decl_qn
                nt.qualified_name = decl_qn
            if decl_qn.startswith("std::function"):
                nt.name = decl_qn
                nt.qualified_name = "std::function"

            # if failed to get qualified name, use name as qualified name
            if len(nt.qualified_name) == 0 or nt.qualified_name.find("::") == -1:
                nt.qualified_name = nt.name

            # set canonical type
            if nt.name != INVALID_NATIVE_TYPE and nt.name != "std::string" and nt.name != "std::function":
                if ntype.kind == TypeKind.UNEXPOSED or ntype.kind == TypeKind.TYPEDEF:
                    if decl.kind == CursorKind.TYPEDEF_DECL:
                        ret = NativeType.from_type(ctype)
                        if ret.name != "":
                            nt.canonical_type = ret

            # whole name
            nt.whole_name = nt.qualified_name

            # const prefix, only for whole name
            nt.is_const = ntype.is_const_qualified()
            if nt.is_const:
                nt.whole_name = "const " + nt.whole_name

            # Check whether it's a std::function typedef
            if None != cdecl.spelling and 0 == cmp(cdecl.spelling, "function"):
                nt.name = "std::function"

            # is enum?
            nt.is_enum = ctype.kind == TypeKind.ENUM

            # if is std::function, get function argument types
            if nt.qualified_name == "std::function":
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

        # multilevel pointer not supported
        if nt.is_pointer and nt.pointer_level > 1:
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

    def decl_in_tpl(self, generator):
        # search in type mapping first
        native_types_dict = generator.tpl_opt['conversions']['native_types']
        if dict_has_key_re(native_types_dict, [self.qualified_name]):
            return dict_get_value_re(native_types_dict, [self.qualified_name])

        # get name
        name = self.qualified_name

        # dict
        to_native_dict = generator.tpl_opt['conversions']['to_native']
        from_native_dict = generator.tpl_opt['conversions']['from_native']

        # get typedef name
        use_typedef = False
        typedef_name = self.canonical_type.name if None != self.canonical_type else None

        # if has typedef name, and type mapping is found, use canonical name
        if None != typedef_name:
            if dict_has_key_re(to_native_dict, [typedef_name]) or dict_has_key_re(from_native_dict, [typedef_name]):
                use_typedef = True
        if use_typedef and self.canonical_type:
            name = self.canonical_type.qualified_name

        # final name
        return name

    def whole_decl_in_tpl(self, generator):
        # get mapping dict
        conversions = generator.tpl_opt['conversions']
        to_native_dict = conversions['to_native']
        from_native_dict = conversions['from_native']

        # get canonical name if has
        use_typedef = False
        name = self.whole_name
        typedef_name = self.canonical_type.name if None != self.canonical_type else None
        if None != typedef_name:
            if dict_has_key_re(to_native_dict, [typedef_name]) or dict_has_key_re(from_native_dict, [typedef_name]):
                use_typedef = True
        if use_typedef and self.canonical_type:
            name = self.canonical_type.whole_name

        # name mapping
        native_types_dict = conversions['native_types']
        to_replace = dict_replace_value_re(native_types_dict, [name])
        if to_replace:
            name = to_replace

        # final name
        return name

    def has_from_native_mapping(self, generator):
        # get argument name
        keys = []
        if self.canonical_type != None:
            keys.append(self.canonical_type.name)
        keys.append(self.name)

        # if arg is an object but no mapping defined, use object for it
        # if arg is an enum, use int for it
        from_native_dict = generator.tpl_opt['conversions']['from_native']
        if self.is_class:
            if not dict_has_key_re(from_native_dict, keys):
                return False
        return True

    def has_to_native_mapping(self, generator):
        # get argument name
        keys = []
        if self.canonical_type != None:
            keys.append(self.canonical_type.name)
        keys.append(self.name)

        # if arg is an object but no mapping defined, use object for it
        # if arg is an enum, use int for it
        to_native_dict = generator.tpl_opt['conversions']['to_native']
        if self.is_class:
            if not dict_has_key_re(to_native_dict, keys):
                return False
        return True

    def lua_from_native(self, convert_opts):
        # get generator, ensure it is in option
        assert(convert_opts.has_key('generator'))
        generator = convert_opts['generator']

        # get argument name
        keys = []
        if self.canonical_type != None:
            keys.append(self.canonical_type.name)
        keys.append(self.name)

        # if arg is an object but no mapping defined, use object for it
        # if arg is an enum, use int for it
        from_native_dict = generator.tpl_opt['conversions']['from_native']
        if self.is_class:
            if not dict_has_key_re(from_native_dict, keys):
                if self.is_ref:
                    keys.append(self.name + "&")
                keys.append("object")
        elif self.is_enum:
            keys.append("int")

        # find mapping, if no mapping, print error
        if dict_has_key_re(from_native_dict, keys):
            tpl = Template(dict_get_value_re(from_native_dict, keys), searchList=[convert_opts])
            return str(tpl).rstrip()
        return "#pragma warning NO CONVERSION FROM NATIVE FOR " + self.name

    def lua_to_native(self, convert_opts):
        # get generator, ensure it is in option
        assert('generator' in convert_opts)
        generator = convert_opts['generator']

        # get argument name
        keys = []
        if self.canonical_type != None:
            keys.append(self.canonical_type.name)
        keys.append(self.name)

        # if arg is an object but no mapping defined, use object for it
        # if arg is an enum, use int for it
        to_native_dict = generator.tpl_opt['conversions']['to_native']
        if self.is_class:
            if not dict_has_key_re(to_native_dict, keys):
                if self.is_ref:
                    keys.append(self.name + "&")
                keys.append("object")
        elif self.is_enum:
            keys.append("int")

        # if it is function, use lambda template
        if self.is_function:
            tpl = Template(file=os.path.join("templates", "lambda.c"),
                           searchList=[convert_opts, self])
            indent = convert_opts['level'] * "\t"
            return str(tpl).replace("\n", "\n" + indent)

        # for other situation, find mapping, if no mapping, print error
        if dict_has_key_re(to_native_dict, keys):
            tpl = dict_get_value_re(to_native_dict, keys)
            tpl = Template(tpl, searchList=[convert_opts])
            return str(tpl).rstrip()
        return "#pragma warning NO CONVERSION TO NATIVE FOR " + self.name + "\n" + convert_opts['level'] * "\t\t" + "ok = false"

class NativeTypedef(object):
    def __init__(self, node, generator):
        self.node = node
        self.generator = generator
        self.qualified_name = get_qualified_name(node)

        # visit
        self.visit_node(self.node)

    def visit_node(self, node):
        for c in node.get_children():
            self.process_node(c)
            self.visit_node(c)

    def process_node(self, node):
        if node.kind == CursorKind.STRUCT_DECL:
            if not self.generator.structs.has_key(self.qualified_name):
                st = NativeClass(node, self.generator)
                st.class_name = self.node.displayname
                st.qualified_name = self.qualified_name
                st.is_typedef = True
                self.generator.structs[self.qualified_name] = st
        elif node.kind == CursorKind.UNION_DECL:
            if not self.generator.unions.has_key(self.qualified_name):
                nu = NativeUnion(node)
                nu.qualified_name = self.qualified_name
                nu.union_name = self.node.displayname
                nu.is_typedef = True
                self.generator.unions[self.qualified_name] = nu
        elif node.kind == CursorKind.ENUM_DECL:
            if not self.generator.enums.has_key(self.qualified_name):
                ne = NativeEnum(node)
                ne.qualified_name = self.qualified_name
                ne.enum_name = self.node.displayname
                ne.is_typedef = True
                self.generator.enums[self.qualified_name] = ne

class NativeEnum(object):
    def __init__(self, node):
        self.node = node
        self.enum_name = node.displayname
        self.qualified_name = get_qualified_name(node)
        self.constants = []
        self.is_typedef = False

        # visit
        self.visit_node(self.node)

    def visit_node(self, node):
        # visit all children
        for c in node.get_children():
            self.process_node(c)
            self.visit_node(c)

    def process_node(self, node):
        if node.kind == CursorKind.ENUM_CONSTANT_DECL:
            self.constants.append(node.spelling)

class NativeUnion(object):
    def __init__(self, node):
        self.node = node
        self.union_name = node.displayname
        self.qualified_name = get_qualified_name(node)
        self.is_typedef = False

class NativeOverloadedFunction(object):
    def __init__(self, func_array):
        self.implementations = func_array
        self.func_name = func_array[0].func_name
        self.min_args = sys.maxint
        self.is_constructor = False
        self.is_destructor = False
        for m in func_array:
            self.min_args = min(self.min_args, m.min_args)

    def append(self, func):
        self.min_args = min(self.min_args, func.min_args)
        self.implementations.append(func)

    def generate_code(self, hfile, cppfile, clazz):
        static = self.implementations[0].static
        override = self.implementations[0].is_override

        # if override method, no need generate
        if override:
            return

        # generate binding code
        tpl = None
        if static:
            tpl = Template(file=os.path.join("templates", "sfunction_overloaded.c"),
                           searchList=[self, clazz, clazz.generator])
        else:
            tpl = Template(file=os.path.join("templates", "ifunction_overloaded.c"),
                           searchList=[self, clazz, clazz.generator])

        # write
        if tpl is not None:
            cppfile.write(str(tpl))

class NativeFunction(object):
    def __init__(self, node):
        self.node = node
        self.is_constructor = False
        self.is_destructor = False
        self.func_name = node.spelling
        self.arguments = []
        self.argumentTips = [arg.spelling for arg in node.get_arguments()]
        self.static = node.kind == CursorKind.CXX_METHOD and node.is_static_method()
        self.implementations = []
        self.not_supported = False
        self.is_override = False
        self.overload = False
        self.ret_type = NativeType.from_type(node.result_type)
        self.min_args = 0
        self.virtual = node.kind == CursorKind.CXX_METHOD and node.is_virtual_method()
        self.pure_virtual = node.kind == CursorKind.CXX_METHOD and node.is_pure_virtual_method()

        # if a operator overload, ignore
        if self.func_name.startswith("operator"):
            self.not_supported = True

        # mark the function as not supported if return type is not supported
        if not self.not_supported:
            if self.ret_type.not_supported:
                self.not_supported = True

        # mark the function as not supported if at least one argument is not supported
        if not self.not_supported:
            for arg in node.type.argument_types():
                nt = NativeType.from_type(arg)
                self.arguments.append(nt)
                if nt.not_supported:
                    self.not_supported = True

        # parse arguments
        if not self.not_supported:
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

    def __eq__(self, other):
        if self.func_name != other.func_name:
            return False
        if self.ret_type.qualified_name != other.ret_type.qualified_name:
            return False
        if len(self.arguments) != len(other.arguments):
            return False
        for a, oa in zip(self.arguments, other.arguments):
            if a.qualified_name != oa.qualified_name:
                return False
        return True

    def __hash__(self):
        hs = self.func_name + self.ret_type.qualified_name
        for arg in self.arguments:
            hs += arg.qualified_name
        return hash(hs)

    def has_default_arg(self, param_node):
        for node in param_node.get_children():
            if node.kind in default_arg_type_arr:
                return True
            if self.has_default_arg(node):
                return True
        return False

    def generate_code(self, hfile, cppfile, clazz):
        # if override method, no need generate
        if self.is_override:
            return

        # generate binding code
        tpl = None
        if self.static:
            tpl = Template(file=os.path.join("templates", "sfunction.c"),
                           searchList=[self, clazz, clazz.generator])
        else:
            if self.is_destructor:
                pass
            else:
                tpl = Template(file=os.path.join("templates", "ifunction.c"),
                               searchList=[self, clazz, clazz.generator])

        # write
        if tpl is not None:
            cppfile.write(str(tpl))

class NativeField(object):
    def __init__(self, node):
        cnode = node.canonical
        self.node = cnode
        self.name = cnode.displayname
        self.type = NativeType.from_type(cnode.type)
        self.location = cnode.location

    def generate_code(self, indent_level=0):
        tolua = ""

        # if type is not support, return
        if self.type.not_supported:
            return tolua

        # if type is pointer or reference, return
        if self.type.is_pointer or self.type.is_ref:
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
        super(NativeClass, self).__init__()
        self.node = node
        self.generator = generator
        self.class_name = node.displayname
        self.qualified_name = get_qualified_name(node)
        self.parents = []
        self.fields = []
        self.methods = {}
        self.static_methods = {}
        self.is_typedef = False
        self.current_access_specifier = AccessSpecifierKind.PRIVATE
        if node.kind == CursorKind.STRUCT_DECL:
            self.current_access_specifier = AccessSpecifierKind.PUBLIC
        self.override_methods = {}
        self.has_constructor = False
        self.qualified_ns = get_qualified_namespace(node)
        self.is_abstract = False
        self.is_ccobject = False

        # visit
        self.visit_node(self.node)

    def is_method_in_parents(self, f):
        if len(self.parents) > 0:
            if self.parents[0].methods.has_key(f.func_name):
                pf = self.parents[0].methods[f.func_name]
                if isinstance(pf, NativeOverloadedFunction):
                    for pfm in pf.implementations:
                        if pfm == f:
                            return True
                else:
                    if pf == f:
                        return True
            return self.parents[0].is_method_in_parents(f)
        return False

    def generate_code(self, hfile, cppfile):
        # function binding code
        for name, m in self.static_methods.items():
            m.generate_code(hfile, cppfile, self)
        for name, m in self.methods.items():
            m.generate_code(hfile, cppfile, self)
        for name, m in self.override_methods.items():
            m.generate_code(hfile, cppfile, self)

        # register code
        tpl = Template(file=os.path.join("templates", "register.c"),
                               searchList=[self, self.generator])
        cppfile.write(str(tpl))

    def should_function_be_generated(self, f):
        if not f.ret_type.has_from_native_mapping(self.generator):
            if not self.generator.is_type_included(f.ret_type.name.replace("*", "")) or\
                    self.generator.is_type_excluded(f.ret_type.name.replace("*", "")):
                return False

        for arg in f.arguments:
            if not arg.has_to_native_mapping(self.generator):
                if not self.generator.is_type_included(arg.name.replace("*", "")) or\
                        self.generator.is_type_excluded(arg.name.replace("*", "")):
                    return False

        return True

    def visit_node(self, node):
        # visit all children
        for c in node.get_children():
            if self.process_node(c):
                self.visit_node(c)

    def process_node(self, node):
        if node.kind == CursorKind.CXX_BASE_SPECIFIER:
            parent = node.get_definition()
            if parent is not None:
                # try to find cached class
                parent_class = None
                parent_qn = get_qualified_name(parent)
                if self.generator.classes.has_key(parent_qn):
                    parent_class = self.generator.classes[parent_qn]
                else:
                    parent_class = NativeClass(parent, self.generator)
                self.generator.classes[parent_qn] = parent_class
                self.parents.append(parent_class)
        elif node.kind == CursorKind.FIELD_DECL:
            if node.semantic_parent == self.node and self.current_access_specifier == AccessSpecifierKind.PUBLIC:
                self.fields.append(NativeField(node))
        elif node.kind == CursorKind.ENUM_DECL:
            if node.semantic_parent == self.node and self.current_access_specifier == AccessSpecifierKind.PUBLIC:
                ne = NativeEnum(node)
                self.generator.enums[get_qualified_name(node)] = ne
            return False
        elif node.kind == CursorKind.CLASS_DECL or node.kind == CursorKind.STRUCT_DECL:
            if node.semantic_parent == self.node and self.current_access_specifier == AccessSpecifierKind.PUBLIC:
                klass = NativeClass(node, self.generator)
                self.generator.classes[klass.qualified_name] = klass
            return False
        elif node.kind == CursorKind.TYPEDEF_DECL:
            if node == node.type.get_declaration() and self.current_access_specifier == AccessSpecifierKind.PUBLIC:
                NativeTypedef(node, self.generator)
            return False
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

                # if virtual
                if nf.pure_virtual:
                    self.is_abstract = True

                # if function should be excluded, return
                if not self.should_function_be_generated(nf):
                    return

                # check if function is override
                if self.is_method_in_parents(nf):
                    nf.is_override = True

                # if override, put to override_methods
                if nf.is_override:
                    if not self.override_methods.has_key(nf.func_name):
                        self.override_methods[nf.func_name] = nf
                    else:
                        nf.overload = True
                        previous_nf = self.override_methods[nf.func_name]
                        if isinstance(previous_nf, NativeOverloadedFunction):
                            previous_nf.append(nf)
                        else:
                            self.override_methods[nf.func_name] = NativeOverloadedFunction([nf, previous_nf])
                            previous_nf.overload = True
                elif nf.static:
                    if not self.static_methods.has_key(nf.func_name):
                        self.static_methods[nf.func_name] = nf
                    else:
                        nf.overload = True
                        previous_nf = self.static_methods[nf.func_name]
                        if isinstance(previous_nf, NativeOverloadedFunction):
                            previous_nf.append(nf)
                        else:
                            self.static_methods[nf.func_name] = NativeOverloadedFunction([nf, previous_nf])
                            previous_nf.overload = True
                else:
                    if not self.methods.has_key(nf.func_name):
                        self.methods[nf.func_name] = nf
                    else:
                        nf.overload = True
                        previous_nf = self.methods[nf.func_name]
                        if isinstance(previous_nf, NativeOverloadedFunction):
                            previous_nf.append(nf)
                        else:
                            self.methods[nf.func_name] = NativeOverloadedFunction([nf, previous_nf])
                            previous_nf.overload = True

                return False
        elif node.kind == CursorKind.CONSTRUCTOR and self.current_access_specifier == AccessSpecifierKind.PUBLIC:                # if function is not supported, skip it
            # create native function
            nf = NativeFunction(node)
            nf.is_constructor = True

            # not supported means at least one argument type is not supported
            if nf.not_supported:
                return

            # if function should be excluded, return
            if not self.should_function_be_generated(nf):
                return

            # set flag
            self.has_constructor = True
            if not self.methods.has_key('constructor'):
                self.methods['constructor'] = nf
            else:
                nf.overload = True
                previous_nf = self.methods['constructor']
                if isinstance(previous_nf, NativeOverloadedFunction):
                    previous_nf.append(nf)
                else:
                    nf = NativeOverloadedFunction([nf, previous_nf])
                    nf.is_constructor = True
                    previous_nf.overload = True
                    self.methods['constructor'] = nf
        elif node.kind == CursorKind.DESTRUCTOR:
            nf = NativeFunction(node)
            nf.is_destructor = True
            self.methods['destructor'] = nf

        return True

class Generator(object):
    def __init__(self, conf):
        super(Generator, self).__init__()
        config = ConfigParser.SafeConfigParser()
        config.read(conf)
        ndk_root = os.getenv("NDK_ROOT")
        c2xc_root = os.getenv("COCOS2DX_CLASSICAL_ROOT") if os.getenv("COCOS2DX_CLASSICAL_ROOT") else ""
        home = os.getenv("HOME") if os.getenv("HOME") else ""
        self.tpl_opt = yaml.load(file("conversions.yaml", "r"))
        self.conf = conf
        self.clang = Index.create()
        self.current_ns = ""
        project_dir = config.get("DEFAULT", "project_dir").replace("${HOME}", home) if config.has_option("DEFAULT", "project_dir") else ""
        clang_args = re.split(r"\s", config.get("DEFAULT", "clang_args")) if config.has_option("DEFAULT", "clang_args") else []
        clang_args = [x.replace("${NDK_ROOT}", ndk_root) for x in clang_args]
        clang_args = [x.replace("${COCOS2DX_CLASSICAL_ROOT}", c2xc_root) for x in clang_args]
        self.clang_args = [x.replace("${PROJECT_DIR}", project_dir) for x in clang_args]
        self.include_namespaces = re.split(r"\s", config.get("DEFAULT", "include_namespaces")) if config.has_option("DEFAULT", "include_namespaces") else []
        src_dirs = re.split(r"\s", config.get("DEFAULT", "src_dirs")) if config.has_option("DEFAULT", "src_dirs") else ["."]
        self.src_dirs = [x.replace("${PROJECT_DIR}", project_dir) for x in src_dirs]
        self.exclude_dirs = re.split(r"\s", config.get("DEFAULT", "exclude_dirs")) if config.has_option("DEFAULT", "exclude_dirs") else ["."]
        self.dst_dir = config.get("DEFAULT", "dst_dir").replace("${PROJECT_DIR}", project_dir) if config.has_option("DEFAULT", "dst_dir") else "."
        exclude_classes = re.split(r"\s", config.get("DEFAULT", "exclude_classes")) if config.has_option("DEFAULT", "exclude_classes") else []
        self.exclude_classes_regex = [re.compile(x) for x in exclude_classes]
        include_classes = re.split(r"\s", config.get("DEFAULT", "include_classes")) if config.has_option("DEFAULT", "include_classes") else []
        self.include_classes_regex = [re.compile(x) for x in include_classes]
        exclude_types = re.split(r"\s", config.get("DEFAULT", "exclude_types")) if config.has_option("DEFAULT", "exclude_types") else []
        self.exclude_types_regex = [re.compile(x) for x in exclude_types]
        include_types = re.split(r"\s", config.get("DEFAULT", "include_types")) if config.has_option("DEFAULT", "include_types") else []
        self.include_types_regex = [re.compile(x) for x in include_types]
        self.target_module = config.get("DEFAULT", "target_module") if config.has_option("DEFAULT", "target_module") else None
        self.hfile_path = ""
        self.cppfile_path = ""
        self.headers = []
        self.target_module_fullname = os.path.splitext(os.path.basename(self.conf))[0]
        self.classes = {}
        self.generated_classes = {}
        self.enums = {}
        self.structs = {}
        self.unions = {}
        self.sorted_classes = []

    @property
    def generator(self):
        return self

    def to_lua_type(self, namespace_class_name, namespace_name):
        script_ns_dict = self.tpl_opt['conversions']['ns_map']
        for (k, v) in script_ns_dict.items():
            if namespace_name.startswith(k):
                return namespace_class_name.replace("*","").replace("const ", "").replace(k, v)
        if namespace_class_name.find("::") >= 0:
            if namespace_class_name.find("std::") == 0:
                return namespace_class_name
            else:
                raise Exception("The namespace (%s) conversion wasn't set in 'ns_map' section of the conversions.yaml" % namespace_class_name)
        else:
            return namespace_class_name.replace("*","").replace("const ", "")

    def sort_classes(self):
        '''
        sorted classes in order of inheritance
        '''
        sorted_list = []
        for class_name in self.generated_classes.iterkeys():
            nclass = self.generated_classes[class_name]
            sorted_list += self.sort_parents(nclass)
        # remove dupes from the list
        no_dupes = []
        [no_dupes.append(i) for i in sorted_list if not no_dupes.count(i)]
        return no_dupes

    def sort_parents(self, nclass):
        '''
        returns the sorted list of parents for a native class
        '''
        sorted_parents = []
        for p in nclass.parents:
            if p.class_name in self.generated_classes.keys():
                sorted_parents += self.sort_parents(p)
        if nclass.class_name in self.generated_classes.keys():
            sorted_parents.append(nclass.class_name)
        return sorted_parents

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

    def is_type_excluded(self, name):
        for r in self.exclude_types_regex:
            if r.match(name):
                return True
        return False

    def is_type_included(self, name):
        for r in self.include_types_regex:
            if r.match(name):
                return True
        return False

    def process_node(self, node):
        if node.kind == CursorKind.CLASS_DECL or node.kind == CursorKind.STRUCT_DECL:
            # check namespace for found class
            if node == node.type.get_declaration() and len(node.get_children_array()) > 0:
                # check class is target or not
                is_targeted_class = False
                qn = get_qualified_name(node)
                ns = get_qualified_namespace(node)
                ns_matched = len(ns) <= 0 or ns in self.include_namespaces
                name_matched = self.is_class_included(node.displayname) and not self.is_class_excluded(node.displayname)
                is_targeted_class = ns_matched and name_matched

                # if it is target class, process it
                # if not target class, just register it
                if is_targeted_class:
                    if not self.generated_classes.has_key(node.displayname):
                        klass = NativeClass(node, self)
                        self.classes[qn] = klass
                        self.generated_classes[node.displayname] = klass
                else:
                    if not self.classes.has_key(qn):
                        self.classes[qn] = NativeClass(node, self)

            return False
        elif node.kind == CursorKind.ENUM_DECL:
            if node == node.type.get_declaration() and len(node.get_children_array()) > 0 and len(node.displayname) > 0:
                qn = get_qualified_name(node)
                ne = NativeEnum(node)
                self.enums[qn] = ne
            return False
        elif node.kind == CursorKind.UNION_DECL:
            if node == node.type.get_declaration() and len(node.get_children_array()) > 0 and len(node.displayname) > 0:
                qn = get_qualified_name(node)
                nu = NativeUnion(node)
                self.unions[qn] = nu
            return False
        elif node.kind == CursorKind.TYPEDEF_DECL:
            if node == node.type.get_declaration():
                NativeTypedef(node, self)
            return False

        return True

    def visit_node(self, node):
        # visit all children
        for c in node.get_children():
            if self.process_node(c):
                self.visit_node(c)

    @staticmethod
    def process_dir(args, dirname, filenames):
        _self = args

        # check excluded dir
        absdir = os.path.abspath(dirname)
        for d in _self.exclude_dirs:
            abs_exclude = os.path.abspath(d)
            if absdir.startswith(abs_exclude):
                return

        # process files under this path
        for f in filenames:
            filepath = os.path.join(dirname, f)
            _self.process_header(filepath)

    def process_header(self, filepath):
        # if file is header, and not hidden, process it
        filename = os.path.basename(filepath)
        if os.path.isfile(filepath) and not filename.startswith(".") and not filename.startswith("lua_"):
            ext = os.path.splitext(filepath)[1][1:]
            if ext == "h":
                tu = self.clang.parse(filepath, self.clang_args)
                print 'parsing file:', filepath

                # verify source file
                if not self.verify_source(tu):
                    print "%s contains errors, skip it" % filepath
                    return

                # record this header
                self.headers.append(filepath)

                # visit from top node
                self.visit_node(tu.cursor)

    def check_class_abstract(self, c, parents):
        puref = {}
        for p in parents:
            puref = dict(self.check_class_abstract(p, p.parents), **puref)

        # visit my functions, if pure virtual add to dict, if not, remove from dict if has
        for name, m in c.methods.items():
            if isinstance(m, NativeOverloadedFunction):
                for f in m.implementations:
                    if f.pure_virtual:
                        puref[f] = f
                    elif puref.has_key(f):
                        del puref[f]
            else:
                if m.pure_virtual:
                    puref[m] = m
                elif puref.has_key(m):
                    del puref[m]
        for name, m in c.override_methods.items():
            if isinstance(m, NativeOverloadedFunction):
                for f in m.implementations:
                    if f.pure_virtual:
                        puref[f] = f
                    elif puref.has_key(m):
                        del puref[f]
            else:
                if m.pure_virtual:
                    puref[m] = m
                elif puref.has_key(m):
                    del puref[m]

        # finally if dict is not empty then this is an abstract class
        if len(puref) > 0:
            c.is_abstract = True

        # return my puref
        return puref

    def generate_code(self):
        # ensure dst dir existence
        if not os.path.exists(self.dst_dir):
            os.makedirs(self.dst_dir)

        # recursively visit all headers
        for d in self.src_dirs:
            if os.path.isfile(d):
                self.process_header(d)
            else:
                os.path.walk(d, self.process_dir, self)

        # walk all classes to find out abstract classes and ccobject types
        for name, c in self.generated_classes.items():
            self.check_class_abstract(c, c.parents)
            if self.is_ccobject_type(c):
                c.is_ccobject = True

            # if class is abstract, remove constructor
            if c.is_abstract:
                if c.has_constructor:
                    del c.methods["constructor"]
                    c.has_constructor = False

        # sort classes
        self.sorted_classes = self.sort_classes()

        # generate header file
        self.hfile_path = os.path.join(self.dst_dir, "lua_" + self.target_module_fullname + "_auto.h")
        hfile = open(self.hfile_path, "w")
        self.cppfile_path = os.path.join(self.dst_dir, "lua_" + self.target_module_fullname + "_auto.cpp")
        cppfile = open(self.cppfile_path, "w")

        # load layout head template
        layout_h = Template(file=os.path.join("templates", "layout_head.h"),
                            searchList=[self])
        layout_c = Template(file=os.path.join("templates", "layout_head.c"),
                            searchList=[self])

        # write header
        hfile.write(str(layout_h))
        cppfile.write(str(layout_c))

        # write classes
        for name, c in self.generated_classes.items():
            c.generate_code(hfile, cppfile)

        # load layout footer template
        layout_h = Template(file=os.path.join("templates", "layout_foot.h"),
                            searchList=[self])
        layout_c = Template(file=os.path.join("templates", "layout_foot.c"),
                            searchList=[self])

        # write footer
        hfile.write(str(layout_h))
        cppfile.write(str(layout_c))

        # close
        hfile.close()
        cppfile.close()

    def is_ccobject_type(self, nc):
        if nc.qualified_name == "cocos2d::CCObject":
            return True
        for pc in nc.parents:
            if self.is_ccobject_type(pc):
                return True
        return False

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
    g.generate_code()

if __name__ == '__main__':
    main()