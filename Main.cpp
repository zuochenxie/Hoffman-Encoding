//
//  main.cpp
//  project2
//
//  Created by Zuochen Xie on 2/2/16.
//  Copyright (c) 2016 Zuochen Xie. All rights reserved.
//

#include "Heap.h"
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	// Read plain.input and create array of character counts (freq)
	int freq[27] = {0};
        fstream file ("plain.input");
        if (!file)
        {
            cout << "Unable to open the input file." << endl;
            return 0;
        }
        char c;
        int index = 0;
        while (file.get(c))
        {
            if (c == 32)
            {
                index = 26;
                freq[index]++;
            }
            else
            {
                index = c - 'a';
                freq[index]++;
            }
        }
	
	// Create heap
	Heap h(freq);
	
	// Collapse heap into the EncodingTrie
	Trie* pEncodingTrie = h.constructEncodingTrie();
	
	pEncodingTrie->encodeAndPrint("plain.input");
	pEncodingTrie->decode("encoded.input");
	//pEncodingTrie->printEncodingMap();
}
