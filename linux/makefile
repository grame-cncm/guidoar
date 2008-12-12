TARGET=libguidoar.a


BASE       = ../src
subprojects := $(BASE)/guido $(BASE)/guido/abstract $(BASE)/lib $(BASE)/parser $(BASE)/operations $(BASE)/visitors

HEADERS = $(wildcard $(BASE)/include/GUIDO*.h) \
	$(BASE)/include/VGDevice.h $(BASE)/include/GDeviceDefs.h \
	$(BASE)/include/ScoreSymbolMap.h $(BASE)/include/VScoreSymbolMap.h  $(BASE)/include/TRect.h

SRC = $(wildcard $(BASE)/guido/*.cpp $(BASE)/guido/abstract/*.cpp $(BASE)/lib/*.cpp $(BASE)/visitors/*.cpp \
			$(BASE)/operations/*.cpp) $(BASE)/parser/parser.cpp $(BASE)/parser/guidoparser.cpp

GCC=g++
OBJ = $(patsubst %.cpp, %.o, $(SRC))
CXXFLAGS = $(addprefix -I, $(subprojects))
LDFLAGS =  -lstdc++

TOOLS = guidoread guidopar guidorpar guidoseq guidodur guidoinfo \
	guidoev2time guidotime2ev guidoevhead guidoevtail \
	guidohead guidotail guidotranspose 
# guido2midi

.PHONY: $(TARGET)

all : $(TARGET) $(TOOLS)

$(TARGET) : $(OBJ)
	ar -ru $(TARGET) $(OBJ)
	ranlib  $(TARGET)

guidotranspose : ../tools/guidotranspose.cpp $(TARGET)
	$(GCC) ../tools/guidotranspose.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidotranspose

guidotail : ../tools/guidotail.cpp $(TARGET)
	$(GCC) ../tools/guidotail.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidotail

guidohead : ../tools/guidohead.cpp $(TARGET)
	$(GCC) ../tools/guidohead.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidohead

guidoevtail : ../tools/guidoevtail.cpp $(TARGET)
	$(GCC) ../tools/guidoevtail.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidoevtail

guidoevhead : ../tools/guidoevhead.cpp $(TARGET)
	$(GCC) ../tools/guidoevhead.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidoevhead

guidotime2ev : ../tools/guidotime2ev.cpp $(TARGET)
	$(GCC) ../tools/guidotime2ev.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidotime2ev

guidoev2time : ../tools/guidoev2time.cpp $(TARGET)
	$(GCC) ../tools/guidoev2time.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidoev2time

guidoinfo : ../tools/guidoinfo.cpp $(TARGET)
	$(GCC) ../tools/guidoinfo.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidoinfo

guido2midi : ../tools/guido2midi.cpp $(TARGET)
	$(GCC) ../tools/guido2midi.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guido2midi

guidoread : ../tools/guidoread.cpp $(TARGET)
	$(GCC) ../tools/guidoread.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidoread

guidopar : ../tools/guidopar.cpp $(TARGET)
	$(GCC) ../tools/guidopar.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidopar

guidorpar : ../tools/guidorpar.cpp $(TARGET)
	$(GCC) ../tools/guidorpar.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidorpar

guidoseq : ../tools/guidoseq.cpp $(TARGET)
	$(GCC) ../tools/guidoseq.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidoseq

guidodur : ../tools/guidoduration.cpp $(TARGET)
	$(GCC) ../tools/guidoduration.cpp $(CXXFLAGS) $(LDFLAGS) libguidoar.a -o guidodur

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

