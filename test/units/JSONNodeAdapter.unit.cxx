/// JSONNodeAdapter tests
#include <gtest/gtest.h>

#include <fileParse/JSONNodeAdapter.hxx>
#include <fileParse/FileDataHandler.hxx>

#include <fstream>
#include <cstdio>

//////////////////////////////////////////////////////////////////////////////
// JSONNodeAdapter basic tests
//////////////////////////////////////////////////////////////////////////////

TEST(JSONNodeAdapter, CreateTopNode)
{
    auto node = createJSONTopNode("TestRoot");

    EXPECT_FALSE(node.isEmpty());
    EXPECT_EQ("TestRoot", node.getCurrentTag());
}

TEST(JSONNodeAdapter, GetTextEmpty)
{
    auto node = createJSONTopNode("TestRoot");
    // Node has no text (it's an object), getText should return empty string
    EXPECT_EQ("", node.getText());
}

TEST(JSONNodeAdapter, GetTextWithContent)
{
    auto node = createJSONTopNode("TestRoot");
    auto child = node.addChild("Value");
    child.addText("Hello World");

    auto retrieved = node.getFirstChildByName("Value");
    ASSERT_TRUE(retrieved.has_value());
    EXPECT_EQ("Hello World", retrieved.value().getText());
}

TEST(JSONNodeAdapter, GetChildNodesEmpty)
{
    auto node = createJSONTopNode("TestRoot");
    auto children = node.getChildNodes();

    EXPECT_TRUE(children.empty());
}

TEST(JSONNodeAdapter, GetChildNodesWithChildren)
{
    auto node = createJSONTopNode("TestRoot");
    [[maybe_unused]] auto c1 = node.addChild("Child1");
    [[maybe_unused]] auto c2 = node.addChild("Child2");

    auto children = node.getChildNodes();

    EXPECT_EQ(2u, children.size());
}

TEST(JSONNodeAdapter, GetFirstChildByNameFound)
{
    auto node = createJSONTopNode("TestRoot");
    auto child1 = node.addChild("Child1");
    child1.addText("First");
    auto child2 = node.addChild("Child2");
    child2.addText("Second");

    auto found = node.getFirstChildByName("Child1");

    ASSERT_TRUE(found.has_value());
    EXPECT_EQ("Child1", found.value().getCurrentTag());
    EXPECT_EQ("First", found.value().getText());
}

TEST(JSONNodeAdapter, GetFirstChildByNameNotFound)
{
    auto node = createJSONTopNode("TestRoot");
    [[maybe_unused]] auto c1 = node.addChild("Child1");
    [[maybe_unused]] auto c2 = node.addChild("Child2");

    auto notFound = node.getFirstChildByName("NonExistent");

    EXPECT_FALSE(notFound.has_value());
}

TEST(JSONNodeAdapter, GetChildNodesByNameEmpty)
{
    auto node = createJSONTopNode("TestRoot");
    [[maybe_unused]] auto c1 = node.addChild("Other1");
    [[maybe_unused]] auto c2 = node.addChild("Other2");

    auto children = node.getChildNodesByName("NonExistent");

    EXPECT_TRUE(children.empty());
}

TEST(JSONNodeAdapter, GetChildNodesByNameMultiple)
{
    auto node = createJSONTopNode("TestRoot");
    auto c1 = node.addChild("Item");
    c1.addText("First");
    [[maybe_unused]] auto c2 = node.addChild("Other");
    auto c3 = node.addChild("Item");
    c3.addText("Second");
    auto c4 = node.addChild("Item");
    c4.addText("Third");

    auto children = node.getChildNodesByName("Item");

    EXPECT_EQ(3u, children.size());
    EXPECT_EQ("First", children[0].getText());
    EXPECT_EQ("Second", children[1].getText());
    EXPECT_EQ("Third", children[2].getText());
}

