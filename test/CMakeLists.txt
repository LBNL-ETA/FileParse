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

		helper/serializers/BaseElementSerializers.hxx
		helper/serializers/BaseElementSerializers.cxx
		helper/serializers/EnumSerializers.hxx
		helper/serializers/EnumSerializers.cxx
		helper/serializers/SetSerializers.hxx
		helper/serializers/SetSerializers.cxx
		helper/serializers/VectorSerializers.hxx
		helper/serializers/VectorSerializers.cxx

		helper/structures/Enums.hxx
		helper/structures/StructureBase.hxx
		helper/structures/StructureEnum.hxx
		helper/structures/StructureSet.hxx
		helper/structures/StructureVector.hxx

		helper/files/BaseElementXML.hxx
		helper/files/BaseElementXML.cxx
		helper/files/VectorElementXML.hxx
		helper/files/VectorElementXML.cxx
		helper/files/SetElementXML.hxx
		helper/files/SetElementXML.cxx
		helper/files/EnumElementXML.hxx
		helper/files/EnumElementXML.cxx

		helper/Utility.hxx

		units/BaseSerializers.unit.cxx
		units/EnumSerializers.unit.cxx
		units/SetSerializers.unit.cxx
		units/VectorSerializers.unit.cxx
		main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)

target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_TEST_NAME} gmock_main ${LIB_NAME})

add_test(NAME ${PROJECT_TEST_NAME}-runner COMMAND ${PROJECT_TEST_NAME} "${CMAKE_CURRENT_LIST_DIR}")

