CFLAGS=-Werror -Wextra -Wall -g -std=c99
CFILES=src/common/*.c src/parser/*.c src/tree/*.c src/shell/*.c src/tools/*.c src/variables/*.c src/alias/*.c src/exectree/*.c src/builtin/*.c src/functions/*.c


42sh:
	gcc $(CFLAGS) $(CFILES) -o 42sh

check: 42sh
	./tests/test.sh

clean:
	rm -f 42sh exec testfile testfileref

prompt: build
	gcc -Werror -Wextra -Wall -g -std=c99 -pedantic -fsanitize=address $(CFILES) -o exec
	./exec

file:
	gcc $(CFLAGS) -g -fsanitize=address $(CFILES) -o exec
	cat tests/ahahah.sh | ./exec

build:
		gcc $(CFLAGS) -pedantic -fsanitize=address $(CFILES) -o exec