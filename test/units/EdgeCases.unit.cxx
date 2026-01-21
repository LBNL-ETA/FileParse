/// Edge case tests to improve branch coverage
#include <gtest/gtest.h>

#include <fileParse/Set.hxx>
#include <fileParse/StringConversion.hxx>
#include <fileParse/FileDataHandler.hxx>
#include <fileParse/Base.hxx>
#include <fileParse/Vector.hxx>

#include "test/helper/MockNodeAdapter.hxx"

//////////////////////////////////////////////////////////////////////////////
// FileDataHandler edge cases
//////////////////////////////////////////////////////////////////////////////

struct SimpleElement
{
    std::string value;
};

template<typename NodeAdapter>
NodeAdapter & operator<<(NodeAdapter & node, const SimpleElement & element)
{
    node << FileParse::Child{"Value", element.value};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter & operator>>(const NodeAdapter & node, SimpleElement & element)
{
    node >> FileParse::Child{"Value", element.value};
    return node;
}

TEST(FileDataHandlerEdgeCases, LoadFromXMLStringInvalidXML)
{
    // Test with malformed XML that cannot be parsed
    const std::string invalidXML = "this is not valid xml";
    auto result = Common::loadFromXMLString<SimpleElement>(invalidXML, "SimpleElement");

    EXPECT_FALSE(result.has_value());
}

TEST(FileDataHandlerEdgeCases, LoadFromXMLStringEmptyXML)
{
    // Test with empty string
    const std::string emptyXML = "";
    auto result = Common::loadFromXMLString<SimpleElement>(emptyXML, "SimpleElement");

    EXPECT_FALSE(result.has_value());
}

TEST(FileDataHandlerEdgeCases, LoadFromXMLStringWrongRootNode)
{
    // Test with valid XML but wrong root node name
    const std::string xml = "<WrongNode><Value>test</Value></WrongNode>";
    auto result = Common::loadFromXMLString<SimpleElement>(xml, "SimpleElement");

    EXPECT_FALSE(result.has_value());
}

TEST(FileDataHandlerEdgeCases, LoadFromXMLStringValidXML)
{
    // Test with valid XML
    const std::string xml = "<SimpleElement><Value>test</Value></SimpleElement>";
    auto result = Common::loadFromXMLString<SimpleElement>(xml, "SimpleElement");

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ("test", result.value().value);
}

TEST(FileDataHandlerEdgeCases, SaveAndLoadRoundTrip)
{
    SimpleElement original;
    original.value = "round-trip test";

    std::string xml = Common::saveToXMLString(original, "SimpleElement");
    auto loaded = Common::loadFromXMLString<SimpleElement>(xml, "SimpleElement");

    ASSERT_TRUE(loaded.has_value());
    EXPECT_EQ(original.value, loaded.value().value);
}

//////////////////////////////////////////////////////////////////////////////
// Set.hxx edge cases
//////////////////////////////////////////////////////////////////////////////

TEST(SetEdgeCases, SerializeEmptyNodeNames)
{
    const std::set<int> data{1, 2, 3};
    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    // Empty nodeNames should return early without adding children
    adapter << FileParse::Child<const std::set<int>>{{}, data};

    // Should have no children added
    EXPECT_TRUE(adapter.getNode().child.empty());
}

TEST(SetEdgeCases, SerializeEmptySet)
{
    const std::set<int> data{};
    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    // Empty set should return early without adding children
    adapter << FileParse::Child{{"Items", "Item"}, data};

    // Should have no children added
    EXPECT_TRUE(adapter.getNode().child.empty());
}

TEST(SetEdgeCases, DeserializeNoMatchingChild)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        // No "Items" child node
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::set<int> data;
    adapter >> FileParse::Child{{"Items", "Item"}, data};

    // Should remain empty
    EXPECT_TRUE(data.empty());
}

TEST(SetEdgeCases, DeserializeOptionalSetNoMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        // No matching children
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::optional<std::set<int>> data;
    adapter >> FileParse::Child{{"Items", "Item"}, data};

    // Should remain nullopt
    EXPECT_FALSE(data.has_value());
}

