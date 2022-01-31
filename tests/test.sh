#!/bin/sh

./42sh -c "echo hello" > testfile
sh -c "echo hello" > testfileref
diff testfile testfileref

./42sh tests/big_tests.sh arg1 arg2 > testfile
sh tests/big_tests.sh arg1 arg2 > testfileref
diff testfile testfileref

./42sh tests/my_tests.sh arg1 arg2 > testfile
sh tests/my_tests.sh arg1 arg2 > testfileref
diff testfile testfileref