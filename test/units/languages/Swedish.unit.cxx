#include "LanguageTestHelper.hxx"

class SwedishTest : public testing::Test
{};

// Hej världen / God morgon
// Swedish uses å, ä, ö
LANGUAGE_TESTS(SwedishTest,
               "Swedish",
               "Hej världen",
               "God morgon på en vacker dag")
