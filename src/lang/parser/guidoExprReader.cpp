/*
  GUIDO Library
  Copyright (C) 2008  Grame

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

#ifndef __guidoreader__
#define __guidoreader__

#include "guidoExpFactory.h"
#include "guidoExprReader.h"
#include "guidoelement.h"
#include "guidoparser.h"

using namespace guido;

namespace guidolang 
{

//______________________________________________________________________________
SGLExpr* guidoExpReader::newIDExpr (const char * id, SGLExpr* e)
{
	return 0;
}

SGLExpr* guidoExpReader::newScoreExpr (const char * gmnCode)
{
	SGLExpr* expr = new SGLExpr;
	guidoparser gp;
	Sguidoelement score = gp.parseString (gmnCode);
	if (score) {
		*expr = guidoExpFactory::instance().createScore(score);
		return expr;
	}
	return 0;  
}

SGLExpr* guidoExpReader::newComposedExpr (compOp op, SGLExpr* e1, SGLExpr* e2)
{
	SGLExpr* expr = new SGLExpr;
	*expr = guidoExpFactory::instance().createComposition(op, *e1, *e2);
	return expr;
}

SGLExpr* guidoExpReader::newAbstractExpr (SGLExpr* var, SGLExpr* e)
{
	SGLExpr* expr = new SGLExpr;
	*expr = guidoExpFactory::instance().createAbstraction(*var, *e);
	return expr;
}

SGLExpr* guidoExpReader::newApplyExpr (SGLExpr* a, SGLExpr* arg)
{
	SGLExpr* expr = new SGLExpr;
	*expr = guidoExpFactory::instance().createApplication(*e, *arg);
	return expr;
}


int guidoExpReader::error(const char * msg, int lineno)
{
	cerr << msg << " on line " << lineno << endl;
	return 0;
}


} // namespace

#endif
