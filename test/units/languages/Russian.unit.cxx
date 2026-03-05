#include "LanguageTestHelper.hxx"

class RussianTest : public testing::Test
{};

// Привет, мир! / Доброе утро
LANGUAGE_TESTS(RussianTest,
               "Russian",
               "Привет, мир!",
               "Доброе утро")