TEST(SetEdgeCases, DeserializeOptionalSetEmptyChildren)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        // Has "Items" node but no "Item" children
        Helper::addChildNode(node, "Items");
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::optional<std::set<int>> data;
    adapter >> FileParse::Child{{"Items", "Item"}, data};

    // Should remain nullopt because nChildNode("Item") == 0
    EXPECT_FALSE(data.has_value());
}

TEST(SetEdgeCases, SerializeOptionalSetEmpty)
{
    const std::optional<std::set<int>> data = std::nullopt;
    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    adapter << FileParse::Child{{"Items", "Item"}, data};

    // Should have no children
    EXPECT_TRUE(adapter.getNode().child.empty());
}

TEST(SetEdgeCases, SerializeOptionalSetWithValue)
{
    const std::optional<std::set<int>> data = std::set<int>{1, 2, 3};
    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    adapter << FileParse::Child{{"Items", "Item"}, data};

    // Should have children
    EXPECT_FALSE(adapter.getNode().child.empty());
}

//////////////////////////////////////////////////////////////////////////////
// StringConversion.hxx edge cases
//////////////////////////////////////////////////////////////////////////////

enum class Color
{
    Red,
    Green,
    Blue,
    Unknown
};

TEST(StringConversionEdgeCases, EnumFromStringArrayNoDefault)
{
    // Test the overload without explicit default (uses array.size() - 1)
    std::array<std::string, 4> colorNames = {"Red", "Green", "Blue", "Unknown"};

    // Valid values
    EXPECT_EQ(FileParse::enumFromString<Color>("Red", colorNames), Color::Red);

    // Invalid value should return last enum (Unknown)
    EXPECT_EQ(FileParse::enumFromString<Color>("Purple", colorNames), Color::Unknown);
}

TEST(StringConversionEdgeCases, EnumFromStringCaseInsensitiveArrayNoDefault)
{
    // Test the overload without explicit default
    std::array<std::string, 4> colorNames = {"Red", "Green", "Blue", "Unknown"};

    // Valid case-insensitive values
    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive<Color>("RED", colorNames), Color::Red);
    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive<Color>("green", colorNames), Color::Green);

    // Invalid value should return last enum (Unknown)
    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive<Color>("Purple", colorNames), Color::Unknown);
}

TEST(StringConversionEdgeCases, EnumFromStringMapEmptyString)
{
    std::map<Color, std::string> colorMap = {
      {Color::Red, "Red"}, {Color::Green, "Green"}, {Color::Blue, "Blue"}};

    // Empty string should return default
    EXPECT_EQ(FileParse::enumFromString<Color>("", colorMap, Color::Unknown), Color::Unknown);
    EXPECT_EQ(FileParse::enumFromString<Color>("", colorMap), Color::Red);   // Default T{} = Red
}

TEST(StringConversionEdgeCases, EnumFromStringCaseInsensitiveMapEmptyString)
{
    std::map<Color, std::string> colorMap = {
      {Color::Red, "Red"}, {Color::Green, "Green"}, {Color::Blue, "Blue"}};

    // Empty string should return default
    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive<Color>("", colorMap, Color::Unknown),
              Color::Unknown);
    EXPECT_EQ(FileParse::enumFromStringCaseInsensitive<Color>("", colorMap),
              Color::Red);   // Default T{} = Red
}

TEST(StringConversionEdgeCases, EnumToStringOutOfBounds)
{
    std::array<std::string, 3> colorNames = {"Red", "Green", "Blue"};

    // Out of bounds index should return "Unknown"
    EXPECT_EQ(FileParse::enumToString(Color::Unknown, colorNames), "Unknown");
}

//////////////////////////////////////////////////////////////////////////////
// Base.hxx edge cases
//////////////////////////////////////////////////////////////////////////////

TEST(BaseEdgeCases, InsertAllChildsEmptyVector)
{
    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    // Empty nodeNames should just return the original node
    auto result = FileParse::insertAllChilds(adapter, {});

    // Should return the same node (no children added)
    EXPECT_EQ("BaseElement", result.getCurrentTag());
}

TEST(BaseEdgeCases, FindParentOfLastTagNotFound)
{
    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    // Looking for non-existent nested tags
    auto result = FileParse::findParentOfLastTag(adapter, {"Level1", "Level2", "Level3"});

    EXPECT_FALSE(result.has_value());
}

