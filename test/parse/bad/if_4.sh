if [[ -f /etc/DIR_COLORS ]] ; then
        match_lhs=$(</etc/DIR_COLORS)
elif type -p dircolors >/dev/null ; then
        match_lhs=$(dircolors --print-database)
else
        match_lhs=""
fi