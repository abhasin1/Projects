/*
Copyright (c) 2004
Gustavo Rodriguez-Rivera
All rights reserved. 

This work was developed by the author(s) at Purdue University
during 2004.

Redistribution and use in source and binary forms are permitted provided that
this entire copyright notice is duplicated in all such copies.  No charge,
other than an "at-cost" distribution fee, may be charged for copies,
derivations, or distributions of this material without the express written
consent of the copyright holders. Neither the name of the University, nor the
name of the author may be used to endorse or promote products derived from
this material without specific prior written permission.

THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR ANY PARTICULAR PURPOSE.
*/

//
// gethttp:
//   Example program that shows how to use openttp.
//   It gets the URL passed as argument
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "openhttp.h"

#include<iostream>

using namespace std;

void printUsage()
{
	fprintf( stderr, "  Usage: gethttp [-h|-t|-a] url\n");
	fprintf( stderr, "  Example: gethttp http://www.cs.purdue.edu\n");
}

void printOutput(int p)
{
	ifstream in;

	if(p==2)
	{
		in.open("final url.txt",ios::in);
	}
	else if(p==1)
	{
		in.open("final words.txt" , ios::in);
	}

	char line[MaxLineLength];

	if(in == NULL)
	{
		cout<<"NULL Check";
		exit(0);
	}
	
	while(in)
	{
		in.getline(line,MaxLineLength);

		cout<<line<<endl;
	}
	in.close();
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
		FILE *data = fopen("store words.txt" , "r");
		FILE *collect = fopen("final words.txt" , "w");


		while(1)
		{
			c = fgetc(data);

			if(c == EOF)
			{
				fclose(data);
				fclose(collect);
				printOutput(1);
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
	FILE *storage = fopen("store words.txt" , "w");

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
void input(int choice , char *url)
{
	char ch;

	int j = 0;
	int count = 0;
	char eat;
	bool k = false;
	char line[MaxLineLength];


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


					//count = 0;
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


				fputc(' ' ,newData);

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

	else if(choice == 2 )
	{
		k = true;
		
		FILE *world = fopen("store.txt" , "r");
	
		FILE *ud = fopen("store url.txt" , "w");

		
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
				choice = 3;
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
	}

	if(k)
	{


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
		printOutput(2);
}
}


int main( int argc, char ** argv )
{
	
	if(argc == 1)
	{
		printf("No Argument Passed..!\n");
		printf("Program Exiting\n");
		exit(0);
	}
	// Skip command
	argv++;
	int hello = 0;
	int nice =0;
	
	// Process the arguments
	
	if(!strcmp(*argv, "-t"))
	{
		hello = 1;
		argv++;
	}
	
	if(!strcmp(*argv, "-a"))
	{
		hello = 2;
		argv++;
	}
	
	
	
	if ( !strcmp(*argv,"-h") )
	{
		printUsage();
		exit(1);
	}
	
	
	
	if ( *argv == NULL )
	{
		// Print usage also if no URL after the arguments
		printUsage();
		exit(1);
	}
	
	// Open URL
	char contentType[ MaxLineLength ];
	char * url = *argv;
	
	
	FILE * f = openhttp( url, contentType );
	
	FILE *temp = fopen("store.txt" , "w");
	
	if ( f == NULL ) 
	{
		exit(1);
	}
	
	
	// Print the content type
	printf( "Content Type: \"%s\"\n", contentType );
	
	// Print to stdout line by line
	
	
	char store[MaxLineLength];
	
	char now[MaxLineLength];
	
	
	char line[ MaxLineLength ];
	while ( fgets( line, MaxLineLength, f ) ) 
	{  			
		fputs( line, temp);
	}
	
	fclose( f );
	fclose(temp);
	
	if(hello==1)
	{
		removeScript();
		input(hello, url);

	}
	
	if(hello == 2)
	{
		input(hello,url);
	}
}


