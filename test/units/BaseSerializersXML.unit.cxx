#include <gtest/gtest.h>

#include "test/helper/files/BaseElementXML.hxx"
#include "test/helper/structures/StructureBase.hxx"

#include "test/helper/FileManipulation.hxx"

class BaseSerializerXMLTest : public testing::Test
{};

TEST_F(BaseSerializerXMLTest, TestReadingBaseElement)
{
    const std::string fileContent{Helper::testBaseElementDatabase()};
    const std::string fileName{"TestRead.xml"};

    File::createFileFromString(fileName, fileContent);

    Helper::BaseElement base{Helper::loadBaseElement(fileName)};

    EXPECT_EQ("TestText", base.text);
    EXPECT_EQ(13, base.integer_number);
    EXPECT_NEAR(3.1415926, base.double_number, 1e-6);
    EXPECT_EQ(true, base.boolean_field);
    EXPECT_EQ("OptionalText", base.optional_text);
    EXPECT_EQ(23, base.optional_int);
    EXPECT_EQ(18u, base.size_t_field);
    ASSERT_EQ(true, base.optional_double.has_value());
    EXPECT_NEAR(4.1415926, base.optional_double.value(), 1e-6);
    ASSERT_EQ(true, base.boolean_optional.has_value());
    if(base.boolean_optional.has_value())
    {
        EXPECT_EQ(false, base.boolean_optional.value());
    }
    if(auto str_ptr = std::get_if<std::string>(&base.variant_field))
    {
        EXPECT_EQ("VariantText", *str_ptr);
    }
    else
    {
        std::cerr << "variant_field does not hold a string value" << std::endl;
        FAIL();
    }

    ASSERT_EQ(true, base.optional_variant.has_value());
    if(auto str_ptr = std::get_if<std::string>(&base.optional_variant.value()))
    {
        EXPECT_EQ("VariantText1", *str_ptr);
    }
    else
    {
        std::cerr << "optional_variant_field does not hold a string value" << std::endl;
        FAIL();
    }


    std::remove(fileName.c_str());
}

TEST_F(BaseSerializerXMLTest, TestWritingBaseElement)
{
    Helper::BaseElement base;
    base.text = "Some example text";
    base.optional_double = 3.1415926;
    base.double_number = 1.4321345;
    base.variant_field = 18.1;
    base.boolean_field = false;

    const std::string fileName{"TestWrite.xml"};

    // Sometimes in debug mode the above file was not removed from the previous run. This is to
    // ensure deletion.
    std::remove(fileName.c_str());

    const auto result{Helper::saveBaseElement(base, fileName)};
    EXPECT_EQ(0, result);

    Helper::BaseElement loadedBase{Helper::loadBaseElement(fileName)};

    EXPECT_EQ(base.text, loadedBase.text);

    constexpr auto tolerance{1e-6};

    if(base.optional_double.has_value() && loadedBase.optional_double.has_value())
    {
        EXPECT_NEAR(base.optional_double.value(), loadedBase.optional_double.value(), tolerance);
    }
    else
    {
        EXPECT_EQ(base.optional_double.has_value(),
                  loadedBase.optional_double.has_value());   // Both should be nullopt
    }

    EXPECT_EQ(base.boolean_optional, loadedBase.boolean_optional);

    if(base.boolean_optional.has_value() && loadedBase.boolean_optional.has_value())
    {
        EXPECT_EQ(base.boolean_optional.value(), loadedBase.boolean_optional.value());
    }
    else
    {
        EXPECT_EQ(base.optional_double.has_value(),
                  loadedBase.optional_double.has_value());   // Both should be nullopt
    }

    EXPECT_NEAR(base.double_number,
                loadedBase.double_number,
                tolerance);   // Assuming double_number is not optional

    if(std::holds_alternative<double>(base.variant_field)
       && std::holds_alternative<double>(loadedBase.variant_field))
    {
        EXPECT_NEAR(std::get<double>(base.variant_field),
                    std::get<double>(loadedBase.variant_field),
                    tolerance);
    }
    else if(std::holds_alternative<std::string>(base.variant_field)
            && std::holds_alternative<std::string>(loadedBase.variant_field))
    {
        EXPECT_EQ(std::get<std::string>(base.variant_field),
                  std::get<std::string>(loadedBase.variant_field));
    }
    else
    {
        EXPECT_FALSE(true);   // Fail test since variant fields are not matching in type
    }

    std::remove(fileName.c_str());
}