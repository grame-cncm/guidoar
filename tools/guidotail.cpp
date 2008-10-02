
#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <stdio.h>
#include <libgen.h>

#include "AROthers.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "tailOperation.h"

using namespace std;
using namespace guido;

//#define debug

//_______________________________________________________________________________
static void usage(char * name)
{
	cerr << "usage: " << basename(name) << " <file> <duration>"  << endl;
	cerr << "       cut a score after a given duration"  << endl;
	cerr << "       file: the input file or '-' the read stdin"  << endl;
	cerr << "       duration: the score duration to preserve,"  << endl;
	cerr << "                 expressed as a non null rational where 1 is a whole note"  << endl;
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
static rational durationArg (const char* dur) 
{
	int num=0, denum=0;
	int n = sscanf(dur, "%d/%d", &num, &denum);
	if (n == 2)
		return rational( num, denum);
	if (n == 1) {
		if (num)	return rational( num, 1);
		if (denum)	return rational( 1, denum);
	}
	return rational (0,0);
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
	rational duration = durationArg (argsPtr[1]);
	if (!duration.getNumerator()) usage(argv[0]);

	SARMusic score = read (argsPtr[0]);
	tailOperation tail;
	Sguidoelement result = tail(score, duration);
	if (result) cout << result << endl;
	return 0;
}
