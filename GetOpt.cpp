#include <stdafx.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <SysInfo\GetOpt.h>
#include <iostream>
#include <fstream>
using namespace std;

const char Option = '-';

extern "C"
{
	int   optind  = 1;    //option index
	char* optarg;         //option arg
	int   opterr  = 1;    //option error
}

int OptGetError(char command)
{
	optarg = NULL;
	errno  = EINVAL;
	optind++;
    if(opterr)
       cout << "error in command line : " << command << endl;;
    return ('?');
}

int getopt(int argc, char *argv[], const char *OptionStr)
{
	unsigned char ch;
	char *lpOpt;

	char *lpIndex = NULL;
	optarg = NULL;

	if(argc > optind)
	{
		if(lpIndex == NULL)
		{			
			lpIndex = argv[optind];
			if( (lpIndex == NULL) || *(lpIndex++) != Option )
				return EOF;
		}

		if((ch = *(lpIndex++)) == '\0') //"-" --> end.
			return EOF;
		
		//Error checking.
		if( ':' == ch || (lpOpt = (char*)strchr(OptionStr, ch)) == NULL)
			return OptGetError(ch);

		//Got valid data.
		if(':' == *(++lpOpt))
		{			
			optind++;
			
			if('\0' == *lpIndex)
			{// parameter is in next argument
				if(argc <= optind)
				{
					cout << "Need parameter of command : " << ch << endl;
					return OptGetError(ch);
				}
			
				lpIndex = argv[optind++];
			}

			optarg = lpIndex;
			lpIndex = NULL;
		}
		else
		{// Option needs no parameter.
			if('\0' == *lpIndex)
			{//next 
				optind++;
				lpIndex = NULL;
			}
			optarg = NULL;
		}

		return ch;
	}	

	return EOF;
}

#ifdef _DEBUG
void TestGetOpt(int argc, char *argv[])
{
	char c;
	while((c = getopt(argc, argv, "abf:")) != -1)
	{
		switch(c)
		{
			case 'a':
				cout << "Get option a" << endl;
			break;
			
			case 'b':
				cout << "Get option b" << endl;
			break;

			case 'f':
				cout << "Get File Name : " << optarg << endl;
			break;

			case ':':
				cout << "need parameter : " << endl;
			break;

			case '?':
				cout << "Unknown command" << endl;
			break;
		}
	}
}
#endif //_DEBUG
