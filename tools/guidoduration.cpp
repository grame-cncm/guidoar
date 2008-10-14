
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

#include "AROthers.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "durationOperation.h"

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
static float floatArg (const char* str) 
{
	float num=0;
	int n = sscanf(str, "x%f", &num);
	if (n != 1) num = -1.0f;
	return num;
}

//_______________________________________________________________________________
static rational durArg (const char* str) 
{
	int num=0, denum=0;
	rational result (0,0);
	int n = sscanf(str, "%d/%d", &num, &denum);
	if (n == 2)
		result.set( num, denum);
	if (n == 1) {
		if (num)	result.set ( num, 1);
		if (denum)	result.set ( 1, denum);
	}
	if (result < rational(0,1)) result.set (0,0);
	return result;
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
	SARMusic score = read (argsPtr[0]);
	durationOperation setdur;
	Sguidoelement result;

	float ratio = floatArg (argsPtr[1]);
	rational dur = durArg (argsPtr[1]);

	if (ratio > 0) {
		result = setdur(score, ratio);
	}
	else if (dur.getNumerator() > 0) {
		result = setdur(score, dur);
	}
	else {
		SARMusic dscore = read (argsPtr[1]);
		result = setdur(score, dscore);
	}
	if (result) cout << result << endl;
	return 0;
}
