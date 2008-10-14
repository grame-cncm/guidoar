
#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <inttypes.h>

#include "AROthers.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "transposeOperation.h"

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
static rational pitchArg (const char* vi) 
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
	SARMusic score = read (argsPtr[0]);
	transposeOperation trsp;
	Sguidoelement result;

	int steps = pitchArg (argsPtr[1]);
	if (steps < 9999) {
		result = trsp(score, steps);
	}
	else {
		SARMusic pscore = read (argsPtr[1]);
		result = trsp(score, pscore);
	}
	if (result) cout << result << endl;
	return 0;
}
