#include "LanguageTestHelper.hxx"

class VietnameseTest : public testing::Test
{};

// Xin chào thế giới
LANGUAGE_TESTS(VietnameseTest,
               "Vietnamese",
               "Xin chào thế giới")
