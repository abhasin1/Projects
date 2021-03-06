#include <stdlib.h>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"array-dictionary.h"

using namespace std;

  // Constructor
ArrayDictionary::ArrayDictionary()
{
	// Add needed code
	arrayDictionary = new DataType[100];
	arrayKey = new KeyType[100];
	
	for(int i=0;i<100;i++)
	{
		arrayDictionary[i] = NULL;
		arrayKey[i] = NULL;
	}
	
	words = 100;
	index = 0;
	
}

// Add a record to the dictionary. Returns false if key already exists
bool ArrayDictionary::addRecord( KeyType key, DataType record)
{
	// Add needed code
	
	bool toCheck = false;
	int currentIndex = 0;
	DataType tmp;
	
	
	if(index>=words)
	{
		words = words*2;
		
		KeyType *newArrayKey = new KeyType[words];
		DataType *newArrayDictionary = new DataType[words];
		
		for(int i=0;i<words;i++)
		{
			newArrayKey[i] = NULL;
			newArrayDictionary[i] = NULL;
		}
		
		for(int i=0;i<index;i++)
		{
			newArrayKey[i] = arrayKey[i];
			newArrayDictionary[i] = arrayDictionary[i];
		}
		
		delete [] arrayKey;
		delete [] arrayDictionary;
		
		arrayKey = newArrayKey;
		arrayDictionary = newArrayDictionary;
	}
	
	
	for(int i=0;i<index;i++)
	{
		if(!strcmp((char *)arrayKey[i] , key))
		{
			toCheck = true;
			arrayKey[i] = key;
			arrayDictionary[i] = record;
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
		arrayKey[index] = newKey;
		arrayDictionary[index] = record;
		index++;
		return true;
	}
	return false;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType ArrayDictionary::findRecord( KeyType key)
{
	// Add needed code
	
	for(int i=0;i<index;i++)
	{
		if(!(strcmp((char *)arrayKey[i] , key)))
		{
			return arrayDictionary[i];
		}
	}
	return NULL;
}

bool
ArrayDictionary::removeElement(KeyType key)
{
	int temp;
	for(int i=0;i<index;i++)
	{
		if(!strcmp((char *)arrayKey[i],key))
		{
			temp = i;
			
			for(int i=temp;i<index-1;i++)
			{
				arrayKey[i] = arrayKey[i+1];
			}
			return true;
		}
	}
	return false;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
ArrayDictionary::keys(int * n)
{
	
	*n=0;
	*n =  *n+index;
	KeyType a[index];
	
	//printf("%d",sizeof(table));
	int i=0;
	
	for(i=0;i<index;i++)
	{
		a[i]=strdup(arrayKey[i]);
	}
	return a;
	
}

