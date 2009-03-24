/*

  Copyright (C) 2009  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the GuidoAR Library use.
  
*/

#include <sstream>
#include <string>
#include "common.cxx"

//#define debug

//_______________________________________________________________________________
static void usage(const char * name)
{
	cerr << "usage: " << name << " files..."  << endl;
	cerr << "       put the input gmn files in sequence"  << endl;
	exit (1);
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
#ifdef debug
	argc = 3;
	char * args[] = {"test.gmn", "test.gmn", 0};
	char ** argsPtr = args;
#else
	if (argc == 1) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif

	garErr err = kNoErr;
	char * buff = readgmn(*argsPtr++);
	string gmnstr = buff;
	delete [] buff;

	for (int i=2; (i<argc) && (err==kNoErr); i++, argsPtr++) {
		stringstream out;
		buff = readgmn(*argsPtr);
		err = guidoGSeq (gmnstr.c_str(), buff, out);
		checkErr (err, "par");
		gmnstr = out.str();
		delete[] buff;
	}
	cout << gmnstr << endl;
	return err;
}
