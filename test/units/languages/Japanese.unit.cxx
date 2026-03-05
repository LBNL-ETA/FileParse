#include "LanguageTestHelper.hxx"

class JapaneseTest : public testing::Test
{};

// こんにちは世界 / おはようございます
LANGUAGE_TESTS(JapaneseTest,
               "Japanese",
               "こんにちは世界",
               "おはようございます")
