#include "LanguageTestHelper.hxx"

class SpanishTest : public testing::Test
{};

// ¡Hola, Mundo! / Buenos días
LANGUAGE_TESTS(SpanishTest,
               "Spanish",
               "¡Hola, Mundo!",
               "Buenos días")
