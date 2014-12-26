#!/usr/bin/python

import sys
from clang.cindex import *
from pprint import pprint
import ConfigParser
import os
import os.path
import re

class NativeClass(object):
    def __init__(self, node):
        self.node = node

    def generate_tolua(self):
        print "generate code for class:", self.node.displayname

class Generator(object):
    def __init__(self, file):
        config = ConfigParser.SafeConfigParser()
        config.read("autolua.conf")
        ndk_root = os.getenv("NDK_ROOT")
        self.clang = Index.create()
        self.file = file
        self.current_ns = ""
        self.current_access_specifier = "public"
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
        self.found_classes = {}
        self.generated_classes = {}

    def build_namespace(self, cursor, namespaces=[]):
        if cursor:
            parent = cursor.semantic_parent
            if parent:
                if parent.kind == CursorKind.NAMESPACE or parent.kind == CursorKind.CLASS_DECL:
                    namespaces.append(parent.displayname)
                    self.build_namespace(parent, namespaces)

        return namespaces

    def get_qualified_name(self, node):
        ns_list = self.build_namespace(node, [])
        ns_list.reverse()
        ns = "::".join(ns_list)
        if len(ns) > 0:
            return ns + "::" + node.displayname
        return node.displayname

    def get_qualified_namespace(self, node):
        ns_list = self.build_namespace(node, [])
        ns_list.reverse()
        ns = "::".join(ns_list)
        return ns

    def process_node(self, node):
        if node.kind == CursorKind.CLASS_DECL:
            # check namespace for found class
            if node == node.type.get_declaration() and len(node.get_children_array()) > 0:
                is_targeted_class = False
                ns = self.get_qualified_namespace(node)
                if len(ns) <= 0 or ns in self.target_ns:
                    is_targeted_class = True

                # if it is target class, process it
                if is_targeted_class and not self.found_classes.has_key(node.displayname):
                    klass = NativeClass(node)
                    self.found_classes[node.displayname] = klass
                    if not self.generated_classes.has_key(node.displayname):
                        klass.generate_tolua()
                        self.generated_classes[node.displayname] = klass

    def visit_node(self, node):
        # visit all children
        for c in node.get_children():
            self.process_node(c)
            self.visit_node(c)

    def generate_tolua(self):
        # parse file
        tu = self.clang.parse(self.file, self.clang_args)
        print 'parsing file:', self.file

        # verify source file
        if not self.verify_source(tu):
            print "%s contains errors, skip it" % self.file
            return

        # visit from top node
        self.visit_node(tu.cursor)

    def print_diag(self, diagnostics):
        print("====\nErrors in parsing headers:")
        severities=['Ignored', 'Note', 'Warning', 'Error', 'Fatal']
        for idx, d in enumerate(diagnostics):
            print "%s. <severity = %s,\n    location = %r,\n    details = %r>" % (
                idx+1, severities[d.severity], d.location, d.spelling)
        print("====")

    def verify_source(self, tu):
        tu = self.clang.parse(self.file, self.clang_args)
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
    g = Generator("simple_class.h")
    g.generate_tolua()

if __name__ == '__main__':
    main()