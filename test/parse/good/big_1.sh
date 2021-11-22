toto=bite tata=chate >chiche 2<flop  echo foo bar baze 1>pipi 4>popo >>pupu
{ toto; ! titi; toto && titi; }
{ true; ! false; { false; }; }
function toto()
{
	echo "je m'appel toto"
}
cat << EOF; echo toto; cat << OF

coucou
c'est moi
EOF
je suis grand
OF


if true; then
	false
elif false; then
	false;
else
	true;
fi

if true; then
	if true; then
		if true; then
			if true; then
				if true; then
					if true; then
						if true; then
							if true; then
								if true; then
									false;
								fi
							fi
						fi
					fi
				fi
			fi
		fi
	fi
else
	true;
fi

if { true toto; false; true & false; true && false; false; } then
	false
elif { true; false; true & false; true && false; false; } then
    true;
else
    if { true; false; true & false; true && false; false; } then
	true;
    fi
fi
if [[ -f /etc/DIR_COLORS ]] ; then
        match_lhs=$(</etc/DIR_COLORS)
elif type -p dircolors >/dev/null ; then
        match_lhs=$(dircolors --print-database)
else
        match_lhs=""
fi#!/bin/sh
for i in toto tata titi; do echo $i; done
