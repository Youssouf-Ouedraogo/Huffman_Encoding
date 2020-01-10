all: fileCompressor.c huffman.o
	gcc -g -Wall -Werror -fsanitize=address -std=c99 -D_BSD_SOURCE -Wall fileCompressor.c huffman.o -o fileCompressor
huffman.o: huffman.c
	gcc -g -c -Wall -Werror -fsanitize=address -std=c99 huffman.c 
clean:
	rm -rf *o fileCompressor
