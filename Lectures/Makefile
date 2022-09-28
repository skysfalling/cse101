CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: lecture1

lecture1: lecture1.o
	$(CC) -o lecture1 lecture1.o

lecture1.o: lecture1.c 
	$(CC) $(CFLAGS) -c lecture1.c

linked_list: linked_list.o
	$(CC) -o linked_list linked_list.o

linked_list.o: linked_list.c
	$(CC) $(CFLAGS) -c linked_list.c

clean:
	rm -f lecture1 linked_list *.o

format:
	clang-format -i -style=file *.{c,h}
