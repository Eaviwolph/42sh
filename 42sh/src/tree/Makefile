CFILES=tree_if.c tree_print.c tree_for.c tree_generic_destroy.c tree_while.c
all:
	gcc -Werror -Wextra -Wall -std=c99 -pedantic -fsanitize=address $(CFILES) -o exec
	./exec
