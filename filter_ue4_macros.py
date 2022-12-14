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
                content = content.replace('URecipe','Recipe')
                content = content.replace("UOldResearch",'OldResearch')
                content = content.replace("UStaticBlock",'StaticBlock')
                content = content.replace("UStaticItem",'StaticItem')
                content = content.replace("UBlockLogic",'BlockLogic')
                content = content.replace("UClass","Class")
                content = content.replace("UObject","Object")
                content = content.replace("UStaticMesh","StaticMesh")
            with open(namepath, 'w') as file:
                file.write(content)