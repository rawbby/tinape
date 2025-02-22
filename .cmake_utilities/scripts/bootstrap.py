#!/bin/python3

import os
import sys
from os.path import abspath, join
from pathlib import Path

from file_lock import *
from run import *

__all__ = []


def lock_venv():
    venv_path = abspath(join(os.getcwd(), '.venv'))
    os.makedirs(venv_path, exist_ok=True)
    return FileLock(join(venv_path, '.lock'))


def bootstrap():
    venv_path = abspath(join(os.getcwd(), '.venv'))
    valid_file = Path(join(venv_path, '.valid'))

    if os.name == 'nt':
        venv_executable = join(venv_path, 'Scripts', 'python.exe')
    else:
        venv_executable = join(venv_path, 'bin', 'python')

    if not valid_file.exists():
        with lock_venv():
            if not valid_file.exists():
                run([sys.executable, '-m', 'venv', '.venv'])
                run([venv_executable, '-m', 'ensurepip', '--upgrade'])
                valid_file.touch()


if __name__ == '__main__':
    bootstrap()
