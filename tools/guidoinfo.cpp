
#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include "guidoelement.h"
#include "guidoparser.h"
#include "counteventsvisitor.h"
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
		Sguidoelement score = r.parseFile( argv[i] );
		if (score) {
			cout << argv[i] << ": " << endl;

			durationvisitor dv;
			rational duration = dv.duration (score);
			cout << "  duration: " << string(duration) << endl;
			
			counteventsvisitor ce;
			cout << "  events count: " << ce.count(score) << endl;
			
			countvoiceseventsvisitor cve;
			vector<int> vcount = cve.count(score);
			size_t n = vcount.size();
			cout << "  voices count: " << n << endl;
			for (int i=0; i < n; i++ ) {
			cout << "     voice " << (i+1) << " events count: " << vcount[i] << endl;
			}
			
		}
		else {
			cerr << argv[i] << ": read failed!" << endl;
			return 1;
		}
	}
	return 0;
}
