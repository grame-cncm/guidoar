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

#include "AROthers.h"
#include "clonevisitor.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "unrolled_guido_browser.h"


#define debug

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
static SARMusic read (const char* file) 
{
	guidoparser r;
	SARMusic score;
	if (!strcmp(file, "-"))
		score = r.parseFile(stdin);
	else
		score = r.parseFile(file);
	if (!score) {
		cerr << file << ": read failed"  << endl;
		exit (1);
	}
	return score;
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) {
#ifdef debug
	const char * file = "a.gmn";
#else
	if (argc != 2) usage(argv[0]);
	char * file = argv[1];
#endif

	Sguidoelement score = read (file);
	if (score) {
		clonevisitor cv;
		unrolled_guido_browser ugb(&cv);
		ugb.browse (score);
//		Sguidoelement unrolled = cv.clone(score, true);
		Sguidoelement unrolled = cv.result();
		if (unrolled) cout << unrolled << endl;
	}
	return 0;
}
