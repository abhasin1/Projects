
// Implementation of a dictionary using an array and sequential search
// The array will be dynamically resized if necessary

#if !defined ARRAY_DICTIONARY_H
#define ARRAY_DICTIONARY_H

#include "dictionary.h"

class ArrayDictionary : public Dictionary 
{
	KeyType *arrayKey;
	
	DataType *arrayDictionary;
	
	int words;
	
	int index;
	
  // Add any member variables you need
  
public:
  // Constructor
  ArrayDictionary();
  
  // Add a record to the dictionary. Returns false if key already exists
  bool addRecord( KeyType key, DataType record);
  
  // Find a key in the dictionary and return corresponding record or NULL
  // Use sequential search
  DataType findRecord( KeyType key);
  
   bool removeElement(KeyType key);
   
   KeyType *keys(int * n);

  // Add other methods you may need
};
#endif
