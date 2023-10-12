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

TEST_F(DoubleMapSerializerTest, Reading)
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

TEST_F(DoubleMapSerializerTest, Writing)
{
    Helper::MapElementDouble mapEl;
    mapEl.values = {{"Value1", 23.856912},
                    {"Value2", 67.431280},
                    {"Value3", 14.903215},
                    {"Value4", 98.540127},
                    {"Value5", 51.284960}};

    const std::string fileName{"TestWrite.xml"};

    std::remove(fileName.c_str());

    Helper::saveMapElementDouble(mapEl, fileName);
    const auto loadedMap{Helper::loadMapElementDouble(fileName)};

    constexpr auto tolerance{1e-6};
    Helper::checkMapValues(mapEl.values, loadedMap.values, tolerance);

    std::remove(fileName.c_str());
}