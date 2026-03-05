include_directories("${PROJECT_SOURCE_DIR}")

set(PROJECT_TEST_NAME ${LIB_NAME}-test)

# Use FetchContent to manage GoogleTest
include(FetchContent)

if (NOT TARGET gtest)
    # Configure FetchContent to download GoogleTest
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.16.0
    )

    FetchContent_MakeAvailable(googletest)

    if (MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif ()
endif ()

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
        helper/serializers/SerializersLanguages.hxx

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
        helper/structures/StructureLanguages.hxx

        helper/files/Attributes.hxx
        helper/files/Attributes.cxx
        helper/files/BaseElement.hxx
        helper/files/BaseElement.cxx
        helper/files/SetElement.hxx
        helper/files/SetElement.cxx
        helper/files/EnumElement.hxx
        helper/files/EnumElement.cxx
        helper/files/MapElement.hxx
        helper/files/MapElement.cxx
        helper/files/VariantElement.hxx
        helper/files/VariantElement.cxx
        helper/files/VectorElement.hxx
        helper/files/VectorElement.cxx

        units/ArraySerializers.unit.cxx
        units/BaseSerializers.unit.cxx
        units/EdgeCases.unit.cxx
        units/DoubleMapSerializers.unit.cxx
        units/EnumeratorsBase.unit.cxx
        units/EnumSerializers.unit.cxx
        units/EnumMapSerializers.unit.cxx
        units/MapKeyAsEnumSerializers.unit.cxx
        units/MapKeyAsStructureSerializers.unit.cxx
        units/MapSameChilds.unit.cxx
        units/SetSerializers.unit.cxx
        units/ToLower.unit.cxx
        units/VariantEdgeCases.unit.cxx
        units/VectorSerializers.unit.cxx
        units/XMLNodeAdapterEdgeCases.unit.cxx
        units/JSONNodeAdapter.unit.cxx
        units/UnifiedNodeAdapter.unit.cxx
        units/FileFormat.unit.cxx
        units/BaseSerializersFile.unit.cxx
        units/VectorSerializersFile.unit.cxx
        units/SetSerializersFile.unit.cxx
        units/EnumSerializersFile.unit.cxx
        units/DoubleMapSerializersFile.unit.cxx
        units/EnumMapSerializersFile.unit.cxx
        units/StringMapSerializersFile.unit.cxx
        units/MapKeyAsStructureSerializersFile.unit.cxx
        units/VariantSerializersFile.unit.cxx
        units/AttributesSerializersFile.unit.cxx
        units/languages/LanguageTestHelper.hxx
        units/languages/English.unit.cxx
        units/languages/ChineseSimplified.unit.cxx
        units/languages/ChineseTraditional.unit.cxx
        units/languages/Japanese.unit.cxx
        units/languages/Korean.unit.cxx
        units/languages/Arabic.unit.cxx
        units/languages/Hebrew.unit.cxx
        units/languages/Russian.unit.cxx
        units/languages/Greek.unit.cxx
        units/languages/Hindi.unit.cxx
        units/languages/Thai.unit.cxx
        units/languages/Georgian.unit.cxx
        units/languages/Armenian.unit.cxx
        units/languages/German.unit.cxx
        units/languages/French.unit.cxx
        units/languages/Spanish.unit.cxx
        units/languages/Portuguese.unit.cxx
        units/languages/Turkish.unit.cxx
        units/languages/Vietnamese.unit.cxx
        units/languages/Polish.unit.cxx
        units/languages/Czech.unit.cxx
        units/languages/Serbian.unit.cxx
        units/languages/SerbianLatin.unit.cxx
        units/languages/Swedish.unit.cxx
        units/languages/Amharic.unit.cxx
        units/languages/Bengali.unit.cxx
        units/languages/Tamil.unit.cxx
        units/languages/Ukrainian.unit.cxx
        units/languages/Emoji.unit.cxx
        main.cxx
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/test)

target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_TEST_NAME} gmock_main ${LIB_NAME})

set(TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")
target_compile_definitions(${PROJECT_TEST_NAME} PRIVATE TEST_DATA_DIR="${TEST_DATA_DIR}")

add_test(NAME ${PROJECT_TEST_NAME}-runner COMMAND ${PROJECT_TEST_NAME} "${CMAKE_CURRENT_LIST_DIR}")
