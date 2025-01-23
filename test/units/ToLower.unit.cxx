#include <gtest/gtest.h>

#include <fileParse/StringConversion.hxx>

TEST(StringConversionTests, ToLowerWarningTest)
{
    std::string input = "TestString";
    std::string output = FileParse::toLower(input);
    EXPECT_EQ(output, "teststring");
}