
import glob
import math
import os
import sys
import tomllib

HEAD = """\
#include "doctest/doctest.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "tomload/tomload.h"

namespace {

std::string load_file(const std::string& filename) {
    std::ifstream file(std::string(TOML_TEST_DIR) + filename);
    if (not file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

struct rhs_nan {};
bool operator==(tomload::float_t f, rhs_nan) {
    return std::isnan(f);
}

}  // namespace

using namespace tomload;
"""


C_STR = {
    '"': '\\"', '\\': '\\\\',
    '\r': '\\r', '\n': '\\n', '\t': '\\t', '\b': '\\b',
    '\0': '" + std::string(1, \'\\0\') + "'}


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


def print_head():
    print(HEAD)


def print_accessor(tom, keys=tuple()):
    if type(tom) in (list, dict, int, float, bool, str):
        print(''.join(check_type(keys, tom)))

    if type(tom) in (list, dict):
        print(''.join(check_size(keys, tom)))

        iters = enumerate(tom) if type(tom) is list else tom.items()
        for k, v in iters:
            print_accessor(v, list(keys) + [k])
    elif type(tom) in (int, float, bool, str):
        print(''.join(check_val(keys, tom)))


def print_check(path, keys=tuple()):
    basename = os.path.basename(path)
    invalid = 'invalid' in path

    with open(path, 'rb') as file:
        try:
            tom = tomllib.load(file)
            if invalid:
                raise RuntimeError('unexpected valid TOML file')
        except tomllib.TOMLDecodeError as ex:
            if invalid:
                pass
            else:
                raise ex


    dir_name, file_name = os.path.split(path)
    all_separated = dir_name.split(os.sep) + [file_name]

    filename = os.sep.join(all_separated[-3:])
    print(f'TEST_CASE("{filename}") {{')
    print(f'    std::string content = load_file("{filename}");')

    if invalid:
        print('')
        print('    CHECK_THROWS_AS(item_t(view_t{content.c_str()}), parse_error&);')
    else:
        print('    item_t t(view_t{content.c_str()});')
        print('')

        print_accessor(tom)

    print('}')
    print('')


def main():
    """Load TOML file and dump CHECK() lines of doctest."""
    if len(sys.argv) >= 2:
        print_head()
        for path in sorted(glob.glob(sys.argv[1] + "/*.toml")):
            if ('hex-escape.toml' in path or
                'escape-esc.toml' in path):
                continue

            print_check(path)


if __name__ == '__main__':
    main()
