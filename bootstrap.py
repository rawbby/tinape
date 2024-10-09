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


def run(command: [str]):
    from subprocess import Popen, PIPE, STDOUT

    print(' '.join(command))
    process = Popen(command, stdout=PIPE, stderr=STDOUT, text=True)
    for stdout_line in iter(process.stdout.readline, ''):
        print(stdout_line, end='')
    process.stdout.close()
    status = process.wait()
    if status:
        sys.exit(status)


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


def ensure_glm(git: str, cmake: str, config: str):
    glm_url = 'https://github.com/g-truc/glm.git'
    glm_dir = abspath(join(dirname(__file__), 'extern', 'glm-source'))
    glm_install_dir = abspath(join(dirname(__file__), 'extern', f"glm"))
    glm_build_dir = join(glm_dir, f"cmake-build")

    glm_options = [
        '-DGLM_BUILD_LIBRARY=ON',
        '-DGLM_BUILD_INSTALL=ON',
        '-DGLM_BUILD_TESTS=OFF',
        '-DGLM_ENABLE_CXX_20=ON',
        '-DGLM_ENABLE_LANG_EXTENSIONS=ON',
        '-DGLM_DISABLE_AUTO_DETECTION=OFF',
        '-DGLM_ENABLE_FAST_MATH=ON',
        '-DGLM_ENABLE_SIMD_AVX=ON',
        '-DGLM_ENABLE_SIMD_AVX2=ON',
        '-DGLM_QUIET=OFF'
    ]

    for glm_option in glm_options:
        key, val = glm_option[2:].split('=')
        append(config, f"set({key} {val})")

    cmake_options = [
        '-S', glm_dir, '-B', glm_build_dir,
        '-DCMAKE_BUILD_TYPE=Release',
        f"-DCMAKE_INSTALL_PREFIX={glm_install_dir}"
    ]

    if not exists(glm_dir):
        run([git, 'clone', glm_url, glm_dir])
        run([git, '-C', glm_dir, 'checkout', '1.0.1'])

    if not exists(glm_install_dir):
        if not exists(glm_build_dir):
            os.makedirs(glm_build_dir)
            run([cmake] + cmake_options + glm_options)
            run([cmake, '--build', glm_build_dir, '--config', 'Release'])
        os.makedirs(glm_install_dir)
        run([cmake, '--install', glm_build_dir])

    return glm_install_dir


def main():
    python = sys.executable
    git = find_executable('git')
    cmake = find_executable('cmake')

    config = abspath(join(dirname(__file__), 'cmake', 'config.cmake'))

    glm_dir = ensure_glm(git, cmake, config)


if __name__ == '__main__':
    ensure_venv()
    main()
