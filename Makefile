all: main.o comment_sm.o
	gcc main.o comment_sm.o -o ccommentator
	make clean

comment_sm.o: comment_sm.c comment_sm.h
	gcc -c comment_sm.c


main.o: main.c
	gcc -c main.c

clean: 
	rm -rf *.o