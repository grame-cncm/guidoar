
#ifdef WIN32
# pragma warning (disable : 4786)
# define basename(name)	(name)
# define _CRT_SECURE_NO_DEPRECATE
#else 
# include <libgen.h>
#endif

#include <iostream>
#include <stdio.h>

#include "AROthers.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "etailOperation.h"

using namespace std;
using namespace guido;

//#define debug

//_______________________________________________________________________________
static void usage(char * name)
{
	cerr << "usage: " << basename(name) << " <score> <evIndex | dscore>"  << endl;
	cerr << "       cut a score before a given event"  << endl;
	cerr << "       score: the input file or '-' the read stdin"  << endl;
	cerr << "       evIndex: index of the cut point event (1 based),"  << endl;
	cerr << "       dscore: a score file used as duration specifier"  << endl;
	exit (1);
}

//_______________________________________________________________________________
static SARMusic read (const char* file) 
{
	guidoparser r;
	SARMusic score;
	if (!strcmp(file, "-"))
		score = r.parseFile(stdin);
	else
		score = r.parseFile(file);
	if (!score) {
		cerr << file << ": read failed"  << endl;
		exit (1);
	}
	return score;
}

//_______________________________________________________________________________
static int numArg (const char* vi) 
{
	int num=0;
	int n = sscanf(vi, "%d", &num);
	if (n != 1) num = -1;
	return num;
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
#ifdef debug
	argc = 3;
	char * args[] = {"bach.gmn", "4", 0};
	char ** argsPtr = args;
#else
	if (argc != 3) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	SARMusic score = read (argsPtr[0]);
	etailOperation tail;
	Sguidoelement result;

	int index = numArg (argsPtr[1]);
	if (index > 0) {
		result = tail(score, index-1);
	}
	else {
		SARMusic dscore = read (argsPtr[1]);
		result = tail(score, dscore);
	}
	if (result) cout << result << endl;
	return 0;
}
