OBJS = basicnode.o heap.o prim.o scanner.o support.o
OPTS = -Wall -g -std=c99
prim: $(OBJS)
	gcc $(OPTS) $(OBJS) -o prim -lm
prim.o: prim.c basicnode.c heap.c scanner.c support.c
	gcc $(OPTS) -c prim.c
scanner.o: scanner.c scanner.h
	gcc $(OPTS) -c scanner.c
basicnode.o: basicnode.c basicnode.h
	gcc $(OPTS) -c basicnode.c
heap.o: heap.c heap.h
	gcc $(OPTS) -c heap.c
support.o: support.c support.h basicnode.h
	gcc $(OPTS) -c support.c

clean:
	rm -f $(OBJS) trees

test:	prim
		./prim g1.txt
