/*
  GUIDO Library
  Copyright (C) 2006  Grame

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

#ifndef __guidoparser__
#define __guidoparser__

extern int lnr;
extern int cnr;
extern int cmnt_level;

#define CINC { if (yyleng > 1) cnr+=yyleng; else cnr++; }
#define LINC { lnr++; cnr=0; }

#define ERROR(msg)		gReader->error(msg, lnr, cnr)
#define gd_error(msg)	gReader->error(msg, lnr, cnr)

#define kSharp +1
#define kFlat (-1)

#define GD_INIT_SEGM	gReader->segmInit();
#define GD_EXIT_SEGM	gReader->segmExit();
#define GD_APP_SEQ   	gReader->segmAppendSeq();

#define GD_INIT_SEQ  	gReader->seqInit();
#define GD_EXIT_SEQ    	gReader->seqExit();

#define GD_NT(x)    	gReader->noteInit(x);
#define GD_SH_NT    	gReader->noteAcc(kSharp);
#define GD_FL_NT    	gReader->noteAcc(kFlat);
#define GD_OCT_NT(x)    gReader->noteOct(x);
#define GD_ENUM_NT(x) 	gReader->noteEnum(x);
#define GD_DENOM_NT(x) 	gReader->noteDenom(x);
#define GD_DOT_NT      	gReader->noteDot();
#define GD_DDOT_NT     	gReader->noteDdot();
#define GD_ABSDUR_NT(x) gReader->noteAbsDur(x);

#define GD_APP_NT    	gReader->seqAppendNote();

#define GD_INIT_CH   	gReader->chordInit();
#define GD_CH_INIT_NT	gReader->chordInitNote();
#define GD_CH_APP_NT 	gReader->chordAppendNote();
#define GD_APP_CH    	gReader->seqAppendChord();

#define GD_TAG_START(x,i) gReader->tagStart(x,i);
#define GD_TAG_END      gReader->tagEnd();
#define GD_TAG_NARG(x)  gReader->tagIntArg(x);
#define GD_TAG_RARG(x)  gReader->tagFloatArg(x);
#define GD_TAG_SARG(x)  gReader->tagStrArg(x);
#define GD_TAG_TARG(x)		/* don't use this! */
#define GD_TAG_ADD_ARG(x)	gReader->tagAddArg(x);
#define GD_TAG_ADD			gReader->tagAdd();
#define GD_TAG_ARG_UNIT(x)	gReader->tagArgUnit(x);
#define GD_TAG_RANGE		gReader->tagRange();

#endif

