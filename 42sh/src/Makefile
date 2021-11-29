CFILES=common/*.c parser/*.c tree/*.c shell/*.c
all:
	gcc -Werror -Wextra -Wall -g -std=c99 -pedantic -fsanitize=address $(CFILES) -o exec
	./exec
