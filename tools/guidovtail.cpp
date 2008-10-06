
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
#include "vtailOperation.h"

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
static int voiceArg (const char* vi) 
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
	char * args[] = {"moz581.gmn", "2", 0};
	char ** argsPtr = args;
#else
	if (argc != 3) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	SARMusic score = read (argsPtr[0]);
	vtailOperation tail;
	Sguidoelement result;

	int nvoices = voiceArg (argsPtr[1]);
	if (nvoices > 0) {
		result = tail(score, nvoices);
	}
	else {
		SARMusic dscore = read (argsPtr[1]);
		result = tail(score, dscore);
	}
	if (result) cout << result << endl;
	return 0;
}
