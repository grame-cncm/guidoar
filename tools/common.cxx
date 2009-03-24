

#ifdef WIN32
# pragma warning (disable : 4786)
# define basename(name)	(name)
# define _CRT_SECURE_NO_DEPRECATE
#else 
# include <libgen.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "libguidoar.h"

using namespace std;
using namespace guido;


//_______________________________________________________________________________
float floatArg (const char* str, float nofloat) 
{
	float num=0;
	int n = sscanf(str, "x%f", &num);
	if (n != 1) num = nofloat;
	return num;
}

//_______________________________________________________________________________
int intArg (const char* str, int noint)  
{
	int num=0;
	int n = sscanf(str, "%d", &num);
	if (n != 1) num = noint;
	return num;
}

//_______________________________________________________________________________
bool rationalArg (const char* str, int* num, int* denom)  
{
	int n = sscanf(str, "%d/%d", num, denom);
	return n == 2;
}

//_______________________________________________________________________________
void readErr (const char * file) 
{
	cerr << "failed to read '" << file << "'" << endl;
	exit(1);
}

//_______________________________________________________________________________
void checkErr (garErr err, const char* operation) 
{
	switch (err) {
		case kInvalidArgument:
			cerr << "invalid gmn file" << endl;
			break;
		case kOperationFailed:
			cerr << operation << " operation failed" << endl;
			break;
		default:
			break;
	}
}

//_______________________________________________________________________________
static char * readgmn (const char * file) 
{
	char *buff = strcmp(file,"-") ? guidoread(file) : guidoreadfd(stdin);
	if (!buff) readErr(file);
	return buff;
}