TEST(JSONNodeAdapter, NChildNode)
{
    auto node = createJSONTopNode("TestRoot");
    [[maybe_unused]] auto c1 = node.addChild("Item");
    [[maybe_unused]] auto c2 = node.addChild("Other");
    [[maybe_unused]] auto c3 = node.addChild("Item");

    EXPECT_EQ(2, node.nChildNode("Item"));
    EXPECT_EQ(1, node.nChildNode("Other"));
    EXPECT_EQ(0, node.nChildNode("NonExistent"));
}

TEST(JSONNodeAdapter, HasChildNode)
{
    auto node = createJSONTopNode("TestRoot");
    [[maybe_unused]] auto c = node.addChild("Child");

    EXPECT_TRUE(node.hasChildNode("Child"));
    EXPECT_FALSE(node.hasChildNode("NonExistent"));
}

TEST(JSONNodeAdapter, GetAttributeNotFound)
{
    auto node = createJSONTopNode("TestRoot");

    auto attr = node.getAttribute("nonexistent");

    EXPECT_FALSE(attr.has_value());
}

TEST(JSONNodeAdapter, GetAttributeFound)
{
    auto node = createJSONTopNode("TestRoot");
    node.addAttribute("myattr", "myvalue");

    auto attr = node.getAttribute("myattr");

    ASSERT_TRUE(attr.has_value());
    EXPECT_EQ("myvalue", attr.value());
}

TEST(JSONNodeAdapter, AddMultipleAttributes)
{
    auto node = createJSONTopNode("TestRoot");
    node.addAttribute("attr1", "value1");
    node.addAttribute("attr2", "value2");

    EXPECT_EQ("value1", node.getAttribute("attr1").value());
    EXPECT_EQ("value2", node.getAttribute("attr2").value());
}

TEST(JSONNodeAdapter, GetContent)
{
    auto node = createJSONTopNode("TestRoot");
    auto child = node.addChild("Child");
    child.addText("content");

    auto content = node.getContent();

    EXPECT_FALSE(content.empty());
    EXPECT_NE(std::string::npos, content.find("TestRoot"));
    EXPECT_NE(std::string::npos, content.find("Child"));
    EXPECT_NE(std::string::npos, content.find("content"));
}

//////////////////////////////////////////////////////////////////////////////
// JSON-specific array handling tests
//////////////////////////////////////////////////////////////////////////////

TEST(JSONNodeAdapter, ArrayCreationFromMultipleChildren)
{
    auto node = createJSONTopNode("TestRoot");
    auto item1 = node.addChild("Value");
    item1.addText("first");
    auto item2 = node.addChild("Value");
    item2.addText("second");
    auto item3 = node.addChild("Value");
    item3.addText("third");

    // Check that we have 3 children named "Value"
    EXPECT_EQ(3, node.nChildNode("Value"));

    // Verify we can retrieve all of them
    auto values = node.getChildNodesByName("Value");
    ASSERT_EQ(3u, values.size());
    EXPECT_EQ("first", values[0].getText());
    EXPECT_EQ("second", values[1].getText());
    EXPECT_EQ("third", values[2].getText());
}

TEST(JSONNodeAdapter, GetFirstChildFromArray)
{
    auto node = createJSONTopNode("TestRoot");
    auto item1 = node.addChild("Value");
    item1.addText("first");
    auto item2 = node.addChild("Value");
    item2.addText("second");

    auto first = node.getFirstChildByName("Value");

    ASSERT_TRUE(first.has_value());
    EXPECT_EQ("first", first.value().getText());
}

//////////////////////////////////////////////////////////////////////////////
// File operations tests
//////////////////////////////////////////////////////////////////////////////

TEST(JSONNodeAdapter, GetTopNodeFromStringValid)
{
    const std::string json = R"({"Root": {"Child": "value"}})";
    auto node = getJSONTopNodeFromString(json, "Root");

    ASSERT_TRUE(node.has_value());
    EXPECT_EQ("Root", node.value().getCurrentTag());
}

TEST(JSONNodeAdapter, GetTopNodeFromStringInvalid)
{
    const std::string json = "not valid json";
    auto node = getJSONTopNodeFromString(json, "Root");

    EXPECT_FALSE(node.has_value());
}

