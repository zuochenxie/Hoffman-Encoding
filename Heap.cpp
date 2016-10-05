//
//  Heap.cpp
//  project2
//
//  Created by Zuochen Xie on 2/5/16.
//  Copyright (c) 2016 Xie Zuochen. All rights reserved.
//

#include "Heap.h"

Heap::Heap(int freq[])
{
    Array = new Trie*[27];
	length = 0;
	int ArrayIndex = 0;
    for (int i = 0; i < 27; i++)
    {
        if (freq[i] != 0)
        {
            length++;
            char letter = (i == 26) ? ' ' : (i + 'a');
            Array[ArrayIndex] = new Trie(letter, freq[i]);
			ArrayIndex++;
        }
    }
	buildHeap();
}

void Heap::buildHeap()
{
    int startIndex = length/2 - 1;
    for ( int i = startIndex; i >= 0; i --)
    {
        percolateDown(i);
    }
}

void Heap::percolateDown(int index)
{
	
	int minChild;
    int leftChildIndex = 2*index + 1;
    int rightChildIndex = 2*index + 2;
    Trie* temp;
    
	
	
    if(leftChildIndex > length-1)
        return;                             //index is a leaf

    if(leftChildIndex <= length-1)
    {
        if(leftChildIndex == length-1)          // If this root has no right child then
        {
            minChild = leftChildIndex;     //     leftChild must hold min key
        }
        else
        {		
			if(Array[leftChildIndex]->getWeight() < Array[rightChildIndex]->getWeight())
                minChild = leftChildIndex;
            else
                minChild = rightChildIndex;
        }
		
		
        if(Array[index]->getWeight() > Array[minChild]->getWeight())
        {
                // Swap
            temp = Array[index];
            Array[index] = Array[minChild];
            Array[minChild] = temp;
            
            percolateDown(minChild);
        }
		
    }
}

void Heap::percolateUp(int index)
{
    int parent = (index-1)/2;
    Trie* temp;
   
    if(index == 0)            //index is root
    {
        return;
    }
    else
    {
        if(Array[parent]->getWeight() > Array[index]->getWeight())
        {
            // Swap
            temp = Array[parent];
            Array[parent] = Array[index];
            Array[index] = temp;
           
            percolateUp(parent);
        }
    }
}

Trie *Heap::deleteMin()
{
    Trie *temp = Array[0];
    Array[0] = Array[length-1];
    Array[length-1] = NULL;
    length--;
    
    percolateDown(0);
    
    if(length == -1)
        return NULL;
    else
        return temp;
}

void Heap::insert(Trie *item)
{
    Array[length] = item;
    percolateUp(length);
    length ++;    
}

void Heap::printArray() {
	for(int i=0; i<length; i++) {
        std::cout << Array[i]->getLetter(), Array[i]->getWeight();
	}
    std::cout << "\n";
}

Trie* Heap::constructEncodingTrie() {
	Trie* pRight;
	Trie* pLeft;
	Trie* pMerged;
	Trie* pEncodingTrie;
	
	while(getLength() >= 2) {
		pRight = deleteMin();
		pLeft = deleteMin();
		pMerged = new Trie(pRight, pLeft);
		insert(pMerged);
	}
	pEncodingTrie = deleteMin();
	return pEncodingTrie;
}