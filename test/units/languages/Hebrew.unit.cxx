#include "LanguageTestHelper.hxx"

class HebrewTest : public testing::Test
{};

// שלום עולם
LANGUAGE_TESTS(HebrewTest,
               "Hebrew",
               "שלום עולם")
