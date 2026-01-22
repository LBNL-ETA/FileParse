#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"

#include "test/helper/files/MapElement.hxx"
#include "test/helper/structures/StructureMap.hxx"

#include "test/helper/FileManipulation.hxx"

class StringMapSerializerJSONTest : public testing::Test
{};

TEST_F(StringMapSerializerJSONTest, ReadingStringMap)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapString.json";

    const auto mapEl{Helper::loadMapElementStringJSON(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const std::map<std::string, std::string> correctOrdered{
      {"Key1", "Value1"}, {"Key2", "Value2"}, {"Key3", "Value3"}};
    const std::unordered_map<std::string, std::string> correctUnordered{
      {"K1", "V1"}, {"K2", "V2"}, {"K3", "V3"}};

    Helper::checkMapEquality(correctOrdered, mapEl->ordered);
    Helper::checkMapEquality(correctUnordered, mapEl->unordered);
}

TEST_F(StringMapSerializerJSONTest, WritingStringMap)
{
    Helper::MapElementString mapEl;
    mapEl.ordered
      = {{"1", "Value1"}, {"2", "Value2"}, {"3", "Value3"}, {"4", "Value4"}, {"5", "Value5"}};

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveMapElementStringJSON(mapEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedMap{Helper::loadMapElementStringJSON(fileName)};
        ASSERT_TRUE(loadedMap.has_value());

    Helper::checkMapEquality(mapEl.ordered, loadedMap->ordered);

    std::remove(fileName.c_str());
}

TEST_F(StringMapSerializerJSONTest, ReadingOptionalStringMap)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapOptionalString.json";

    const auto mapEl{Helper::loadMapElementOptionalStringJSON(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const std::map<std::string, std::string> correct{
      {"Key1", "Optional1"}, {"Key2", "Optional2"}, {"Key3", "Optional3"}};

    ASSERT_EQ(true, mapEl->values.has_value());

    Helper::checkMapEquality(correct, mapEl->values.value());
}

TEST_F(StringMapSerializerJSONTest, WritingOptionalStringMap)
{
    Helper::MapElementOptionalString mapEl;
    mapEl.values = {{"o1", "1"}, {"o2", "2"}, {"o3", "3"}, {"o4", "4"}, {"o5", "5"}};

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveMapElementOptionalStringJSON(mapEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedMap{Helper::loadMapElementOptionalStringJSON(fileName)};
    ASSERT_TRUE(loadedMap.has_value());

    ASSERT_EQ(true, loadedMap->values.has_value());

    Helper::checkMapEquality(mapEl.values.value(), loadedMap->values.value());

    std::remove(fileName.c_str());
}

TEST_F(StringMapSerializerJSONTest, ReadingEmpty)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapEmptyOptionalString.json";

    const auto mapEl{Helper::loadMapElementStringJSON(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    EXPECT_EQ(0u, mapEl->ordered.size());
}

TEST_F(StringMapSerializerJSONTest, WritingEmpty)
{
    Helper::MapElementString mapEl;

    const std::string fileName{"TestWrite.json"};

    std::remove(fileName.c_str());

    const auto result{Helper::saveMapElementStringJSON(mapEl, fileName)};
    EXPECT_EQ(result, 0);

    const auto loadedVector{Helper::loadMapElementStringJSON(fileName)};

    EXPECT_EQ(mapEl.ordered.size(), loadedVector->ordered.size());

    std::remove(fileName.c_str());
}
