#######################################
# CMAKE libguidoar
#######################################
project(libguidoar)
cmake_minimum_required(VERSION 2.6)

#######################################
# version management
set (VERSION "0.90")
set (VERSIONSTR "v.0.90")

### for relative path to win32 libs
if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
    
if(UNIX)
	add_definitions(-Wall -DGCC)
endif(UNIX)

if(APPLE)
	set (CMAKE_OSX_ARCHITECTURES "x86_64 i386 ppc")
	set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif(APPLE)

if(WIN32)
 add_definitions(-DWINVER=0x0400 -DWIN32)
 if(${CMAKE_GENERATOR} STREQUAL "Visual Studio 6")
  add_definitions(-DVC6)
 elseif(${CMAKE_GENERATOR} STREQUAL "Visual Studio 8 2005")
  add_definitions(-DVC2005)
 endif(${CMAKE_GENERATOR} STREQUAL "Visual Studio 6")
endif(WIN32)


#######################################
# set directories, src and headers.
set (GAR 		${CMAKE_CURRENT_SOURCE_DIR}/..)
set (GARSRC 	${GAR}/src)
set (GARTOOLS   ${GAR}/tools)
set (SRCFOLDERS  interface guido guido/abstract lib operations visitors midi parser)

foreach(folder ${SRCFOLDERS})
	set(SRC ${SRC} "${GARSRC}/${folder}/*.cpp")			# add source files
endforeach(folder)
file (GLOB CORESRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})

foreach(folder ${SRCFOLDERS})
	set(HEADERS ${HEADERS} "${GARSRC}/${folder}/*.h")		# add header files
endforeach(folder)
file (GLOB COREH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

foreach(folder ${SRCFOLDERS})
	set(INCL ${INCL} "${GARSRC}/${folder}")				# add include folders
endforeach(folder)

if(WIN32)
	set(INCL ${INCL} "../win32")				# add win32 include
elseif(APPLE)
	set(INCL ${INCL} "/usr/local/include")
endif(WIN32)

#######################################
# set includes
include_directories( ${INCL})
set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)


#######################################
# set library target
if(APPLE OR WIN32)
	set(target libguidoar)
else(APPLE OR WIN32)
	set(target guidoar)
endif(APPLE OR WIN32)

if(WIN32)
	enable_language(RC)
	set(LIBCONTENT ${CORESRC} ${COREH} ${GAR}/win32/libguidoar.rc)
else(WIN32)
	set(LIBCONTENT ${CORESRC} ${COREH})
endif(WIN32)

add_library(${target} SHARED ${LIBCONTENT})
set_target_properties (${target} PROPERTIES DEFINE_SYMBOL GUIDOAR_EXPORTS)
set_target_properties (${target} PROPERTIES PUBLIC_HEADER "${COREH}")
set_target_properties (${target} PROPERTIES 
			FRAMEWORK TRUE 
			FRAMEWORK_VERSION A
			COMPILE_FLAGS -I/usr/local/include
			MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${VERSIONSTR}
			MACOSX_FRAMEWORK_BUNDLE_VERSION ${VERSION}
)

if(${USEMidiShare})
	message ("USEMidiShare is on. Call cmake -DUSEMidiShare=0 option to remove midishare support")
	if(APPLE)
		set (MSH "-framework MidiShare -framework Player" )
	elseif(UNIX)
		set (MSH "-lMidiShare -lPlayer" )
	elseif(WIN32)
		set (MSH "../win32/Player32" )
	endif(APPLE)
	target_link_libraries( ${target} ${MSH})
	set_target_properties (${target} PROPERTIES COMPILE_FLAGS -DUSEMidiShare)
	set (TOOLS 	${TOOLS} guido2midi)
	
else(${USEMidiShare})
	message ("call cmake -DUSEMidiShare=1 option to include midishare support")
endif(${USEMidiShare})


#######################################
# set sample targets
set (TOOLS 	${TOOLS}  
			guido2unrolled guidobottom guidoduration guidoev2time guidoevhead
			guidoevtail guidohead guidoinfo guidopar guidoread guidorpar 
			guidoseq guidotail guidotime2ev guidotop guidotranspose
			guidoapplyrythm guidoapplypitch)

foreach(sample ${TOOLS})
	add_executable( ${sample} ${GARTOOLS}/${sample}.cpp )
	target_link_libraries( ${sample} ${target})
	add_dependencies(${sample} ${target})
endforeach(sample)

if(${USEMidiShare})
	target_link_libraries( guido2midi ${MSH})
	set_target_properties (guido2midi PROPERTIES COMPILE_FLAGS -I/usr/local/include)
endif(${USEMidiShare})



#######################################
# install setup
install ( TARGETS ${target}
    	LIBRARY DESTINATION lib
    	ARCHIVE DESTINATION lib
    	FRAMEWORK DESTINATION "/Library/Frameworks" CONFIGURATIONS Release
    	PUBLIC_HEADER DESTINATION include/libguidoar
)
