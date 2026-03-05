#include "LanguageTestHelper.hxx"

class KoreanTest : public testing::Test
{};

// 안녕하세요 세계
LANGUAGE_TESTS(KoreanTest,
               "Korean",
               "안녕하세요 세계")
