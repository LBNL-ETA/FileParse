#include "LanguageTestHelper.hxx"

class PolishTest : public testing::Test
{};

// Witaj Świecie / Dzień dobry
LANGUAGE_TESTS(PolishTest,
               "Polish",
               "Witaj Świecie",
               "Dzień dobry")
