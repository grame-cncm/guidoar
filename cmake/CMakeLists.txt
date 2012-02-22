#######################################
# CMAKE guidoar
#######################################
project(guidoar)
cmake_minimum_required(VERSION 2.6)

set(target guidoar)

#######################################
# version management
set (VERSION "0.90")
set (VERSIONSTR "v.0.90")

### for relative path to win32 libs
#if(COMMAND cmake_policy)
#      cmake_policy(SET CMP0003 NEW)
#endif()

if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()
 
if(UNIX)
	add_definitions(-Wall -DGCC)
endif()

if(APPLE)
	set (CMAKE_OSX_ARCHITECTURES "x86_64 i386 ppc")
	set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif()

if(WIN32)
 add_definitions(-DWINVER=0x0400 -DWIN32)
endif()


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
endif()

#######################################
# set includes
include_directories( ${INCL})
set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)


#######################################
# set library target
set(LIBCONTENT ${CORESRC} ${COREH})
if(WIN32)
	enable_language(RC)
	set(LIBCONTENT ${LIBCONTENT} ${GAR}/rsrc/libguidoar.rc)
endif()

add_library(${target} SHARED ${LIBCONTENT})
set_target_properties (${target} PROPERTIES DEFINE_SYMBOL GUIDOAR_EXPORTS)
set_target_properties (${target} PROPERTIES PUBLIC_HEADER "${COREH}")
set_target_properties (${target} PROPERTIES 
			FRAMEWORK TRUE 
			FRAMEWORK_VERSION A
			MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${VERSIONSTR}
			MACOSX_FRAMEWORK_BUNDLE_VERSION ${VERSION}
)

if(${USEMidiShare})
	message (STATUS "MidiShare support is on. Call cmake -DUSEMidiShare=0 to change.")
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
	
else()
	message (STATUS "MidiShare support is off. Use -DUSEMidiShare=1 to change.")
endif()


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
endforeach()

if(${USEMidiShare})
	target_link_libraries( guido2midi ${MSH})
	set_target_properties (guido2midi PROPERTIES COMPILE_FLAGS -I/usr/local/include)
endif()


if(UNIX AND NOT APPLE)
#######################################
# install setup
install ( TARGETS ${target}
    	LIBRARY DESTINATION /usr/local/lib
     	PUBLIC_HEADER DESTINATION /usr/local/include/guidoar
)

endif()
