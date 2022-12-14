# -*- coding: utf-8 -*-

import os
import re
import sys

filename = 'doxygen-awesome-css/doxygen-custom/header.html'

with open(filename, 'r') as file:
    content = file.read()

content.replace('<a href="https://github.com/jothepro/doxygen-awesome-css" class="github-corner" title="View source on GitHub" target="_blank">', "")

with open(filename, 'w') as file:
    file.write(content)