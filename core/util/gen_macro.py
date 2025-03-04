#!/usr/bin/env python3

from os.path import dirname, join

MAX_COUNT = 96


def generate_range(n):
    output = []
    for u in range(1, n + 1):
        output.append(f"#define RANGE_{u} {','.join(str(i) for i in range(u))}")
    return '\n'.join(output)


def generate_macro_map(n):
    params = ','.join(f"_{i}" for i in range(1, n + 1))
    return f"#define MACRO_MAP{n}({params},VALUE,...)VALUE"


def generate_fixed_macros():
    return (
        '#define PACK(...)(__VA_ARGS__)\n'
        '#define UNPACK_IMPL_(...)__VA_ARGS__\n'
        '#define UNPACK(PACKED_ARG)UNPACK_IMPL_ PACKED_ARG\n'
        '#define JOIN_UNPACK(PACKED_ARG)JOIN(,UNPACK(PACKED_ARG))'
    )


def generate_for_each(n):
    lines = []
    lines.append('#define FOR_EACH_0(F,...)')
    for i in range(1, n + 1):
        params = ','.join(['F'] + [f"x{j}" for j in range(i)] + ['...'])
        expansion = ','.join([f"F(x{j})" for j in range(i)])
        lines.append(f"#define FOR_EACH_{i}({params}){expansion}")
    return '\n'.join(lines)


def generate_for_each_macro(n):
    macros = ','.join(f"FOR_EACH_{i}" for i in range(n, -1, -1))
    return f"#define FOR_EACH(F,...)MACRO_MAP{n}(__VA_ARGS__,{macros})(F,__VA_ARGS__)"


def generate_pop(n):
    lines = []
    lines.append('#define POP_0()')
    lines.append('#define POP_1(_0)')
    for i in range(2, n + 1):
        params = ','.join(f"_{j}" for j in range(0, i))
        expansion = ','.join(f"_{j}" for j in range(0, i - 1))
        lines.append(f"#define POP_{i}({params}){expansion}")
    return '\n'.join(lines)


def generate_pop_macro(n):
    macros = ','.join(f"POP_{i}" for i in range(n, -1, -1))
    return f"#define POP(...)MACRO_MAP{n}(__VA_ARGS__,{macros})(__VA_ARGS__)"


def generate_enumerate(n):
    lines = []
    lines.append('#define ENUMERATE_0(F)')
    for i in range(1, n + 1):
        params = ','.join(f"_{j}" for j in range(i))
        expanded = ','.join(f"F({j},_{j})" for j in range(i))
        lines.append(f"#define ENUMERATE_{i}(F,{params}){expanded}")
    return '\n'.join(lines)


def generate_enumerate_macro(n):
    macros = ','.join(f"ENUMERATE_{i}" for i in range(n, -1, -1))
    return f"#define ENUMERATE(F,...)MACRO_MAP{n}(__VA_ARGS__,{macros})(F,__VA_ARGS__)"


def generate_argc(n):
    numbers = ','.join(str(i) for i in range(n, -1, -1))
    return f"#define ARGC(...)MACRO_MAP{n}(__VA_ARGS__,{numbers})"


def generate_head_tail():
    return (
        '#define HEAD_IMPL_(HEAD,...)HEAD\n'
        '#define HEAD(...)HEAD_IMPL_(__VA_ARGS__)\n'
        '#define TAIL_IMPL_(HEAD,...)__VA_ARGS__\n'
        '#define TAIL(...)TAIL_IMPL_(__VA_ARGS__)'
    )


def generate_reverse(n):
    lines = []
    lines.append('#define REVERSE_0(...)')
    for i in range(1, n + 1):
        params = ','.join(f"x{j}" for j in range(i))
        reversed_params = ','.join(f"x{j}" for j in reversed(range(i)))
        lines.append(f"#define REVERSE_{i}({params}){reversed_params}")
    return '\n'.join(lines)


def generate_reverse_macro(n):
    macros = ','.join(f"REVERSE_{i}" for i in range(n, 0, -1))
    return f"#define REVERSE(...)MACRO_MAP{n}(__VA_ARGS__,{macros})(__VA_ARGS__)"


def generate_join(n):
    lines = []
    lines.append('#define JOIN_0()')
    lines.append('#define JOIN_1(S,_0) _0')
    for i in range(2, n + 1):
        params = ','.join(f"_{j}" for j in range(i))
        expansion_parts = [f"_{0}"]
        for j in range(1, i):
            expansion_parts.append(f"S _{j}")
        expansion = ' '.join(expansion_parts)
        lines.append(f"#define JOIN_{i}(S,{params}){expansion}")
    return '\n'.join(lines)


def generate_join_macro(n):
    macros = ','.join(f"JOIN_{i}" for i in range(n, 0, -1))
    return f"#define JOIN(S,...)MACRO_MAP{n}(__VA_ARGS__,{macros})(S,__VA_ARGS__)"


def main():
    output = []
    output.append(generate_range(MAX_COUNT))
    output.append(generate_macro_map(MAX_COUNT))
    output.append(generate_fixed_macros())
    output.append(generate_for_each(MAX_COUNT))
    output.append(generate_for_each_macro(MAX_COUNT))
    output.append(generate_pop(MAX_COUNT))
    output.append(generate_pop_macro(MAX_COUNT))
    output.append(generate_enumerate(MAX_COUNT))
    output.append(generate_enumerate_macro(MAX_COUNT))
    output.append(generate_argc(MAX_COUNT))
    output.append(generate_head_tail())
    output.append(generate_reverse(MAX_COUNT))
    output.append(generate_reverse_macro(MAX_COUNT))
    output.append(generate_join(MAX_COUNT))
    output.append(generate_join_macro(MAX_COUNT))

    with open(join(dirname(__file__), 'include', 'macro.hpp'), 'w') as f:
        f.write('#pragma once\n')
        f.write('// clang-format off\n')
        f.write('#define STRINGIFY(X)#X\n')
        f.write('#define TOSTRING(X)STRINGIFY(X)\n')
        for line in output:
            f.write(line)
            f.write('\n')
        f.write('// clang-format on\n')


if __name__ == '__main__':
    main()
