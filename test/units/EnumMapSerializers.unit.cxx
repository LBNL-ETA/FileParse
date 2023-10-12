#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElementXML.hxx"
#include "test/helper/structures/StructureMap.hxx"

#include "test/helper/FileManipulation.hxx"
#include "test/helper/serializers/SerializersMap.hxx"

class EnumMapSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(EnumMapSerializerTest, Reading)
{
    const std::string fileContent{Helper::testMapElementDayAsKeyDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    const auto mapEl{Helper::loadMapElementEnum(fileName)};

    using Helper::Day;

    const std::map<Day, std::string> correct{
      {Day::Friday, "Happy"}, {Day::Saturday, "Relax"}, {Day::Monday, "Back to Work"}};

    Helper::checkMapEquality(correct, mapEl.days);

    std::remove(fileName.c_str());
}

TEST_F(EnumMapSerializerTest, Writing)
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

    Helper::saveSetElementEnum(mapEl, fileName);

    const auto loadedMap{Helper::loadMapElementEnum(fileName)};

    Helper::checkMapEquality(mapEl.days, loadedMap.days);

    std::remove(fileName.c_str());
}