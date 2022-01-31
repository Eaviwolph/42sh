CFILES=*.c
all:
	gcc -Werror -Wextra -Wall -std=c99 -pedantic -fsanitize=address $(CFILES) -o exec
	./exec