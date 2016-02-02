#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
#include "openhttp.h"
#include "webcrawler.h"

void mainFormat(int x);
void input(int choice);
void newLine();
void link(char *url);
void store100();
void removeScript();
// Add your implementation here

URLRecord *record = new URLRecord();

//int hello = 0;
int counter = 0;

using namespace std;

WebCrawler::WebCrawler(int maxUrls, int nurlRoots, const char ** urlRoots)
{
	int i =0;
	int p =0;
	int np = 0;
	_maxUrls = maxUrls;
	_urlArray = (URLRecord *)malloc(maxUrls * sizeof(URLRecord));
	char ch;
	
	_headURL = 0;
	_tailURL = nurlRoots;
	
	_urlToUrlRecord = new HashTable<int>();
	_wordToURLRecordList = new HashTable<URLRecordList *>();

	for(i=0;i<nurlRoots;i++)
	{
		char * ext = (char*)urlRoots[i];

		char contentType[ MaxLineLength ];
		
		
		FILE *f = openhttp(ext, contentType );
		
		if ( f == NULL ) 
		{
			exit(1);
		}
		
		FILE *temp = fopen("store.txt" , "w");
		
		char line[ MaxLineLength ];	
		
		
		while ( fgets( line, MaxLineLength, f ) ) 
		{  			
			fputs( line, temp);
		}
		
		fclose( f );
		fclose(temp);	
		
		if (ext == NULL )
		{
			exit(1);
		}	
		removeScript();
		input(1);
		
		
		
		record->_url = (char *)urlRoots[i];
		
		store100();


		FILE *st = fopen("100.txt" , "r");

		char *s = (char *)malloc(counter*sizeof(char));

		ch = fgetc(st);

		int j = 0;

		while(ch != EOF)
		{
			s[j] = ch;
			j++;
			ch = fgetc(st);
		}
		fclose(st);
		record->_description = s;

		_urlArray[i] = *(record);
		//printf("%s\n" , _urlArray[p]._url);
		//p++;
	}
	 crawl();
}
void store100()
{
	char ch;
	counter = 0;   // Global Variable counter, counting the number of characters in the file

	FILE *data = fopen("final words.txt" , "r");
	FILE *des = fopen("100.txt" , "w");


	int flags = 0;
	ch = fgetc(data);

	while(ch != EOF)
	{
		counter++;

		if(ch == EOF)
		{
			fclose(data);
			fclose(des);
			break;
		}

		if(ch == ' ')
		{
			flags++;
		}

		fputc(ch, des);

		if(flags >=99)
		{
			fclose(data);
			fclose(des);
			break;
		}

		ch = fgetc(data);
	}

	fclose(data);
	fclose(des);
}

