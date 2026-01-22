/// EnumMap file serialization tests (XML, JSON, and unified)
#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"
#include "test/helper/files/MapElement.hxx"
#include "test/helper/structures/StructureMap.hxx"

class EnumMapSerializerFileTest : public testing::Test
{
protected:
    void TearDown() override
    {
        for(const auto & file : tempFiles)
        {
            std::remove(file.c_str());
        }
    }

    void addTempFile(const std::string & name)
    {
        tempFiles.push_back(name);
    }

    std::vector<std::string> tempFiles;
};

//////////////////////////////////////////////////////////////////////////////
// XML-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(EnumMapSerializerFileTest, ReadEnumStringXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapEnumString.xml";

    const auto mapEl{Helper::loadMapElementEnumXML(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    using Helper::Day;
    const std::map<Day, std::string> correct{
      {Day::Friday, "Happy"}, {Day::Saturday, "Relax"}, {Day::Monday, "Back to Work"}};
    Helper::checkMapEquality(correct, mapEl->days);
}

TEST_F(EnumMapSerializerFileTest, WriteAndReadEnumStringXML)
{
    const std::string fileName{"TestWriteEnumMap.xml"};
    addTempFile(fileName);

    using Helper::Day;
    Helper::MapElementEnum mapEl;
    mapEl.days = {{Day::Monday, "Value1"}, {Day::Tuesday, "Value2"}, {Day::Wednesday, "Value3"}};

    const auto result{Helper::saveMapElementEnumXML(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementEnumXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(mapEl.days, loaded->days);
}

TEST_F(EnumMapSerializerFileTest, ReadEnumDoubleXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapEnumAsKey.xml";

    const auto mapEl{Helper::loadMapElementEnumDoubleXML(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    using Helper::Day;
    const std::map<Day, double> correct{
      {Day::Monday, 47.8621}, {Day::Thursday, 83.2934}, {Day::Saturday, 12.7845}};
    Helper::checkMapEquality(correct, mapEl->days);
}

TEST_F(EnumMapSerializerFileTest, WriteAndReadEnumDoubleXML)
{
    const std::string fileName{"TestWriteEnumDoubleMap.xml"};
    addTempFile(fileName);

    using Helper::Day;
    Helper::MapElementEnumDouble mapEl;
    mapEl.days = {{Day::Monday, 21.5394}, {Day::Tuesday, 76.2843}, {Day::Wednesday, 43.9172}};

    const auto result{Helper::saveMapElementEnumDoubleXML(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementEnumDoubleXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(mapEl.days, loaded->days);
}

//////////////////////////////////////////////////////////////////////////////
// JSON-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(EnumMapSerializerFileTest, ReadEnumStringJSON)
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

TEST_F(EnumMapSerializerFileTest, WriteAndReadEnumStringJSON)
{
    const std::string fileName{"TestWriteEnumMap.json"};
    addTempFile(fileName);

    using Helper::Day;
    Helper::MapElementEnum mapEl;
    mapEl.days = {{Day::Monday, "Value1"}, {Day::Tuesday, "Value2"}, {Day::Wednesday, "Value3"}};

    const auto result{Helper::saveMapElementEnumJSON(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementEnumJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(mapEl.days, loaded->days);
}

TEST_F(EnumMapSerializerFileTest, ReadEnumDoubleJSON)
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

TEST_F(EnumMapSerializerFileTest, WriteAndReadEnumDoubleJSON)
{
    const std::string fileName{"TestWriteEnumDoubleMap.json"};
    addTempFile(fileName);

    using Helper::Day;
    Helper::MapElementEnumDouble mapEl;
    mapEl.days = {{Day::Monday, 21.5394}, {Day::Tuesday, 76.2843}, {Day::Wednesday, 43.9172}};

    const auto result{Helper::saveMapElementEnumDoubleJSON(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementEnumDoubleJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(mapEl.days, loaded->days);
}

//////////////////////////////////////////////////////////////////////////////
// Unified tests (auto-detect format)
//////////////////////////////////////////////////////////////////////////////

TEST_F(EnumMapSerializerFileTest, UnifiedReadEnumStringXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapEnumString.xml";

    const auto mapEl{Helper::loadMapElementEnum(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    using Helper::Day;
    const std::map<Day, std::string> correct{
      {Day::Friday, "Happy"}, {Day::Saturday, "Relax"}, {Day::Monday, "Back to Work"}};
    Helper::checkMapEquality(correct, mapEl->days);
}

TEST_F(EnumMapSerializerFileTest, UnifiedReadEnumStringJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapEnumString.json";

    const auto mapEl{Helper::loadMapElementEnum(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    using Helper::Day;
    const std::map<Day, std::string> correct{
      {Day::Friday, "Happy"}, {Day::Saturday, "Relax"}, {Day::Monday, "Back to Work"}};
    Helper::checkMapEquality(correct, mapEl->days);
}

TEST_F(EnumMapSerializerFileTest, UnifiedWriteAndReadXML)
{
    const std::string fileName{"TestWriteEnumMapUnified.xml"};
    addTempFile(fileName);

    using Helper::Day;
    Helper::MapElementEnum mapEl;
    mapEl.days = {{Day::Sunday, "Rest"}, {Day::Saturday, "Play"}};

    const auto result{Helper::saveMapElementEnum(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementEnum(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(mapEl.days, loaded->days);
}

TEST_F(EnumMapSerializerFileTest, UnifiedWriteAndReadJSON)
{
    const std::string fileName{"TestWriteEnumMapUnified.json"};
    addTempFile(fileName);

    using Helper::Day;
    Helper::MapElementEnum mapEl;
    mapEl.days = {{Day::Sunday, "Rest"}, {Day::Saturday, "Play"}};

    const auto result{Helper::saveMapElementEnum(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementEnum(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(mapEl.days, loaded->days);
}
