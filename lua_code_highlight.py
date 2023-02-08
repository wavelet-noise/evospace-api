# -*- coding: utf-8 -*-

import os
import re
import string
import sys


def paren_matcher (n):
    return r'[^()]*?(?:\("*n+r"[^()]*?"+r"\)[^()]*?)*?'*n

def replace_with_span(line, word, color):
    return line.replace(word, '<span class=“line” style="color: ' + color + '">' + word + '</span>')

def replace_quotes(line, color):
    quotes = re.findall(r'"(.*?)"', line)
    for quote in quotes:
        line = line.replace('"' + quote + '"', '<span class=“line” style="color: ' + color + '>"' + quote  + '"</span>')
    
    return line

red_color = '#E17873'

for root, dirs, files in os.walk('./'):
    for filename in files:
        namepath = os.path.join(root, filename)
        if namepath.find('.md') != -1:
            print('prepare lua ' + namepath)
            # Slurp file into a single string
            new_content = ''
            now_parsing = 'none'
            with open(namepath, 'r') as file:
                content = file.read()
                lines = content.splitlines()
                for line in lines:
                    if line.find('```lua') != -1:
                        now_parsing = 'lua'
                        new_content += '\n<div class="fragment">'
                        line = line.replace('```lua', '')
                    elif line.find('```json') != -1:
                        now_parsing = 'json'
                        new_content += '\n<div class="fragment">'
                        line = line.replace('```json', '')
                    elif line.find('```') != -1:
                        now_parsing = 'none'
                        new_content += '\n</div>'
                        line = line.replace('```', '')

                    line = replace_quotes(line, '#C89682')

                    if now_parsing == 'lua':
                        line = replace_with_span(line, 'function', red_color)
                        line = replace_with_span(line, 'print', red_color)
                        line = replace_with_span(line, 'end', red_color)
                        line = replace_with_span(line, 'then', red_color)
                        line = replace_with_span(line, 'do', red_color)
                        line = replace_with_span(line, 'local', red_color)
                        line = replace_with_span(line, '=', red_color)

                    new_content += line
                    new_content += '\n'
            with open(namepath, 'w') as file:
                file.write(new_content)