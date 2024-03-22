# -*- coding: utf-8 -*-

import os
import re
import sys

def camel_to_snake_case(camel_case_str):
    snake_case_parts = []
    current_word = ""

    for i, char in enumerate(camel_case_str):
        if char.isupper():
            if current_word:
                if current_word[-1].isdigit() and not (len(current_word) > 1 and current_word[-2] == 'D'):
                    if snake_case_parts:
                        snake_case_parts[-1] = snake_case_parts[-1] + current_word
                    else:
                        snake_case_parts.append(current_word)
                else:
                    snake_case_parts.append(current_word)
            current_word = char.lower()
        else:
            current_word += char

    if current_word:
        if current_word[-1].isdigit() and not (len(current_word) > 1 and current_word[-2] == 'D'):
            if snake_case_parts:
                snake_case_parts[-1] = snake_case_parts[-1] + current_word
            else:
                snake_case_parts.append(current_word)
        else:
            snake_case_parts.append(current_word)

    return '_'.join(snake_case_parts)

def camel_to_snake_case(name):
    return re.sub(r'(?<!^)(?=[A-Z])', '_', name).lower()

def is_excluded(name):
    # Exclude if it starts with "U" or "F" followed by an uppercase letter, indicating CamelCase.
    return re.match(r'^(F|U|T|E)[A-Z]', name)

def replace_camel_case_with_snake_case(text):
    def replace(match):
        matched_str = match.group(0)
        # Apply exclusion criteria based on the starting characters "U" or "F".
        if is_excluded(matched_str):
            return matched_str
        return camel_to_snake_case(matched_str)

    # Pattern to match CamelCase identifiers.
    pattern = r'\b[A-Z][a-zA-Z0-9]*\b'

    result_lines = []
    for line in text.splitlines():
        # Skip processing for comment lines.
        if line.strip().startswith("*"):
            result_lines.append(line)
        else:
            result_lines.append(re.sub(pattern, replace, line))

    return '\n'.join(result_lines)


def paren_matcher (n):
    return r"[^()]*?(?:\("*n+r"[^()]*?"+r"\)[^()]*?)*?"*n

for root, dirs, files in os.walk("./"):
    for filename in files:
        namepath = os.path.join(root, filename)
        if namepath.find(".h") != -1 and namepath.find(".html") == -1:
            print(namepath)
            # Slurp file into a single string
            with open(namepath, 'r') as file:
                content = file.read()
                content = content.replace('FVector', 'Vec3')
                content = content.replace('std::vector', 'UArray')
                content = content.replace('std::unordered_map', 'UTable')
                content = content.replace('std::map', 'UTable')

                content = re.sub(r'\bm[A-Z]\w+', lambda x: x.group().replace("m", ""), content)

                content = replace_camel_case_with_snake_case(content)
                
                regex = '^(\s*)((?:UFUNCTION|UCLASS|UPROPERTY|UENUM|GENERATED_BODY)\s*\('+paren_matcher(25)+'\))'
                content = re.sub(regex, r'\1', content, flags=re.MULTILINE)
                content = re.sub(r'\bU[A-Z]\w+', lambda x: x.group().replace("U", ""), content)
                content = re.sub(r'\bF[A-Z]\w+', lambda x: x.group().replace("F", ""), content)
                content = re.sub(r'\bE[A-Z]\w+', lambda x: x.group().replace("E", ""), content)
                content = re.sub(r'\bT[A-Z]\w+', lambda x: x.group().replace("T", ""), content)
                
            with open(namepath, 'w') as file:
                file.write(content)