#include <string>
#include <fstream>
#include <iostream>

#include "Heap.h"

// Constructor for new Trie
Trie::Trie(char letter, int weight) {
	this->letter = letter;
	this->weight = weight;
	pParent = NULL;
	pLeftChild = NULL;
	pRightChild = NULL;
}
// Constructor for combined Trie node
Trie::Trie(Trie* pT1, Trie* pT2) {
	letter = '#';
	weight = pT1->getWeight() + pT2->getWeight();
	pParent = NULL;
	// First deleted node from heap should be right child
	// Second deleted node from heap should be left child
	pRightChild = pT1;
	pLeftChild = pT2;
	pRightChild->setParent(this);
	pLeftChild->setParent(this);
}

// Always delete a Trie from its root!
Trie::~Trie() {
	delete pRightChild;
	delete pLeftChild;
}
	
bool Trie::isBigger(Trie* pOther) {
	return (weight > pOther->getWeight());
}

// Returns std::string array of size 27
std::string* Trie::getEncodingMap() {
	std::string* encodingMap = new std::string[27];
	getEncodingMapHelper(encodingMap, "");
	return encodingMap;	
}

// The encodingMap is passed down by reference to each of the leaf nodes recursively from the root,
// along with the accumulating path to the leaf node (encoding) from the root.
// IN/OUT: std::string[] encodingMap
// IN: std::string encoding
void Trie::getEncodingMapHelper(std::string* encodingMap, std::string encoding) {
	if(letter == '#') {
		pRightChild->getEncodingMapHelper(encodingMap, encoding+"0");
		pLeftChild->getEncodingMapHelper(encodingMap, encoding+"1");
	} else {
		int index = (letter == 32) ? 26 : (letter-'a');
		encodingMap[index] = encoding;
	}
}

void Trie::printEncodingMap() {
	std::string* encodingMap = getEncodingMap();
	for(int i=0; i<27; i++) {
		if(encodingMap[i] != "") {
			char c = (i==26) ? ' ' : i+'a';
			printf("%c: %s\n", c, encodingMap[i].c_str());
		}
	}
}

void Trie::encodeAndPrint(std::string filename) {
	std::string* encodingMap = getEncodingMap();
	std::fstream file (filename.c_str());
	if (!file) {
		std::cout << "Unable to open the input file." << std::endl;
		return;
	}
	char c;
	while (file.get(c)) {
		int index = (c == ' ') ? 26 : c-'a';
		std::cout << encodingMap[index];
	}
	std::cout << std::endl;
}
    
void Trie::decode(std::string filename) {
	std::ifstream file (filename.c_str());
	if (!file)
	  {
	    std::cout << "Unable to open encoded file" << std::endl;
	    return;
	}
	
	Trie* pT = this;
	char c;
	while(!file.eof()) {
	  while(pT->getLetter() == '#') {
		  file.get(c);
	    if(c == '0') pT = pT->getRightChild();
	    else if(c == '1') pT = pT->getLeftChild();
		else if(c == 0) {
			std::cout << "ERROR: encoded.input is empty!" << std::endl;
			return;
		}
		else {
			std::cout << std::endl << "ERROR: Invalid character \'" << c << "\' in encoded.input!" << std::endl;
			return;
		}
	  }
	  if(!file.eof()) std::cout << pT->getLetter();
	  pT = this;
	}
	std::cout << std::endl;
}