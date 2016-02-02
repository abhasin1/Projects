
// Implementation of a dictionary using a hash table

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash-dictionary.h"

// Constructor
HashDictionary::HashDictionary()
{
	buckets = new HashDictionaryEntry * [TableSize];
	
	for(int i = 0; i < TableSize; i++)
	{
		buckets[i] = NULL;
	}
}

// Add a record to the dictionary. Returns false if key already exists
bool HashDictionary::addRecord( KeyType key, DataType record )
{
	int h = hash(key);
	
	HashDictionaryEntry * entry1 = buckets[h];
	
	while(entry1 != NULL)
	{
		if(!strcmp(entry1->_key, key))
		{
			entry1->_data = record;
			return false;
		}
		
		entry1 = entry1->_next;
	}
	
	entry1 = new HashDictionaryEntry();
	entry1->_key = (KeyType)malloc(sizeof(char) * strlen(key));
	memcpy((void *)entry1->_key, (void *)key, strlen(key) + 1);
	entry1->_data = record;
	entry1->_next = buckets[h];
	buckets[h] = entry1;
	return true;
	
}

// Find a key in the dictionary and return corresponding record or NULL
DataType HashDictionary::findRecord( KeyType key )
{
	int h = hash(key);
	
	HashDictionaryEntry *entry1 = buckets[h];
	
	while(entry1 != NULL)
	{
		if(!strcmp(key, entry1->_key))
		{
			return entry1->_data;
		}
		
		entry1 = entry1->_next;
	}
	
	return NULL;
	
}

int HashDictionary::hash( KeyType key )
{
	int h=0, i=0;
	
	int length = strlen(key);
	
	if(key == NULL)
	{
		return 0;
	}
	
	for(i=0;i<length;i++)
	{
		h += i * key[i];
	}
	
	return h % TableSize;
}


// Returns all the elements in the table as an array of strings.

bool HashDictionary::removeElement(KeyType key)
{
	
}


// *n is the size of the table and it is returned by reference
KeyType* HashDictionary:: keys(int * n)
{
	
}
