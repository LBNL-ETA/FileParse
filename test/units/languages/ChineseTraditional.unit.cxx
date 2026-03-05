#include "LanguageTestHelper.hxx"

class ChineseTraditionalTest : public testing::Test
{};

// 你好，世界！
LANGUAGE_TESTS(ChineseTraditionalTest,
               "Chinese (Traditional)",
               "你好，世界！")
