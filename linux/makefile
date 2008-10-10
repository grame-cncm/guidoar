TARGET=libguidoar.a


BASE       = ../src
subprojects := $(BASE)/guido $(BASE)/guido/abstract $(BASE)/lib $(BASE)/parser $(BASE)/operations $(BASE)/visitors

HEADERS = $(wildcard $(BASE)/include/GUIDO*.h) \
	$(BASE)/include/VGDevice.h $(BASE)/include/GDeviceDefs.h \
	$(BASE)/include/ScoreSymbolMap.h $(BASE)/include/VScoreSymbolMap.h  $(BASE)/include/TRect.h

SRC = $(wildcard $(BASE)/guido/*.cpp $(BASE)/guido/abstract/*.cpp $(BASE)/lib/*.cpp $(BASE)/visitors/*.cpp \
			$(BASE)/operations/*.cpp) $(BASE)/parser/parser.cpp $(BASE)/parser/guidoparser.cpp

OBJ = $(patsubst %.cpp, %.o, $(SRC))
CXXFLAGS = $(addprefix -I, $(subprojects))

TOOLS = guidoread guidopar guidorpar guidoseq guidodur guido2midi guidoinfo \
	guidoev2time guidotime2ev guidoevhead guidoevtail guidovhead guidovtail \
	guidohead guidotail guidotranspose

.PHONY: $(TARGET)

all : $(TARGET) $(TOOLS)

$(TARGET) : $(OBJ)
	ar -ru $(TARGET) $(OBJ)
	ranlib  $(TARGET)

guidotranspose : ../tools/guidotranspose.cpp $(TARGET)
	g++ ../tools/guidotranspose.cpp $(CXXFLAGS) libguidoar.a -o guidotranspose

guidotail : ../tools/guidotail.cpp $(TARGET)
	g++ ../tools/guidotail.cpp $(CXXFLAGS) libguidoar.a -o guidotail

guidohead : ../tools/guidohead.cpp $(TARGET)
	g++ ../tools/guidohead.cpp $(CXXFLAGS) libguidoar.a -o guidohead

guidovtail : ../tools/guidovtail.cpp $(TARGET)
	g++ ../tools/guidovtail.cpp $(CXXFLAGS) libguidoar.a -o guidovtail

guidovhead : ../tools/guidovhead.cpp $(TARGET)
	g++ ../tools/guidovhead.cpp $(CXXFLAGS) libguidoar.a -o guidovhead

guidoevtail : ../tools/guidoevtail.cpp $(TARGET)
	g++ ../tools/guidoevtail.cpp $(CXXFLAGS) libguidoar.a -o guidoevtail

guidoevhead : ../tools/guidoevhead.cpp $(TARGET)
	g++ ../tools/guidoevhead.cpp $(CXXFLAGS) libguidoar.a -o guidoevhead

guidotime2ev : ../tools/guidotime2ev.cpp $(TARGET)
	g++ ../tools/guidotime2ev.cpp $(CXXFLAGS) libguidoar.a -o guidotime2ev

guidoev2time : ../tools/guidoev2time.cpp $(TARGET)
	g++ ../tools/guidoev2time.cpp $(CXXFLAGS) libguidoar.a -o guidoev2time

guidoinfo : ../tools/guidoinfo.cpp $(TARGET)
	g++ ../tools/guidoinfo.cpp $(CXXFLAGS) libguidoar.a -o guidoinfo

guido2midi : ../tools/guido2midi.cpp $(TARGET)
	g++ ../tools/guido2midi.cpp $(CXXFLAGS) libguidoar.a -o guido2midi

guidoread : ../tools/guidoread.cpp $(TARGET)
	g++ ../tools/guidoread.cpp $(CXXFLAGS) libguidoar.a -o guidoread

guidopar : ../tools/guidopar.cpp $(TARGET)
	g++ ../tools/guidopar.cpp $(CXXFLAGS) libguidoar.a -o guidopar

guidorpar : ../tools/guidorpar.cpp $(TARGET)
	g++ ../tools/guidorpar.cpp $(CXXFLAGS) libguidoar.a -o guidorpar

guidoseq : ../tools/guidoseq.cpp $(TARGET)
	g++ ../tools/guidoseq.cpp $(CXXFLAGS) libguidoar.a -o guidoseq

guidodur : ../tools/guidoduration.cpp $(TARGET)
	g++ ../tools/guidoduration.cpp $(CXXFLAGS) libguidoar.a -o guidodur

dep:
	makedepend -- $(CXXFLAGS) -- $(SRC)

install:
	install  -g root -o root -m 644 $(TARGET) /usr/local/lib
	install  -g root -o root  -m 644 $(HEADERS) /usr/local/include

uninstall:
	rm -f  /usr/local/lib/$(TARGET)
	cd /usr/local/include && rm -f GUIDO*.h

clean:
	rm $(TARGET) $(OBJ)
# DO NOT DELETE

../src/guido/guidoelement.o: ../src/guido/guidoelement.h ../src/lib/export.h
../src/guido/guidoelement.o: ../src/visitors/visitable.h
../src/guido/guidoelement.o: ../src/visitors/basevisitor.h ../src/lib/ctree.h
../src/guido/guidoelement.o: ../src/lib/smartpointer.h
../src/guido/guidoelement.o: ../src/visitors/gmnvisitor.h
../src/guido/guidoelement.o: ../src/guido/abstract/ARTypes.h
../src/guido/guidoelement.o: ../src/guido/guidotags.h
../src/guido/guidoelement.o: ../src/lib/streambeautifuller.h
../src/guido/guidoelement.o: ../src/visitors/visitor.h
../src/guido/guidoelement.o: ../src/lib/tree_browser.h ../src/lib/browser.h
../src/guido/abstract/ARChord.o: ../src/guido/abstract/ARChord.h
../src/guido/abstract/ARChord.o: ../src/lib/export.h
../src/guido/abstract/ARChord.o: ../src/guido/guidoelement.h
../src/guido/abstract/ARChord.o: ../src/visitors/visitable.h
../src/guido/abstract/ARChord.o: ../src/visitors/basevisitor.h
../src/guido/abstract/ARChord.o: ../src/lib/ctree.h ../src/lib/smartpointer.h
../src/guido/abstract/ARChord.o: ../src/lib/rational.h
../src/guido/abstract/ARChord.o: ../src/guido/abstract/ARNote.h
../src/guido/abstract/ARChord.o: ../src/guido/abstract/ARTypes.h
../src/guido/abstract/ARChord.o: ../src/guido/guidotags.h
../src/guido/abstract/ARChord.o: ../src/lib/functor.h
../src/guido/abstract/ARChord.o: ../src/visitors/visitor.h
../src/guido/abstract/ARFactory.o: ../src/guido/guidotags.h
../src/guido/abstract/ARFactory.o: ../src/guido/abstract/ARFactory.h
../src/guido/abstract/ARFactory.o: ../src/lib/export.h ../src/lib/functor.h
../src/guido/abstract/ARFactory.o: ../src/lib/singleton.h
../src/guido/abstract/ARFactory.o: ../src/guido/abstract/ARTypes.h
../src/guido/abstract/ARFactory.o: ../src/lib/smartpointer.h
../src/guido/abstract/ARFactory.o: ../src/guido/abstract/ARChord.h
../src/guido/abstract/ARFactory.o: ../src/guido/guidoelement.h
../src/guido/abstract/ARFactory.o: ../src/visitors/visitable.h
../src/guido/abstract/ARFactory.o: ../src/visitors/basevisitor.h
../src/guido/abstract/ARFactory.o: ../src/lib/ctree.h ../src/lib/rational.h
../src/guido/abstract/ARFactory.o: ../src/guido/abstract/ARNote.h
../src/guido/abstract/ARFactory.o: ../src/guido/abstract/AROthers.h
../src/guido/abstract/ARFactory.o: ../src/guido/abstract/ARTag.h
../src/guido/abstract/ARFactory.o: ../src/visitors/visitor.h
../src/guido/abstract/ARNote.o: ../src/guido/abstract/ARNote.h
../src/guido/abstract/ARNote.o: ../src/guido/guidoelement.h
../src/guido/abstract/ARNote.o: ../src/lib/export.h
../src/guido/abstract/ARNote.o: ../src/visitors/visitable.h
../src/guido/abstract/ARNote.o: ../src/visitors/basevisitor.h
../src/guido/abstract/ARNote.o: ../src/lib/ctree.h ../src/lib/smartpointer.h
../src/guido/abstract/ARNote.o: ../src/lib/rational.h
../src/guido/abstract/ARNote.o: ../src/visitors/visitor.h
../src/guido/abstract/AROthers.o: ../src/guido/abstract/AROthers.h
../src/guido/abstract/AROthers.o: ../src/lib/export.h
../src/guido/abstract/AROthers.o: ../src/guido/guidoelement.h
../src/guido/abstract/AROthers.o: ../src/visitors/visitable.h
../src/guido/abstract/AROthers.o: ../src/visitors/basevisitor.h
../src/guido/abstract/AROthers.o: ../src/lib/ctree.h
../src/guido/abstract/AROthers.o: ../src/lib/smartpointer.h
../src/guido/abstract/AROthers.o: ../src/visitors/visitor.h
../src/guido/abstract/ARTag.o: ../src/guido/abstract/ARTag.h
../src/guido/abstract/ARTag.o: ../src/lib/export.h
../src/guido/abstract/ARTag.o: ../src/guido/guidoelement.h
../src/guido/abstract/ARTag.o: ../src/visitors/visitable.h
../src/guido/abstract/ARTag.o: ../src/visitors/basevisitor.h
../src/guido/abstract/ARTag.o: ../src/lib/ctree.h ../src/lib/smartpointer.h
../src/guido/abstract/ARTag.o: ../src/visitors/visitor.h
../src/lib/rational.o: ../src/lib/rational.h ../src/lib/export.h
../src/lib/streambeautifuller.o: ../src/lib/streambeautifuller.h
../src/lib/streambeautifuller.o: ../src/lib/export.h
../src/visitors/clonevisitor.o: ../src/guido/abstract/ARFactory.h
../src/visitors/clonevisitor.o: ../src/lib/export.h ../src/lib/functor.h
../src/visitors/clonevisitor.o: ../src/lib/singleton.h
../src/visitors/clonevisitor.o: ../src/guido/abstract/ARTypes.h
../src/visitors/clonevisitor.o: ../src/lib/smartpointer.h
../src/visitors/clonevisitor.o: ../src/guido/guidotags.h
../src/visitors/clonevisitor.o: ../src/guido/abstract/ARChord.h
../src/visitors/clonevisitor.o: ../src/guido/guidoelement.h
../src/visitors/clonevisitor.o: ../src/visitors/visitable.h
../src/visitors/clonevisitor.o: ../src/visitors/basevisitor.h
../src/visitors/clonevisitor.o: ../src/lib/ctree.h ../src/lib/rational.h
../src/visitors/clonevisitor.o: ../src/guido/abstract/ARNote.h
../src/visitors/clonevisitor.o: ../src/guido/abstract/AROthers.h
../src/visitors/clonevisitor.o: ../src/guido/abstract/ARTag.h
../src/visitors/clonevisitor.o: ../src/visitors/visitor.h
../src/visitors/clonevisitor.o: ../src/visitors/clonevisitor.h
../src/visitors/clonevisitor.o: ../src/lib/tree_browser.h
../src/visitors/clonevisitor.o: ../src/lib/browser.h
../src/visitors/counteventsvisitor.o: ../src/guido/abstract/ARChord.h
../src/visitors/counteventsvisitor.o: ../src/lib/export.h
../src/visitors/counteventsvisitor.o: ../src/guido/guidoelement.h
../src/visitors/counteventsvisitor.o: ../src/visitors/visitable.h
../src/visitors/counteventsvisitor.o: ../src/visitors/basevisitor.h
../src/visitors/counteventsvisitor.o: ../src/lib/ctree.h
../src/visitors/counteventsvisitor.o: ../src/lib/smartpointer.h
../src/visitors/counteventsvisitor.o: ../src/lib/rational.h
../src/visitors/counteventsvisitor.o: ../src/guido/abstract/ARNote.h
../src/visitors/counteventsvisitor.o: ../src/visitors/counteventsvisitor.h
../src/visitors/counteventsvisitor.o: ../src/guido/abstract/ARTypes.h
../src/visitors/counteventsvisitor.o: ../src/guido/guidotags.h
../src/visitors/counteventsvisitor.o: ../src/lib/tree_browser.h
../src/visitors/counteventsvisitor.o: ../src/lib/browser.h
../src/visitors/counteventsvisitor.o: ../src/visitors/visitor.h
../src/visitors/durationvisitor.o: ../src/guido/abstract/ARChord.h
../src/visitors/durationvisitor.o: ../src/lib/export.h
../src/visitors/durationvisitor.o: ../src/guido/guidoelement.h
../src/visitors/durationvisitor.o: ../src/visitors/visitable.h
../src/visitors/durationvisitor.o: ../src/visitors/basevisitor.h
../src/visitors/durationvisitor.o: ../src/lib/ctree.h
../src/visitors/durationvisitor.o: ../src/lib/smartpointer.h
../src/visitors/durationvisitor.o: ../src/lib/rational.h
../src/visitors/durationvisitor.o: ../src/guido/abstract/ARNote.h
../src/visitors/durationvisitor.o: ../src/guido/abstract/AROthers.h
../src/visitors/durationvisitor.o: ../src/visitors/durationvisitor.h
../src/visitors/durationvisitor.o: ../src/guido/abstract/ARTypes.h
../src/visitors/durationvisitor.o: ../src/guido/guidotags.h
../src/visitors/durationvisitor.o: ../src/lib/tree_browser.h
../src/visitors/durationvisitor.o: ../src/lib/browser.h
../src/visitors/durationvisitor.o: ../src/visitors/visitor.h
../src/visitors/event2timevisitor.o: ../src/guido/abstract/ARChord.h
../src/visitors/event2timevisitor.o: ../src/lib/export.h
../src/visitors/event2timevisitor.o: ../src/guido/guidoelement.h
../src/visitors/event2timevisitor.o: ../src/visitors/visitable.h
../src/visitors/event2timevisitor.o: ../src/visitors/basevisitor.h
../src/visitors/event2timevisitor.o: ../src/lib/ctree.h
../src/visitors/event2timevisitor.o: ../src/lib/smartpointer.h
../src/visitors/event2timevisitor.o: ../src/lib/rational.h
../src/visitors/event2timevisitor.o: ../src/guido/abstract/ARNote.h
../src/visitors/event2timevisitor.o: ../src/visitors/event2timevisitor.h
../src/visitors/event2timevisitor.o: ../src/visitors/durationvisitor.h
../src/visitors/event2timevisitor.o: ../src/guido/abstract/ARTypes.h
../src/visitors/event2timevisitor.o: ../src/guido/guidotags.h
../src/visitors/event2timevisitor.o: ../src/lib/tree_browser.h
../src/visitors/event2timevisitor.o: ../src/lib/browser.h
../src/visitors/event2timevisitor.o: ../src/visitors/visitor.h
../src/visitors/event2timevisitor.o: ../src/visitors/counteventsvisitor.h
../src/visitors/gmnvisitor.o: ../src/visitors/gmnvisitor.h
../src/visitors/gmnvisitor.o: ../src/lib/export.h
../src/visitors/gmnvisitor.o: ../src/guido/abstract/ARTypes.h
../src/visitors/gmnvisitor.o: ../src/lib/smartpointer.h
../src/visitors/gmnvisitor.o: ../src/guido/guidotags.h
../src/visitors/gmnvisitor.o: ../src/lib/streambeautifuller.h
../src/visitors/gmnvisitor.o: ../src/visitors/visitor.h
../src/visitors/gmnvisitor.o: ../src/visitors/basevisitor.h
../src/visitors/gmnvisitor.o: ../src/guido/abstract/ARChord.h
../src/visitors/gmnvisitor.o: ../src/guido/guidoelement.h
../src/visitors/gmnvisitor.o: ../src/visitors/visitable.h ../src/lib/ctree.h
../src/visitors/gmnvisitor.o: ../src/lib/rational.h
../src/visitors/gmnvisitor.o: ../src/guido/abstract/ARNote.h
../src/visitors/gmnvisitor.o: ../src/guido/abstract/AROthers.h
../src/visitors/gmnvisitor.o: ../src/guido/abstract/ARTag.h
../src/visitors/midicontextvisitor.o: ../src/guido/abstract/ARChord.h
../src/visitors/midicontextvisitor.o: ../src/lib/export.h
../src/visitors/midicontextvisitor.o: ../src/guido/guidoelement.h
../src/visitors/midicontextvisitor.o: ../src/visitors/visitable.h
../src/visitors/midicontextvisitor.o: ../src/visitors/basevisitor.h
../src/visitors/midicontextvisitor.o: ../src/lib/ctree.h
../src/visitors/midicontextvisitor.o: ../src/lib/smartpointer.h
../src/visitors/midicontextvisitor.o: ../src/lib/rational.h
../src/visitors/midicontextvisitor.o: ../src/guido/abstract/ARNote.h
../src/visitors/midicontextvisitor.o: ../src/guido/abstract/AROthers.h
../src/visitors/midicontextvisitor.o: ../src/guido/abstract/ARTag.h
../src/visitors/midicontextvisitor.o: ../src/visitors/visitor.h
../src/visitors/midicontextvisitor.o: ../src/visitors/midicontextvisitor.h
../src/visitors/midicontextvisitor.o: ../src/guido/abstract/ARTypes.h
../src/visitors/midicontextvisitor.o: ../src/guido/guidotags.h
../src/visitors/midicontextvisitor.o: ../src/visitors/unrolled_guido_browser.h
../src/visitors/midicontextvisitor.o: ../src/lib/browser.h
../src/visitors/unrolled_guido_browser.o: ../src/guido/abstract/ARNote.h
../src/visitors/unrolled_guido_browser.o: ../src/guido/guidoelement.h
../src/visitors/unrolled_guido_browser.o: ../src/lib/export.h
../src/visitors/unrolled_guido_browser.o: ../src/visitors/visitable.h
../src/visitors/unrolled_guido_browser.o: ../src/visitors/basevisitor.h
../src/visitors/unrolled_guido_browser.o: ../src/lib/ctree.h
../src/visitors/unrolled_guido_browser.o: ../src/lib/smartpointer.h
../src/visitors/unrolled_guido_browser.o: ../src/lib/rational.h
../src/visitors/unrolled_guido_browser.o: ../src/guido/abstract/AROthers.h
../src/visitors/unrolled_guido_browser.o: ../src/guido/abstract/ARTag.h
../src/visitors/unrolled_guido_browser.o: ../src/visitors/visitor.h
../src/visitors/unrolled_guido_browser.o: ../src/visitors/unrolled_guido_browser.h
../src/visitors/unrolled_guido_browser.o: ../src/guido/abstract/ARTypes.h
../src/visitors/unrolled_guido_browser.o: ../src/guido/guidotags.h
../src/visitors/unrolled_guido_browser.o: ../src/lib/browser.h
../src/operations/durationOperation.o: ../src/guido/abstract/ARFactory.h
../src/operations/durationOperation.o: ../src/lib/export.h
../src/operations/durationOperation.o: ../src/lib/functor.h
../src/operations/durationOperation.o: ../src/lib/singleton.h
../src/operations/durationOperation.o: ../src/guido/abstract/ARTypes.h
../src/operations/durationOperation.o: ../src/lib/smartpointer.h
../src/operations/durationOperation.o: ../src/guido/guidotags.h
../src/operations/durationOperation.o: ../src/guido/abstract/AROthers.h
../src/operations/durationOperation.o: ../src/guido/guidoelement.h
../src/operations/durationOperation.o: ../src/visitors/visitable.h
../src/operations/durationOperation.o: ../src/visitors/basevisitor.h
../src/operations/durationOperation.o: ../src/lib/ctree.h
../src/operations/durationOperation.o: ../src/guido/abstract/ARTag.h
../src/operations/durationOperation.o: ../src/visitors/visitor.h
../src/operations/durationOperation.o: ../src/guido/abstract/ARNote.h
../src/operations/durationOperation.o: ../src/lib/rational.h
../src/operations/durationOperation.o: ../src/visitors/durationvisitor.h
../src/operations/durationOperation.o: ../src/lib/tree_browser.h
../src/operations/durationOperation.o: ../src/lib/browser.h
../src/operations/durationOperation.o: ../src/operations/durationOperation.h
../src/operations/durationOperation.o: ../src/visitors/clonevisitor.h
../src/operations/durationOperation.o: ../src/operations/operation.h
../src/operations/eheadOperation.o: ../src/guido/abstract/ARNote.h
../src/operations/eheadOperation.o: ../src/guido/guidoelement.h
../src/operations/eheadOperation.o: ../src/lib/export.h
../src/operations/eheadOperation.o: ../src/visitors/visitable.h
../src/operations/eheadOperation.o: ../src/visitors/basevisitor.h
../src/operations/eheadOperation.o: ../src/lib/ctree.h
../src/operations/eheadOperation.o: ../src/lib/smartpointer.h
../src/operations/eheadOperation.o: ../src/lib/rational.h
../src/operations/eheadOperation.o: ../src/guido/abstract/ARFactory.h
../src/operations/eheadOperation.o: ../src/lib/functor.h
../src/operations/eheadOperation.o: ../src/lib/singleton.h
../src/operations/eheadOperation.o: ../src/guido/abstract/ARTypes.h
../src/operations/eheadOperation.o: ../src/guido/guidotags.h
../src/operations/eheadOperation.o: ../src/guido/abstract/AROthers.h
../src/operations/eheadOperation.o: ../src/guido/abstract/ARTag.h
../src/operations/eheadOperation.o: ../src/visitors/visitor.h
../src/operations/eheadOperation.o: ../src/visitors/clonevisitor.h
../src/operations/eheadOperation.o: ../src/visitors/counteventsvisitor.h
../src/operations/eheadOperation.o: ../src/lib/tree_browser.h
../src/operations/eheadOperation.o: ../src/lib/browser.h
../src/operations/eheadOperation.o: ../src/operations/eheadOperation.h
../src/operations/eheadOperation.o: ../src/operations/headOperation.h
../src/operations/eheadOperation.o: ../src/visitors/durationvisitor.h
../src/operations/eheadOperation.o: ../src/operations/operation.h
../src/operations/eheadOperation.o: ../src/visitors/event2timevisitor.h
../src/operations/etailOperation.o: ../src/guido/abstract/ARNote.h
../src/operations/etailOperation.o: ../src/guido/guidoelement.h
../src/operations/etailOperation.o: ../src/lib/export.h
../src/operations/etailOperation.o: ../src/visitors/visitable.h
../src/operations/etailOperation.o: ../src/visitors/basevisitor.h
../src/operations/etailOperation.o: ../src/lib/ctree.h
../src/operations/etailOperation.o: ../src/lib/smartpointer.h
../src/operations/etailOperation.o: ../src/lib/rational.h
../src/operations/etailOperation.o: ../src/guido/abstract/ARFactory.h
../src/operations/etailOperation.o: ../src/lib/functor.h
../src/operations/etailOperation.o: ../src/lib/singleton.h
../src/operations/etailOperation.o: ../src/guido/abstract/ARTypes.h
../src/operations/etailOperation.o: ../src/guido/guidotags.h
../src/operations/etailOperation.o: ../src/guido/abstract/AROthers.h
../src/operations/etailOperation.o: ../src/guido/abstract/ARTag.h
../src/operations/etailOperation.o: ../src/visitors/visitor.h
../src/operations/etailOperation.o: ../src/visitors/clonevisitor.h
../src/operations/etailOperation.o: ../src/visitors/counteventsvisitor.h
../src/operations/etailOperation.o: ../src/lib/tree_browser.h
../src/operations/etailOperation.o: ../src/lib/browser.h
../src/operations/etailOperation.o: ../src/operations/etailOperation.h
../src/operations/etailOperation.o: ../src/operations/tailOperation.h
../src/operations/etailOperation.o: ../src/visitors/durationvisitor.h
../src/operations/etailOperation.o: ../src/operations/operation.h
../src/operations/etailOperation.o: ../src/visitors/event2timevisitor.h
../src/operations/headOperation.o: ../src/guido/abstract/ARNote.h
../src/operations/headOperation.o: ../src/guido/guidoelement.h
../src/operations/headOperation.o: ../src/lib/export.h
../src/operations/headOperation.o: ../src/visitors/visitable.h
../src/operations/headOperation.o: ../src/visitors/basevisitor.h
../src/operations/headOperation.o: ../src/lib/ctree.h
../src/operations/headOperation.o: ../src/lib/smartpointer.h
../src/operations/headOperation.o: ../src/lib/rational.h
../src/operations/headOperation.o: ../src/guido/abstract/ARFactory.h
../src/operations/headOperation.o: ../src/lib/functor.h
../src/operations/headOperation.o: ../src/lib/singleton.h
../src/operations/headOperation.o: ../src/guido/abstract/ARTypes.h
../src/operations/headOperation.o: ../src/guido/guidotags.h
../src/operations/headOperation.o: ../src/guido/abstract/AROthers.h
../src/operations/headOperation.o: ../src/guido/abstract/ARTag.h
../src/operations/headOperation.o: ../src/visitors/visitor.h
../src/operations/headOperation.o: ../src/visitors/clonevisitor.h
../src/operations/headOperation.o: ../src/operations/headOperation.h
../src/operations/headOperation.o: ../src/visitors/durationvisitor.h
../src/operations/headOperation.o: ../src/lib/tree_browser.h
../src/operations/headOperation.o: ../src/lib/browser.h
../src/operations/headOperation.o: ../src/operations/operation.h
../src/operations/interleaveOperation.o: ../src/visitors/clonevisitor.h
../src/operations/interleaveOperation.o: ../src/lib/export.h
../src/operations/interleaveOperation.o: ../src/guido/guidoelement.h
../src/operations/interleaveOperation.o: ../src/visitors/visitable.h
../src/operations/interleaveOperation.o: ../src/visitors/basevisitor.h
../src/operations/interleaveOperation.o: ../src/lib/ctree.h
../src/operations/interleaveOperation.o: ../src/lib/smartpointer.h
../src/operations/interleaveOperation.o: ../src/guido/abstract/ARTypes.h
../src/operations/interleaveOperation.o: ../src/guido/guidotags.h
../src/operations/interleaveOperation.o: ../src/visitors/visitor.h
../src/operations/interleaveOperation.o: ../src/visitors/durationvisitor.h
../src/operations/interleaveOperation.o: ../src/lib/rational.h
../src/operations/interleaveOperation.o: ../src/lib/tree_browser.h
../src/operations/interleaveOperation.o: ../src/lib/browser.h
../src/operations/interleaveOperation.o: ../src/operations/interleaveOperation.h
../src/operations/interleaveOperation.o: ../src/operations/operation.h
../src/operations/interleaveOperation.o: ../src/visitors/counteventsvisitor.h
../src/operations/interleaveOperation.o: ../src/guido/abstract/ARFactory.h
../src/operations/interleaveOperation.o: ../src/lib/functor.h
../src/operations/interleaveOperation.o: ../src/lib/singleton.h
../src/operations/interleaveOperation.o: ../src/guido/abstract/ARNote.h
../src/operations/interleaveOperation.o: ../src/guido/abstract/AROthers.h
../src/operations/parOperation.o: ../src/visitors/clonevisitor.h
../src/operations/parOperation.o: ../src/lib/export.h
../src/operations/parOperation.o: ../src/guido/guidoelement.h
../src/operations/parOperation.o: ../src/visitors/visitable.h
../src/operations/parOperation.o: ../src/visitors/basevisitor.h
../src/operations/parOperation.o: ../src/lib/ctree.h
../src/operations/parOperation.o: ../src/lib/smartpointer.h
../src/operations/parOperation.o: ../src/guido/abstract/ARTypes.h
../src/operations/parOperation.o: ../src/guido/guidotags.h
../src/operations/parOperation.o: ../src/visitors/visitor.h
../src/operations/parOperation.o: ../src/visitors/durationvisitor.h
../src/operations/parOperation.o: ../src/lib/rational.h
../src/operations/parOperation.o: ../src/lib/tree_browser.h
../src/operations/parOperation.o: ../src/lib/browser.h
../src/operations/parOperation.o: ../src/operations/parOperation.h
../src/operations/parOperation.o: ../src/operations/operation.h
../src/operations/parOperation.o: ../src/guido/abstract/ARFactory.h
../src/operations/parOperation.o: ../src/lib/functor.h ../src/lib/singleton.h
../src/operations/parOperation.o: ../src/guido/abstract/ARNote.h
../src/operations/parOperation.o: ../src/guido/abstract/AROthers.h
../src/operations/seqOperation.o: ../src/visitors/clonevisitor.h
../src/operations/seqOperation.o: ../src/lib/export.h
../src/operations/seqOperation.o: ../src/guido/guidoelement.h
../src/operations/seqOperation.o: ../src/visitors/visitable.h
../src/operations/seqOperation.o: ../src/visitors/basevisitor.h
../src/operations/seqOperation.o: ../src/lib/ctree.h
../src/operations/seqOperation.o: ../src/lib/smartpointer.h
../src/operations/seqOperation.o: ../src/guido/abstract/ARTypes.h
../src/operations/seqOperation.o: ../src/guido/guidotags.h
../src/operations/seqOperation.o: ../src/visitors/visitor.h
../src/operations/seqOperation.o: ../src/operations/seqOperation.h
../src/operations/seqOperation.o: ../src/guido/abstract/ARTag.h
../src/operations/seqOperation.o: ../src/operations/operation.h
../src/operations/seqOperation.o: ../src/lib/rational.h
../src/operations/seqOperation.o: ../src/guido/abstract/ARFactory.h
../src/operations/seqOperation.o: ../src/lib/functor.h ../src/lib/singleton.h
../src/operations/seqOperation.o: ../src/guido/abstract/ARNote.h
../src/operations/seqOperation.o: ../src/guido/abstract/AROthers.h
../src/operations/seqOperation.o: ../src/lib/tree_browser.h
../src/operations/seqOperation.o: ../src/lib/browser.h
../src/operations/tailOperation.o: ../src/guido/abstract/ARNote.h
../src/operations/tailOperation.o: ../src/guido/guidoelement.h
../src/operations/tailOperation.o: ../src/lib/export.h
../src/operations/tailOperation.o: ../src/visitors/visitable.h
../src/operations/tailOperation.o: ../src/visitors/basevisitor.h
../src/operations/tailOperation.o: ../src/lib/ctree.h
../src/operations/tailOperation.o: ../src/lib/smartpointer.h
../src/operations/tailOperation.o: ../src/lib/rational.h
../src/operations/tailOperation.o: ../src/guido/abstract/AROthers.h
../src/operations/tailOperation.o: ../src/guido/abstract/ARTag.h
../src/operations/tailOperation.o: ../src/visitors/visitor.h
../src/operations/tailOperation.o: ../src/visitors/clonevisitor.h
../src/operations/tailOperation.o: ../src/guido/abstract/ARTypes.h
../src/operations/tailOperation.o: ../src/guido/guidotags.h
../src/operations/tailOperation.o: ../src/operations/tailOperation.h
../src/operations/tailOperation.o: ../src/visitors/durationvisitor.h
../src/operations/tailOperation.o: ../src/lib/tree_browser.h
../src/operations/tailOperation.o: ../src/lib/browser.h
../src/operations/tailOperation.o: ../src/operations/operation.h
../src/operations/transposeOperation.o: /usr/include/math.h
../src/operations/transposeOperation.o: /usr/include/features.h
../src/operations/transposeOperation.o: /usr/include/sys/cdefs.h
../src/operations/transposeOperation.o: /usr/include/bits/wordsize.h
../src/operations/transposeOperation.o: /usr/include/gnu/stubs.h
../src/operations/transposeOperation.o: /usr/include/gnu/stubs-32.h
../src/operations/transposeOperation.o: /usr/include/bits/huge_val.h
../src/operations/transposeOperation.o: /usr/include/bits/mathdef.h
../src/operations/transposeOperation.o: /usr/include/bits/mathcalls.h
../src/operations/transposeOperation.o: ../src/guido/abstract/ARNote.h
../src/operations/transposeOperation.o: ../src/guido/guidoelement.h
../src/operations/transposeOperation.o: ../src/lib/export.h
../src/operations/transposeOperation.o: ../src/visitors/visitable.h
../src/operations/transposeOperation.o: ../src/visitors/basevisitor.h
../src/operations/transposeOperation.o: ../src/lib/ctree.h
../src/operations/transposeOperation.o: ../src/lib/smartpointer.h
../src/operations/transposeOperation.o: ../src/lib/rational.h
../src/operations/transposeOperation.o: ../src/guido/abstract/ARFactory.h
../src/operations/transposeOperation.o: ../src/lib/functor.h
../src/operations/transposeOperation.o: ../src/lib/singleton.h
../src/operations/transposeOperation.o: ../src/guido/abstract/ARTypes.h
../src/operations/transposeOperation.o: ../src/guido/guidotags.h
../src/operations/transposeOperation.o: ../src/guido/abstract/AROthers.h
../src/operations/transposeOperation.o: ../src/guido/abstract/ARTag.h
../src/operations/transposeOperation.o: ../src/visitors/visitor.h
../src/operations/transposeOperation.o: ../src/visitors/clonevisitor.h
../src/operations/transposeOperation.o: ../src/operations/transposeOperation.h
../src/operations/transposeOperation.o: ../src/operations/operation.h
../src/operations/transposeOperation.o: ../src/lib/tree_browser.h
../src/operations/transposeOperation.o: ../src/lib/browser.h
../src/operations/vheadOperation.o: ../src/guido/abstract/AROthers.h
../src/operations/vheadOperation.o: ../src/lib/export.h
../src/operations/vheadOperation.o: ../src/guido/guidoelement.h
../src/operations/vheadOperation.o: ../src/visitors/visitable.h
../src/operations/vheadOperation.o: ../src/visitors/basevisitor.h
../src/operations/vheadOperation.o: ../src/lib/ctree.h
../src/operations/vheadOperation.o: ../src/lib/smartpointer.h
../src/operations/vheadOperation.o: ../src/guido/abstract/ARTag.h
../src/operations/vheadOperation.o: ../src/visitors/visitor.h
../src/operations/vheadOperation.o: ../src/operations/vheadOperation.h
../src/operations/vheadOperation.o: ../src/guido/abstract/ARTypes.h
../src/operations/vheadOperation.o: ../src/guido/guidotags.h
../src/operations/vheadOperation.o: ../src/visitors/clonevisitor.h
../src/operations/vheadOperation.o: ../src/operations/operation.h
../src/operations/vheadOperation.o: ../src/lib/tree_browser.h
../src/operations/vheadOperation.o: ../src/lib/browser.h
../src/operations/vtailOperation.o: ../src/guido/abstract/ARFactory.h
../src/operations/vtailOperation.o: ../src/lib/export.h ../src/lib/functor.h
../src/operations/vtailOperation.o: ../src/lib/singleton.h
../src/operations/vtailOperation.o: ../src/guido/abstract/ARTypes.h
../src/operations/vtailOperation.o: ../src/lib/smartpointer.h
../src/operations/vtailOperation.o: ../src/guido/guidotags.h
../src/operations/vtailOperation.o: ../src/guido/abstract/AROthers.h
../src/operations/vtailOperation.o: ../src/guido/guidoelement.h
../src/operations/vtailOperation.o: ../src/visitors/visitable.h
../src/operations/vtailOperation.o: ../src/visitors/basevisitor.h
../src/operations/vtailOperation.o: ../src/lib/ctree.h
../src/operations/vtailOperation.o: ../src/guido/abstract/ARTag.h
../src/operations/vtailOperation.o: ../src/visitors/visitor.h
../src/operations/vtailOperation.o: ../src/operations/vtailOperation.h
../src/operations/vtailOperation.o: ../src/visitors/clonevisitor.h
../src/operations/vtailOperation.o: ../src/operations/operation.h
../src/operations/vtailOperation.o: ../src/lib/tree_browser.h
../src/operations/vtailOperation.o: ../src/lib/browser.h
../src/parser/parser.o: ../src/parser/gmnreader.h ../src/guido/guidoelement.h
../src/parser/parser.o: ../src/lib/export.h ../src/visitors/visitable.h
../src/parser/parser.o: ../src/visitors/basevisitor.h ../src/lib/ctree.h
../src/parser/parser.o: ../src/lib/smartpointer.h ../src/lib/rational.h
../src/parser/parser.o: ../src/parser/guidoparse.cpp /usr/include/assert.h
../src/parser/parser.o: /usr/include/features.h /usr/include/sys/cdefs.h
../src/parser/parser.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
../src/parser/parser.o: /usr/include/gnu/stubs-32.h
../src/parser/parser.o: ../src/parser/guidoparse.hpp
../src/parser/parser.o: ../src/parser/guidolex.cpp /usr/include/stdio.h
../src/parser/parser.o: /usr/include/bits/types.h
../src/parser/parser.o: /usr/include/bits/typesizes.h /usr/include/libio.h
../src/parser/parser.o: /usr/include/_G_config.h /usr/include/wchar.h
../src/parser/parser.o: /usr/include/bits/wchar.h /usr/include/gconv.h
../src/parser/parser.o: /usr/include/bits/stdio_lim.h
../src/parser/parser.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
../src/parser/parser.o: /usr/include/errno.h /usr/include/bits/errno.h
../src/parser/parser.o: /usr/include/linux/errno.h /usr/include/asm/errno.h
../src/parser/parser.o: /usr/include/asm-generic/errno.h
../src/parser/parser.o: /usr/include/asm-generic/errno-base.h
../src/parser/parser.o: /usr/include/stdlib.h /usr/include/sys/types.h
../src/parser/parser.o: /usr/include/time.h /usr/include/endian.h
../src/parser/parser.o: /usr/include/bits/endian.h /usr/include/sys/select.h
../src/parser/parser.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
../src/parser/parser.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
../src/parser/parser.o: /usr/include/bits/pthreadtypes.h
../src/parser/parser.o: /usr/include/alloca.h /usr/include/math.h
../src/parser/parser.o: /usr/include/bits/huge_val.h
../src/parser/parser.o: /usr/include/bits/mathdef.h
../src/parser/parser.o: /usr/include/bits/mathcalls.h
../src/parser/parser.o: ../src/parser/unicode.cpp
../src/parser/guidoparser.o: ../src/parser/guidoparser.h /usr/include/stdio.h
../src/parser/guidoparser.o: /usr/include/features.h /usr/include/sys/cdefs.h
../src/parser/guidoparser.o: /usr/include/bits/wordsize.h
../src/parser/guidoparser.o: /usr/include/gnu/stubs.h
../src/parser/guidoparser.o: /usr/include/gnu/stubs-32.h
../src/parser/guidoparser.o: /usr/include/bits/types.h
../src/parser/guidoparser.o: /usr/include/bits/typesizes.h
../src/parser/guidoparser.o: /usr/include/libio.h /usr/include/_G_config.h
../src/parser/guidoparser.o: /usr/include/wchar.h /usr/include/bits/wchar.h
../src/parser/guidoparser.o: /usr/include/gconv.h
../src/parser/guidoparser.o: /usr/include/bits/stdio_lim.h
../src/parser/guidoparser.o: /usr/include/bits/sys_errlist.h
../src/parser/guidoparser.o: ../src/lib/export.h ../src/parser/gmnreader.h
../src/parser/guidoparser.o: ../src/guido/guidoelement.h
../src/parser/guidoparser.o: ../src/visitors/visitable.h
../src/parser/guidoparser.o: ../src/visitors/basevisitor.h ../src/lib/ctree.h
../src/parser/guidoparser.o: ../src/lib/smartpointer.h ../src/lib/rational.h
../src/parser/guidoparser.o: ../src/guido/abstract/ARTypes.h
../src/parser/guidoparser.o: ../src/guido/guidotags.h
../src/parser/guidoparser.o: ../src/guido/abstract/AROthers.h
../src/parser/guidoparser.o: ../src/guido/abstract/ARFactory.h
../src/parser/guidoparser.o: ../src/lib/functor.h ../src/lib/singleton.h
../src/parser/guidoparser.o: ../src/guido/abstract/ARChord.h
../src/parser/guidoparser.o: ../src/guido/abstract/ARNote.h
../src/parser/guidoparser.o: ../src/guido/abstract/ARTag.h
../src/parser/guidoparser.o: ../src/visitors/visitor.h
