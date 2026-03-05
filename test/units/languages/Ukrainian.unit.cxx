#include "LanguageTestHelper.hxx"

class UkrainianTest : public testing::Test
{};

// Привіт світе / Доброго ранку
// Ukrainian Cyrillic has unique chars: ґ, є, ї, і
LANGUAGE_TESTS(UkrainianTest,
               "Ukrainian",
               "Привіт світе",
               "Ґанок, єдність, їжак, індик")
