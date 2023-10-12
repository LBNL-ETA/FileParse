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

TEST_F(MapSerializerTest, ReadingStringMap)
{
    const std::string fileContent{Helper::testMapElementStringDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto mapEl{Helper::loadMapElementString(fileName)};

    const std::map<std::string, std::string> correct{{"Key1", "Value1"}, {"Key2", "Value2"}, {"Key3", "Value3"}};

    Helper::checkMapEquality(correct, mapEl.values);

    std::remove(fileName.c_str());
}

TEST_F(MapSerializerTest, WritingStringMap)
{
    Helper::MapElementString mapEl;
    mapEl.values = {{"1", "Value1"}, {"2", "Value2"}, {"3", "Value3"}, {"4", "Value4"}, {"5", "Value5"}};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    Helper::saveSetElementDouble(mapEl, fileName);

    const auto loadedMap{Helper::loadMapElementString(fileName)};

    Helper::checkMapEquality(mapEl.values, loadedMap.values);

    std::remove(fileName.c_str());
}

TEST_F(MapSerializerTest, ReadingOptionalStringMap)
{
    const std::string fileContent{Helper::testMapElementOptionalStringDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto mapEl{Helper::loadMapElementOptionalString(fileName)};

    const std::map<std::string, std::string> correct{
      {"Key1", "Optional1"}, {"Key2", "Optional2"}, {"Key3", "Optional3"}};

    ASSERT_EQ(true, mapEl.values.has_value());

    Helper::checkMapEquality(correct, mapEl.values.value());

    std::remove(fileName.c_str());
}

TEST_F(MapSerializerTest, WritingOptionalStringMap)
{
    Helper::MapElementOptionalString mapEl;
    mapEl.values = {{"o1", "1"}, {"o2", "2"}, {"o3", "3"}, {"o4", "4"}, {"o5", "5"}};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    Helper::saveSetElementOptionalDouble(mapEl, fileName);

    const auto loadedMap{Helper::loadMapElementOptionalString(fileName)};

    ASSERT_EQ(true, loadedMap.values.has_value());

    Helper::checkMapEquality(mapEl.values.value(), loadedMap.values.value());

    std::remove(fileName.c_str());
}