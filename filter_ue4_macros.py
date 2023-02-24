# -*- coding: utf-8 -*-

import os
import re
import sys


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
                regex = '^(\s*)((?:UFUNCTION|UCLASS|UPROPERTY|UENUM|GENERATED_BODY)\s*\('+paren_matcher(25)+'\))'
                content = re.sub(regex, r'\1', content, flags=re.MULTILINE)
                content = re.sub(r'\bU[A-Z]\w+', lambda x: x.group().replace("U", ""), content)
                content = re.sub(r'\bF[A-Z]\w+', lambda x: x.group().replace("F", ""), content)
                content = content.replace('FVector', 'Vec3')
            with open(namepath, 'w') as file:
                file.write(content)