/*

  Copyright (C) 2003-2008  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
*/


#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "AROthers.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "counteventsvisitor.h"
#include "durationvisitor.h"

using namespace std;
using namespace guido;

//#define guidodebug

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
static void infos (const Sguidoelement& score) 
{
	if (score) {
		durationvisitor dv;
		rational duration = dv.duration (score);
#ifdef WIN32
		cout << "  duration: " << duration.getNumerator() << "/" << duration.getDenominator() << endl;
#else
		cout << "  duration: " << string(duration) << endl;
#endif
		counteventsvisitor ce;
		cout << "  events count: " << ce.count(score) << endl;
			
		countvoiceseventsvisitor cve;
		unsigned int n = score->size();
		cout << "  voices count: " << n << endl;
		for (unsigned int i=0; i < n; i++ ) {
			cout << "     voice " << (i+1) << " events count: " << cve.count(score, i) << endl;
		}		
	}
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) {
	if (argc == 1) {
#ifdef guidodebug
		Sguidoelement score = read( "test.gmn" );
#else
		Sguidoelement score = read( "-" );
#endif
		infos(score);
	}
	else for (int i=1; i< argc; i++) {
		Sguidoelement  score = read( argv[i] );
		cout << argv[i] << ": " << endl;
		infos(score);
	}
	return 0;
}
