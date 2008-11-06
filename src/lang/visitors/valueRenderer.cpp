/*

  MusicXML Library
  Copyright (C) 2006,2007  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <iostream>

#include "exceptions.h"
#include "guidoexpression.h"
#include "guidoApplyValue.h"
#include "guidoClosureValue.h"
#include "guidoMixValue.h"
#include "guidoScoreValue.h"
#include "guidoSeqValue.h"
#include "valueRenderer.h"

#include "AROthers.h"
#include "seqOperation.h"
#include "parOperation.h"

using namespace std;
using namespace guido;

namespace guidolang 
{

//______________________________________________________________________________
Sguidoelement valueRenderer::render(const Sguidoexpression& exp)
{ 
	try {
		SguidoEnv env = guidoEnv::create();		
		Sguidovalue val = exp->eval(env);
		if (val) return render(val);
	} catch (const TException& e)  { 
		cerr << e.msg << " - file: '" << e.file << "' line: " << e.line << endl;
	}
	return 0;
}

//______________________________________________________________________________
Sguidoelement valueRenderer::render(const Sguidovalue& val)
{ 
	fScore = 0;
	val->acceptIn (*this);
	return fScore;
}

//______________________________________________________________________________
// the visit methods
//______________________________________________________________________________
void valueRenderer::visitStart( Sguidovalue& exp )
{
	cerr << __FILE__ << ": unexpected Sguidovalue received" << endl;
}

//______________________________________________________________________________
void valueRenderer::visitStart( SguidoSeqValue& exp )
{
	valueRenderer v;
	SARMusic s1 = dynamic_cast<ARMusic*> ((guidoelement*)v.render(exp->getArg1()));
	SARMusic s2 = dynamic_cast<ARMusic*> ((guidoelement*)v.render(exp->getArg2()));
	if (s1 && s2) {
		seqOperation seq;
		fScore = seq(s1, s2);
	}
}

//______________________________________________________________________________
void valueRenderer::visitStart( SguidoScoreValue& exp )
{
	fScore = exp->getScore();
}

//______________________________________________________________________________
void valueRenderer::visitStart( SguidoMixValue& exp )
{
	valueRenderer v;
	SARMusic s1 = dynamic_cast<ARMusic*> ((guidoelement*)v.render(exp->getArg1()));
	SARMusic s2 = dynamic_cast<ARMusic*> ((guidoelement*)v.render(exp->getArg2()));
	if (s1 && s2) {
		parOperation mix;
		fScore = mix(s1, s2);
	}
}

}
