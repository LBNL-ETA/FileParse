#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/files/VariantElementXML.hxx"
#include "test/helper/structures/StructureVariant.hxx"

#include "test/helper/FileManipulation.hxx"

TEST(VariantSerializerXMLTest, Reading)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "VariantInParentNode.xml";

    const auto variantEl{Helper::loadVariantAll(fileName.string())};
    ASSERT_TRUE(variantEl.has_value());

    ASSERT_EQ(variantEl->values.size(), 2);

    const Helper::VariantParent & tempVariant = variantEl->values[0];
    ASSERT_EQ(tempVariant.name, "Parent Temperature");
    ASSERT_TRUE(std::holds_alternative<Helper::ElementTemperature>(tempVariant.value));
    const auto & temp = std::get<Helper::ElementTemperature>(tempVariant.value);
    ASSERT_NEAR(temp.temperature, 23.15, 1e-6);
    ASSERT_EQ(true, tempVariant.optionalString.has_value());
    EXPECT_EQ("test optional", tempVariant.optionalString.value());


    const Helper::VariantParent & humidityVariant = variantEl->values[1];
    ASSERT_EQ(humidityVariant.name, "Parent Humidity");
    ASSERT_TRUE(std::holds_alternative<Helper::ElementHumidity>(humidityVariant.value));
    const auto & humidity = std::get<Helper::ElementHumidity>(humidityVariant.value);
    ASSERT_EQ(humidity.humidity, "9.493743");
    EXPECT_EQ(false, humidityVariant.optionalString.has_value());
}

TEST(VariantSerializerXMLTest, Serialization)
{
    const std::string fileName{"TestSerialization.xml"};

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

    const auto result{Helper::saveVariantAll(original, fileName)};
    EXPECT_EQ(result, 0);

    const auto deserialized{Helper::loadVariantAll(fileName)};
    ASSERT_TRUE(deserialized.has_value());

    ASSERT_EQ(deserialized->values.size(), 2);

    const Helper::VariantParent & tempVariant = deserialized->values[0];
    ASSERT_EQ(tempVariant.name, "Parent Temperature");
    ASSERT_TRUE(std::holds_alternative<Helper::ElementTemperature>(tempVariant.value));
    const auto & temp = std::get<Helper::ElementTemperature>(tempVariant.value);
    ASSERT_NEAR(temp.temperature, 23.15, 1e-6);
    ASSERT_EQ(true, tempVariant.optionalString.has_value());
    EXPECT_EQ("test value", tempVariant.optionalString.value());

    const Helper::VariantParent & humidityVariant = deserialized->values[1];
    ASSERT_EQ(humidityVariant.name, "Parent Humidity");
    ASSERT_TRUE(std::holds_alternative<Helper::ElementHumidity>(humidityVariant.value));
    const auto & humidity = std::get<Helper::ElementHumidity>(humidityVariant.value);
    ASSERT_EQ(humidity.humidity, "9.493743");
    EXPECT_EQ(false, humidityVariant.optionalString.has_value());

    std::remove(fileName.c_str());
}