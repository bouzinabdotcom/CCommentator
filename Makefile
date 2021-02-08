all: main.o comment_sm.o removecode.o
	gcc main.o comment_sm.o removecode.o -o ccommentator
	make clean

removecode.o: comment_sm.o
	gcc -c removecode.c

comment_sm.o: 
	gcc -c comment_sm.c


main.o: main.c
	gcc -c main.c

clean: 
	rm -rf *.o