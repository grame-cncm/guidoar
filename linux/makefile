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

TOOLS = guidoread guidopar guidorpar guidoseq guidodur

.PHONY: $(TARGET)

all : $(TARGET) $(TOOLS)

$(TARGET) : $(OBJ)
	ar -ru $(TARGET) $(OBJ)
	ranlib  $(TARGET)

guidoread : ../tools/guidoread.cpp
	g++ ../tools/guidoread.cpp $(CXXFLAGS) libguidoar.a -o guidoread

guidopar : ../tools/guidopar.cpp
	g++ ../tools/guidopar.cpp $(CXXFLAGS) libguidoar.a -o guidopar

guidorpar : ../tools/guidorpar.cpp
	g++ ../tools/guidorpar.cpp $(CXXFLAGS) libguidoar.a -o guidorpar

guidoseq : ../tools/guidoseq.cpp
	g++ ../tools/guidoseq.cpp $(CXXFLAGS) libguidoar.a -o guidoseq

guidodur : ../tools/guidoduration.cpp
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
