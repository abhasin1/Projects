#include<iostream>
#include <string.h>
#include "search-engine.h"
#include "webcrawl.h"
#include<fstream>
#include <sys/time.h>


using namespace std;

SearchEngine::SearchEngine( int port, DictionaryType dictionaryType): MiniHTTPD(port)
{
	// Create dictionary of the indicated type -->> DONE
	
	// Populate dictionary and sort it if necessary

	if(dictionaryType == ArrayDictionaryType)
	{
		_wordToURLList = new ArrayDictionary();
	}

	else if(dictionaryType == HashDictionaryType)
	{
		_wordToURLList = new HashDictionary();
	}

	else if(dictionaryType == AVLDictionaryType)
	{
		_wordToURLList = new AVLDictionary();
	}
	
	else if(dictionaryType == BinarySearchDictionaryType)
	{
		_wordToURLList = new BinarySearchDictionary();
	}
	
	
	char temp[10000];
	int lineCounter = 0;
	nurls = 0;
	int chCounter = 0; //number of characters
	int index = 0; // counting the url's
	char *setUrl;
	char *store;
	char *des;
	
	char *store1;
	
	char *currentWord;
	int currentIndex = 0;
	URLRecordList *head;
	URLRecordList *node;
	
	ifstream wFile("word.txt"); // Reading the word file
	ifstream uFile("url.txt"); // Reading the URL file
	
	while(uFile.getline(temp,1024))
	{
		lineCounter++;
	}
	
	nurls = lineCounter/3; //1st line is the url
	
	URLRecord *urlArray = (URLRecord *) malloc(sizeof(URLRecord)*nurls);
	
	lineCounter = 0;
	uFile.clear(); // clearing the file pointer
	uFile.seekg(0); // REsetting the file pointer
	
	//Fetching the data from the url file
	
	while(uFile.getline(temp,10000))
	{
		if(lineCounter==0)
		{
			setUrl = temp;
			setUrl = strtok(setUrl, " ");
			setUrl = strtok(NULL, " ");
			
			int len = strlen(setUrl);
			
			store = (char *) malloc(sizeof(char)*len);
			
			for(chCounter=0;chCounter<len;chCounter++)
			{
				store[chCounter] = setUrl[chCounter];
			}
			
			store[chCounter] = '\0';
			urlArray[index]._url = store;
			lineCounter++;
		}
		
		else if(lineCounter == 1)
		{
			int len1;
			len1 = strlen(temp);
			
			des = (char *) malloc(sizeof(char) * len1);
			
			for(chCounter = 0; chCounter<len1;chCounter++)
			{
				des[chCounter] = temp[chCounter];
			}
			des[chCounter] = '\0';
			urlArray[index]._description = des;
			lineCounter++;
		}
		
		else
		{
			lineCounter = 0;
			index++;
		}
	}
	
	//Fetching word.txt to url list
	
	int wCount = 0;

	while(wFile.getline(temp,10000))
	{
		currentWord = new char[100];

		head = NULL;
		URLRecordList * tempNode = NULL;

		store1 = strtok (temp, " ");
		currentWord = store1;
		currentWord[strlen(currentWord)] = '\0';

		store1 = strtok (NULL, " ");
		
		while(store1 != NULL)
		{
			node = new URLRecordList;
			currentIndex = atoi(store1);

			node->_urlRecord = &urlArray[currentIndex];
			node->_next = NULL;

			if (head == NULL)
			{
				head = node;
				tempNode = head;
			}
			else
			{
				tempNode->_next = node;
				tempNode = node;
			}

			store1 = strtok (NULL, " ");
		}
		

		_wordToURLList->addRecord((const char *)currentWord , (URLRecordList *) head);

	}

}

