/*

  Copyright (C) 2003-2008  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
*/

#include "common.cxx"

//#define debug

//_______________________________________________________________________________
static void usage(char * name)
{
	cerr << "usage: " << basename(name) << " <score>"  << endl;
	cerr << "       generates an unrolled version of a score"  << endl;
	cerr << "       score: the input file or '-' to read stdin"  << endl;
	exit (1);
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) {
#ifdef debug
	const char * file = "a.gmn";
#else
	if (argc != 2) usage(argv[0]);
	char * file = argv[1];
#endif
	
	char *buff = readgmn(file);
	garErr err = guido2unrolled(buff, cout);
	delete[] buff;
	checkErr (err, "unroll");
	return err;
}