TEST(JSONNodeAdapter, GetTopNodeFromStringEmpty)
{
    const std::string json = "";
    auto node = getJSONTopNodeFromString(json, "Root");

    EXPECT_FALSE(node.has_value());
}

TEST(JSONNodeAdapter, GetTopNodeFromStringWrongRoot)
{
    const std::string json = R"({"WrongRoot": {"Child": "value"}})";
    auto node = getJSONTopNodeFromString(json, "ExpectedRoot");

    EXPECT_FALSE(node.has_value());
}

TEST(JSONNodeAdapter, GetTopNodeFromFileNonExistent)
{
    auto node = getJSONTopNodeFromFile("this_file_does_not_exist_12345.json", "Root");

    EXPECT_FALSE(node.has_value());
}

TEST(JSONNodeAdapter, GetTopNodeFromFileInvalidContent)
{
    const std::string tempFile = "temp_invalid_json_test.json";
    {
        std::ofstream out(tempFile);
        out << "this is not valid json";
    }

    auto node = getJSONTopNodeFromFile(tempFile, "Root");

    EXPECT_FALSE(node.has_value());

    std::remove(tempFile.c_str());
}

TEST(JSONNodeAdapter, GetTopNodeFromFileValid)
{
    const std::string tempFile = "temp_valid_json_test.json";
    {
        std::ofstream out(tempFile);
        out << R"({"Root": {"Child": "test"}})";
    }

    auto node = getJSONTopNodeFromFile(tempFile, "Root");

    ASSERT_TRUE(node.has_value());
    EXPECT_EQ("Root", node.value().getCurrentTag());

    std::remove(tempFile.c_str());
}

TEST(JSONNodeAdapter, WriteToFileAndReadBack)
{
    const std::string tempFile = "temp_write_json_test.json";

    // Create and write
    auto writeNode = createJSONTopNode("TestDoc");
    auto child = writeNode.addChild("Data");
    child.addText("test value");

    int result = writeNode.writeToFile(tempFile);
    EXPECT_EQ(0, result);

    // Read back
    auto readNode = getJSONTopNodeFromFile(tempFile, "TestDoc");
    ASSERT_TRUE(readNode.has_value());

    auto dataChild = readNode.value().getFirstChildByName("Data");
    ASSERT_TRUE(dataChild.has_value());
    EXPECT_EQ("test value", dataChild.value().getText());

    std::remove(tempFile.c_str());
}

//////////////////////////////////////////////////////////////////////////////
// Integration tests with FileDataHandler
//////////////////////////////////////////////////////////////////////////////

struct JSONTestData
{
    std::string name;
    int value{0};
};

template<typename NodeAdapter>
NodeAdapter & operator<<(NodeAdapter & node, const JSONTestData & data)
{
    auto nameNode = node.addChild("Name");
    nameNode.addText(data.name);
    auto valueNode = node.addChild("Value");
    valueNode.addText(std::to_string(data.value));
    return node;
}

template<typename NodeAdapter>
const NodeAdapter & operator>>(const NodeAdapter & node, JSONTestData & data)
{
    if(auto nameNode = node.getFirstChildByName("Name"); nameNode.has_value())
    {
        data.name = nameNode.value().getText();
    }
    if(auto valueNode = node.getFirstChildByName("Value"); valueNode.has_value())
    {
        data.value = std::stoi(valueNode.value().getText());
    }
    return node;
}

TEST(JSONNodeAdapter, SerializationRoundTrip)
{
    JSONTestData original;
    original.name = "TestName";
    original.value = 42;

    // Serialize
    auto node = createJSONTopNode("TestData");
    node << original;

    // Get JSON string
    auto jsonStr = node.getContent();
    EXPECT_FALSE(jsonStr.empty());

    // Deserialize
    auto readNode = getJSONTopNodeFromString(jsonStr, "TestData");
    ASSERT_TRUE(readNode.has_value());

    JSONTestData loaded;
    readNode.value() >> loaded;

    EXPECT_EQ("TestName", loaded.name);
    EXPECT_EQ(42, loaded.value);
}

