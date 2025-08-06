
import math
import os
import sys
import tomllib

C_STR = {
    '"': '\\"', '\\': '\\\\',
    '\r': '\\r', '\n': '\\n', '\t': '\\t', '\b': '\\b'}


def c_str(s):
    return '"' + ''.join(C_STR.get(c, c) for c in s) + '"'


def c_bool(b):
    return str(b).lower()


def c_float(f):
    if f == float('inf'):
        return 'std::numeric_limits<double>::infinity()'
    elif f == float('-inf'):
        return '-std::numeric_limits<double>::infinity()'
    elif math.isnan(f):
        return 'rhs_nan{}'
    else:
        return str(f)


TYPE_CHECK = {
    list: 'is_array', dict: 'is_table',
    int: 'is_integer', float: 'is_float', bool: 'is_boolean', str: 'is_string'}
TYPE_GET = {
    int: 'get_integer', float: 'get_float', bool: 'get_bool', str: 'get_string'}
KEY_CONV = {
    int: int, str: c_str}
VAL_CONV = {
    int: int, float: c_float, bool: c_bool, str: c_str}


def chain_keys(keys):
    for key in keys:
        func = KEY_CONV[type(key)]
        yield f'[{func(key)}]'


def check_type(keys, val):
    yield '    CHECK(t'
    yield from chain_keys(keys)
    name = TYPE_CHECK[type(val)]
    yield f'.{name}() == true);'


def check_size(keys, val):
    yield '    CHECK(t'
    yield from chain_keys(keys)
    yield f'.size() == {len(val)});'


def check_val(keys, val):
    yield '    CHECK(t'
    yield from chain_keys(keys)
    name = TYPE_GET[type(val)]
    func = VAL_CONV[type(val)]
    yield f'.{name}() == {func(val)});'


def print_load(argv1):
    filename = os.path.basename(argv1)

    print(f'TEST_CASE("{filename}") {{')
    print(f'    std::string content = load_file("{filename}");')
    print('    item_t t(view_t{content.c_str()});')
    print('')


def print_check(tom, keys=tuple()):
    if type(tom) in (list, dict, int, float, bool, str):
        print(''.join(check_type(keys, tom)))

    if type(tom) in (list, dict):
        print(''.join(check_size(keys, tom)))

        iters = enumerate(tom) if type(tom) is list else tom.items()
        for k, v in iters:
            print_check(v, list(keys) + [k])
    elif type(tom) in (int, float, bool, str):
        print(''.join(check_val(keys, tom)))


def main():
    """Load TOML file and dump CHECK() lines of doctest."""
    if len(sys.argv) >= 2:
        with open(sys.argv[1], 'rb') as file:
            print_load(sys.argv[1])
            print_check(tomllib.load(file))
            print('}')


if __name__ == '__main__':
    main()
