#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <iostream>

class Trie {
  private:
	char letter;
	int weight;
	Trie* pParent;
	
	// Note: right child is 0, left child is 1!
	Trie* pRightChild;
	Trie* pLeftChild;
	
  public:
	// constructor for new Trie
	Trie(char letter, int weight);
	// constructor for combined Trie node
	Trie(Trie* t1, Trie* t2);
	
	~Trie();

	char getLetter() { return letter; }
	int getWeight() { return weight; }
	Trie* getParent() { return pParent; }
	
	Trie* getRightChild() { return pRightChild; }
	Trie* getLeftChild() { return pLeftChild; }
	
	void setParent(Trie* pParent) {this->pParent = pParent;}
	
	bool isBigger(Trie* pOther);
	
	std::string* getEncodingMap();
	void getEncodingMapHelper(std::string* encodingArr, std::string encoding);
	
	void printEncodingMap();
	void encodeAndPrint(std::string filename);
	void decode(std::string filename);
};

// Heap of Tries
class Heap {
  private:
	Trie** Array;
	int length;
	  
  public:
	Heap(int freqArr[]);
	void buildHeap();
	void percolateDown(int index);
	void percolateUp(int index);
	Trie* deleteMin();
	void insert(Trie* pT);
	int getLength() { return length; }
	Trie** getArray() { return Array; }
	void printArray();
	Trie* constructEncodingTrie();
};

#endif	// HEAP_H