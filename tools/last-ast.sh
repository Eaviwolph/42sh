#!/bin/bash

shopt -s nullglob
shopt -s xpg_echo

lred='\e[1;31m'
lyellow='\e[1;33m'
lblue='\e[1;34m'
lpurple='\e[1;35m'
norm='\e[0m'

echo -n "${lyellow}Finding last generated dotyfile... $norm"
for i in /tmp/42sh-ast-*.dot; do
	test "$last" || last="$i"
	test "$i" -nt "$last" && last="$i"
done

if ! test "$last"; then
    echo "${lred}Not found !$norm"
    exit 1
fi
echo "${lblue}${last}${norm}"
echo "${lyellow}Generating ${lblue}${last%*.dot}.png${lyellow}...$norm"
dot -Tpng $last -o ${last%*.dot}.png
if ! test -s ${last%*.dot}.png; then
	rm -f ast.png $last
	echo "${lred}Bad dotty file not found !$norm"
	exit 2
fi
echo "${lyellow}Updating link ${lblue}ast.png${lyellow}...$norm"
ln -sf ${last%*.dot}.png ast.png
echo "${lyellow}Showing ${lblue}${last%*.dot}.png${lyellow}...$norm"
xview=`which xview`
test -x "$xview" || { echo "${lred}xview not found !$norm"; exit 2; }
"$xview" ast.png &
