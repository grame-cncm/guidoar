/*

  Copyright (C) 2009-2012  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the GuidoAR Library use.
  
*/

#include "common.cxx"

//#define debug

//_______________________________________________________________________________
static void usage (char * name)
{
	cerr << "usage: " << basename(name) << " score|-  interval|pscore"  << endl;
	cerr << "       transpose the input score"  << endl;
	cerr << "       use '-' to read score from standard input"  << endl;
	cerr << "       interval: the transposing interval"  << endl;
	cerr << "       pscore  : a score file used as a pitch specifier"  << endl;
	cerr << "                 using first voice, first note, lowest pitch."  << endl;
	exit (1);
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
#ifdef debug
	char * args[] = {"a.gmn", "2", 0};
	char ** argsPtr = args;
#else
	if (argc != 3) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif

	char *buff = readgmn(argsPtr[0]);
	garErr err = kNoErr;
	int steps = intArg (argsPtr[1], 9999);
	if (steps < 9999) {
		err = guidoVTranpose(buff, steps, cout);
	}
	else {
		char *gmn = readgmn(argsPtr[1]);
		err = guidoGTranpose(buff, gmn, cout);
		delete[] gmn;
	}
	delete[] buff;
	checkErr (err, "transpose");
	return err;
}
