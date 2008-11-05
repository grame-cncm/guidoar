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

#include "valueVisitor.h"
#include "guidoApplyValue.h"
#include "guidoClosureValue.h"
#include "guidoMixValue.h"
#include "guidoScoreValue.h"
#include "guidoSeqValue.h"

#include "AROthers.h"
#include "seqOperation.h"
#include "parOperation.h"

using namespace std;
using namespace guido;

namespace guidolang 
{

//______________________________________________________________________________
Sguidoelement valueVisitor::visit(const Sguidovalue& exp)
{ 
	fScore = 0;
	exp->acceptIn (*this);
	return fScore;
}

//______________________________________________________________________________
// the visit methods
//______________________________________________________________________________
void valueVisitor::visitStart( Sguidovalue& exp )
{
	cerr << __FILE__ << ": unexpected Sguidovalue received" << endl;
}

//______________________________________________________________________________
void valueVisitor::visitStart( SguidoSeqValue& exp )
{
	valueVisitor v;
	SARMusic s1 = dynamic_cast<ARMusic*> ((guidoelement*)v.visit(exp->getArg1()));
	SARMusic s2 = dynamic_cast<ARMusic*> ((guidoelement*)v.visit(exp->getArg2()));
	if (s1 && s2) {
		seqOperation seq;
		fScore = seq(s1, s2);
	}
}

//______________________________________________________________________________
void valueVisitor::visitStart( SguidoScoreValue& exp )
{
	fScore = exp->getScore();
}

//______________________________________________________________________________
void valueVisitor::visitStart( SguidoMixValue& exp )
{
	valueVisitor v;
	SARMusic s1 = dynamic_cast<ARMusic*> ((guidoelement*)v.visit(exp->getArg1()));
	SARMusic s2 = dynamic_cast<ARMusic*> ((guidoelement*)v.visit(exp->getArg2()));
	if (s1 && s2) {
		parOperation mix;
		fScore = mix(s1, s2);
	}
}

//______________________________________________________________________________
void valueVisitor::visitStart( SguidoClosureValue& exp )
{

}

//______________________________________________________________________________
void valueVisitor::visitStart( SguidoApplyValue& exp )
{
	Sguidovalue	arg = exp->getArg2 ();
	SguidoClosureValue c = dynamic_cast<guidoClosureValue*> ((guidovalue*)exp->getArg1 ());
	if (c) {
	}

}

}
