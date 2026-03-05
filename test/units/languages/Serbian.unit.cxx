#include "LanguageTestHelper.hxx"

class SerbianTest : public testing::Test
{};

// Ћирилица: Здраво свете / Добро јутро
LANGUAGE_TESTS(SerbianTest,
               "Serbian",
               "Здраво свете",
               "Добро јутро")
