import os
import sys
from os.path import join, dirname, abspath, isfile, exists


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


def run(command: [str], cwd=None) -> str:
    from subprocess import Popen, PIPE, STDOUT

    cwd = cwd if cwd is not None else join(dirname(__file__))

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


def find_executable(executable_name: str) -> str:
    if os.name == 'nt':
        executable_name += '.exe'

    for path in os.getenv('PATH').split(os.pathsep):
        executable_path = join(path, executable_name)
        if isfile(executable_path) and os.access(executable_path, os.X_OK):
            return executable_path

    print(f"Failed to find executable {executable_name}")
    sys.exit(1)


def ensure_venv():
    venv_path = abspath(join(dirname(__file__), '.venv'))
    if os.name == 'nt':
        venv_executable = join(venv_path, 'Scripts', 'python.exe')
    else:
        venv_executable = join(venv_path, 'bin', 'python')

    if not exists(venv_executable):
        run([sys.executable, '-m', 'venv', '.venv'])

    if sys.executable != venv_executable:
        run([venv_executable, __file__] + sys.argv[1:])
        sys.exit()


def ensure_cnl(git: str, cmake: str):
    cnl_url = 'https://github.com/johnmcfarlane/cnl.git'
    cnl_dir = abspath(join(dirname(__file__), 'extern', 'cnl-source'))
    cnl_install_dir = abspath(join(dirname(__file__), 'extern', 'cnl'))
    cnl_build_dir = join(cnl_dir, 'cmake-build-release')

    cnl_options = [
        '-DBUILD_TESTING=OFF',
        '-DCNL_EXCEPTIONS=OFF',
        '-DCNL_SANITIZE=OFF',
        '-DCNL_INT128=ON',
    ]

    cmake_options = [
        '-S', cnl_dir, '-B', cnl_build_dir,
        '-DCMAKE_BUILD_TYPE=Release',
        f"-DCMAKE_INSTALL_PREFIX={cnl_install_dir}",
    ]

    if not exists(cnl_dir):
        run([git, 'clone', cnl_url, cnl_dir])
        run([git, 'checkout', 'v1.1.7'], cwd=cnl_dir)

    if not exists(cnl_install_dir):
        os.makedirs(cnl_install_dir)

    if not exists(cnl_build_dir):
        os.makedirs(cnl_build_dir)

    run([cmake] + cmake_options + cnl_options)
    run([cmake, '--install', cnl_build_dir, '--prefix', cnl_install_dir])

    return cnl_install_dir


def ensure_absl(git: str, cmake: str):
    absl_url = 'https://github.com/abseil/abseil-cpp.git'
    absl_dir = abspath(join(dirname(__file__), 'extern', 'absl-source'))
    absl_install_dir = abspath(join(dirname(__file__), 'extern', 'absl'))
    absl_build_dir = join(absl_dir, 'cmake-build-release')

    absl_options = [
        '-DBUILD_TESTING=OFF',
        '-DABSL_BUILD_TESTING=OFF',
        '-DABSL_ENABLE_INSTALL=ON',
    ]

    cmake_options = [
        '-S', absl_dir, '-B', absl_build_dir,
        '-DCMAKE_BUILD_TYPE=Release',
        f"-DCMAKE_INSTALL_PREFIX={absl_install_dir}",
    ]

    if not exists(absl_dir):
        run([git, 'clone', absl_url, absl_dir])
        run([git, 'checkout', '20240722.0'], cwd=absl_dir)

    if not exists(absl_install_dir):
        os.makedirs(absl_install_dir)

    if not exists(absl_build_dir):
        os.makedirs(absl_build_dir)

    run([cmake] + cmake_options + absl_options)
    run([cmake, '--build', absl_build_dir, '--config', 'Release'])
    run([cmake, '--install', absl_build_dir, '--prefix', absl_install_dir])

    return absl_install_dir


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
    git = find_executable('git')
    cmake = find_executable('cmake')

    config = abspath(join(dirname(__file__), 'cmake', 'config.cmake'))

    append(config, 'set(_IGNORE_CMAKE_C_COMPILER "${CMAKE_C_COMPILER}")')
    append(config, 'set(_IGNORE_Python3_EXECUTABLE "${Python3_EXECUTABLE}")')
    append(config, 'set(_IGNORE_Python_EXECUTABLE "${Python_EXECUTABLE}")')

    cnl_dir = ensure_cnl(git, cmake)
    sdl_dir = ensure_sdl(git, cmake)
    absl_dir = ensure_absl(git, cmake)

    append(config, f"set(CNL_DIR \"{cnl_dir.replace('\\', '/')}\")")
    append(config, f"set(SDL_DIR \"{sdl_dir.replace('\\', '/')}\")")
    append(config, f"set(ABSL_DIR \"{absl_dir.replace('\\', '/')}\")")


if __name__ == '__main__':
    ensure_venv()
    main()