TEST(BaseEdgeCases, AssignIfHasValueWithValue)
{
    std::optional<int> source = 42;
    int target = 0;

    FileParse::assignIfHasValue(source, target);

    EXPECT_EQ(42, target);
}

TEST(BaseEdgeCases, AssignIfHasValueNoValue)
{
    std::optional<int> source = std::nullopt;
    int target = 100;

    FileParse::assignIfHasValue(source, target);

    // Target should remain unchanged
    EXPECT_EQ(100, target);
}

//////////////////////////////////////////////////////////////////////////////
// Vector.hxx edge cases
//////////////////////////////////////////////////////////////////////////////

TEST(VectorEdgeCases, SerializeEmptyNodeNames)
{
    const std::vector<int> data{1, 2, 3};
    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    // Empty nodeNames should return early without adding children
    adapter << FileParse::Child<const std::vector<int>>{{}, data};

    // Should have no children added
    EXPECT_TRUE(adapter.getNode().child.empty());
}

TEST(VectorEdgeCases, SerializeEmptyVector)
{
    const std::vector<int> data{};
    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    // Empty vector should return early without adding children
    adapter << FileParse::Child{{"Items", "Item"}, data};

    // Should have no children added
    EXPECT_TRUE(adapter.getNode().child.empty());
}

TEST(VectorEdgeCases, DeserializeNoMatchingChild)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        // No "Items" child node
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::vector<int> data;
    adapter >> FileParse::Child{{"Items", "Item"}, data};

    // Should remain empty
    EXPECT_TRUE(data.empty());
}

TEST(VectorEdgeCases, DeserializeOptionalVectorNoMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        // No matching children
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::optional<std::vector<int>> data;
    adapter >> FileParse::Child{{"Items", "Item"}, data};

    // Should remain nullopt
    EXPECT_FALSE(data.has_value());
}

TEST(VectorEdgeCases, DeserializeOptionalVectorEmptyChildren)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        // Has "Items" node but no "Item" children
        Helper::addChildNode(node, "Items");
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::optional<std::vector<int>> data;
    adapter >> FileParse::Child{{"Items", "Item"}, data};

    // Should remain nullopt because nChildNode("Item") == 0
    EXPECT_FALSE(data.has_value());
}

TEST(VectorEdgeCases, SerializeOptionalVectorEmpty)
{
    const std::optional<std::vector<int>> data = std::nullopt;
    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    adapter << FileParse::Child{{"Items", "Item"}, data};

    // Should have no children
    EXPECT_TRUE(adapter.getNode().child.empty());
}

TEST(VectorEdgeCases, SerializeOptionalVectorWithValue)
{
    const std::optional<std::vector<int>> data = std::vector<int>{1, 2, 3};
    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    adapter << FileParse::Child{{"Items", "Item"}, data};

    // Should have children
    EXPECT_FALSE(adapter.getNode().child.empty());
}

//////////////////////////////////////////////////////////////////////////////
// Common.hxx edge cases
//////////////////////////////////////////////////////////////////////////////

TEST(CommonEdgeCases, ChildDeserializeNoMatch)
{
    auto mockData = []() {
        Helper::MockNode node{"BaseElement"};
        // No matching child
        return node;
    };

    auto elementNode = mockData();
    const Helper::MockNodeAdapter adapter{&elementNode};

    std::string data = "original";
    adapter >> FileParse::Child{"NonExistent", data};

    // Data should remain unchanged when child not found
    EXPECT_EQ("original", data);
}

TEST(CommonEdgeCases, ChildSerializeMultiLevel)
{
    Helper::MockNode elementNode("BaseElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    std::string data = "nested value";
    adapter << FileParse::Child{{"Level1", "Level2", "Level3"}, data};

    // Should have nested structure
    ASSERT_EQ(1u, adapter.getNode().child.size());
    EXPECT_EQ("Level1", adapter.getNode().child[0].tag);
    ASSERT_EQ(1u, adapter.getNode().child[0].child.size());
    EXPECT_EQ("Level2", adapter.getNode().child[0].child[0].tag);
}