void WebCrawler::crawl()
{
	 int i,j = 0;
	 char sto[MaxLineLength];
	 int count = 0;
	 int hello = 0;
	 char *no;
	 int k = 0;
	 int q = 0;
	 int check = 0;
	 bool c;

	URLRecord *record1 = new URLRecord();
	bool e;
	char ch;
	 
	int num = 0; // Check to skip the .pdf files..

	char contentType[ MaxLineLength ];
	char line[ MaxLineLength ];
	char line2[MaxLineLength];
	
	for(i=0;i<_tailURL;i++)
	{
		if(_urlToUrlRecord->find(_urlArray[i]._url, &_headURL))
		{
		  printf("URL is already in hash table\n");
		  continue;
		}
		else
		{
			e = _urlToUrlRecord->insertItem(_urlArray[i]._url, i);
		}
	}
	
		int con = _tailURL;
		
	 for(i=0;i<con;i++)
	 {
		char *ext = _urlArray[i]._url;
		link(ext);
		
		ifstream in;
		in.open("final url.txt" , ios::in);

		if(in == NULL)
		{
			cout<<"Null in final url.txt";
			exit(0);
		}

		while(in.getline(line2, MaxLineLength))
		{
			URLRecord *newRecord = new URLRecord();
			 char *storage;

			no = (char *)line2;
			
			int l = strlen(no);

			if(no[l-1] == 'f' && no[l-2] == 'd' && no[l-3] == 'p') // Check to skip the pdf files
			{
				cout<<"pdf File\n\n\n";
				num = 1;
			}
			
			if(num!=1)
			{
				//count++; // This value will be added in tail url to get total URL's
				
				storage = (char *)line2;

				FILE *f = openhttp(storage, contentType);
				//printf("%x\n" , f);
				
				if ( f == NULL )
				{
					//exit(1);
					//cout<<"Trash"<<endl;
					hello = 1;
					continue;
				}
				
				FILE *temp = fopen("store.txt" , "w");
				
				while ( fgets( line, MaxLineLength, f ) )
				{
					fputs( line, temp);
				}
				
				fclose( f );
				fclose(temp);
				
				if(hello!=1 && num!=1)
				{
					removeScript();
					input(1);
					store100();
				}
				
				FILE *st = fopen("100.txt" , "r");
				
				char *s = (char *)malloc(counter*sizeof(char));
				
				ch = fgetc(st);
				
				int j = 0;
				
				while(ch != EOF)
				{
					s[j] = ch;
					j++;
					ch = fgetc(st);
				}
				fclose(st);
						
				
				if(_tailURL>_maxUrls)
				{
					cout<<"Reached max\n";
					break;
				}
				
				char *p  = strdup(line2);
				
				newRecord->_url = p;
				newRecord->_description = s;
	

				_urlArray[_tailURL] = *(newRecord);




				if(_urlToUrlRecord->find(_urlArray[_tailURL]._url, &_headURL))
				{
				  printf("URL is already in hash table\n");
				  continue;
				}

				else
				{
					e = _urlToUrlRecord->insertItem(_urlArray[_tailURL]._url, _tailURL);
					_tailURL++;
				}

				if(f!=NULL)
				{
					hello = 0;
				}

			}
			num = 0;
		}

		cout<<"_TailURL-->"<<_tailURL<<endl;

	 }
					
		uToFile();


	
	 char store[100];
	 int newCheck = 0;
	 char *currentWord;
	 char *store1;
	 int t = 0;
	 int ba,ca = 0;

	int lineCounter = 0;
	URLRecordList *head;
	URLRecordList *entryNode;
	int currentIndex;
	
	for(i=0;i<_tailURL;i++)
	{
		char *array = strdup(_urlArray[i]._url);
		char *desc = strdup(_urlArray[i]._description);
		//int desLength = strlen(desc);
		
		URLRecordList * tempNode = NULL;
		
		currentWord = new char[100];
		
		store1 = (char *) malloc(sizeof(char)* 10000);		
		
		store1 = strtok (desc, " ");
		
		//currentWord = store1;
		//currentWord[strlen(currentWord)] = '\0';
		
		store1 = strtok (NULL, " ");

		while(store1 != NULL)
		{
			URLRecordList * recordWord = new URLRecordList();
			
			
			if(_wordToURLRecordList->find((const char *)store1, &recordWord))
			{
				_wordToURLRecordList->insertItem2((const char *) store1, i);
			}
			else
			{
				_wordToURLRecordList->insertItem2((const char *) store1, i);
				
				delete(recordWord);
			}
			
			
			store1 = strtok (NULL, " ");
		}
		
		free(store1);
	}
		
	wToFile();
	/*
	//cout<<"Ab is:"<<ab<<endl;
	//cout<<"ba is:"<<ba<<endl;
	//cout<<"ca is:"<<ca<<endl;
	//cout<<"i is:"<<i<<endl;
	*/
}



void WebCrawler::uToFile()
{
	ofstream out;
	
	out.open("url.txt" , ios::out);
	
	for(int i = 0; i<_tailURL;i++)
	{
		out<<i;
		out<<" ";
		out<<_urlArray[i]._url<<endl;
		out<<_urlArray[i]._description<<endl<<endl;
	}
	
	out.close();
}
	
void WebCrawler::wToFile()
{
	int count = 0;
	
	ofstream out;
	
	out.open("word.txt" , ios::out);
	
	for(int i = 0;i<2039;i++) // 2039 is the table size in the hash table
	{
		HashTableEntry<URLRecordList *> *e = _wordToURLRecordList->getWord(i);		
		
		while(e!=NULL)
		{
			URLRecordList *list = new URLRecordList();
			list = e->data;
			
			out<<e->key<<" ";
			//count++;
				
			while(list!=NULL)
			{
				out<<list->_urlRecordIndex<<" ";
				list = list->_next;
			}
			
			out<<endl;
			
			e = e->next;
		}
		
	}
	//cout<<"the count is"<<count<<endl;
	out.close();
}

