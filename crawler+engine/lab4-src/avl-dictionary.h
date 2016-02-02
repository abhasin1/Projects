#if !defined AVL_DICTIONARY_H
#define AVL_DICTIONARY_H



#include "dictionary.h"

struct AVLNode
{
    int height;
    KeyType key;
    DataType data;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;
};

class AVLDictionary : public Dictionary
{
	// Add any member variables you need
	AVLNode *root;

	public:
	// Constructor
	AVLDictionary();
  
	// Add a record to the dictionary. Returns false if key already exists
	bool addRecord( KeyType key, DataType record);
  
	// Find a key in the dictionary and return corresponding record or NULL
	DataType findRecord( KeyType key);

	// Add other methods you may need
	void restructure(AVLNode *node);
	
	bool removeElement(KeyType key);
   
   	KeyType *keys(int * n);
	
	void check();
	
	void print();
	
	void checkRecursive(AVLNode * node);
	
	void printNode(char * s, AVLNode * node, int depth);
	
	void preorder(AVLNode* temp);

};
#endif
