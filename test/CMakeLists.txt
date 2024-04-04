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
        helper/MockNodeAdapter.hxx
        helper/MockNodeAdapter.cxx
        helper/Utility.hxx
		helper/UtilityCMA.hxx

		helper/serializers/SerializerCMAEnumOptions.hxx
		helper/serializers/SerializerCMAStringOptions.hxx
        helper/serializers/SerializerCMAValues.hxx
        helper/serializers/SerializersBaseElement.hxx
        helper/serializers/SerializersEnum.hxx
		helper/serializers/SerializersMap.hxx
		helper/serializers/SerializersSet.hxx
		helper/serializers/SerializersVariant.hxx
		helper/serializers/SerializersVector.hxx

		helper/structures/CMAEnumOptions.hxx
		helper/structures/CMAStringOptions.hxx
		helper/structures/CMAValues.hxx
		helper/structures/Enums.hxx
		helper/structures/Enums.cxx
		helper/structures/StructureBase.hxx
		helper/structures/StructureEnum.hxx
		helper/structures/StructureSet.hxx
		helper/structures/StructureMap.hxx
		helper/structures/StructureVariant.hxx
		helper/structures/StructureVector.hxx

		helper/files/BaseElementXML.hxx
		helper/files/BaseElementXML.cxx
		helper/files/SetElementXML.hxx
		helper/files/SetElementXML.cxx
		helper/files/EnumElementXML.hxx
		helper/files/EnumElementXML.cxx
		helper/files/MapElementXML.hxx
		helper/files/MapElementXML.cxx
		helper/files/VariantElementXML.hxx
		helper/files/VariantElementXML.cxx
		helper/files/VectorElementXML.hxx
		helper/files/VectorElementXML.cxx

        units/ArraySerializers.unit.cxx
        units/BaseSerializers.unit.cxx
        units/BaseSerializersXML.unit.cxx
		units/DoubleMapSerializers.unit.cxx
		units/DoubleMapSerializersXML.unit.cxx
		units/EnumSerializers.unit.cxx
		units/EnumSerializersXML.unit.cxx
		units/EnumMapSerializers.unit.cxx
		units/EnumMapSerializersXML.unit.cxx
		units/StringMapSerializersXML.unit.cxx
        units/MapKeyAsEnumSerializers.unit.cxx
        units/MapKeyAsStructureSerializers.unit.cxx
        units/MapKeyAsStructureSerializersXML.unit.cxx
		units/SetSerializers.unit.cxx
		units/SetSerializersXML.unit.cxx
		units/VariantSerializersXML.unit.cxx
		units/VectorSerializers.unit.cxx
		units/VectorSerializersXML.unit.cxx
		main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_TEST_NAME} gmock_main ${LIB_NAME})

add_test(NAME ${PROJECT_TEST_NAME}-runner COMMAND ${PROJECT_TEST_NAME} "${CMAKE_CURRENT_LIST_DIR}")

