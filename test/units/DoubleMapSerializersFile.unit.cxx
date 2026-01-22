/// DoubleMap file serialization tests (XML, JSON, and unified)
#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"
#include "test/helper/files/MapElement.hxx"
#include "test/helper/structures/StructureMap.hxx"

class DoubleMapSerializerFileTest : public testing::Test
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
    static constexpr auto tolerance{1e-6};
};

//////////////////////////////////////////////////////////////////////////////
// XML-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(DoubleMapSerializerFileTest, ReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapDouble.xml";

    const auto mapEl{Helper::loadMapElementDoubleXML(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const std::map<std::string, double> correct{
      {"Key1", 37.582914}, {"Key2", 92.143057}, {"Key3", 15.907634}};
    Helper::checkMapValues(correct, mapEl->values, tolerance);
}

TEST_F(DoubleMapSerializerFileTest, WriteAndReadXML)
{
    const std::string fileName{"TestWriteDoubleMap.xml"};
    addTempFile(fileName);

    Helper::MapElementDouble mapEl;
    mapEl.values = {{"Value1", 23.856912}, {"Value2", 67.431280}, {"Value3", 14.903215}};

    const auto result{Helper::saveMapElementDoubleXML(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementDoubleXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapValues(mapEl.values, loaded->values, tolerance);
}

//////////////////////////////////////////////////////////////////////////////
// JSON-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(DoubleMapSerializerFileTest, ReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapDouble.json";

    const auto mapEl{Helper::loadMapElementDoubleJSON(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const std::map<std::string, double> correct{
      {"Key1", 37.582914}, {"Key2", 92.143057}, {"Key3", 15.907634}};
    Helper::checkMapValues(correct, mapEl->values, tolerance);
}

TEST_F(DoubleMapSerializerFileTest, WriteAndReadJSON)
{
    const std::string fileName{"TestWriteDoubleMap.json"};
    addTempFile(fileName);

    Helper::MapElementDouble mapEl;
    mapEl.values = {{"Value1", 23.856912}, {"Value2", 67.431280}, {"Value3", 14.903215}};

    const auto result{Helper::saveMapElementDoubleJSON(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementDoubleJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapValues(mapEl.values, loaded->values, tolerance);
}

//////////////////////////////////////////////////////////////////////////////
// Unified tests (auto-detect format)
//////////////////////////////////////////////////////////////////////////////

TEST_F(DoubleMapSerializerFileTest, UnifiedReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapDouble.xml";

    const auto mapEl{Helper::loadMapElementDouble(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const std::map<std::string, double> correct{
      {"Key1", 37.582914}, {"Key2", 92.143057}, {"Key3", 15.907634}};
    Helper::checkMapValues(correct, mapEl->values, tolerance);
}

TEST_F(DoubleMapSerializerFileTest, UnifiedReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapDouble.json";

    const auto mapEl{Helper::loadMapElementDouble(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const std::map<std::string, double> correct{
      {"Key1", 37.582914}, {"Key2", 92.143057}, {"Key3", 15.907634}};
    Helper::checkMapValues(correct, mapEl->values, tolerance);
}

TEST_F(DoubleMapSerializerFileTest, UnifiedWriteAndReadXML)
{
    const std::string fileName{"TestWriteDoubleMapUnified.xml"};
    addTempFile(fileName);

    Helper::MapElementDouble mapEl;
    mapEl.values = {{"A", 1.5}, {"B", 2.5}, {"C", 3.5}};

    const auto result{Helper::saveMapElementDouble(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementDouble(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapValues(mapEl.values, loaded->values, tolerance);
}

TEST_F(DoubleMapSerializerFileTest, UnifiedWriteAndReadJSON)
{
    const std::string fileName{"TestWriteDoubleMapUnified.json"};
    addTempFile(fileName);

    Helper::MapElementDouble mapEl;
    mapEl.values = {{"A", 1.5}, {"B", 2.5}, {"C", 3.5}};

    const auto result{Helper::saveMapElementDouble(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementDouble(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapValues(mapEl.values, loaded->values, tolerance);
}