TEST(JSONNodeAdapter, FileRoundTrip)
{
    const std::string tempFile = "temp_json_roundtrip_test.json";

    JSONTestData original;
    original.name = "FileTest";
    original.value = 123;

    // Serialize to file
    auto writeNode = createJSONTopNode("TestData");
    writeNode << original;
    int writeResult = writeNode.writeToFile(tempFile);
    EXPECT_EQ(0, writeResult);

    // Deserialize from file
    auto readNode = getJSONTopNodeFromFile(tempFile, "TestData");
    ASSERT_TRUE(readNode.has_value());

    JSONTestData loaded;
    readNode.value() >> loaded;

    EXPECT_EQ("FileTest", loaded.name);
    EXPECT_EQ(123, loaded.value);

    std::remove(tempFile.c_str());
}

//////////////////////////////////////////////////////////////////////////////
// Attribute tests (stored as properties in JSON)
//////////////////////////////////////////////////////////////////////////////

TEST(JSONNodeAdapter, AttributesAsProperties)
{
    auto node = createJSONTopNode("Test");
    auto child = node.addChild("AttributesTest");
    child.addAttribute("Name", "Text");
    child.addAttribute("Age", "23");

    // Verify attributes can be retrieved
    auto retrieved = node.getFirstChildByName("AttributesTest");
    ASSERT_TRUE(retrieved.has_value());
    EXPECT_EQ("Text", retrieved.value().getAttribute("Name").value());
    EXPECT_EQ("23", retrieved.value().getAttribute("Age").value());

    // Verify JSON output contains expected values
    auto content = node.getContent();
    EXPECT_NE(std::string::npos, content.find("AttributesTest"));
    EXPECT_NE(std::string::npos, content.find("Name"));
    EXPECT_NE(std::string::npos, content.find("Text"));
}

//////////////////////////////////////////////////////////////////////////////
// Edge cases
//////////////////////////////////////////////////////////////////////////////

TEST(JSONNodeAdapter, EmptyNodeOperations)
{
    JSONNodeAdapter emptyNode(nullptr);

    EXPECT_TRUE(emptyNode.isEmpty());
    EXPECT_EQ("", emptyNode.getText());
    EXPECT_EQ("", emptyNode.getCurrentTag());
    EXPECT_TRUE(emptyNode.getChildNodes().empty());
    EXPECT_FALSE(emptyNode.getFirstChildByName("any").has_value());
    EXPECT_TRUE(emptyNode.getChildNodesByName("any").empty());
    EXPECT_EQ(0, emptyNode.nChildNode("any"));
    EXPECT_FALSE(emptyNode.hasChildNode("any"));
    EXPECT_FALSE(emptyNode.getAttribute("any").has_value());
    EXPECT_EQ("", emptyNode.getContent());
}

TEST(JSONNodeAdapter, NestedStructure)
{
    auto root = createJSONTopNode("Root");
    auto level1 = root.addChild("Level1");
    auto level2 = level1.addChild("Level2");
    auto level3 = level2.addChild("Level3");
    level3.addText("deep value");

    // Navigate through nested structure
    auto l1 = root.getFirstChildByName("Level1");
    ASSERT_TRUE(l1.has_value());

    auto l2 = l1.value().getFirstChildByName("Level2");
    ASSERT_TRUE(l2.has_value());

    auto l3 = l2.value().getFirstChildByName("Level3");
    ASSERT_TRUE(l3.has_value());
    EXPECT_EQ("deep value", l3.value().getText());
}

TEST(JSONNodeAdapter, MixedChildrenAndAttributes)
{
    auto root = createJSONTopNode("Root");
    root.addAttribute("version", "1.0");
    auto child = root.addChild("Child");
    child.addText("child content");

    EXPECT_EQ("1.0", root.getAttribute("version").value());
    auto childNode = root.getFirstChildByName("Child");
    ASSERT_TRUE(childNode.has_value());
    EXPECT_EQ("child content", childNode.value().getText());
}
