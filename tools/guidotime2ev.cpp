
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


#include "AROthers.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "event2timevisitor.h"

using namespace std;
using namespace guido;

//#define guidodebug

//_______________________________________________________________________________
static void usage(char * name)
{
	cerr << "usage: " << basename(name) << " <score> <time> [voiceIndex]"  << endl;
	cerr << "       converts a time position to an event index"  << endl;
	cerr << "       score: the input file or '-' to read stdin"  << endl;
	cerr << "       time: a time position expressed as a rational (where 1 is a whole note)"  << endl;
	cerr << "       voiceIndex: optional voice index (defaults to the first voice)"  << endl;
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
static rational timeArg (const char* time) 
{
	int num=-1, denum=0;
	int n = sscanf(time, "%d/%d", &num, &denum);
	if (n == 2)
		return rational( num, denum);
	if (n == 1) {
		if (num>=0)	return rational( num, 1);
		if (denum)	return rational( 1, denum);
	}
	return rational (-1,1);
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
	char *name = argv[0];
#ifdef guidodebug
	argc = 4;
	char * args[] = {"test.gmn", "0", "1", 0};
	char ** argsPtr = args;
#else
	if ((argc != 3) && (argc != 4)) usage(name);
	char ** argsPtr = &argv[1];
#endif
	const char *file = argsPtr[0];

	rational time = timeArg (argsPtr[1]);		// get the event index argument
	if (time < double(0)) usage(name);
	
	int voiceIndex = 1;									// default voice is 1
	if (argc == 4) voiceIndex = numArg (argsPtr[2]);	// get the voice index argument
	if (voiceIndex <= 0) usage(name);
		
	SARMusic score = read (file);
	event2timevisitor convert;
	int index = convert.time2event (score, time, voiceIndex-1);
	cout << file << ": voice " << voiceIndex << " time " << string(time)
		 << ": event " << index+1 << endl;
	return 0;
}
