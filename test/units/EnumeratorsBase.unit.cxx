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
    EXPECT_EQ(FileParse::enumFromString("Yellow", colorNames, Color::Unknown),
              Color::Yellow);
    EXPECT_EQ(FileParse::enumFromString("Purple", colorNames, Color::Unknown),
              Color::Unknown);
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
    EXPECT_EQ(FileParse::enumFromString("Purple", colorMap), Color::Red);
}