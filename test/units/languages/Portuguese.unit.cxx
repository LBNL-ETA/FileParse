#include "LanguageTestHelper.hxx"

class PortugueseTest : public testing::Test
{};

// Olá, Mundo! / Obrigado pela atenção
LANGUAGE_TESTS(PortugueseTest,
               "Portuguese",
               "Olá, Mundo!",
               "Obrigado pela atenção")
