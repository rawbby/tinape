import os
import sys
from os.path import join, dirname, abspath, isfile, exists
from pathlib import Path

from extern.file_lock import FileLock
from extern.run import *


def append(file_path, line):
    if not exists(dirname(file_path)):
        os.makedirs(dirname(file_path))

    with open(file_path, 'a'):
        ...

    with open(file_path, 'r') as file:
        lines = file.readlines()

    if line + '\n' not in lines:
        with open(file_path, 'a') as file:
            file.write(line + '\n')


def find_executable(executable_name: str) -> str:
    if os.name == 'nt':
        executable_name += '.exe'

    for path in os.getenv('PATH').split(os.pathsep):
        executable_path = join(path, executable_name)
        if isfile(executable_path) and os.access(executable_path, os.X_OK):
            return executable_path

    print(f"Failed to find executable {executable_name}")
    sys.exit(1)


def ensure_sdl_net(git: str, cmake: str):
    sdl_net_url = 'https://github.com/libsdl-org/SDL_net.git'
    sdl_net_dir = abspath(join(dirname(__file__), 'extern', 'sdl-net-source'))
    sdl_net_install_dir = abspath(join(dirname(__file__), 'extern', 'sdl'))
    sdl_net_build_dir = join(sdl_net_dir, 'cmake-build-release')

    sdl_net_options = [
        '-DSDL2NET_SAMPLES=OFF',
        '-DSDL2NET_BUILD_SHARED_LIBS=OFF',
        '-DSDL2NET_INSTALL=ON',
        '-DBUILD_SHARED_LIBS=OFF',
    ]

    cmake_options = [
        '-S', sdl_net_dir, '-B', sdl_net_build_dir,
        '-DCMAKE_BUILD_TYPE=Release',
        f"-DCMAKE_INSTALL_PREFIX={sdl_net_install_dir}",
        f"-DCMAKE_PREFIX_PATH={sdl_net_install_dir}",
    ]

    if not exists(sdl_net_dir):
        run([git, 'clone', sdl_net_url, sdl_net_dir])
        # TODO wait for next release of sdl
        # run([git, 'checkout', 'release-2.2.0'], cwd=sdl_net_dir)

    if not exists(sdl_net_install_dir):
        os.makedirs(sdl_net_install_dir)

    if not exists(sdl_net_build_dir):
        os.makedirs(sdl_net_build_dir)

    run([cmake] + cmake_options + sdl_net_options)
    run([cmake, '--build', sdl_net_build_dir, '--config', 'Release'])
    run([cmake, '--install', sdl_net_build_dir, '--prefix', sdl_net_install_dir])

    return sdl_net_install_dir


def ensure_sdl(git: str, cmake: str):
    sdl_url = 'https://github.com/libsdl-org/SDL.git'
    sdl_dir = abspath(join(dirname(__file__), 'extern', 'sdl-source'))
    sdl_install_dir = abspath(join(dirname(__file__), 'extern', 'sdl'))
    sdl_build_dir = join(sdl_dir, 'cmake-build-release')

    sdl_options = [
        '-DSDL_SHARED=OFF',
        '-DSDL_STATIC=ON',
        '-DSDL_TEST_LIBRARY=OFF',
        '-DSDL_TESTS=OFF',
        '-DSDL_EXAMPLES=OFF',
    ]

    cmake_options = [
        '-S', sdl_dir, '-B', sdl_build_dir,
        '-DCMAKE_BUILD_TYPE=Release',
        f"-DCMAKE_INSTALL_PREFIX={sdl_install_dir}",
    ]

    if not exists(sdl_dir):
        run([git, 'clone', sdl_url, sdl_dir])
        # TODO wait for next release of sdl
        # run([git, 'checkout', 'release-2.30.8'], cwd=sdl_dir)

    if not exists(sdl_install_dir):
        os.makedirs(sdl_install_dir)

    if not exists(sdl_build_dir):
        os.makedirs(sdl_build_dir)

    run([cmake] + cmake_options + sdl_options)
    run([cmake, '--build', sdl_build_dir, '--config', 'Release'])
    run([cmake, '--install', sdl_build_dir, '--prefix', sdl_install_dir])

    ensure_sdl_net(git, cmake)

    return sdl_install_dir


def main():
    lock_filename = abspath(join(os.getcwd(), 'extern', '.lock'))
    valid_file = Path(abspath(join(os.getcwd(), 'extern', '.valid')))

    with FileLock(lock_filename):
        if valid_file.exists():
            return

        git = find_executable('git')
        cmake = find_executable('cmake')

        sdl_dir = ensure_sdl(git, cmake).replace('\\', '/')

        config = abspath(join(os.getcwd(), 'extern', 'config.cmake'))
        append(config, f'set(SDL_DIR "{sdl_dir}")')

        valid_file.touch()


if __name__ == '__main__':
    main()
