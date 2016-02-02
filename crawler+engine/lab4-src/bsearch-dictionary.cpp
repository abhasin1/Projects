// Implementation of a dictionary using an array and binary search
// It will inherit from the ArrayDictionary

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bsearch-dictionary.h"
#include<iostream>

using namespace std;
//#include "heap.h"

// Constructor
BinarySearchDictionary::BinarySearchDictionary()
{
	
    binaryDictionary = new DataType[100];
    binaryKey = new KeyType[100];
   
    for(int i = 0; i < 100; i++)
    {
        binaryDictionary[i] = NULL;
        binaryKey[i] = NULL;
    }

    index = 0; // number of next index of the array
    words = 100; // current size of the number of words the dictionary can hold
  
  // toSort = false;
    
    
}


bool BinarySearchDictionary::addRecord( KeyType key, DataType record )
{
	
  bool toCheck = false;
  int currentIndex = 0;
  DataType tmp;
	
	
	if(index>=words)
	{
		words = words*2;
		
		KeyType *newBinaryKey = new KeyType[words];
		DataType *newBinaryDictionary = new DataType[words];
		
		for(int i=0;i<words;i++)
		{
			newBinaryKey[i] = NULL;
			newBinaryDictionary[i] = NULL;
		}
		
		for(int i=0;i<index;i++)
		{
			newBinaryKey[i] = binaryKey[i];
			newBinaryDictionary[i] = binaryDictionary[i];
		}
		
		delete [] binaryKey;
		delete [] binaryDictionary;
		
		binaryKey = newBinaryKey;
		binaryDictionary = newBinaryDictionary;
	}
	
	
	for(int i=0;i<index;i++)
	{
		if(!strcmp((char *)binaryKey[i] , key))
		{
			toCheck = true;
			binaryKey[i] = key;
			binaryDictionary[i] = record;
			currentIndex = i;
			break;
		}
	}
	
	if(toCheck)
	{
		currentIndex = 0;
		return false;
	}
	
	else
	{
		KeyType newKey = (KeyType) malloc(strlen(key));
		memcpy((void *) newKey , (void*)key , strlen(key)+1);
		binaryKey[index] = newKey;
		binaryDictionary[index] = record;
		index++;
		return true;
	}
	return false;

}

// Find a key in the dictionary and return corresponding record or NULL
DataType BinarySearchDictionary::findRecord( KeyType key )
{
    // Use binary search
    
   
    if (!toSort )
    {
        sort();
        toSort = true;
	cout<<"Check1\n";
    }
   
    int low = 0;
    int high = index;
   
    while ( low < high )
    {
        int mid = (high + low) / 2; // syntax sugar
       
       int result = strcmp ( binaryKey[mid], key );
       
        if ( result == 0 )
        {
            // found key   
	cout<<"Check2\n";
                
            return binaryDictionary[mid];
        }
        else if ( result > 0 )
        {
            // key in table is larger than key
            high = mid - 1;
        }
        else
        {
            // key in table is < key
            high = mid + 1;
        }
    }
   
    return NULL;
   
}

// Sort array using heap sort.
void BinarySearchDictionary::sort()
{
    //Heap * h = new Heap(index);
   // h.heapSort(binaryDictionary, index);
}

bool BinarySearchDictionary::removeElement(KeyType key)
{
	
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType* BinarySearchDictionary:: keys(int * n)
{
	
}


