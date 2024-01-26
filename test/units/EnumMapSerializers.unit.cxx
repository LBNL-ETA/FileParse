#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElementXML.hxx"
#include "test/helper/structures/StructureMap.hxx"

#include "test/helper/FileManipulation.hxx"

class EnumMapSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(EnumMapSerializerTest, ReadingEnumAsKey_String)
{
    const std::string fileContent{Helper::testMapElementDayStringDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto mapEl{Helper::loadMapElementEnum(fileName)};

    using Helper::Day;

    const std::map<Day, std::string> correct{
      {Day::Friday, "Happy"}, {Day::Saturday, "Relax"}, {Day::Monday, "Back to Work"}};

    Helper::checkMapEquality(correct, mapEl.days);

    std::remove(fileName.c_str());
}

TEST_F(EnumMapSerializerTest, WritingEnumAsKey_String)
{
    using Helper::Day;
    Helper::MapElementEnum mapEl;
    mapEl.days = {{Day::Monday, "Value1"},
                  {Day::Tuesday, "Value2"},
                  {Day::Wednesday, "Value3"},
                  {Day::Thursday, "Value4"},
                  {Day::Friday, "Value5"}};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveMapElementEnum(mapEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedMap{Helper::loadMapElementEnum(fileName)};

    Helper::checkMapEquality(mapEl.days, loadedMap.days);

    std::remove(fileName.c_str());
}

TEST_F(EnumMapSerializerTest, ReadingEnumAsKey_Double)
{
    const std::string fileContent{Helper::testMapElementDayDoubleDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto mapEl{Helper::loadMapElementEnumDouble(fileName)};

    using Helper::Day;

    const std::map<Day, double> correct{
      {Day::Monday, 47.8621}, {Day::Thursday, 83.2934}, {Day::Saturday, 12.7845}};

    Helper::checkMapEquality(correct, mapEl.days);

    std::remove(fileName.c_str());
}

TEST_F(EnumMapSerializerTest, WritingEnumAsKey_Double)
{
    using Helper::Day;
    Helper::MapElementEnumDouble mapEl;
    mapEl.days = {{Day::Monday, 21.5394},
                  {Day::Tuesday, 76.2843},
                  {Day::Wednesday, 43.9172},
                  {Day::Thursday, 95.0328},
                  {Day::Friday, 58.4627}};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveMapElementEnumDouble(mapEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedMap{Helper::loadMapElementEnumDouble(fileName)};

    Helper::checkMapEquality(mapEl.days, loadedMap.days);

    std::remove(fileName.c_str());
}