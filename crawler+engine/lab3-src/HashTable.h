#include <stdlib.h>
#include <string.h>

//Hash table node struct
template <typename Data>

struct HashTableEntry
{
  const char* key;
  Data data;
  HashTableEntry* next;
};


//Hash table class
template <typename Data>
class HashTable
{
	private:

	enum {TableSize = 2039};

	HashTableEntry<Data>** buckets; //array of pointers
	int hash(const char* key);

	public:
	HashTable();

  //Returns true if key exists. Substitute data if key exists
  bool insertItem(const char* key, Data data);

  //Returns true if key exists. Puts data into the 'data' pointer
  bool find(const char* key, Data* data);

  //Removes element with the given key
  bool RemoveElement(const char* key);
  
  int HashTable<Data>::insertItem2(const char* key, int url);
  HashTableEntry<Data> * HashTable<Data>::getWord(int index);
};


template <typename Data>

HashTable<Data>::HashTable()
{
  buckets = (HashTableEntry<Data>**) malloc(TableSize * sizeof(HashTableEntry<Data>*));
  
  for (int i = 0; i < TableSize; i++)
  {
    buckets[i] = NULL;
  }
}


template <typename Data>
int HashTable<Data>::hash(const char* key)
{
  int h=0, i=0;
  const char* p = key;

  while (*p)
  {
    h += i * (*p);
    p++;
    i++;
  }

  return h % TableSize;
}


template <typename Data>
bool HashTable<Data>::insertItem(const char* key, Data data)
{
  //Get hash bucket
  int h = hash(key);
  HashTableEntry<Data>* e = buckets[h];

  //find entry
  while (e != NULL)
  {
    if (!(strcmp(key, e->key)))
    {
      //entry found
      e->data = data;
      return true;
    }
    //key not found
    e = e->next;
  }

  //key not found, create new entry
  e = new HashTableEntry<Data>();
  e->key = strdup(key);
  e->data = data;
  e->next = buckets[h];
  buckets[h] = e;
  return false;
}


template <typename Data>
bool HashTable<Data>::find(const char* key, Data* data)
{
  int h = hash(key);
  

  //Get hash bucket
  HashTableEntry<Data>* e = buckets[h];

  while (e != NULL)
  {
	  
    if (!strcmp(key, e->key))
    {
      //key found
      *data = e->data;
      return true;
    }
    e = e->next;
  }

  //key not found
  return false;
}



template <typename Data>
int HashTable<Data>::insertItem2(const char* key, int url)
{
  //Get hash bucket
  int h = hash(key);
  HashTableEntry<Data>* e = buckets[h];

  //find entry
  while (e != NULL)
  {
    if (!(strcmp(key, e->key)))
    {
      //entry found
      //e->data = data;
      break;
    }
    //key not found
    e = e->next;
  }

  //key not found, create new entry
  
  if(e == NULL)
  {
	  e = new HashTableEntry<Data>();
	
	  e->key = strdup(key);
	  e->data = (Data) malloc(sizeof(Data));
	  
	  e->data->_urlRecordIndex = url;
	  e->data->_next = NULL;
	  
	  e->next = buckets[h];
	  buckets[h] = e;
	  //return false; // Have to return a index later here
	  return url;
  }
  
  Data list = e->data;
  
  while(5 ==5)
  {
	if(list == NULL)
	{
		break;
	}

	if(list->_urlRecordIndex == url)
	{
		return list->_urlRecordIndex;
	}
	
	if(list->_next == NULL)
	{
		break;
	}
	
	list = list->_next;
  }
  
  
  Data newList = (Data) malloc(sizeof(Data));
  
  list->_next = newList;
  newList->_urlRecordIndex = url;
  newList->_next = NULL;
  
  return newList->_urlRecordIndex;
}


template <typename Data>
HashTableEntry<Data> * HashTable<Data>::getWord(int index)
{	
  return buckets[index];
}
