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
        self.clang = Index.create()
        self.file = file
        self.tmp_file = "tmp.h"
        self.current_access_specifier = "public"
        self.clang_args = [
            "-x", "c++-header"
        ]
        self.content = None
        with open(file) as f:
            self.content = f.read()

    def process_node(self, node):
        extent = node.extent
        if node.kind == CursorKind.ENUM_DECL:
            print self.content[extent.begin_int_data:extent.end_int_data]
        elif node.kind == CursorKind.CXX_ACCESS_SPEC_DECL:
            self.current_access_specifier = node.get_access_specifier()

    def visit_node(self, node):
        # visit all children
        for c in node.get_children():
            self.process_node(c)
            self.visit_node(c)

    def generate_tolua(self):
        self.preprocess_source()

        # parse file
        tu = self.clang.parse(self.tmp_file, self.clang_args)
        print 'parsing file: ', self.file

        # visit from top node
        self.visit_node(tu.cursor)

    def preprocess_source(self):
        # remove all include
        self.content = re.sub(r"#include(.*)", "", self.content)

        # remove CC_DLL, CC_EX_DLL
        self.content = self.content.replace("CC_DLL", "")
        self.content = self.content.replace("CC_EX_DLL", "")

        # remove namespace macro
        self.content = self.content.replace("NS_CC_BEGIN", "")
        self.content = self.content.replace("NS_CC_END", "")
        self.content = self.content.replace("NS_CC_EXT_BEGIN", "")
        self.content = self.content.replace("NS_CC_EXT_END", "")
        self.content = self.content.replace("NS_TIMELINE_BEGIN", "")
        self.content = self.content.replace("NS_TIMELINE_END", "")
        self.content = re.sub(r"USING_NS_CC(\s*);", "", self.content)

        # remove create func macro
        self.content = re.sub(r"CREATE_FUNC\((.*)\)", r"static \1* create();", self.content)

        # save
        with open(self.tmp_file, "w") as f:
            f.write(self.content)

def main():
    # set libclang path
    Config.set_library_file("libclang/libclang.dylib")

    # generate
    v = Visitor("simple_class.h")
    v.generate_tolua()

if __name__ == '__main__':
    main()