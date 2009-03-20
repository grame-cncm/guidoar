
#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libguidoar.h"

using namespace std;
using namespace guido;

//#define debug

//_______________________________________________________________________________
static void usage(const char * name)
{
	cerr << "usage: " << name << " <file> <interval | pscore>"  << endl;
	cerr << "       transpose the input gmn files"  << endl;
	cerr << "       file    : the file to be transposed"  << endl;
	cerr << "                 use '-' for stdin input"  << endl;
	cerr << "       interval: the transposing interval"  << endl;
	cerr << "       pscore  : a score file used as a pitch specifier:"  << endl;
	cerr << "                 uses first voice, first note, lowest pitch."  << endl;
	exit (1);
}

//_______________________________________________________________________________
static void readErr (const char * file) 
{
	cerr << "failed to read '" << file << "'" << endl;
	exit(1);
}

//_______________________________________________________________________________
static int pitchArg (const char* vi) 
{
	int num=0;
	int n = sscanf(vi, "%d", &num);
	if (n != 1) num = 9999;
	return num;
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
#ifdef debug
	argc = 3;
	char * args[] = {"a.gmn", "2", 0};
	char ** argsPtr = args;
#else
	if (argc != 3) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif

	const char *file = argsPtr[0];
	char *buff = strcmp(file,"-") ? guidoread(file) : guidoread(stdin);
	if (!buff) readErr(file);

	garErr err = kNoErr;
	int steps = pitchArg (argsPtr[1]);
	if (steps < 9999) {
		err = guidoTranpose(buff, steps, cout);
	}
	else {
		char *gmn = guidoread(argsPtr[1]);
		if (!gmn) readErr(argsPtr[1]);
		err = guidoTranpose(buff, gmn, cout);
	}

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
	return 0;
}
