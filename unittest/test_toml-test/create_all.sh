python3 tests2doctest.py ../toml-test/tests/valid/array/ > valid/array.cpp
python3 tests2doctest.py ../toml-test/tests/valid/bool/ > valid/bool.cpp
python3 tests2doctest.py ../toml-test/tests/valid/comment/ > valid/comment.cpp
python3 tests2doctest.py ../toml-test/tests/valid/float/ > valid/float.cpp
python3 tests2doctest.py ../toml-test/tests/valid/inline-table/ > valid/inline-table.cpp
python3 tests2doctest.py ../toml-test/tests/valid/integer/ > valid/integer.cpp
python3 tests2doctest.py ../toml-test/tests/valid/key/ > valid/key.cpp
python3 tests2doctest.py ../toml-test/tests/valid/root/ > valid/root.cpp
python3 tests2doctest.py ../toml-test/tests/valid/string/ > valid/string.cpp
python3 tests2doctest.py ../toml-test/tests/valid/table/ > valid/table.cpp

python3 tests2doctest.py ../toml-test/tests/invalid/array/ > invalid/array.cpp
python3 tests2doctest.py ../toml-test/tests/invalid/bool/ > invalid/bool.cpp
python3 tests2doctest.py ../toml-test/tests/invalid/control/ > invalid/control.cpp
python3 tests2doctest.py ../toml-test/tests/invalid/float/ > invalid/float.cpp
# python3 tests2doctest.py ../toml-test/tests/invalid/encoding/ > invalid/encoding.cpp
python3 tests2doctest.py ../toml-test/tests/invalid/inline-table/ > invalid/inline-table.cpp
python3 tests2doctest.py ../toml-test/tests/invalid/integer/ > invalid/integer.cpp
python3 tests2doctest.py ../toml-test/tests/invalid/key/ > invalid/key.cpp
python3 tests2doctest.py ../toml-test/tests/invalid/string/ > invalid/string.cpp
python3 tests2doctest.py ../toml-test/tests/invalid/table/ > invalid/table.cpp
