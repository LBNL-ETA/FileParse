#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElement.hxx"
#include "test/helper/structures/StructureMap.hxx"

class DoubleMapSerializerJSONTest : public testing::Test
{};

TEST_F(DoubleMapSerializerJSONTest, Reading)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapDouble.json";

    const auto mapEl{Helper::loadMapElementDoubleJSON(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const std::map<std::string, double> correct{
      {"Key1", 37.582914}, {"Key2", 92.143057}, {"Key3", 15.907634}};

    constexpr auto tolerance{1e-6};
    Helper::checkMapValues(correct, mapEl->values, tolerance);
}

TEST_F(DoubleMapSerializerJSONTest, Writing)
{
    Helper::MapElementDouble mapEl;
    mapEl.values = {{"Value1", 23.856912},
                    {"Value2", 67.431280},
                    {"Value3", 14.903215},
                    {"Value4", 98.540127},
                    {"Value5", 51.284960}};

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveMapElementDoubleJSON(mapEl, fileName)};
    EXPECT_EQ(result, 0);
    const auto loadedMap{Helper::loadMapElementDoubleJSON(fileName)};
    ASSERT_TRUE(loadedMap.has_value());

    constexpr auto tolerance{1e-6};
    Helper::checkMapValues(mapEl.values, loadedMap->values, tolerance);

    std::remove(fileName.c_str());
}
