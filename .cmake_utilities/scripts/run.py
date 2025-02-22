import os
import sys

from os.path import join
from subprocess import Popen, PIPE, STDOUT

__all__ = ['run']


def run(command: [str], cwd=None) -> str:
    cwd = cwd if cwd is not None else join(os.getcwd())

    print(' '.join(command), flush=True)
    process = Popen(command, stdout=PIPE, stderr=STDOUT, text=True, cwd=cwd)
    stdout = ''
    for stdout_line in iter(process.stdout.readline, ''):
        stdout += stdout_line
        print(stdout_line, end='', flush=True)
    process.stdout.close()
    status = process.wait()
    if status:
        sys.exit(status)
    return stdout
