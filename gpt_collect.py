import os
from glob import glob
from os.path import join, abspath, relpath

import pyperclip

__all__ = []


def main():
    cwd = abspath(join(os.getcwd()))
    core_header_files = glob(join(cwd, '**', '*.hpp'), recursive=True)
    core_header_files = [relpath(p, cwd) for p in core_header_files]

    buffer = ["Consider the following C++20 codebase. Find major problems."]
    for p in core_header_files:
        buffer.append(f"File: `{p}`")
        buffer.append('```')
        with open(p) as f:
            buffer.append(f.read())
        buffer.append('```')

    content = '\n'.join(buffer)
    for _ in range(16):
        content = content.replace('\n\n', '\n')
        content = content.replace('  ', ' ')

    pyperclip.copy(content)


if __name__ == '__main__':
    main()
