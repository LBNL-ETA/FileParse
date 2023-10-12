#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElementXML.hxx"
#include "test/helper/structures/StructureMap.hxx"

#include "test/helper/FileManipulation.hxx"
#include "test/helper/serializers/SerializersMap.hxx"

class DoubleMapSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(DoubleMapSerializerTest, ReadingStringMap)
{
    const std::string fileContent{Helper::testMapElementDoubleDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto mapEl{Helper::loadMapElementDouble(fileName)};

    const std::map<std::string, double> correct{{"Key1", 37.582914}, {"Key2", 92.143057}, {"Key3", 15.907634}};

    constexpr auto tolerance{1e-6};
    Helper::checkMapValues(correct, mapEl.values, tolerance);

    std::remove(fileName.c_str());
}

//TEST_F(StringMapSerializerTest, WritingStringMap)
//{
//    Helper::MapElementString mapEl;
//    mapEl.values = {{"1", "Value1"}, {"2", "Value2"}, {"3", "Value3"}, {"4", "Value4"}, {"5", "Value5"}};
//
//    const std::string fileName{"TestWrite.xml"};
//
//    std::remove(fileName.c_str());
//
//    Helper::saveSetElementDouble(mapEl, fileName);
//
//    const auto loadedMap{Helper::loadMapElementString(fileName)};
//
//    Helper::checkMapEquality(mapEl.values, loadedMap.values);
//
//    std::remove(fileName.c_str());
//}
//
//TEST_F(StringMapSerializerTest, ReadingOptionalStringMap)
//{
//    const std::string fileContent{Helper::testMapElementOptionalStringDatabase()};
//    const std::string fileName{"TestRead.xml"};
//
//    File::createFileFromString(fileName, fileContent);
//
//    const auto mapEl{Helper::loadMapElementOptionalString(fileName)};
//
//    const std::map<std::string, std::string> correct{
//      {"Key1", "Optional1"}, {"Key2", "Optional2"}, {"Key3", "Optional3"}};
//
//    ASSERT_EQ(true, mapEl.values.has_value());
//
//    Helper::checkMapEquality(correct, mapEl.values.value());
//
//    std::remove(fileName.c_str());
//}
//
//TEST_F(StringMapSerializerTest, WritingOptionalStringMap)
//{
//    Helper::MapElementOptionalString mapEl;
//    mapEl.values = {{"o1", "1"}, {"o2", "2"}, {"o3", "3"}, {"o4", "4"}, {"o5", "5"}};
//
//    const std::string fileName{"TestWrite.xml"};
//
//    std::remove(fileName.c_str());
//
//    Helper::saveSetElementOptionalDouble(mapEl, fileName);
//
//    const auto loadedMap{Helper::loadMapElementOptionalString(fileName)};
//
//    ASSERT_EQ(true, loadedMap.values.has_value());
//
//    Helper::checkMapEquality(mapEl.values.value(), loadedMap.values.value());
//
//    std::remove(fileName.c_str());
//}
//
//TEST_F(StringMapSerializerTest, ReadingEmpty)
//{
//    const std::string fileContent{Helper::testMapElementEmptyStringDatabase()};
//    const std::string fileName{"TestRead.xml"};
//
//    File::createFileFromString(fileName, fileContent);
//
//    const auto mapEl{Helper::loadMapElementString(fileName)};
//
//    EXPECT_EQ(0u, mapEl.values.size());
//
//    std::remove(fileName.c_str());
//}
//
//TEST_F(StringMapSerializerTest, WritingEmpty)
//{
//    Helper::MapElementString mapEl;
//
//    const std::string fileName{"TestWrite.xml"};
//
//    std::remove(fileName.c_str());
//
//    Helper::saveSetElementDouble(mapEl, fileName);
//
//    const auto loadedVector{Helper::loadMapElementString(fileName)};
//
//    EXPECT_EQ(mapEl.values.size(), loadedVector.values.size());
//
//    std::remove(fileName.c_str());
//}