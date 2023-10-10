include_directories("${PROJECT_SOURCE_DIR}")

set(PROJECT_TEST_NAME ${LIB_NAME}-test)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

add_executable(${PROJECT_TEST_NAME}
        helper/FileManipulation.hxx
        helper/FileManipulation.cxx

		helper/serializers/TestBaseElementSerializers.hxx
		helper/serializers/TestBaseElementSerializers.cxx
		helper/serializers/TestVectorSerializers.hxx
		helper/serializers/TestVectorSerializers.cxx
		helper/serializers/TestEnumSerializers.hxx
		helper/serializers/TestEnumSerializers.cxx

        helper/TestStructures.hxx
        helper/files/TestBaseElementXML.hxx
        helper/files/TestBaseElementXML.cxx
        helper/files/TestVectorElementXML.hxx
        helper/files/TestVectorElementXML.cxx
        helper/files/TestEnumElementXML.hxx
        helper/files/TestEnumElementXML.cxx
		helper/Utility.hxx
		units/BaseSerializers.unit.cxx
		units/EnumSerializers.unit.cxx
		units/VectorSerializers.unit.cxx
		main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)

target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_TEST_NAME} gmock_main ${LIB_NAME})

add_test(NAME ${PROJECT_TEST_NAME}-runner COMMAND ${PROJECT_TEST_NAME} "${CMAKE_CURRENT_LIST_DIR}")

