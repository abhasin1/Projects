
#include "minihttpd.h"
#include "dictionary.h"
#include "array-dictionary.h"
#include "hash-dictionary.h"
#include "avl-dictionary.h"
#include "bsearch-dictionary.h"



// Types of dictionaries used
enum DictionaryType
{
  ArrayDictionaryType,
  HashDictionaryType,
  AVLDictionaryType,
  BinarySearchDictionaryType
};

// Inherits from MiniHTTPD
class SearchEngine : public MiniHTTPD
{
  Dictionary * _wordToURLList;
  int nurls; // FOr the count of total number of the urls
  
  // Add any other member variables you need
 public:
  // Constructor for SearchEngine
  SearchEngine( int port, DictionaryType dictionaryType);

  // Called when a request arrives
  void dispatch( FILE * out, const char * requestLine );

};



