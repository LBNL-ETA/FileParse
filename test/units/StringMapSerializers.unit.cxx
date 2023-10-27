#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElementXML.hxx"
#include "test/helper/structures/StructureMap.hxx"

#include "test/helper/FileManipulation.hxx"

class StringMapSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(StringMapSerializerTest, ReadingStringMap)
{
    const std::string fileContent{Helper::testMapElementStringDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto mapEl{Helper::loadMapElementString(fileName)};

    const std::map<std::string, std::string> correctOrdered{{"Key1", "Value1"}, {"Key2", "Value2"}, {"Key3", "Value3"}};
    const std::unordered_map<std::string, std::string> correctUnordered{{"K1", "V1"}, {"K2", "V2"}, {"K3", "V3"}};

    Helper::checkMapEquality(correctOrdered, mapEl.ordered);
    Helper::checkMapEquality(correctUnordered, mapEl.unordered);

    std::remove(fileName.c_str());
}

TEST_F(StringMapSerializerTest, WritingStringMap)
{
    Helper::MapElementString mapEl;
    mapEl.ordered = {{"1", "Value1"}, {"2", "Value2"}, {"3", "Value3"}, {"4", "Value4"}, {"5", "Value5"}};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    Helper::saveMapElementDouble(mapEl, fileName);

    const auto loadedMap{Helper::loadMapElementString(fileName)};

    Helper::checkMapEquality(mapEl.ordered, loadedMap.ordered);

    std::remove(fileName.c_str());
}

TEST_F(StringMapSerializerTest, ReadingOptionalStringMap)
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

TEST_F(StringMapSerializerTest, WritingOptionalStringMap)
{
    Helper::MapElementOptionalString mapEl;
    mapEl.values = {{"o1", "1"}, {"o2", "2"}, {"o3", "3"}, {"o4", "4"}, {"o5", "5"}};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    Helper::saveMapElementOptionalDouble(mapEl, fileName);

    const auto loadedMap{Helper::loadMapElementOptionalString(fileName)};

    ASSERT_EQ(true, loadedMap.values.has_value());

    Helper::checkMapEquality(mapEl.values.value(), loadedMap.values.value());

    std::remove(fileName.c_str());
}

TEST_F(StringMapSerializerTest, ReadingEmpty)
{
    const std::string fileContent{Helper::testMapElementEmptyStringDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto mapEl{Helper::loadMapElementString(fileName)};

    EXPECT_EQ(0u, mapEl.ordered.size());

    std::remove(fileName.c_str());
}

TEST_F(StringMapSerializerTest, WritingEmpty)
{
    Helper::MapElementString mapEl;

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    Helper::saveMapElementDouble(mapEl, fileName);

    const auto loadedVector{Helper::loadMapElementString(fileName)};

    EXPECT_EQ(mapEl.ordered.size(), loadedVector.ordered.size());

    std::remove(fileName.c_str());
}