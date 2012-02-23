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

if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()
 
if(UNIX)
	add_definitions(-Wall -DGCC)
endif()

if(APPLE)
	set (CMAKE_OSX_ARCHITECTURES "x86_64 i386")
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


#######################################
# set includes
include_directories( ${INCL} ${GARSRC}/midisharelight)
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

if(APPLE)
	set (MSH "-L${GARSRC}/midisharelight/macos -lmidisharelight")
elseif(UNIX)
	set (MSH "-L/usr/local/lib -lmidisharelight")
elseif(WIN32)
	set (MSH "${GARSRC}/midisharelight/win32/midisharelight.lib")
endif()
target_link_libraries( ${target} ${MSH})


#######################################
# set tools targets
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


if(UNIX AND NOT APPLE)
#######################################
# install setup
install ( TARGETS ${target}
    	LIBRARY DESTINATION /usr/local/lib
     	PUBLIC_HEADER DESTINATION /usr/local/include/guidoar
)

endif()
