#include <gtest/gtest.h>

#include "helper/TestBaseElementXML.hxx"
#include "helper/TestStructures.hxx"

#include "helper/FileManipulation.hxx"
#include "test/helper/serializers/TestBaseElementSerializers.hxx"

class BaseSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(BaseSerializerTest, TestReadingBaseElement)
{
    const std::string fileContent{Helper::testBaseElementDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    Helper::BaseElement base{Helper::loadBaseElement(fileName)};

    EXPECT_EQ("TestText", base.text);
    EXPECT_EQ(13, base.integer_number);
    EXPECT_NEAR(3.1415926, base.double_number, 1e-6);
    EXPECT_EQ("OptionalText", base.optional_text);
    EXPECT_EQ(23, base.optional_int);
    ASSERT_EQ(true, base.optional_double.has_value());
    EXPECT_NEAR(4.1415926, base.optional_double.value(), 1e-6);
    if(auto str_ptr = std::get_if<std::string>(&base.variant_field))
    {
        EXPECT_EQ("VariantText", *str_ptr);
    }
    else
    {
        std::cerr << "variant_field does not hold a string value" << std::endl;
        FAIL();
    }

    std::remove(fileName.c_str());
}

TEST_F(BaseSerializerTest, TestWritingBaseElement)
{
    Helper::BaseElement base;
    base.text = "Some example text";
    base.optional_double = 3.1415926;
    base.double_number = 1.4321345;
    base.variant_field = 18.1;

    const std::string fileName{"TestWrite.xml"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to ensure deletion.
    std::remove(fileName.c_str());

    Helper::saveBaseElement(base, fileName);

    Helper::BaseElement loadedBase{Helper::loadBaseElement(fileName)};

    EXPECT_EQ(base.text, loadedBase.text);

    constexpr auto tolerance{1e-6};

    if(base.optional_double.has_value() && loadedBase.optional_double.has_value())
    {
        EXPECT_NEAR(*base.optional_double, *loadedBase.optional_double, tolerance);
    }
    else
    {
        EXPECT_EQ(base.optional_double.has_value(), loadedBase.optional_double.has_value());   // Both should be nullopt
    }

    EXPECT_NEAR(base.double_number, loadedBase.double_number, tolerance);   // Assuming double_number is not optional

    // Check for variant_field
    if(std::holds_alternative<double>(base.variant_field) && std::holds_alternative<double>(loadedBase.variant_field))
    {
        EXPECT_NEAR(std::get<double>(base.variant_field), std::get<double>(loadedBase.variant_field), tolerance);
    }
    else if(std::holds_alternative<std::string>(base.variant_field)
            && std::holds_alternative<std::string>(loadedBase.variant_field))
    {
        EXPECT_EQ(std::get<std::string>(base.variant_field), std::get<std::string>(loadedBase.variant_field));
    }
    else
    {
        EXPECT_FALSE(true);   // Fail test since variant fields are not matching in type
    }

    std::remove(fileName.c_str());
}