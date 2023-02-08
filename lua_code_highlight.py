# -*- coding: utf-8 -*-

import os
import re

LUATOKENS = [
    (r'\b(and|break|do|else|elseif|end|false|for|function|if|in|local|nil|not|or|repeat|return|then|true|until|while)\b', 'keyword'),
    (r'[+-]?\d+\.\d+', 'number'),
    (r'[+-]?\d+', 'number'),
    (r'".*?"', 'string'),
    (r"'.*?'", 'string'),
    (r'[\+\-\*\/\^%%#=<>~]', 'operator'),
    (r'[\[\]\{\}\(\)\.,;:]', 'punctuation'),
    (r'\b(and|or)\b', 'boolean'),
    (r'\b(nil)\b', 'null'),
    (r'[a-zA-Z_][a-zA-Z0-9_]*', 'identifier'),
    (r'\n', 'newline'),
    (r'--[^\n]*', 'comment')
]

def tokenize_lua(code):
    tokens = []
    i = 0
    while i < len(code):
        for pattern, token_type in LUATOKENS:
            match = re.match(pattern, code[i:])
            if match:
                value = match.group(0)
                if token_type == 'string':
                    value = value[1:-1]
                tokens.append((token_type, value))
                i += len(value)
                break
        else:
            i += 1
    return tokens

JSONTOKENS = [
    (r'\b(true|false|null)\b', 'boolean'),
    (r'-?\d+(?:\.\d+)?(?:[eE][+-]?\d+)?', 'number'),
    (r'"(?:\\.|[^"\\])*"', 'string'),
    (r'[\[\]\{\}\:,]', 'punctuation'),
    (r'\n', 'newline')
]

def tokenize_json(code):
    tokens = []
    i = 0
    while i < len(code):
        for pattern, token_type in JSONTOKENS:
            match = re.match(pattern, code[i:])
            if match:
                value = match.group(0)
                if token_type == 'string':
                    value = value[1:-1].replace('\\"', '"')
                tokens.append((token_type, value))
                i += len(value)
                break
        else:
            i += 1
    return tokens

TOKEN_COLORS = {
    'text': '#D4D4D4',
    'newline': '#D4D4D4',
    'keyword': '#569CD6',
    'string': '#CE9178',
    'number': '#B5CEA8',
    'operator': '#D4D4D4',
    'punctuation': '#D4D4D4',
    'boolean': '#B5CEA8',
    'null': '#CE9178',
    'identifier': '#DCDCAA',
    'comment': '#DCFFAA',
}
TOKEN_DEFAULT_COLOR = '#D4D4D4'

# Regular expression to find the code blocks
code_block_regex = re.compile(r'```(lua|json)([\s\S]+?)```|([\s\S]+?)')

def extract_code_blocks(text):
    code_blocks = []
    pos = 0
    while pos < len(text):
        match = code_block_regex.match(text, pos)
        if match.group(1):
            code_type = match.group(1)
            code = match.group(2)
            code_blocks.append((code_type, code))
        else:
            code_blocks.append(('text', match.group(3)))
        pos = match.end()
    return code_blocks

def decorate_tokens(tokens):
    html = ""
    for token in tokens:
        if token[0] == 'newline':
            html += '<br>\n'
        elif token[0] == 'whitespace':
            html += ' '
        else:
            color = TOKEN_COLORS[token[0]]
            html += '<span style="color: ' + color + '">' + token[1] + '</span>'
            
    return html

def decorate_codeblocks(code_blocks):
    md = ""
    for code_block in code_blocks:
        if code_block[0] == 'lua':
            md += '<div class="fragment">\n'
            tokens = tokenize_lua(code_block[1])
            md += decorate_tokens(tokens)
            md += '</div">\n'
        elif code_block[0] == 'json':
            md += '<div class="fragment">\n'
            tokens = tokenize_json(code_block[1])
            md += decorate_tokens(tokens)
            md += '</div">\n'
        else:
            md += code_block[1]
    return md


for root, dirs, files in os.walk('./'):
    for filename in files:
        namepath = os.path.join(root, filename)
        if namepath.find('.md') != -1:
            print('prepare lua ' + namepath)
            # Slurp file into a single string
            new_content = ''
            now_parsing = 'none'
            with open(namepath, 'r') as file:
                code = file.read()
                
                code_blocks = extract_code_blocks(code)
                md = decorate_codeblocks(code_blocks)
                
            with open(namepath, 'w') as file:
                file.write(md)