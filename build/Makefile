#
# 
#

.PHONY : macos ios android win32 win64

system	:= $(shell uname -s)
ifeq ($(system), Darwin)
	TARGET = mac
else
ifeq ($(system), MINGW32_NT-6.1)
	TARGET = windows
else
ifeq ($(system), MINGW32_NT-6.2)
	TARGET = windows
else
ifeq ($(system), Linux)
	TARGET = linux
endif
endif
endif
endif


OUT  := guidoar.framework guidoar.tgz libguidoar.a
MACX := macos
IOS  := ios

# try to detect Visual Studio version used
ifeq ($(TARGET), windows)
 MSVC ?= C:\Program Files (x86)\Microsoft Visual Studio 12.0
 ifneq ($(wildcard "$(MSVC)"), "") 
  WIN32VS ?= Visual Studio 12 2013
  WIN64VS ?= $(WIN32VS) Win64
  endif
 else
 MSVC := C:\Program Files (x86)\Microsoft Visual Studio 10.0
 ifneq ($(wildcard "$(MSVC)"), "") 
  WIN32VS ?= Visual Studio 10
  WIN64VS ?= $(WIN32VS) Win64
 endif
endif

LINUX := linux

MIDIEXPORT ?= no
CMAKEOPT ?= -Wno-dev 
ifeq ($(MIDIEXPORT), yes)
	CMAKEOPT += -DMIDIEXPORT=yes
else
	CMAKEOPT += -DMIDIEXPORT=no
endif

all :
	make $(TARGET)

help :
	@echo guidoar makefile - Targets are :
	@echo "   all (default): build the guidoar library,"	
	@echo "                  the platform targets is automatically evaluated by the default target."	
	@echo 
	@echo "Platform targets to build the guidoar library are:"	
	@echo "   macos"	
	@echo "   ios"	
	@echo "   mac     (build also ios library)"	
	@echo "   windows (build 32 and 64 bits library)"	
	@echo "   linux"	
	@echo "   android      : build the guidoar static library for Android"	

#===============================================================
# building the library on Mac OS X
#===============================================================
.PHONY : $(MACX) $(IOS) $(MACX)/Release/guidoar.framework $(IOS)/Release-iphoneos/libguidoar.a

mac :
	make macos
	make $(IOS)	

$(MACX) : $(MACX)/guidoar.xcodeproj guidoar.framework guidoar.tgz

guidoar.framework :  $(MACX)/guidoar.xcodeproj  $(MACX)/Release/guidoar.framework
	rm -rf guidoar.framework
	cp -R $(MACX)/Release/guidoar.framework .

$(MACX)/Release/guidoar.framework :
	xcodebuild -jobs 8 -project $(MACX)/guidoar.xcodeproj -target ALL_BUILD -configuration Release

$(MACX)/guidoar.xcodeproj : CMakeLists.txt
	[ -d $(MACX) ] || mkdir $(MACX)
	cd $(MACX) && cmake .. -G Xcode $(CMAKEOPT)

guidoar.tgz : guidoar.framework
	tar czf guidoar.tgz guidoar.framework

#===============================================================
# building the library for iOS
#===============================================================
$(IOS) : $(IOS)/guidoar.xcodeproj libguidoar.a

libguidoar.a : $(IOS)/guidoar.xcodeproj $(IOS)/Release-iphoneos/libguidoar.a
	cp $(IOS)/Release-iphoneos/libguidoar.a .

$(IOS)/Release-iphoneos/libguidoar.a :
	xcodebuild -jobs 8 -project $(IOS)/guidoar.xcodeproj -target ALL_BUILD -configuration Release
 
ioscmake:
$(IOS)/guidoar.xcodeproj : CMakeLists.txt
	[ -d $(IOS) ] || mkdir $(IOS)
	cd $(IOS) && cmake .. -G Xcode $(CMAKEOPT) -DIOS=yes

macclean :
	rm -rf $(IOS) $(MACX) $(OUT)

iosclean :
	rm -rf $(IOS) libguidoar.a

#===============================================================
# building the library on windows
#===============================================================
.PHONY : win32 win64 win32/Release/guidoar.dll win64/Release/guidoar64.dll

windows :
	make win32
	make win64

win32 : win32/guidoar.sln guidoar.dll guidoar.lib 

guidoar.lib : guidoar.dll

guidoar.dll : win32/Release/guidoar.dll
	cp win32/Release/guidoar.dll .
	cp win32/Release/guidoar.lib .

win32/Release/guidoar.dll : win32/guidoar.sln
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild win32/guidoar.sln /maxcpucount:4 /p:Configuration=Release"

win32cmake:
win32/guidoar.sln : CMakeLists.txt
	[ -d win32 ] || mkdir win32
	cd win32 && cmake .. -G "$(WIN32VS)" $(CMAKEOPT)


win64 : win64/guidoar.sln guidoar64.dll guidoar64.lib 

guidoar64.lib : guidoar64.dll

guidoar64.dll : win64/Release/guidoar64.dll
	cp win64/Release/guidoar64.dll .
	cp win64/Release/guidoar64.lib .

win64/Release/guidoar64.dll : win64/guidoar.sln
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild win64/guidoar.sln /maxcpucount:4 /p:Configuration=Release"

win64cmake:
win64/guidoar.sln : CMakeLists.txt
	[ -d win64 ] || mkdir win64
	cd win64 && cmake .. -G "$(WIN64VS)" $(CMAKEOPT) -DMIDIEXPORT=yes

winclean:
	rm -rf win32 win64 guidoar*.lib guidoar.dll

#===============================================================
# building the library on linux
#===============================================================
.PHONY : $(LINUX) libguidoar.so

linux : $(LINUX)/Makefile libguidoar.so

libguidoar.so :  $(LINUX)/Makefile  $(LINUX)/libguidoar.so
	rm -rf guidoar*.so*
	make -C $(LINUX)
	cp -R $(LINUX)/libguidoar*.so* .

$(LINUX)/libguidoar.so : 
	make -C $(LINUX)
	
linuxcmake:
$(LINUX)/Makefile : CMakeLists.txt
	[ -d $(LINUX) ] || mkdir $(LINUX)
	cd $(LINUX) && cmake .. -G "Unix Makefiles" -DMIDIEXPORT=yes

linuxclean:
	rm -rf $(LINUX)

install:
	make -C $(LINUX) install


#===============================================================
# building the library for Android
#===============================================================
android :
	ndk-build -C android -j 4
	cp android/libs/armeabi/libguidoar.so android
	
androidclean:
	cd android && rm -rf libguidoar.so libs obj

