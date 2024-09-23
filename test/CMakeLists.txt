include_directories("${PROJECT_SOURCE_DIR}")

set(PROJECT_TEST_NAME ${LIB_NAME}-test)

# Use FetchContent to manage GoogleTest
include(FetchContent)

if (NOT TARGET gtest)
    # Configure FetchContent to download GoogleTest
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
    )

    FetchContent_MakeAvailable(googletest)

    if (MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
endif()

# Add the test executable
add_executable(${PROJECT_TEST_NAME}
    helper/FileManipulation.hxx
    helper/FileManipulation.cxx
    helper/MockNodeAdapter.hxx
    helper/MockNodeAdapter.cxx
    helper/Utility.hxx
    helper/UtilityCMA.hxx

    helper/serializers/SerializerAttributes.hxx
    helper/serializers/SerializerCMAEnumOptions.hxx
    helper/serializers/SerializerCMAStringOptions.hxx
    helper/serializers/SerializerCMAValues.hxx
    helper/serializers/SerializersBaseElement.hxx
    helper/serializers/SerializersEnum.hxx
    helper/serializers/SerializersMap.hxx
    helper/serializers/SerializersSet.hxx
    helper/serializers/SerializersVariant.hxx
    helper/serializers/SerializersVector.hxx

    helper/structures/Attributes.hxx
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

    helper/files/AttributesXML.hxx
    helper/files/AttributesXML.cxx
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
    units/AttributesSerializers.unit.cxx
    units/BaseSerializers.unit.cxx
    units/BaseSerializersXML.unit.cxx
    units/DoubleMapSerializers.unit.cxx
    units/DoubleMapSerializersXML.unit.cxx
    units/EnumeratorsBase.unit.cxx
    units/EnumSerializers.unit.cxx
    units/EnumSerializersXML.unit.cxx
    units/EnumMapSerializers.unit.cxx
    units/EnumMapSerializersXML.unit.cxx
    units/StringMapSerializersXML.unit.cxx
    units/MapKeyAsEnumSerializers.unit.cxx
    units/MapKeyAsStructureSerializers.unit.cxx
    units/MapKeyAsStructureSerializersXML.unit.cxx
    units/MapSameChilds.unit.cxx
    units/SetSerializers.unit.cxx
    units/SetSerializersXML.unit.cxx
    units/VariantSerializersXML.unit.cxx
    units/VectorSerializers.unit.cxx
    units/VectorSerializersXML.unit.cxx
    main.cxx
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/test)

target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_TEST_NAME} gmock_main ${LIB_NAME})

set(TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")
target_compile_definitions(${PROJECT_TEST_NAME} PRIVATE TEST_DATA_DIR="${TEST_DATA_DIR}")

add_test(NAME ${PROJECT_TEST_NAME}-runner COMMAND ${PROJECT_TEST_NAME} "${CMAKE_CURRENT_LIST_DIR}")
