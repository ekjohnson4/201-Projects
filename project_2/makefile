trees:
		gcc -o trees trees.c BSTree.c AVLTree.c queue.c basicnode.c scanner.c

clean:
		rm -f *.o

test:	trees
	@echo testing simple BST
		./trees -b corpus.txt commands.txt
	@echo testing simple AVL
		./trees -a corpus.txt commands.txt
