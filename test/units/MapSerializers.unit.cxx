#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElementXML.hxx"
#include "test/helper/structures/StructureMap.hxx"

#include "test/helper/FileManipulation.hxx"
#include "test/helper/serializers/SerializersMap.hxx"

class MapSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(MapSerializerTest, Reading)
{
    const std::string fileContent{Helper::testMapElementStringDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto mapEl{Helper::loadMapElementString(fileName)};

    const std::map<std::string, std::string> correct{{"Key1", "Value1"}, {"Key2", "Value2"}, {"Key3", "Value3"}};

    Helper::checkMapEquality(correct, mapEl.values);

    std::remove(fileName.c_str());
}

//TEST_F(MapSerializerTest, Writing)
//{
//    Helper::VectorElement vectorEl;
//    vectorEl.values = {1, 2, 3, 4, 5};
//
//    const std::string fileName{"TestWrite.xml"};
//
//    // Sometimes in debug mode the above file was not removed from the previous run. This is to ensure deletion.
//    std::remove(fileName.c_str());
//
//    Helper::saveVectorElement(vectorEl, fileName);
//
//    const auto loadedVector{Helper::loadVectorElement(fileName)};
//
//    constexpr auto tolerance{1e-6};
//    Helper::checkVectorValues(vectorEl.values, loadedVector.values, tolerance);
//
//    std::remove(fileName.c_str());
//}