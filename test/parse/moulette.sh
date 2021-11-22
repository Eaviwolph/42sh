#!/bin/bash

my42sh="../../src/42sh"

# check good syntax
for file in good/*; do
    $my42sh < "$file" &>/dev/null
    echo ">>>>>>Return: $?"
done

# check bad syntax
for file in bad/*; do
    $my42sh < "$file" &>/dev/null
    echo ">>>>>>Return: $?"
done
