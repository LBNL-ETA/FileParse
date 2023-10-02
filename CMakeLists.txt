cmake_minimum_required(VERSION 3.5)

project( FileParse VERSION 0.0.1 LANGUAGES CXX )
set(LIB_NAME ${PROJECT_NAME})

if(NOT "${CMAKE_CXX_STANDARD}")
	set(CMAKE_CXX_STANDARD 17)
endif()

if(NOT "${CMAKE_CXX_EXTENSIONS}")
	set(CMAKE_CXX_EXTENSIONS OFF)
endif()

include(GNUInstallDirs)
if(NOT "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()

if(NOT "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()

if(NOT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
endif()

include(CMakeLists-XMLParser.txt)

set(XMLParser_LIB $<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/lib/Debug/XMLParser.lib,${CMAKE_BINARY_DIR}/lib/Release/XMLParser.lib>)

add_subdirectory(src)

target_include_directories(${LIB_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

Option(BUILD_FileParse_tests "Build FileParse tests." ON)

if(BUILD_FileParse_tests)
	enable_testing()
	add_subdirectory( test )
endif()