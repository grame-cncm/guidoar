/*

  Copyright (C) 2009  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the GuidoAR Library use.
  
*/

#include "common.cxx"
#include "AROthers.h"
#include "pitchvisitor.h"
#include "guidoparser.h"
#include "guidoelement.h"

#define debug 0

//_______________________________________________________________________________
static void usage(const char * name)
{
	cerr << "usage: " << name << "<-low|-high> <-once|-loop|-fbloop> score1 score2"  << endl;
	cerr << "       applies the rythm of score1 to score2"  << endl;
	cerr << "       where the first arg indicates the apply mode:"  << endl;
	cerr << "             -low uses chord lowest pitch value"  << endl;
	cerr << "             -high uses chord highest pitch value"  << endl;
	cerr << "             -once applies the rythmic structure only once"  << endl;
	cerr << "             -loop applies the rythmic structure endlessly in a loop"  << endl;
	cerr << "             -fbloop applies the rythmic structure endlessly in a forward-backward loop"  << endl;
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
static chordPitchMode getpmode (const char * str)
{
	if (!strcmp(str, "-low")) return kUseLowest;
	if (!strcmp(str, "-high")) return kUseHighest;
	return chordPitchMode(-1);
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
#if debug
	argc = 5;
	char * args[] = {"-high", "-once", "test.gmn", "chords.gmn", 0};
	char ** argsPtr = args;
#else
	if (argc != 5) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	chordPitchMode pmode = getpmode(*argsPtr++);
	TApplyMode mode = getmode(*argsPtr++);
	if (mode < 0) usage(argv[0]);
	if (pmode < 0) usage(argv[0]);
	
	char *rythm = readgmn(*argsPtr++);
	char *gmn = readgmn(*argsPtr++);
	garErr err = kNoErr;
	err = guidoApplyPitch(gmn, rythm, mode, pmode, cout);
	delete[] gmn;
	delete[] rythm;
	checkErr (err, "pitch");
	return err;
}
