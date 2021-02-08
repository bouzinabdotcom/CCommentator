test.comment_sm: catch.o comment_sm.o comment_sm.test.o  
	g++ -o test.comment_sm catch.o comment_sm.o comment_sm.test.o  

test.removecode: catch.o removecode.o removecode.test.o
	g++ -o test.removecode catch.o comment_sm.o removecode.o removecode.test.o

catch.o:
	g++ -c catch2/catch.cpp

comment_sm.o: 
	g++ -c ../comment_sm.c

removecode.o: comment_sm.o
	g++ -c ../removecode.c

removecode.test.o: removecode.o catch.o
	g++ -c removecode.test.cpp

comment_sm.test.o: comment_sm.o
	g++ -c comment_sm.test.cpp

clean:
	rm -rf *.o