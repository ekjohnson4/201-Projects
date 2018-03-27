calculon:
		gcc -o trees trees.c BSTree.c queue.c basicnode.c scanner.c

clean:
		rm -f *.o

test:	calculon
		./trees -b corpus.txt commands.txt
