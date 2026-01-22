#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElementJSON.hxx"
#include "test/helper/structures/StructureMap.hxx"

#include "test/helper/FileManipulation.hxx"

class EnumMapSerializerJSONTest : public testing::Test
{};

TEST_F(EnumMapSerializerJSONTest, ReadingEnumAsKey_String)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapEnumString.json";

    const auto mapEl{Helper::loadMapElementEnumJSON(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    using Helper::Day;

    const std::map<Day, std::string> correct{
      {Day::Friday, "Happy"}, {Day::Saturday, "Relax"}, {Day::Monday, "Back to Work"}};

    Helper::checkMapEquality(correct, mapEl->days);
}

TEST_F(EnumMapSerializerJSONTest, WritingEnumAsKey_String)
{
    using Helper::Day;
    Helper::MapElementEnum mapEl;
    mapEl.days = {{Day::Monday, "Value1"},
                  {Day::Tuesday, "Value2"},
                  {Day::Wednesday, "Value3"},
                  {Day::Thursday, "Value4"},
                  {Day::Friday, "Value5"}};

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveMapElementEnumJSON(mapEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedMap{Helper::loadMapElementEnumJSON(fileName)};
    ASSERT_TRUE(loadedMap.has_value());

    Helper::checkMapEquality(mapEl.days, loadedMap->days);

    std::remove(fileName.c_str());
}

TEST_F(EnumMapSerializerJSONTest, ReadingEnumAsKey_Double)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapEnumAsKey.json";

    const auto mapEl{Helper::loadMapElementEnumDoubleJSON(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    using Helper::Day;

    const std::map<Day, double> correct{
      {Day::Monday, 47.8621}, {Day::Thursday, 83.2934}, {Day::Saturday, 12.7845}};

    Helper::checkMapEquality(correct, mapEl->days);
}

TEST_F(EnumMapSerializerJSONTest, WritingEnumAsKey_Double)
{
    using Helper::Day;
    Helper::MapElementEnumDouble mapEl;
    mapEl.days = {{Day::Monday, 21.5394},
                  {Day::Tuesday, 76.2843},
                  {Day::Wednesday, 43.9172},
                  {Day::Thursday, 95.0328},
                  {Day::Friday, 58.4627}};

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveMapElementEnumDoubleJSON(mapEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedMap{Helper::loadMapElementEnumDoubleJSON(fileName)};
    ASSERT_TRUE(loadedMap.has_value());

    Helper::checkMapEquality(mapEl.days, loadedMap->days);

    std::remove(fileName.c_str());
}
