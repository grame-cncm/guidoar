
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
#include "headOperation.h"

using namespace std;
using namespace guido;

//#define debug

//_______________________________________________________________________________
static void usage(char * name)
{
	cerr << "usage: " << basename(name) << " <score> <duration | dscore>"  << endl;
	cerr << "       cut a score after a given duration"  << endl;
	cerr << "       score: the input file or '-' the read stdin"  << endl;
	cerr << "       duration: the score duration to preserve,"  << endl;
	cerr << "                 expressed as a non null rational where 1 is a whole note"  << endl;
	cerr << "       dscore: a score file used as duration specifier"  << endl;
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
	char * args[] = {"bach.gmn", "2/4", 0};
	char ** argsPtr = args;
#else
	if (argc != 3) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	SARMusic score = read (argsPtr[0]);
	headOperation head;
	Sguidoelement result;

	rational duration = durationArg (argsPtr[1]);
	if (duration.getNumerator()) {
		result = head(score, duration);
	}
	else {
		SARMusic dscore = read (argsPtr[1]);
		result = head(score, dscore);
	}
	if (result) cout << result << endl;
	return 0;
}
