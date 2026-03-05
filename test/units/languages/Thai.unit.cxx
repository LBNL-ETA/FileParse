#include "LanguageTestHelper.hxx"

class ThaiTest : public testing::Test
{};

// สวัสดีชาวโลก
LANGUAGE_TESTS(ThaiTest,
               "Thai",
               "สวัสดีชาวโลก")
