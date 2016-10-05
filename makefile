Main: Main.o Trie.o Heap.o
	g++ -Wall -o Encoder Main.o Trie.o Heap.o

Trie.o: Trie.cpp Heap.h
	g++ -Wall -c Trie.cpp

Heap.o: Heap.cpp Heap.h
	g++ -Wall -c Heap.cpp

clean:
	rm *.o