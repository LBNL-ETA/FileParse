#include <gtest/gtest.h>

#include <fileParse/StringConversion.hxx>

// Define a test enumeration for testing purposes
enum class Color
{
    Red,
    Green,
    Blue,
    Yellow,
    Unknown
};

// Test cases for enumerator conversion utilities
TEST(EnumConversionTests, EnumFromStringWithArray)
{
    std::array<std::string, 4> colorNames = {"Red", "Green", "Blue", "Yellow"};

    EXPECT_EQ(FileParse::enumFromString("Red", colorNames, Color::Unknown), Color::Red);
    EXPECT_EQ(FileParse::enumFromString("Green", colorNames, Color::Unknown), Color::Green);
    EXPECT_EQ(FileParse::enumFromString("Blue", colorNames, Color::Unknown), Color::Blue);
    EXPECT_EQ(FileParse::enumFromString("Yellow", colorNames, Color::Unknown), Color::Yellow);
    EXPECT_EQ(FileParse::enumFromString("Purple", colorNames, Color::Unknown), Color::Unknown);
}

// Testing the cases where incorrect caps of the enumerators were passed
TEST(EnumConversionTests, EnumFromStringIncorrectCaps)
{
    std::array<std::string, 4> colorNames = {"Red", "Green", "Blue", "Yellow"};

    EXPECT_EQ(FileParse::enumFromString("red", colorNames, Color::Unknown), Color::Unknown);
    EXPECT_EQ(FileParse::enumFromString("grEen", colorNames, Color::Unknown), Color::Unknown);
}

// Testing the case-insensitive version of the enumFromString function
TEST(EnumConversionTests, EnumFromStringCaseInsensitive)
{
    std::array<std::string, 4> colorNames = {"Red", "Green", "Blue", "Yellow"};

    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive("red", colorNames, Color::Unknown),
              Color::Red);
    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive("grEen", colorNames, Color::Unknown),
              Color::Green);
    EXPECT_EQ(FileParse::enumFromString("yeLloW", colorNames, Color::Unknown), Color::Unknown);
}

TEST(EnumConversionTests, EnumToStringWithArray)
{
    std::array<std::string, 4> colorNames = {"Red", "Green", "Blue", "Yellow"};

    EXPECT_EQ(FileParse::enumToString(Color::Red, colorNames), "Red");
    EXPECT_EQ(FileParse::enumToString(Color::Green, colorNames), "Green");
    EXPECT_EQ(FileParse::enumToString(Color::Blue, colorNames), "Blue");
    EXPECT_EQ(FileParse::enumToString(Color::Yellow, colorNames), "Yellow");
    EXPECT_EQ(FileParse::enumToString(Color::Unknown, colorNames), "Unknown");
}

TEST(EnumConversionTests, EnumToStringWithMap)
{
    std::map<Color, std::string> colorMap = {{Color::Red, "Red"},
                                             {Color::Green, "Green"},
                                             {Color::Blue, "Blue"},
                                             {Color::Yellow, "Yellow"}};

    EXPECT_EQ(FileParse::enumToString(Color::Red, colorMap), "Red");
    EXPECT_EQ(FileParse::enumToString(Color::Green, colorMap), "Green");
    EXPECT_EQ(FileParse::enumToString(Color::Blue, colorMap), "Blue");
    EXPECT_EQ(FileParse::enumToString(Color::Yellow, colorMap), "Yellow");
    EXPECT_EQ(FileParse::enumToString(Color::Unknown, colorMap), "Unknown");
}

TEST(EnumConversionTests, EnumFromStringWithMap)
{
    std::map<Color, std::string> colorMap = {{Color::Red, "Red"},
                                             {Color::Green, "Green"},
                                             {Color::Blue, "Blue"},
                                             {Color::Yellow, "Yellow"}};

    EXPECT_EQ(FileParse::enumFromString("Red", colorMap), Color::Red);
    EXPECT_EQ(FileParse::enumFromString("Green", colorMap), Color::Green);
    EXPECT_EQ(FileParse::enumFromString("Blue", colorMap), Color::Blue);
    EXPECT_EQ(FileParse::enumFromString("Yellow", colorMap), Color::Yellow);

    // This value does not exist. Note that the first enumerator value will be used if not provided by the user
    EXPECT_EQ(FileParse::enumFromString("Purple", colorMap), Color::Red);

    // Here user explicitly provided the default value and test will pass
    EXPECT_EQ(FileParse::enumFromString("Purple", colorMap, Color::Unknown), Color::Unknown);
}

TEST(EnumConversionTests, EnumFromStringWithMapCaseInsenstive)
{
    std::map<Color, std::string> colorMap = {{Color::Red, "Red"},
                                             {Color::Green, "Green"},
                                             {Color::Blue, "Blue"},
                                             {Color::Yellow, "Yellow"}};

    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive("red", colorMap), Color::Red);
    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive("greEn", colorMap), Color::Green);
    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive("bLuE", colorMap), Color::Blue);
    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive("Non-existent", colorMap, Color::Unknown), Color::Unknown);
    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive("Non-existent", colorMap), Color::Red);
}