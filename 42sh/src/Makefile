CFILES=common/*.c parser/*.c tree/*.c shell/*.c
all:
	gcc -Werror -Wextra -Wall -g -std=c99 -pedantic -fsanitize=address $(CFILES) -o exec
	./exec

CC=gcc -Wall -Werror -Wextra -std=c99 -pedantic -g3 -fsanitize=address
eavi:
	${CC} shell/shell.c variables/dvar.c variables/var.c variables/dvarinterface.c parser/dtoken.c parser/lexer.c parser/extendedgetline.c alias/dalias.c alias/alias.c alias/daliasinterface.c
eavi2:
	${CC} tree/*.c exectree/*.c shell/shell.c variables/dvar.c variables/var.c variables/dvarinterface.c parser/dtoken.c parser/lexer.c parser/extendedgetline.c alias/dalias.c alias/alias.c alias/daliasinterface.c