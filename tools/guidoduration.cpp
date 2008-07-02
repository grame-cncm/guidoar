
#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include "guidoelement.h"
#include "guidoparser.h"
#include "durationvisitor.h"

using namespace std;
using namespace guido;

//_______________________________________________________________________________
int main(int argc, char *argv[]) {
	if (argc == 1) {
		guidoparser r;
		Sguidoelement g = r.parseFile( stdin );
		if (g) {
			durationvisitor dv;
			rational duration = dv.duration (g);
			cout << string(duration) << endl;
		}
	}
	else for (int i=1; i< argc; i++) {
		guidoparser r;
		Sguidoelement g = r.parseFile( argv[i] );
		if (g) {
			durationvisitor dv;
			rational duration = dv.duration (g);
			cout << argv[i] << ": " << string(duration) << endl;
		}
		else {
			cerr << argv[i] << ": read failed!" << endl;
			return 1;
		}
	}
	return 0;
}
