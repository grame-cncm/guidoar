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
	cerr << "usage: " << basename(name) << " <score> <duration | dscore>"  << endl;
	cerr << "       cut a score after a given duration"  << endl;
	cerr << "       score: the input file or '-' the read stdin"  << endl;
	cerr << "       duration: the score duration to preserve,"  << endl;
	cerr << "                 expressed as a non null rational where 1 is a whole note"  << endl;
	cerr << "       dscore: a score file used as duration specifier"  << endl;
	exit (1);
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

	char *buff = readgmn(argsPtr[0]);
	garErr err = kNoErr;

	int num, denom;
	if (rationalArg(argsPtr[1], &num, &denom)) {
		err = guidoVTail(buff, rational(num,denom), cout);
	}
	else {
		char *gmn = readgmn(argsPtr[1]);
		err = guidoGTail(buff, gmn, cout);
		delete[] gmn;
	}
	delete[] buff;
	checkErr (err, "head");
	return err;
}
