#include <gtest/gtest.h>

#include "helper/TestXML.hxx"
#include "helper/TestStructures.hxx"

#include "helper/FileManipulation.hxx"
#include "helper/TestSerializers.hxx"

class BaserSerializerTest : public testing::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}
};

TEST_F(BaserSerializerTest, TestReadingBaseElement)
{
    const std::string fileContent{Helper::testDatabase()};
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

    std::remove(fileName.c_str());
}