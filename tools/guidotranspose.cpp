/*

  Copyright (C) 2009  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the GuidoAR Library use.
  
*/

#include "common.cxx"

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
		err = guidoTranpose(buff, steps, cout);
	}
	else {
		char *gmn = readgmn(argsPtr[1]);
		err = guidoTranpose(buff, gmn, cout);
		delete[] gmn;
	}
	delete[] buff;
	checkErr (err, "transpose");
	return err;
}
