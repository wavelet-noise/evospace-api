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
                snake_case_parts.append(current_word)
            current_word = char.lower()
        elif char.isdigit():
            if current_word and current_word[-1].isdigit():
                current_word += char
            else:
                if current_word:
                    snake_case_parts.append(current_word)
                current_word = char
        else:
            current_word += char

    if current_word:
        snake_case_parts.append(current_word)

    return '_'.join(snake_case_parts)


def replace_camel_case_with_snake_case(text):
    def replace(match):
        matched_str = match.group(0)
        if matched_str.startswith("F") or matched_str.startswith("U") or matched_str in {'Vec2i', 'Vec3i', 'Vec3'}:
            return matched_str
        return camel_to_snake_case(matched_str)

    # Regex pattern to match CamelCase words
    pattern = r'\b(?:F|U)?[A-Z][a-zA-Z0-9]*\b'
    result = re.sub(pattern, replace, text)
    return result


def paren_matcher (n):
    return r"[^()]*?(?:\("*n+r"[^()]*?"+r"\)[^()]*?)*?"*n

for root, dirs, files in os.walk("./"):
    for filename in files:
        namepath = os.path.join(root, filename)
        if namepath.find(".h") != -1:
            print(namepath)
            # Slurp file into a single string
            with open(namepath, 'r') as file:
                content = file.read()
                content = replace_camel_case_with_snake_case(content)
                regex = '^(\s*)((?:UFUNCTION|UCLASS|UPROPERTY|UENUM|GENERATED_BODY)\s*\('+paren_matcher(25)+'\))'
                content = re.sub(regex, r'\1', content, flags=re.MULTILINE)
                content = re.sub(r'\bU[A-Z]\w+', lambda x: x.group().replace("U", ""), content)
                content = re.sub(r'\bF[A-Z]\w+', lambda x: x.group().replace("F", ""), content)
                content = content.replace('FVector', 'Vec3')
            with open(namepath, 'w') as file:
                file.write(content)