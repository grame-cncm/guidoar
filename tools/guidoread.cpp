/*

  Copyright (C) 2009-2012  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the GuidoAR Library use.
  
*/

#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <stdlib.h>

#include "AROthers.h"
#include "guidoelement.h"
#include "guidoparser.h"

using namespace std;
using namespace guido;

//_______________________________________________________________________________
int main(int argc, char *argv[]) {
	for (int i=1; i<argc; i++) {
		guidoparser r;
		Sguidoelement g = r.parseFile( argv[i] );
		if (g) cout << g << endl;
		else {
			cerr << argv[i] << ": read failed!" << endl;
			return 1;
		}
	}
	return 0;
}
