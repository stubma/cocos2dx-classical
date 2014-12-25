#!/usr/bin/python

import sys
from clang.cindex import *
from pprint import pprint
import ConfigParser
import os
import os.path
import re

class Visitor(object):
    def __init__(self, file):
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
            "-D_SIZE_T_DEFINED_"
        ]
        self.content = None
        with open(file) as f:
            self.content = f.read()

    def build_namespace(self, cursor, namespaces=[]):
        if cursor:
            parent = cursor.semantic_parent
            if parent:
                if parent.kind == CursorKind.NAMESPACE or parent.kind == CursorKind.CLASS_DECL:
                    namespaces.append(parent.displayname)
                    self.build_namespace(parent, namespaces)

        return namespaces

    def get_qualified_name(self, declaration_cursor):
        ns_list = self.build_namespace(declaration_cursor, [])
        ns_list.reverse()
        ns = "::".join(ns_list)
        if len(ns) > 0:
            return ns + "::" + declaration_cursor.displayname
        return declaration_cursor.displayname

    def process_node(self, node):
        # print "%s, %s" % (node.kind.name, node.semantic_parent and node.semantic_parent.displayname or "")
        if node.kind == CursorKind.CXX_BASE_SPECIFIER:
            pass #print node.kind.name
        elif node.kind == CursorKind.CXX_ACCESS_SPEC_DECL:
            self.current_access_specifier = node.get_access_specifier()
        elif node.kind == CursorKind.FIELD_DECL:
            qn = self.get_qualified_name(node)
            if not qn.startswith("std::"):
                print "field", node.displayname
        elif node.kind == CursorKind.NAMESPACE:
            self.current_ns = node.displayname
        elif node.kind == CursorKind.CLASS_DECL:
            qn = self.get_qualified_name(node)
            if not qn.startswith("std::"):
                print "class found:", node.displayname

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
    v = Visitor("simple_class.h")
    v.generate_tolua()

if __name__ == '__main__':
    main()