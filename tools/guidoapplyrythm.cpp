/*

  Copyright (C) 2009-2012  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the GuidoAR Library use.
  
*/

#include "common.cxx"

#define debug 0

//_______________________________________________________________________________
static void usage(const char * name)
{
	cerr << "usage: " << name << " -low|-high -once|-loop|-fbloop  score1|-  score2"  << endl;
	cerr << "       applies the rythm of score1 to score2"  << endl;
	cerr << "       use '-' to read score1 from standard input"  << endl;
	cerr << "       the options indicate the apply mode:"  << endl;
	cerr << "             -once applies the rythmic structure only once"  << endl;
	cerr << "             -loop applies the rythmic structure in a loop"  << endl;
	cerr << "             -fbloop applies the rythmic structure in a forward-backward loop"  << endl;
	exit (1);
}

//_______________________________________________________________________________
static TApplyMode getmode (const char * str)
{
	if (!strcmp(str, "-once")) return kApplyOnce;
	if (!strcmp(str, "-loop")) return kApplyForwardLoop;
	if (!strcmp(str, "-fbloop")) return kApplyForwardBackwardLoop;
	return TApplyMode(-1);
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
#if debug
	argc = 4;
	char * args[] = {"test.gmn", "simple.gmn", 0};
	char ** argsPtr = args;
	TApplyMode mode = kApplyForwardLoop;
#else
	if (argc != 4) usage(argv[0]);
	char ** argsPtr = &argv[1];
	TApplyMode mode = getmode(*argsPtr++);
#endif
	if (mode < 0) usage(argv[0]);
	
	char *rythm = readgmn(*argsPtr++);
	char *gmn = readgmn(*argsPtr++);
	garErr err = kNoErr;
	err = guidoApplyRythm(gmn, rythm, mode, cout);
	delete[] gmn;
	delete[] rythm;
	checkErr (err, "rythm");
	return err;
}
