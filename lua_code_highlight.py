# -*- coding: utf-8 -*-

import os
import re
import string
import sys


def paren_matcher (n):
    return r'[^()]*?(?:\("*n+r"[^()]*?"+r"\)[^()]*?)*?'*n

def replace_with_span(line, word, color):
    line.replace(word,'<span class=“line” style="color: ' + color + '">function</span>')

for root, dirs, files in os.walk('./'):
    for filename in files:
        namepath = os.path.join(root, filename)
        if namepath.find('.md') != -1:
            print(namepath)
            # Slurp file into a single string
            new_content = ''
            now_lua = False
            with open(namepath, 'r') as file:
                content = file.read()
                lines = content.splitlines()
                for line in lines:
                    if line.find('```lua') != -1:
                        now_lua = True
                        content += '\n<div class="fragment">'
                    elif line.find('```') != -1:
                        now_lua = False
                        content += '\n</div>'

                    if now_lua:
                        replace_with_span(line, 'function', '#5555ff')
                        replace_with_span(line, 'print', '#5555ff')
                        replace_with_span(line, 'end', '#ff55ff')
                        replace_with_span(line, 'then', '#ff55ff')
                        replace_with_span(line, 'do', '#ff55ff')
                    else:
                        new_content += line
                        new_content += '\n'
            with open(namepath, 'w') as file:
                file.write(new_content)