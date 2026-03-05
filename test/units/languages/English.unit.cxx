#include "LanguageTestHelper.hxx"

class EnglishTest : public testing::Test
{};

LANGUAGE_TESTS(EnglishTest, "English", "Hello, World!", "Good morning")

TEST_F(EnglishTest, XMLStringNoOptional)
{
    LanguageTest::verifyXMLStringRoundTrip("English", "Hello, World!");
}

TEST_F(EnglishTest, JSONStringNoOptional)
{
    LanguageTest::verifyJSONStringRoundTrip("English", "Hello, World!");
}
