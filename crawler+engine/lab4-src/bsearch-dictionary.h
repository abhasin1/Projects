// Implementation of a dictionary using an array and binary search
// The class inherits from ArrayDictionary
#if !defined BSEARCH_DICTIONARY_H
#define BSEARCH_DICTIONARY_H

#include "dictionary.h"


class BinarySearchDictionary : public Dictionary
{
    // Add any member variables you need
   
    KeyType * binaryKey;
    DataType * binaryDictionary;
    int index; // number of next index of the array
    int words; // current size of the number of words the dictionary can hold
    bool toSort;

    public:
    // Constructor
    BinarySearchDictionary();
 
    // No need for addRecord since it will use the one in ArrayDictionary
   
    bool addRecord( KeyType key, DataType record );
   
    // Find a key in the dictionary and return corresponding record or NULL
    // Use binary search
    DataType findRecord( KeyType key );

    // Sort array using heap sort.
    void sort();

    
   bool removeElement(KeyType key);
   
   KeyType *keys(int * n);
    // Add other methods you may need
};
#endif

