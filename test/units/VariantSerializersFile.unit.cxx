/// Variant file serialization tests (XML, JSON, and unified)
#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/files/VariantElement.hxx"
#include "test/helper/structures/StructureVariant.hxx"

class VariantSerializerFileTest : public testing::Test
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

    Helper::VariantsAll createTestData()
    {
        Helper::VariantsAll original;

        Helper::VariantParent tempParent;
        tempParent.name = "Parent Temperature";
        tempParent.value = Helper::ElementTemperature{23.15};
        tempParent.optionalString = "test value";
        original.values.push_back(tempParent);

        Helper::VariantParent humidityParent;
        humidityParent.name = "Parent Humidity";
        humidityParent.value = Helper::ElementHumidity{"9.493743"};
        original.values.push_back(humidityParent);

        return original;
    }

    void verifyTestData(const Helper::VariantsAll & data, bool hasOptional = true)
    {
        ASSERT_EQ(data.values.size(), 2);

        const Helper::VariantParent & tempVariant = data.values[0];
        ASSERT_EQ(tempVariant.name, "Parent Temperature");
        ASSERT_TRUE(std::holds_alternative<Helper::ElementTemperature>(tempVariant.value));
        const auto & temp = std::get<Helper::ElementTemperature>(tempVariant.value);
        ASSERT_NEAR(temp.temperature, 23.15, 1e-6);
        if(hasOptional)
        {
            ASSERT_TRUE(tempVariant.optionalString.has_value());
        }

        const Helper::VariantParent & humidityVariant = data.values[1];
        ASSERT_EQ(humidityVariant.name, "Parent Humidity");
        ASSERT_TRUE(std::holds_alternative<Helper::ElementHumidity>(humidityVariant.value));
        const auto & humidity = std::get<Helper::ElementHumidity>(humidityVariant.value);
        ASSERT_EQ(humidity.humidity, "9.493743");
        EXPECT_FALSE(humidityVariant.optionalString.has_value());
    }

    std::vector<std::string> tempFiles;
};

//////////////////////////////////////////////////////////////////////////////
// XML-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(VariantSerializerFileTest, ReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VariantInParentNode.xml";

    const auto variantEl{Helper::loadVariantAllXML(fileName.string())};
    ASSERT_TRUE(variantEl.has_value());

    ASSERT_EQ(variantEl->values.size(), 2);

    const Helper::VariantParent & tempVariant = variantEl->values[0];
    ASSERT_EQ(tempVariant.name, "Parent Temperature");
    ASSERT_TRUE(std::holds_alternative<Helper::ElementTemperature>(tempVariant.value));
    const auto & temp = std::get<Helper::ElementTemperature>(tempVariant.value);
    ASSERT_NEAR(temp.temperature, 23.15, 1e-6);
    ASSERT_TRUE(tempVariant.optionalString.has_value());
    EXPECT_EQ("test optional", tempVariant.optionalString.value());

    const Helper::VariantParent & humidityVariant = variantEl->values[1];
    ASSERT_EQ(humidityVariant.name, "Parent Humidity");
    ASSERT_TRUE(std::holds_alternative<Helper::ElementHumidity>(humidityVariant.value));
    const auto & humidity = std::get<Helper::ElementHumidity>(humidityVariant.value);
    ASSERT_EQ(humidity.humidity, "9.493743");
    EXPECT_FALSE(humidityVariant.optionalString.has_value());
}

TEST_F(VariantSerializerFileTest, WriteAndReadXML)
{
    const std::string fileName{"TestWriteVariant.xml"};
    addTempFile(fileName);

    auto original = createTestData();

    const auto result{Helper::saveVariantAllXML(original, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadVariantAllXML(fileName)};
    ASSERT_TRUE(loaded.has_value());
    verifyTestData(loaded.value());
}

//////////////////////////////////////////////////////////////////////////////
// JSON-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(VariantSerializerFileTest, ReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VariantInParentNode.json";

    const auto variantEl{Helper::loadVariantAllJSON(fileName.string())};
    ASSERT_TRUE(variantEl.has_value());

    ASSERT_EQ(variantEl->values.size(), 2);

    const Helper::VariantParent & tempVariant = variantEl->values[0];
    ASSERT_EQ(tempVariant.name, "Parent Temperature");
    ASSERT_TRUE(std::holds_alternative<Helper::ElementTemperature>(tempVariant.value));
    const auto & temp = std::get<Helper::ElementTemperature>(tempVariant.value);
    ASSERT_NEAR(temp.temperature, 23.15, 1e-6);
    ASSERT_TRUE(tempVariant.optionalString.has_value());
    EXPECT_EQ("test optional", tempVariant.optionalString.value());

    const Helper::VariantParent & humidityVariant = variantEl->values[1];
    ASSERT_EQ(humidityVariant.name, "Parent Humidity");
    ASSERT_TRUE(std::holds_alternative<Helper::ElementHumidity>(humidityVariant.value));
    const auto & humidity = std::get<Helper::ElementHumidity>(humidityVariant.value);
    ASSERT_EQ(humidity.humidity, "9.493743");
    EXPECT_FALSE(humidityVariant.optionalString.has_value());
}

TEST_F(VariantSerializerFileTest, WriteAndReadJSON)
{
    const std::string fileName{"TestWriteVariant.json"};
    addTempFile(fileName);

    auto original = createTestData();

    const auto result{Helper::saveVariantAllJSON(original, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadVariantAllJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());
    verifyTestData(loaded.value());
}

//////////////////////////////////////////////////////////////////////////////
// Unified tests (auto-detect format)
//////////////////////////////////////////////////////////////////////////////

TEST_F(VariantSerializerFileTest, UnifiedReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VariantInParentNode.xml";

    const auto variantEl{Helper::loadVariantAll(fileName.string())};
    ASSERT_TRUE(variantEl.has_value());
    ASSERT_EQ(variantEl->values.size(), 2);
}

TEST_F(VariantSerializerFileTest, UnifiedReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VariantInParentNode.json";

    const auto variantEl{Helper::loadVariantAll(fileName.string())};
    ASSERT_TRUE(variantEl.has_value());
    ASSERT_EQ(variantEl->values.size(), 2);
}

TEST_F(VariantSerializerFileTest, UnifiedWriteAndReadXML)
{
    const std::string fileName{"TestWriteVariantUnified.xml"};
    addTempFile(fileName);

    auto original = createTestData();

    const auto result{Helper::saveVariantAll(original, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadVariantAll(fileName)};
    ASSERT_TRUE(loaded.has_value());
    verifyTestData(loaded.value());
}

TEST_F(VariantSerializerFileTest, UnifiedWriteAndReadJSON)
{
    const std::string fileName{"TestWriteVariantUnified.json"};
    addTempFile(fileName);

    auto original = createTestData();

    const auto result{Helper::saveVariantAll(original, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadVariantAll(fileName)};
    ASSERT_TRUE(loaded.has_value());
    verifyTestData(loaded.value());
}
