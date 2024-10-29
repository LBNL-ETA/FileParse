cmake_minimum_required(VERSION 3.5)
project(FileParse CXX)
set(LIB_NAME ${PROJECT_NAME})

# Set the runtime library to dynamic for all configurations in MSVC
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(LIB_MAJOR_VERSION "1")
set(LIB_MINOR_VERSION "0")
set(LIB_PATCH_VERSION "1")
set(LIB_VERSION_STRING "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")

# Set C++ standard and extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Include additional CMake files
set(xmlParser_Branch "v1.0.1")

include(FetchContent)
FetchContent_Declare(
  XMLParser
  GIT_REPOSITORY https://github.com/LBNL-ETA/XMLParser.git
  GIT_TAG ${xmlParser_Branch}
)
FetchContent_MakeAvailable(XMLParser)

# Assuming the target name is xmlParser
target_include_directories(xmlParser SYSTEM PUBLIC ${xmlParser_INCLUDE_DIRS})

add_subdirectory(include/fileParse)

# Include directories for targets
target_include_directories(${LIB_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(BUILD_FileParse_tests "Build FileParse tests." ON)

if(BUILD_FileParse_tests)
    enable_testing()
    add_subdirectory(test)
endif()

# Explicitly set the runtime library for each target
if (MSVC)
    set_target_properties(${LIB_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    # Set runtime for tests if enabled
    if(TARGET FileParse-test)
        set_target_properties(FileParse-test PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()

    # Repeat for other targets, including any third-party or external targets
endif()
