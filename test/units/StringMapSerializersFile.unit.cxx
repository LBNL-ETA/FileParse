/// StringMap file serialization tests (XML, JSON, and unified)
#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/Utility.hxx"
#include "test/helper/files/MapElement.hxx"
#include "test/helper/structures/StructureMap.hxx"

class StringMapSerializerFileTest : public testing::Test
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

TEST_F(StringMapSerializerFileTest, ReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapString.xml";

    const auto mapEl{Helper::loadMapElementStringXML(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const std::map<std::string, std::string> correctOrdered{
      {"Key1", "Value1"}, {"Key2", "Value2"}, {"Key3", "Value3"}};
    const std::unordered_map<std::string, std::string> correctUnordered{
      {"K1", "V1"}, {"K2", "V2"}, {"K3", "V3"}};

    Helper::checkMapEquality(correctOrdered, mapEl->ordered);
    Helper::checkMapEquality(correctUnordered, mapEl->unordered);
}

TEST_F(StringMapSerializerFileTest, WriteAndReadXML)
{
    const std::string fileName{"TestWriteStringMap.xml"};
    addTempFile(fileName);

    Helper::MapElementString mapEl;
    mapEl.ordered = {{"1", "Value1"}, {"2", "Value2"}, {"3", "Value3"}};

    const auto result{Helper::saveMapElementStringXML(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementStringXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(mapEl.ordered, loaded->ordered);
}

TEST_F(StringMapSerializerFileTest, ReadOptionalXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapOptionalString.xml";

    const auto mapEl{Helper::loadMapElementOptionalStringXML(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());
    ASSERT_TRUE(mapEl->values.has_value());

    const std::map<std::string, std::string> correct{
      {"Key1", "Optional1"}, {"Key2", "Optional2"}, {"Key3", "Optional3"}};
    Helper::checkMapEquality(correct, mapEl->values.value());
}

TEST_F(StringMapSerializerFileTest, WriteAndReadOptionalXML)
{
    const std::string fileName{"TestWriteOptionalStringMap.xml"};
    addTempFile(fileName);

    Helper::MapElementOptionalString mapEl;
    mapEl.values = {{"o1", "1"}, {"o2", "2"}, {"o3", "3"}};

    const auto result{Helper::saveMapElementOptionalStringXML(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementOptionalStringXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    ASSERT_TRUE(loaded->values.has_value());
    Helper::checkMapEquality(mapEl.values.value(), loaded->values.value());
}

TEST_F(StringMapSerializerFileTest, ReadEmptyXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapEmptyOptionalString.xml";

    const auto mapEl{Helper::loadMapElementStringXML(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());
    EXPECT_EQ(0u, mapEl->ordered.size());
}

TEST_F(StringMapSerializerFileTest, WriteAndReadEmptyXML)
{
    const std::string fileName{"TestWriteEmptyStringMap.xml"};
    addTempFile(fileName);

    Helper::MapElementString mapEl;

    const auto result{Helper::saveMapElementStringXML(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementStringXML(fileName)};
    EXPECT_EQ(mapEl.ordered.size(), loaded->ordered.size());
}

//////////////////////////////////////////////////////////////////////////////
// JSON-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(StringMapSerializerFileTest, ReadJSON)
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

TEST_F(StringMapSerializerFileTest, WriteAndReadJSON)
{
    const std::string fileName{"TestWriteStringMap.json"};
    addTempFile(fileName);

    Helper::MapElementString mapEl;
    mapEl.ordered = {{"1", "Value1"}, {"2", "Value2"}, {"3", "Value3"}};

    const auto result{Helper::saveMapElementStringJSON(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementStringJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(mapEl.ordered, loaded->ordered);
}

TEST_F(StringMapSerializerFileTest, ReadOptionalJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapOptionalString.json";

    const auto mapEl{Helper::loadMapElementOptionalStringJSON(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());
    ASSERT_TRUE(mapEl->values.has_value());

    const std::map<std::string, std::string> correct{
      {"Key1", "Optional1"}, {"Key2", "Optional2"}, {"Key3", "Optional3"}};
    Helper::checkMapEquality(correct, mapEl->values.value());
}

TEST_F(StringMapSerializerFileTest, WriteAndReadOptionalJSON)
{
    const std::string fileName{"TestWriteOptionalStringMap.json"};
    addTempFile(fileName);

    Helper::MapElementOptionalString mapEl;
    mapEl.values = {{"o1", "1"}, {"o2", "2"}, {"o3", "3"}};

    const auto result{Helper::saveMapElementOptionalStringJSON(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementOptionalStringJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    ASSERT_TRUE(loaded->values.has_value());
    Helper::checkMapEquality(mapEl.values.value(), loaded->values.value());
}

TEST_F(StringMapSerializerFileTest, ReadEmptyJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapEmptyOptionalString.json";

    const auto mapEl{Helper::loadMapElementStringJSON(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());
    EXPECT_EQ(0u, mapEl->ordered.size());
}

TEST_F(StringMapSerializerFileTest, WriteAndReadEmptyJSON)
{
    const std::string fileName{"TestWriteEmptyStringMap.json"};
    addTempFile(fileName);

    Helper::MapElementString mapEl;

    const auto result{Helper::saveMapElementStringJSON(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementStringJSON(fileName)};
    EXPECT_EQ(mapEl.ordered.size(), loaded->ordered.size());
}

//////////////////////////////////////////////////////////////////////////////
// Unified tests (auto-detect format)
//////////////////////////////////////////////////////////////////////////////

TEST_F(StringMapSerializerFileTest, UnifiedReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapString.xml";

    const auto mapEl{Helper::loadMapElementString(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const std::map<std::string, std::string> correctOrdered{
      {"Key1", "Value1"}, {"Key2", "Value2"}, {"Key3", "Value3"}};
    Helper::checkMapEquality(correctOrdered, mapEl->ordered);
}

TEST_F(StringMapSerializerFileTest, UnifiedReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "MapString.json";

    const auto mapEl{Helper::loadMapElementString(fileName.string())};
    ASSERT_TRUE(mapEl.has_value());

    const std::map<std::string, std::string> correctOrdered{
      {"Key1", "Value1"}, {"Key2", "Value2"}, {"Key3", "Value3"}};
    Helper::checkMapEquality(correctOrdered, mapEl->ordered);
}

TEST_F(StringMapSerializerFileTest, UnifiedWriteAndReadXML)
{
    const std::string fileName{"TestWriteStringMapUnified.xml"};
    addTempFile(fileName);

    Helper::MapElementString mapEl;
    mapEl.ordered = {{"A", "Alpha"}, {"B", "Beta"}};

    const auto result{Helper::saveMapElementString(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementString(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(mapEl.ordered, loaded->ordered);
}

TEST_F(StringMapSerializerFileTest, UnifiedWriteAndReadJSON)
{
    const std::string fileName{"TestWriteStringMapUnified.json"};
    addTempFile(fileName);

    Helper::MapElementString mapEl;
    mapEl.ordered = {{"A", "Alpha"}, {"B", "Beta"}};

    const auto result{Helper::saveMapElementString(mapEl, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadMapElementString(fileName)};
    ASSERT_TRUE(loaded.has_value());
    Helper::checkMapEquality(mapEl.ordered, loaded->ordered);
}
