#include "LanguageTestHelper.hxx"

class ChineseSimplifiedTest : public testing::Test
{};

// 你好，世界！ / 早上好
LANGUAGE_TESTS(ChineseSimplifiedTest,
               "Chinese (Simplified)",
               "你好，世界！",
               "早上好")
