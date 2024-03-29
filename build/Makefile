#
# Guido AR Makefile
#
#


TARGET := undefined

system	:= $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep -e MINGW -e MSYS > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), Darwin)
	GENERATOR ?= Xcode
	PREFIX ?= /usr/local
	PROJ ?= $(BUILDDIR)/guidoar.xcodeproj
	JOBS ?= -jobs 4
else
ifeq ($(system), MINGW)
	GENERATOR ?= "Visual Studio 14 2015 Win64"
	PROJ ?= $(BUILDDIR)/guidoar.sln
	JOBS ?= /maxcpucount:4
else
	GENERATOR ?= "Unix Makefiles"
	PREFIX ?= /usr/local
	PROJ ?= $(BUILDDIR)/Makefile
	JOBS ?= -j 4
endif
endif

.PHONY: ios android

BUILDDIR ?= guidoardir
MIDIEXPORT ?= yes
CMAKEOPT ?= -Wno-dev 

ifeq ($(MIDIEXPORT), yes)
	CMAKEOPT += -DMIDIEXPORT=yes
else
	CMAKEOPT += -DMIDIEXPORT=no
endif
BUILDOPT ?= --config Release


#===============================================================
all : $(PROJ)
	cmake --build $(BUILDDIR)  $(BUILDOPT) -- $(JOBS)

$(PROJ) : $(BUILDDIR)
	cd $(BUILDDIR) && cmake $(CMAKEOPT) .. -G $(GENERATOR)

cmake : $(BUILDDIR)
	cd $(BUILDDIR) && cmake $(CMAKEOPT) .. 

$(BUILDDIR) :
	mkdir $(BUILDDIR)

parser:
	make -C ../src/parser

localinstall:
	cp bin/guido* ~/bin

#===============================================================
help :
	@echo guidoar makefile - Targets are :
	@echo "   all (default): build the guidoar library,"
	@echo 
	@echo "Platform targets to build the guidoar library are:"	
	@echo "   ios"	
	@echo "   windows (build 32 and 64 bits library)"	
	@echo "   linux"	
	@echo "   android : build the guidoar static library for Android"	
	@echo "Misc:"
	@echo "   parser        : regenerate the parser"	
	@echo "   localinstall  : install tools in ~/bin"	

#===============================================================
# building the library for iOS
#===============================================================
ios : iosdir/guidoar.xcodeproj
	cd iosdir && cmake --build .  $(BUILDOPT) --target guidoar -- $(JOBS)

iosdir/guidoar.xcodeproj:
	@[ -d iosdir ] || mkdir iosdir
	cd iosdir && cmake -DIOS=yes -DMIDIEXPORT=$(MIDIEXPORT) -DIOS=on .. -G Xcode


#===============================================================
# building the library for Android
#===============================================================
android : PLATFORM ?= 22
android : J ?= 6
android :
	@echo "### Android platform is android-$(PLATFORM)"
	@echo "### Use PLATFORM=xx to change"
	ndk-build -C android -j $(J) APP_PLATFORM=android-$(PLATFORM)
	
androidclean:
	cd android && rm -rf libs obj


#===============================================================
# install target
#===============================================================
install:
	cmake --build $(BUILDDIR) --config Release --target install 


