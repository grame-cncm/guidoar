#######################################
# CMAKE guidoar
#######################################
project(guidoar)
cmake_minimum_required(VERSION 2.6)

set(target guidoar)

#######################################
# version management
set (VERSION 1.00)
set (VERSIONSTR "v.1.00")
set (SOVERS 1)

if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()
 
if(UNIX)
	add_definitions(-Wall -DGCC)
endif()

#######################################
# windows support
if(WIN32)
 add_definitions(-DWINVER=0x0400 -DWIN32)
 if (${CMAKE_GENERATOR} MATCHES ".*Win64")
  set (WIN win64)
 else()
  set (WIN win32)
 endif ()
endif()


if(APPLE)
 	add_definitions(-DAPPLE)

#######################################
#   iOS support
	if ( IOS )
		message (STATUS "Generates project for iOS - Use -DIOS=no to change.")
		set (CMAKE_XCODE_EFFECTIVE_PLATFORMS "iPhoneOS")
		set (CMAKE_OSX_ARCHITECTURES "arm64 armv7 armv7s")
		set (CMAKE_OSX_SYSROOT "iphoneos")
		set (libtype STATIC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGUIDOAR_EXPORTS -stdlib=libc++")
	else ()
		message (STATUS "Generates Mac OS project- Use -DIOS=yes to change.")
	 	#######################################
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
		set (CMAKE_C++_FLAGS -mmacosx-version-min=10.7)
		set (CMAKE_LDFLAGS -mmacosx-version-min=10.7)
		set (CMAKE_OSX_DEPLOYMENT_TARGET 10.7)
		set (MACOSX_DEPLOYMENT_TARGET 10.7)
	endif ()
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


#######################################
# set includes
include_directories( ${INCL} ${GARSRC}/midisharelight)
#set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)

#######################################
# midi export support
if (MIDIEXPORT STREQUAL "yes")
	message (STATUS "MIDI export will be generated (requires MidiShareLight) - Use -DMIDIEXPORT=no to change.")
	add_definitions(-DMIDIEXPORT)	
	if (WIN32)
		if (${CMAKE_CL_64})
			set(LINK ${LINK} " ${GARSRC}/midisharelight/win64/midisharelight64.lib")
		else()
			set(LINK ${LINK} " ${GARSRC}/midisharelight/win32/midisharelight.lib")
		endif()
	elseif(APPLE)
		set(LINK ${LINK} "-L${GARSRC}/midisharelight/macos -lmidisharelight")
	elseif(UNIX)
		set(LINK ${LINK} "-L/usr/local/lib -lmidisharelight")
	endif (WIN32)
else()
	message (STATUS "MIDI export will not be generated - Use -DMIDIEXPORT=yes to change (requires MidiShareLight).")
endif()


#######################################
# set library target
set(LIBCONTENT ${CORESRC} ${COREH})
if(WIN32)
	enable_language(RC)
	set(LIBCONTENT ${LIBCONTENT} ${GAR}/rsrc/libguidoar.rc)
endif()

if (IOS)
	add_library(${target} STATIC ${LIBCONTENT})

else()
	add_library(${target} SHARED ${LIBCONTENT})
	set_target_properties (${target} PROPERTIES DEFINE_SYMBOL GUIDOAR_EXPORTS)
	set_target_properties (${target} PROPERTIES PUBLIC_HEADER "${COREH}")
	set_target_properties (${target} PROPERTIES 
			FRAMEWORK TRUE 
			FRAMEWORK_VERSION A
			VERSION ${VERSION}
			SOVERSION ${SOVERS}
			MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${VERSIONSTR}
			MACOSX_FRAMEWORK_BUNDLE_VERSION ${VERSION}
	)
endif()

if(APPLE)
	set (LINK "-L${GARSRC}/midisharelight/macos -lmidisharelight -lc++")
elseif(UNIX)
	set (LINK "-L/usr/local/lib -lmidisharelight")
elseif(WIN32)
	set (LINK "${GARSRC}/midisharelight/${WIN}/midisharelight.lib")
endif()
target_link_libraries( ${target} ${LINK})


#######################################
# set tools targets
if (NOT IOS)

file (GLOB TOOLS RELATIVE ${GARTOOLS} "${GARTOOLS}/*.cpp")

foreach(toolcpp ${TOOLS})
	string(REPLACE ".cpp" "" tool ${toolcpp})
	add_executable( ${tool} ${GARTOOLS}/${tool}.cpp )
	target_link_libraries( ${tool} ${target})
	add_dependencies(${tool} ${target})
endforeach()

if(${USEMidiShare})
	target_link_libraries( guido2midi ${MSH})
	set_target_properties (guido2midi PROPERTIES COMPILE_FLAGS -I/usr/local/include)
endif()
endif()


if(UNIX AND NOT APPLE)
#######################################
# install setup
install ( TARGETS ${target}
    	LIBRARY DESTINATION /usr/lib
     	PUBLIC_HEADER DESTINATION /usr/local/include/guidoar
)

endif()
