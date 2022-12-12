import re
import sys


def paren_matcher (n):
    return r"[^()]*?(?:\("*n+r"[^()]*?"+r"\)[^()]*?)*?"*n

for filename in os.listdir("."):
    f = os.path.join(directory, filename)
    # checking if it is a file
    if os.path.isfile(f):
        # Slurp file into a single string
        with open(filename, 'r') as file:
            content = file.read()
            regex = '^(\s*)((?:UFUNCTION|UCLASS|UPROPERTY|UENUM)\s*\('+paren_matcher(25)+'\))'
            content = re.sub(regex, r'\1/* UE4 Macro: \2 */', content, flags=re.MULTILINE)
        with open(filename, 'w') as file:
            file.write(content)