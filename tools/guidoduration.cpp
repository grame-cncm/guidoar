
#ifdef WIN32
# pragma warning (disable : 4786)
# define basename(name)	(name)
# define _CRT_SECURE_NO_DEPRECATE
#else 
# include <libgen.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "libguidoar.h"

using namespace std;
using namespace guido;

//#define debug

//_______________________________________________________________________________
static void usage(char * name)
{
	cerr << "usage: " << basename(name) << " <score> <duration | mult | dscore>"  << endl;
	cerr << "       stretch a score duration"  << endl;
	cerr << "       score: the input file or '-' to read stdin"  << endl;
	cerr << "       duration: the target duration expressed as a rational (where 1 is a whole note),"  << endl;
	cerr << "       mult: a non null multiplier expressed as a float value in the form of 'x<float number>',"  << endl;
	cerr << "       dscore: a score file used as a target duration"  << endl;
	exit (1);
}

//_______________________________________________________________________________
static void readErr (const char * file) 
{
	cerr << "failed to read '" << file << "'" << endl;
	exit(1);
}

//_______________________________________________________________________________
static float floatArg (const char* str) 
{
	float num=0;
	int n = sscanf(str, "x%f", &num);
	if (n != 1) num = -1.0f;
	return num;
}

//_______________________________________________________________________________
static bool durArg (const char* str, int* num, int* denom) 
{
	int n = sscanf(str, "%d/%d", num, denom);
	return n == 2;
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
#ifdef debug
	argc = 3;
	char * args[] = {"test.gmn", "x2", 0};
	char ** argsPtr = args;
#else
	if (argc != 3) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	
	garErr err;
	int num, denom;

	char *buff = strcmp(argsPtr[0],"-") ? guidoread(argsPtr[0]) : guidoread(stdin);
	if (!buff) readErr(argsPtr[0]);

	float ratio = floatArg(argsPtr[1]);
	if (ratio > 0) {
		err = guidoMultDuration(buff, ratio, cout);
	}
	else if (durArg (argsPtr[1], &num, &denom)) {
		err = guidoSetDuration(buff, rational(num, denom), cout);
	}
	else {
		char *gmn = guidoread(argsPtr[1]);
		if (!gmn) readErr(argsPtr[1]);
		err = guidoSetDuration(buff, gmn, cout);
		delete[] gmn;
	}
	delete[] buff;


	switch (err) {
		case kInvalidArgument:
			cerr << "invalid gmn file" << endl;
			break;
		case kOperationFailed:
			cerr << "duration operation failed" << endl;
			break;
		default:
			break;
	}
	return 0;
}
