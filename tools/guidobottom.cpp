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
	cerr << "usage: " << basename(name) << " <score> <voicenum | vscore>"  << endl;
	cerr << "       cut a score after a given duration"  << endl;
	cerr << "       score: the input file or '-' to read stdin"  << endl;
	cerr << "       voicenum: number of voices to preserve,"  << endl;
	cerr << "       vscore: a score file used as voice specifier"  << endl;
	exit (1);
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
#ifdef debug
	char * args[] = {"moz581.gmn", "2", 0};
	char ** argsPtr = args;
#else
	if (argc != 3) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	garErr err;
	char *buff = readgmn(argsPtr[0]);

	int nvoices = intArg (argsPtr[1], -1);
	if (nvoices > 0) {
		err = guidoVBottom(buff, nvoices, cout);
	}
	else {
		char *gmn = readgmn(argsPtr[1]);
		err = guidoGBottom(buff, gmn, cout);
		delete[] gmn;
	}
	delete[] buff;
	checkErr (err, "bottom");
	return err;
}
