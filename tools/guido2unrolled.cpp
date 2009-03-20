/*

  Copyright (C) 2003-2008  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
*/

#ifdef WIN32
# pragma warning (disable : 4786)
# define basename(name)	(name)
# define _CRT_SECURE_NO_DEPRECATE
#else 
# include <libgen.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "libguidoar.h"


//#define debug

using namespace std;
using namespace guido;


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
	
	garErr err;
	char * buff;
	if (!strcmp(file, "-"))
		buff = guidoread(stdin);
	else
		buff = guidoread(file);
	if (!buff) cerr << "failed to read '" << file << "'" << endl;
	else err = guido2unrolled(buff, cout);
	delete[] buff;

	switch (err) {
		case kInvalidArgument:
			cerr << "unable to parse gmn file '" << file << "'" << endl;
			break;
		case kOperationFailed:
			cerr << "unroll operation failed" << endl;
			break;
		default:
			break;
	}
	return err;
}
