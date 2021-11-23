#!/bin/sh
exet="exec"
exepb="parse/bad"
exepg="parse/good"

s=./../build/42sh
r=./42shtest

for i in $exet/*.sh
do
    echo "----------$i"
    testfile="testfile"
    testfileref="testfileref"
    cat "$i" | $s > "$testfile"
    cat "$i" | $r > "$testfileref"
    diff "$testfile" "$testfileref"
done

for i in $exepg/*.sh
do
    echo "----------$i"
    testfile="testfile"
    testfileref="testfileref"
    cat "$i" | $s > "$testfile"
    cat "$i" | $r > "$testfileref"
    diff "$testfile" "$testfileref"
done