#include "LanguageTestHelper.hxx"

class TurkishTest : public testing::Test
{};

// Merhaba Dünya / Günaydın
LANGUAGE_TESTS(TurkishTest,
               "Turkish",
               "Merhaba Dünya",
               "Günaydın")
