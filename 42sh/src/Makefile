CFILES=common/*.c parser/*.c tree/*.c shell/*.c tools/*.c variables/*.c alias/*.c
all:
	gcc -Werror -Wextra -Wall -g -std=c99 -pedantic -fsanitize=address $(CFILES) -o exec
	./exec

CC=gcc -Wall -Werror -Wextra -std=c99 -pedantic -g3 -fsanitize=address

var=variables/dvar.c variables/var.c variables/dvarinterface.c
parser=parser/dtoken.c parser/lexer.c parser/extendedgetline.c
alias=alias/dalias.c alias/alias.c alias/daliasinterface.c
tools=tools/*.c
exect=exectree/*.c
tree=tree/*.c

eavi:
	${CC} shell/shell.c $(var) $(parser) $(alias) $(tools) $(exect) $(tree)
