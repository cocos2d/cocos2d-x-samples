#!/usr/bin/env python
#coding=utf-8
#

"""****************************************************************************
Copyright (c) 2014 cocos2d-x.org
Copyright (c) 2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************"""

'''
format the libs/cocos2d-x/templates/xxx

Facilitate the use of formatted cocos2d-x directly generate sample project
'''

import os
import sys
import json
import re

class ProjectFormat(object):
    CONFIG_FILE = "config.json"
    KEY_REPLACE_STRING = 'replace_string'
    KEY_MODIFY_CFG = 'modify_files'
    KEY_MODIFY_MUL_LINE_CFG = 'modify_mul_line_files'
    ENGINE_RELATE_DIR = ''
    def __init__(self):
        self.file_base_path = os.path.abspath(os.path.join(os.path.dirname(__file__), ProjectFormat.ENGINE_RELATE_DIR))
        self.config_json = self.getConfigJson();

    def getConfigJson(self):

        cfg_json_path = os.path.join(self.file_base_path, ProjectFormat.CONFIG_FILE)
        f = open(cfg_json_path)
        config_json = json.load(f)
        f.close()

        return config_json

    def modify_mul_line_file(self, file_path, pattern, replace_str):
        f = open(file_path)
        content = f.read()
        f.close()

        new_content = re.sub(pattern, replace_str, content)

        f = open(file_path, "w")
        f.write(new_content)
        f.close()
    def modify_file(self, file_path, pattern, replace_str):
            f = open(file_path)
            lines = f.readlines()
            f.close()

            new_lines = []
            for line in lines:
                new_line = re.sub(pattern, replace_str, line)
                new_lines.append(new_line)

            f = open(file_path, "w")
            f.writelines(new_lines)
            f.close()

    def modify_files(self, configFile, operationFun):
        modify_cfg = self.config_json[configFile]
        for cfg in modify_cfg:
            file_path = cfg["file_path"]
            file_path = os.path.join(self.file_base_path, file_path)

            if not os.path.isfile(file_path):
                print("%s is not a file." % file_path)
                continue

            pattern = cfg["pattern"]
            replace_str = cfg["replace_string"]
            operationFun(file_path, pattern, replace_str)



def main():
    projectObj = ProjectFormat()
    projectObj.modify_files(ProjectFormat.KEY_MODIFY_CFG, projectObj.modify_file)
    projectObj.modify_files(ProjectFormat.KEY_MODIFY_MUL_LINE_CFG, projectObj.modify_mul_line_file)

# -------------- main --------------
if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        traceback.print_exc()
        sys.exit(1)