void SearchEngine::dispatch( FILE * fout, const char * documentRequested )
{
	if (strcmp(documentRequested, "/")==0)
	  {
	    // Send initial form
	    fprintf(fout, "<TITLE>CS251 Search</TITLE>\r\n");
	    fprintf(fout, "<CENTER><H1><em>GRABB Search</em></H1>\n");
	    fprintf(fout, "<H2>\n");
	    fprintf(fout, "<FORM ACTION=\"search\">\n");
	    fprintf(fout, "Search:\n");
	    fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
	    fprintf(fout, "</H2>\n");
	    fprintf(fout, "</FORM></CENTER>\n");
	    return;
	  }

	int numberOfWords = 0; // Counter for total number of words for search
	char * store1;
	int wCount = 0; // word counter.
	int chCount = 0; // character counter.
	int rCount = 0; // result counter.
	URLRecordList * temp;
	
	hrtime_t startTime;
	hrtime_t endTime;
	startTime = gethrtime(); // start time counter

	while(documentRequested[wCount] != '\0')
	{
		if(documentRequested[wCount] == '+')
		{
			numberOfWords++;
		}

		wCount++;
	}
	
	char * words = (char *)malloc(numberOfWords * (sizeof(char) * 50));

	store1 = strtok ((char *)documentRequested, "=+");
	store1 = strtok (NULL, "+");

	URLRecord * output = NULL;
	
	while (store1 != NULL)
	{
		for(int i = 0; store1[i] != '\0'; i++)
		{
			words[chCount] = store1[i];
			chCount++;
		}
		
		words[chCount] = ' ';
		chCount++;
		temp = (URLRecordList *)_wordToURLList->findRecord(store1);
		
		if (temp == NULL && output != NULL)
		{
			delete[] output;
			output = NULL;
			rCount = 0;
			break;
		}
		else if (temp != NULL)
		{
			if (output == NULL)
			{
				output = (URLRecord *)malloc(sizeof(URLRecord) * nurls);

				while (temp != NULL)
				{
					output[rCount] = * temp->_urlRecord;
					rCount++;
					temp = temp->_next;
				}
			}
			else
			{
				URLRecord * newOutput = (URLRecord *)malloc(sizeof(URLRecord) * nurls);
				int newCounter = 0;

				while (temp != NULL)
				{
					bool located = false;

					for(int i = 0; i < rCount; i++)
					{
						if (!strcmp(temp->_urlRecord->_url, output[i]._url))
						{
							located = true;
						}
					}

					if (located)
					{
						newOutput[newCounter] = *temp->_urlRecord;
						newCounter++;
					}

					temp = temp->_next;
				}

				delete[] output;
				output = newOutput;
				rCount = newCounter;
			}
		}

		store1 = strtok (NULL, "+");
	}
	
	words[chCount - 1] = '\0'; // terminating null character at the end of the word.
	chCount = 0; // we have all the characters....resetting word count to zero.
	wCount = 0; // we have all the words....resetting word count to zero.
	endTime = gethrtime(); // end time counter.

	
	
	fprintf( stderr, "Search for words: \"%s\"\n", words);
	fprintf(fout, "<HR><h4>Search Executed in %d nanoseconds</h4><br><H2>\n", (long)endTime - (long)startTime);
	fprintf( fout, "<TITLE>Search Results</TITLE>\r\n");
	fprintf( fout, "<H1> <Center><em>GRABB Search</em></H1>\n");
	fprintf( fout, "<H2> Search Results for \"%s\"</center></H2>\n", words );

	
	for ( int i = 0; i < rCount; i++ )
	{
		fprintf( fout, "<h2>%d. <a href=\"%s\">%s</a></h2>\n", i+1, output[i]._url, output[i]._url );
		fprintf( fout, "<h3><blockquote border=\"1\">%s<p></blockquote>\n",output[i]._description);
	}

	// Add search form at the end
	  fprintf(fout, "<HR><H2>\n");
	  fprintf(fout, "<FORM ACTION=\"search\">\n");
	  fprintf(fout, "Search:\n");
	  fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
	  fprintf(fout, "</H2>\n");
	  fprintf(fout, "</FORM>\n");

	
}

void printUsage()
{
	const char * usage =
	"Usage: search-engine port (array | hash | avl | bsearch)\n"
	"  It starts a search engine at this port using the\n"
	"  data structure indicated. Port has to be larger than 1024.\n";
	
	fprintf(stderr, usage);
}

int main(int argc, char ** argv)
{
	if (argc < 3) {
		printUsage();
		return 1;
	}
	
	// Get port
	int port;
	sscanf( argv[1], "%d", &port);
	
	// Get DictionaryType
	const char * dictType = argv[2];
	DictionaryType dictionaryType;
	if (!strcmp(dictType, "array")) {
		dictionaryType = ArrayDictionaryType;
	}
	else if (!strcmp(dictType, "hash")) {
		dictionaryType = HashDictionaryType;
	}
	else if (!strcmp(dictType, "avl")) {
		dictionaryType = AVLDictionaryType;
	}
	else if (!strcmp(dictType, "bsearch")) {
		dictionaryType = BinarySearchDictionaryType;
	}
	else {
		printUsage();
		return 0;
	}
	
	SearchEngine httpd(port, dictionaryType);
	
	httpd.run();
	
	return 0;
}
