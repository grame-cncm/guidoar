/*

  Copyright (C) 2009  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the GuidoAR Library use.
  
*/

#include "common.cxx"

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
int main(int argc, char *argv[]) 
{
#ifdef debug
	char * args[] = {"test.gmn", "x2", 0};
	char ** argsPtr = args;
#else
	if (argc != 3) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	
	garErr err;
	int num, denom;
	char *buff = readgmn(argsPtr[0]);

	float ratio = floatArg(argsPtr[1], -1.0f);
	if (ratio > 0) {
		err = guidoMultDuration(buff, ratio, cout);
	}
	else if (rationalArg (argsPtr[1], &num, &denom)) {
		err = guidoSetDuration(buff, rational(num, denom), cout);
	}
	else {
		char *gmn = readgmn(argsPtr[1]);
		err = guidoSetDuration(buff, gmn, cout);
		delete[] gmn;
	}
	delete[] buff;
	checkErr (err, "duration");
	return err;
}
