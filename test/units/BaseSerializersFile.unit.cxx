/// BaseElement file serialization tests (XML, JSON, and unified)
#include <filesystem>
#include <gtest/gtest.h>

#include "test/helper/files/BaseElement.hxx"
#include "test/helper/structures/StructureBase.hxx"

#include "test/helper/FileManipulation.hxx"

class BaseSerializerFileTest : public testing::Test
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

    // Helper to verify loaded BaseElement matches expected values from test data files
    void verifyTestDataContent(const Helper::BaseElement & base)
    {
        EXPECT_EQ("TestText", base.text);
        EXPECT_EQ(13, base.integer_number);
        EXPECT_NEAR(3.1415926, base.double_number, 1e-6);
        EXPECT_EQ(true, base.boolean_field);
        EXPECT_EQ("OptionalText", base.optional_text);
        EXPECT_EQ(23, base.optional_int);
        EXPECT_EQ(18u, base.size_t_field);
        ASSERT_TRUE(base.optional_double.has_value());
        EXPECT_NEAR(4.1415926, base.optional_double.value(), 1e-6);
        ASSERT_TRUE(base.boolean_optional.has_value());
        EXPECT_EQ(false, base.boolean_optional.value());

        auto str_ptr = std::get_if<std::string>(&base.variant_field);
        ASSERT_NE(nullptr, str_ptr);
        EXPECT_EQ("VariantText", *str_ptr);

        ASSERT_TRUE(base.optional_variant.has_value());
        auto opt_str_ptr = std::get_if<std::string>(&base.optional_variant.value());
        ASSERT_NE(nullptr, opt_str_ptr);
        EXPECT_EQ("VariantText1", *opt_str_ptr);
    }

    // Helper to verify round-trip serialization
    void verifyRoundTrip(const Helper::BaseElement & original, const Helper::BaseElement & loaded)
    {
        EXPECT_EQ(original.text, loaded.text);
        EXPECT_EQ(original.integer_number, loaded.integer_number);
        EXPECT_EQ(original.boolean_field, loaded.boolean_field);
        EXPECT_EQ(original.size_t_field, loaded.size_t_field);

        constexpr auto tolerance{1e-6};
        EXPECT_NEAR(original.double_number, loaded.double_number, tolerance);

        if(original.optional_double.has_value() && loaded.optional_double.has_value())
        {
            EXPECT_NEAR(original.optional_double.value(), loaded.optional_double.value(), tolerance);
        }
        else
        {
            EXPECT_EQ(original.optional_double.has_value(), loaded.optional_double.has_value());
        }

        EXPECT_EQ(original.boolean_optional, loaded.boolean_optional);

        if(std::holds_alternative<double>(original.variant_field)
           && std::holds_alternative<double>(loaded.variant_field))
        {
            EXPECT_NEAR(std::get<double>(original.variant_field),
                        std::get<double>(loaded.variant_field),
                        tolerance);
        }
        else if(std::holds_alternative<std::string>(original.variant_field)
                && std::holds_alternative<std::string>(loaded.variant_field))
        {
            EXPECT_EQ(std::get<std::string>(original.variant_field),
                      std::get<std::string>(loaded.variant_field));
        }
        else
        {
            FAIL() << "Variant fields do not match in type";
        }
    }

    // Create a test BaseElement for write tests
    Helper::BaseElement createTestElement()
    {
        Helper::BaseElement base;
        base.text = "Some example text";
        base.integer_number = 42;
        base.optional_double = 3.1415926;
        base.double_number = 1.4321345;
        base.variant_field = 18.1;
        base.boolean_field = false;
        base.size_t_field = 100;
        return base;
    }

    std::vector<std::string> tempFiles;
};

//////////////////////////////////////////////////////////////////////////////
// XML-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(BaseSerializerFileTest, ReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "BaseElement.xml";

    const auto base{Helper::loadBaseElementXML(fileName.string())};
    ASSERT_TRUE(base.has_value());

    verifyTestDataContent(base.value());
}

TEST_F(BaseSerializerFileTest, WriteAndReadXML)
{
    const std::string fileName{"TestWriteBase.xml"};
    addTempFile(fileName);

    auto base = createTestElement();

    const auto result{Helper::saveBaseElementXML(base, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadBaseElementXML(fileName)};
    ASSERT_TRUE(loaded.has_value());

    verifyRoundTrip(base, loaded.value());
}

//////////////////////////////////////////////////////////////////////////////
// JSON-specific tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(BaseSerializerFileTest, ReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "BaseElement.json";

    const auto base{Helper::loadBaseElementJSON(fileName.string())};
    ASSERT_TRUE(base.has_value());

    verifyTestDataContent(base.value());
}

TEST_F(BaseSerializerFileTest, WriteAndReadJSON)
{
    const std::string fileName{"TestWriteBase.json"};
    addTempFile(fileName);

    auto base = createTestElement();

    const auto result{Helper::saveBaseElementJSON(base, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadBaseElementJSON(fileName)};
    ASSERT_TRUE(loaded.has_value());

    verifyRoundTrip(base, loaded.value());
}

//////////////////////////////////////////////////////////////////////////////
// Unified tests (auto-detect format)
//////////////////////////////////////////////////////////////////////////////

TEST_F(BaseSerializerFileTest, UnifiedReadXML)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "BaseElement.xml";

    // Auto-detects XML from .xml extension
    const auto base{Helper::loadBaseElement(fileName.string())};
    ASSERT_TRUE(base.has_value());

    verifyTestDataContent(base.value());
}

TEST_F(BaseSerializerFileTest, UnifiedReadJSON)
{
    std::filesystem::path productPath{TEST_DATA_DIR};
    const auto fileName = productPath / "BaseElement.json";

    // Auto-detects JSON from .json extension
    const auto base{Helper::loadBaseElement(fileName.string())};
    ASSERT_TRUE(base.has_value());

    verifyTestDataContent(base.value());
}

TEST_F(BaseSerializerFileTest, UnifiedWriteAndReadXML)
{
    const std::string fileName{"TestWriteBaseUnified.xml"};
    addTempFile(fileName);

    auto base = createTestElement();

    // Auto-detects XML from .xml extension
    const auto result{Helper::saveBaseElement(base, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadBaseElement(fileName)};
    ASSERT_TRUE(loaded.has_value());

    verifyRoundTrip(base, loaded.value());
}

TEST_F(BaseSerializerFileTest, UnifiedWriteAndReadJSON)
{
    const std::string fileName{"TestWriteBaseUnified.json"};
    addTempFile(fileName);

    auto base = createTestElement();

    // Auto-detects JSON from .json extension
    const auto result{Helper::saveBaseElement(base, fileName)};
    EXPECT_EQ(0, result);

    const auto loaded{Helper::loadBaseElement(fileName)};
    ASSERT_TRUE(loaded.has_value());

    verifyRoundTrip(base, loaded.value());
}

TEST_F(BaseSerializerFileTest, UnifiedSaveWithUnknownExtensionFails)
{
    const std::string fileName{"TestWriteBase.txt"};

    auto base = createTestElement();

    // Should fail because .txt extension is not recognized
    const auto result{Helper::saveBaseElement(base, fileName)};
    EXPECT_EQ(-1, result);
}
