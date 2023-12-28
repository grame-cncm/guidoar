/*
  GUIDO Library
  Copyright (C) 2006 Grame - 2023 D.Fober

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

#pragma once

namespace guido 
{

enum {
	kTMusic=1,
	kTVoice,
	kTChord,
	kTNote,
	
	kTagStart=10,
	kTAcc = kTagStart,
	kTAccel,
	kTAccelBegin,
	kTAccelEnd,
	kTAccent,
	kTAccidental,
	kTAccol,
	kTAlter,
	kTArpeggio,
	kTAuto,
	kTAutoBreak,
	kTBar,
	kTBarFormat,
	kTBeam,
	kTBeamBegin,
	kTBeamEnd,
	kTBeamsAuto,
	kTBeamsFull,
	kTBeamsOff,
	kTBembel,
	kTBow,
	kTBreathMark,
	kTClef,
	kTCluster,
	kTCoda,
	kTColor,
	kTComposer,
	kTCresc,
	kTCrescBegin,
	kTCrescEnd,
	kTCue,
	kTDaCapo,
	kTDaCapoAlFine,
	kTDaCoda,
	kTDalSegno,
	kTDalSegnoAlFine,
	kTDecresc,
	kTDecrescBegin,
	kTDecrescEnd,
	kTDefineTag,
	kTDim,
	kTDimBegin,
	kTDimEnd,
	kTDiminuendo,
	kTDispDur,
	kTDotFormat,
	kTDoubleBar,
	kTEndBar,
	kTFBeam,
	kTFBeamBegin,
	kTFBeamEnd,
	kTFermata,
	kTFine,
	kTFingering,
	kTFooter,
	kTGlissando,
	kTGlissandoBegin,
	kTGlissandoEnd,
	kTGrace,
	kTHarmony,
	kTHarmonic,
	kTHeadsCenter,
	kTHeadsLeft,
	kTHeadsNormal,
	kTHeadsReverse,
	kTHeadsRight,
	kTInstr,
	kTInstrument,
	kTIntens,
	kTKey,
	kTLabel,
	kTLyrics,
	kTMarcato,
	kTMark,
	kTMerge,
	kTMeter,
	kTMord,
	kTMrest,
	kTNewLine,
	kTNewPage,
	kTNewSystem,
	kTNoteFormat,
	kTOct,
	kTPageFormat,
	kTPedalOn,
	kTPedalOff,
	kTPizz,
	kTPort,
	kTRepeatBegin,
	kTRepeatEnd,
	kTRestFormat,
	kTRit,
	kTRitBegin,
	kTRitEnd,
	kTSegno,
	kTShareLocation,
	kTSlur,
	kTSlurBegin,
	kTSlurEnd,
	kTSpace,
	kTSpecial,
	kTSplitChord,
	kTStacc,
	kTStaccBegin,
	kTStaccEnd,
	kTStaff,
	kTStaffFormat,
	kTStaffOff,
	kTStaffOn,
	kTStemsAuto,
	kTStemsDown,
	kTStemsOff,
	kTStemsUp,
	kTSymbol,
	kTSystemFormat,
	kTTempo,
	kTTen,
	kTText,
	kTTie,
	kTTieBegin,
	kTTieEnd,
	kTTitle,
	kTTrem,
	kTTremBegin,
	kTTremEnd,
	kTTrill,
	kTTrillBegin,
	kTTrillEnd,
	kTTuplet,
	kTTupletBegin,
	kTTupletEnd,
	kTTurn,
	kTUnits,
	kTVolta,
	kTVoltaBegin,
	kTVoltaEnd,
	kTDrHoos,
	kTDrRenz,
	kTBackward,		// a tag specific to the normal form of a chord

	kTagEnd
};

} //namespace