void mainFormat(int x)
{
	int newCounter = x;
	char c;
	char eat;
	int extra;



		if(newCounter==1)//Making here the main formatting... Need to change the if condition here later on..
		{
			FILE *data = fopen("new.txt" , "r");
			FILE *collect = fopen("arjun.txt" , "w");

			while(1)
			{
				c = fgetc(data);

				if(c == EOF)
				{
					fclose(data);
					fclose(collect);
					break;
				}

				if(c==' ')
				{
					eat=fgetc(data);

					while((eat=='\t') || (eat=='\n') || (eat==' '))
					{
						if(eat=='\n')
						{
							extra++;
						}

						eat=fgetc(data);
					}

					if(extra>2)
					{
						fputc(' ' , collect);
						extra=0;
					}

					else
					{
						fputc(c,collect);

						extra = 0;
					}

					fputc(eat,collect);

				}
				else if(c=='\t')
				{
					eat=fgetc(data);

					while((eat=='\t') || (eat=='\n') || (eat==' '))
					{
						if(eat=='\n')
						{
							extra++;
						}
						eat=fgetc(data);
					}

					if(extra>=2)
					{
						fputc(' ' , collect);
						extra = 0;
					}

					else
					{
						extra = 0;
					}

					fputc(eat , collect);

				}
				else
				{
					fputc(c,collect);
				}
			}



			fclose(data);
			fclose(collect);
	}



		if(newCounter==2)
		{
			FILE *data = fopen("newLine.txt" , "r");
			FILE *collect = fopen("final words.txt" , "w");


			while(1)
			{
				c = fgetc(data);

				if(c == EOF)
				{
					fclose(data);
					fclose(collect);
					break;
				}

				if(c==' ')
				{
					eat=fgetc(data);

					while((eat=='\t') || (eat=='\n') || (eat==' '))
					{
						if(eat=='\n')
						{
							extra++;
						}

						eat=fgetc(data);
					}

					if(extra>2)
					{
						fputc(' ' , collect);
						extra=0;
					}

					else
					{
						fputc(c,collect);
						extra = 0;
					}

					fputc(eat,collect);

				}


				else
				{
					fputc(c,collect);
				}
			}
		}
}

void newLine()
{

	char c;
	char eat;

	int counter = 0;
	int check1;


	FILE *data = fopen("arjun.txt" , "r");
	FILE *storage = fopen("newLine.txt" , "w");


	while(1)
	{

		check1++;

		c = fgetc(data);

		if(c == EOF)
		{
			fclose(data);
			fclose(storage);
			//exit(0);
			break;
		}

		if (c == '\n')
		{

			eat = fgetc(data);

			while (eat == '\n' || eat == '\t' || eat == ' ')
			{
				if (eat == '\n')
				{
					counter = 5;
				}

				if (eat != EOF)
				{
					eat = fgetc(data);
				}

				if(eat == EOF)
				{
					//exit(0);
					break;
				}
			}

			if (counter == 5)
			{
				fputc(' ' , storage);
				//printf("I am Counter...!!!\n");
				counter = 0;
			}


				if(eat == '\r')
					fputc(' ' , storage);
				if(eat!='\r')
				fputc(eat,storage);
		}

		else
		{
			if(c!=EOF && c!='\r')
			{
				fputc(c,storage);
			}
		}
	}

		fclose(data);
		fclose(storage);
}


