CC = gcc		
CFLAGS = -Wall -g

OBJ = main.o functions_hash_table.o functions.o

inverted_search: $(OBJ)
	$(CC) $(OBJ) -o inverted_search

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o inverted_search

