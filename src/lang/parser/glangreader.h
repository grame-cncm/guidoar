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

#ifndef __glangreader__
#define __glangreader__


namespace guidolang 
{

//class SGLExpr;

//______________________________________________________________________________
/*!
\brief	An abstract class supporting the glang parser interface.
*/
class glangreader
{ 
	public:
		enum compOp { kSeqOp, kParOp, kHeadOp, kTailOp, kTopOp, kBottomOp };

		virtual ~glangreader() {}
		
		virtual SGLExpr* newIDExpr			(const char *, SGLExpr*) = 0;
		virtual SGLExpr* newScoreExpr		(const char *) = 0;
		virtual SGLExpr* newComposedExpr	(compOp op, SGLExpr*, SGLExpr*) = 0;
		virtual SGLExpr* newAbstractExpr	(SGLExpr*, SGLExpr*) = 0;
		virtual SGLExpr* newApplyExpr		(SGLExpr*, SGLExpr*) = 0;

		virtual int error(const char * msg, int lineno) = 0;
};

} // namespace

#endif