void link(char *url)
{
	char ch;

	FILE *world = fopen("store.txt" , "r");

	FILE *ud = fopen("store url.txt" , "w");

	if(ud == NULL)
	{
		cout<<"No URL Found on the page\n";
		exit(0);
	}

	
	char eat; // eating extra characters in URL
	
	int check = 0; // for URL only
	int check1 = 0;
	
	while(1)
	{
		ch = fgetc(world);
		

		if(ch=='<')
		{
			check1 = 1;
		}

		if(ch == EOF)
		{
			fclose(world);
			fclose(ud);
			break;
		}

		if(ch == 'a')
		{
			ch = fgetc(world);

			if(ch == ' ')
			{
				
				eat = fgetc(world);


				if(eat == 'h')
				while(eat != '=' )
				{
					eat = fgetc(world);
					check = 1;
				}


				eat = fgetc(world);
				eat = fgetc(world);

				if((check == 1) && ((eat == 'h') || (eat == '/')))
				{
					ch = fgetc(world);
					fputc(eat,ud);

					
					while(ch != '"')
					{
						fputc(ch,ud);
						ch = fgetc(world);
					}


					fputc('\n' , ud);
				}
			}
		}
		check1 = 0;
	}
	
	fclose(world);
	fclose(ud);

	char line[MaxLineLength];
	string str;
	ifstream in;
	ofstream out;

	out.open("final url.txt" , ios::out);

	in.open("store url.txt" , ios::in);

	if(in == NULL)
	{
		exit(0);
	}

	while(in)
	{
		in.getline(line,MaxLineLength);

		if(line[0] == '/')
		{
			str = line;
			out<<url<<str;
			out<<endl;
			//p++;
		}

		else
		{
			out<<line<<endl;
		}
	}
	//cout<<p;
	in.close();
	out.close();
}



void removeScript()
{
	char line[MaxLineLength];
	ifstream in;
	in.open("store.txt" , ios::in);
	int count;
	int counter;
	int check = 0;

	char eat;

	ofstream out;
	out.open("remove.txt" , ios::out);

	while(in.getline(line,MaxLineLength))
	{
		for(int i = 0;i<strlen(line);i++)
		{
			if(line[i] == '<'  && line[i+1] == 's' && line[i+2] == 'c')
			{
				check = 1;
			}

				for(int j=0;j<strlen(line);j++)
				{
					if(line[j] == '<' && line[j+1] =='/' && line[j+2] == 's' && line[j+3] == 'c')
					{
						//cout<<"I am In...!\n";
						check = 0;
					}
				}
		}

		if(check == 0)
		{
			out<<line;
			out<<endl;
		}
	}

	in.close();
	out.close();

}

void input(int choice)
{
	char ch;

	int j = 0;
	int count = 0;
	int lineCounter = 0;
	int scrCount = 0;
	char eat;


	if(choice==1)
	{
		FILE *data = fopen("remove.txt" , "r");
		FILE *newData = fopen("new.txt" , "w");

		while(1)
		{
			ch = fgetc(data);


			if(ch==EOF)
			{
				fclose(data);
				fclose(newData);
				break;
			}

			else if(ch=='&')
			{
				ch = fgetc(data);

				do
				{
					ch = fgetc(data);
				}while(ch!=';');
			}


			else if(ch=='<')
			{
				ch = fgetc(data);


				if(ch=='!')
				{
					count = 1;

					while(ch!='>' && count==1)
					{
						ch = fgetc(data);
					}
				}
				/*
				if(ch=='>')
				{
					ch = fgetc(data);
				}
*/

				while(ch!='>')
				{
					ch = fgetc(data);
				}


				fputc(' ' , newData);

				if(ch=='h')                         //removing head of the page
				{
					ch = fgetc(data);

					while(ch!='>')
					{
						ch = fgetc(data);
					}

				}
				
			}

			if(ch!='>' && ch!=';' && ch!='}' && ch!='{' && ch!='*' && ch!='^' && ch!='/' && ch!='#' && ch!='%')
			{
					fputc(ch,newData);// if it doesn't go in if then simply print it out....!
			}

		}

		fclose(data);
		fclose(newData);


		mainFormat(1);
		newLine();
		mainFormat(2);
	}
}
int main( int argc, char ** argv )
{	
	
	WebCrawler *crawls;
	
	int position = 0;
	
	
	if(argc == 1)
	{
		printf("No Argument Passed..!\n");
		printf("Program Exiting\n");
		exit(0);
	}
	
	
	argv++;
	int hello = 0;
	int max;
	
	int flag = argc;
	
	// Process the arguments
	
	int i = 0;
	

	if(!strcmp(*argv, "-u"))
	{
		position = 1;
		argv++;
		flag = flag - 2;
	}
	
	

	if(position == 1)
	{
		
		if(!(argv[0][0] == 'h'))
		{
			flag--;
			max = atoi(argv[0]);
			argv++;
		}
		
			WebCrawler *crawls = new WebCrawler(max,flag, (const char **) argv);
		
	}
	
	
	if ( *argv == NULL )
	{
		// Print usage also if no URL after the arguments
		//printUsage();
		printf("Hello\n");
		exit(1);
	}
	
}
