
#ifdef WIN32
# pragma warning (disable : 4786)
# define basename(name)	(name)
#else 
# include <libgen.h>
#endif

#include <iostream>
#include <stdio.h>

#include "AROthers.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "vtailOperation.h"

using namespace std;
using namespace guido;

//#define debug

//_______________________________________________________________________________
static void usage(char * name)
{
	cerr << "usage: " << basename(name) << " <file> <voicenum>"  << endl;
	cerr << "       cut a score after a given duration"  << endl;
	cerr << "       file: the input file or '-' the read stdin"  << endl;
	cerr << "       voicenum: number of voices to preserve,"  << endl;
	exit (1);
}

//_______________________________________________________________________________
static void readErr(const char * name)
{
	cerr << name << ": read failed"  << endl;
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
	if (!score) readErr(file);
	return score;
}

//_______________________________________________________________________________
static rational voiceArg (const char* vi) 
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
	char * args[] = {"test.gmn", "1", 0};
	char ** argsPtr = args;
#else
	if (argc != 3) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	int nvoices = voiceArg (argsPtr[1]);
	if (nvoices < 0) usage(argv[0]);

	SARMusic score = read (argsPtr[0]);
	vtailOperation tail;
	Sguidoelement result = tail(score, nvoices);
	if (result) cout << result << endl;
	return 0;
}
