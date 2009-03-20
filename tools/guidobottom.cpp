
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

//#define debug

//_______________________________________________________________________________
static void usage(char * name)
{
	cerr << "usage: " << basename(name) << " <score> <voicenum | vscore>"  << endl;
	cerr << "       cut a score after a given duration"  << endl;
	cerr << "       score: the input file or '-' to read stdin"  << endl;
	cerr << "       voicenum: number of voices to preserve,"  << endl;
	cerr << "       vscore: a score file used as voice specifier"  << endl;
	exit (1);
}

//_______________________________________________________________________________
static int voiceArg (const char* vi) 
{
	int num=0;
	int n = sscanf(vi, "%d", &num);
	if (n != 1) num = -1;
	return num;
}

//_______________________________________________________________________________
static void readErr (const char * file) 
{
	cerr << "failed to read '" << file << "'" << endl;
	exit(1);
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
#ifdef debug
	argc = 3;
	char * args[] = {"moz581.gmn", "2", 0};
	char ** argsPtr = args;
#else
	if (argc != 3) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	garErr err;
	char * buff;
	if (!strcmp(argsPtr[0], "-"))
		buff = guidoread(stdin);
	else
		buff = guidoread(argsPtr[0]);
	if (!buff) readErr(argsPtr[0]);

	int nvoices = voiceArg (argsPtr[1]);
	if (nvoices > 0) {
		err = guidoBottom(buff, nvoices, cout);
	}
	else {
		char* gmn = guidoread(argsPtr[1]);
		if (!gmn) readErr(argsPtr[1]);
		err = guidoBottom(buff, gmn, cout);
		delete[] gmn;
	}
	delete[] buff;

	switch (err) {
		case kInvalidArgument:
			cerr << "invalid gmn file" << endl;
			break;
		case kOperationFailed:
			cerr << "bottom operation failed" << endl;
			break;
		default:
			break;
	}
	return err;
}
