bst: bst.o class.o
	g++ -g -Wall -std=c++11 bst.o class.o -o bst

bst.o: bst.cpp
	g++ -c -g -Wall -std=c++11 bst.cpp -o bst.o

class.o: class.cpp
	g++ -c -g -Wall -std=c++11 class.cpp -o class.o

clear:
	rm *.o ./bst