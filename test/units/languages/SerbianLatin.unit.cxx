#include "LanguageTestHelper.hxx"

class SerbianLatinTest : public testing::Test
{};

// Latinica: Zdravo svete / Dobro jutro
// Serbian Latin uses đ, ž, č, ć, š which are important to test
LANGUAGE_TESTS(SerbianLatinTest,
               "Serbian (Latin)",
               "Zdravo svete",
               "Čežnja za šljivovicom i đevrek")
