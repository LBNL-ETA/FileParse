/// XMLNodeAdapter edge case tests to improve branch coverage
#include <gtest/gtest.h>

#include <fileParse/XMLNodeAdapter.hxx>
#include <fileParse/FileDataHandler.hxx>

#include <fstream>
#include <cstdio>

//////////////////////////////////////////////////////////////////////////////
// XMLNodeAdapter edge cases
//////////////////////////////////////////////////////////////////////////////

TEST(XMLNodeAdapterEdgeCases, CreateTopNode)
{
    auto node = createTopNode("TestRoot");

    EXPECT_FALSE(node.isEmpty());
    EXPECT_EQ("TestRoot", node.getCurrentTag());
}

TEST(XMLNodeAdapterEdgeCases, GetTextEmpty)
{
    auto node = createTopNode("TestRoot");
    // Node has no text, getText should return empty string
    EXPECT_EQ("", node.getText());
}

TEST(XMLNodeAdapterEdgeCases, GetTextWithContent)
{
    auto node = createTopNode("TestRoot");
    node.addText("Hello World");

    EXPECT_EQ("Hello World", node.getText());
}

TEST(XMLNodeAdapterEdgeCases, GetChildNodesEmpty)
{
    auto node = createTopNode("TestRoot");
    auto children = node.getChildNodes();

    EXPECT_TRUE(children.empty());
}

TEST(XMLNodeAdapterEdgeCases, GetChildNodesWithChildren)
{
    auto node = createTopNode("TestRoot");
    [[maybe_unused]] auto c1 = node.addChild("Child1");
    [[maybe_unused]] auto c2 = node.addChild("Child2");

    auto children = node.getChildNodes();

    EXPECT_EQ(2u, children.size());
}

TEST(XMLNodeAdapterEdgeCases, GetFirstChildByNameFound)
{
    auto node = createTopNode("TestRoot");
    auto child1 = node.addChild("Child1");
    child1.addText("First");
    auto child2 = node.addChild("Child2");
    child2.addText("Second");

    auto found = node.getFirstChildByName("Child1");

    ASSERT_TRUE(found.has_value());
    EXPECT_EQ("Child1", found.value().getCurrentTag());
    EXPECT_EQ("First", found.value().getText());
}

TEST(XMLNodeAdapterEdgeCases, GetFirstChildByNameNotFound)
{
    auto node = createTopNode("TestRoot");
    [[maybe_unused]] auto c1 = node.addChild("Child1");
    [[maybe_unused]] auto c2 = node.addChild("Child2");

    auto notFound = node.getFirstChildByName("NonExistent");

    EXPECT_FALSE(notFound.has_value());
}

TEST(XMLNodeAdapterEdgeCases, GetChildNodesByNameEmpty)
{
    auto node = createTopNode("TestRoot");
    [[maybe_unused]] auto c1 = node.addChild("Other1");
    [[maybe_unused]] auto c2 = node.addChild("Other2");

    auto children = node.getChildNodesByName("NonExistent");

    EXPECT_TRUE(children.empty());
}

TEST(XMLNodeAdapterEdgeCases, GetChildNodesByNameMultiple)
{
    auto node = createTopNode("TestRoot");
    [[maybe_unused]] auto c1 = node.addChild("Item");
    [[maybe_unused]] auto c2 = node.addChild("Other");
    [[maybe_unused]] auto c3 = node.addChild("Item");
    [[maybe_unused]] auto c4 = node.addChild("Item");

    auto children = node.getChildNodesByName("Item");

    EXPECT_EQ(3u, children.size());
}

TEST(XMLNodeAdapterEdgeCases, NChildNode)
{
    auto node = createTopNode("TestRoot");
    [[maybe_unused]] auto c1 = node.addChild("Item");
    [[maybe_unused]] auto c2 = node.addChild("Other");
    [[maybe_unused]] auto c3 = node.addChild("Item");

    EXPECT_EQ(2, node.nChildNode("Item"));
    EXPECT_EQ(1, node.nChildNode("Other"));
    EXPECT_EQ(0, node.nChildNode("NonExistent"));
}

TEST(XMLNodeAdapterEdgeCases, HasChildNode)
{
    auto node = createTopNode("TestRoot");
    [[maybe_unused]] auto c = node.addChild("Child");

    EXPECT_TRUE(node.hasChildNode("Child"));
    EXPECT_FALSE(node.hasChildNode("NonExistent"));
}

TEST(XMLNodeAdapterEdgeCases, GetAttributeNotFound)
{
    auto node = createTopNode("TestRoot");

    auto attr = node.getAttribute("nonexistent");

    EXPECT_FALSE(attr.has_value());
}

TEST(XMLNodeAdapterEdgeCases, GetAttributeFound)
{
    auto node = createTopNode("TestRoot");
    node.addAttribute("myattr", "myvalue");

    auto attr = node.getAttribute("myattr");

    ASSERT_TRUE(attr.has_value());
    EXPECT_EQ("myvalue", attr.value());
}

TEST(XMLNodeAdapterEdgeCases, AddMultipleAttributes)
{
    auto node = createTopNode("TestRoot");
    node.addAttribute("attr1", "value1");
    node.addAttribute("attr2", "value2");

    EXPECT_EQ("value1", node.getAttribute("attr1").value());
    EXPECT_EQ("value2", node.getAttribute("attr2").value());
}

TEST(XMLNodeAdapterEdgeCases, GetContent)
{
    auto node = createTopNode("TestRoot");
    auto child = node.addChild("Child");
    child.addText("content");

    auto content = node.getContent();

    EXPECT_FALSE(content.empty());
    EXPECT_NE(std::string::npos, content.find("TestRoot"));
    EXPECT_NE(std::string::npos, content.find("Child"));
}

//////////////////////////////////////////////////////////////////////////////
// File operations edge cases
//////////////////////////////////////////////////////////////////////////////

TEST(XMLNodeAdapterEdgeCases, GetTopNodeFromStringValid)
{
    const std::string xml = "<Root><Child>value</Child></Root>";
    auto node = getTopNodeFromString(xml, "Root");

    ASSERT_TRUE(node.has_value());
    EXPECT_EQ("Root", node.value().getCurrentTag());
}

TEST(XMLNodeAdapterEdgeCases, GetTopNodeFromStringInvalid)
{
    const std::string xml = "not valid xml";
    auto node = getTopNodeFromString(xml, "Root");

    EXPECT_FALSE(node.has_value());
}

TEST(XMLNodeAdapterEdgeCases, GetTopNodeFromStringEmpty)
{
    const std::string xml = "";
    auto node = getTopNodeFromString(xml, "Root");

    EXPECT_FALSE(node.has_value());
}

TEST(XMLNodeAdapterEdgeCases, GetTopNodeFromStringWrongRoot)
{
    const std::string xml = "<WrongRoot><Child>value</Child></WrongRoot>";
    auto node = getTopNodeFromString(xml, "ExpectedRoot");

    EXPECT_FALSE(node.has_value());
}

TEST(XMLNodeAdapterEdgeCases, GetTopNodeFromFileNonExistent)
{
    auto node = getTopNodeFromFile("this_file_does_not_exist_12345.xml", "Root");

    EXPECT_FALSE(node.has_value());
}

TEST(XMLNodeAdapterEdgeCases, GetTopNodeFromFileInvalidContent)
{
    // Create a temporary file with invalid XML
    const std::string tempFile = "temp_invalid_test.xml";
    {
        std::ofstream out(tempFile);
        out << "this is not valid xml";
    }

    auto node = getTopNodeFromFile(tempFile, "Root");

    EXPECT_FALSE(node.has_value());

    // Cleanup
    std::remove(tempFile.c_str());
}

TEST(XMLNodeAdapterEdgeCases, GetTopNodeFromFileValid)
{
    // Create a temporary file with valid XML
    const std::string tempFile = "temp_valid_test.xml";
    {
        std::ofstream out(tempFile);
        out << "<Root><Child>test</Child></Root>";
    }

    auto node = getTopNodeFromFile(tempFile, "Root");

    ASSERT_TRUE(node.has_value());
    EXPECT_EQ("Root", node.value().getCurrentTag());

    // Cleanup
    std::remove(tempFile.c_str());
}

TEST(XMLNodeAdapterEdgeCases, WriteToFileAndReadBack)
{
    const std::string tempFile = "temp_write_test.xml";

    // Create and write
    auto writeNode = createTopNode("TestDoc");
    auto child = writeNode.addChild("Data");
    child.addText("test value");

    int result = writeNode.writeToFile(tempFile);
    EXPECT_EQ(0, result);   // 0 indicates success

    // Read back
    auto readNode = getTopNodeFromFile(tempFile, "TestDoc");
    ASSERT_TRUE(readNode.has_value());

    auto dataChild = readNode.value().getFirstChildByName("Data");
    ASSERT_TRUE(dataChild.has_value());
    EXPECT_EQ("test value", dataChild.value().getText());

    // Cleanup
    std::remove(tempFile.c_str());
}

//////////////////////////////////////////////////////////////////////////////
// FileDataHandler with actual file operations
//////////////////////////////////////////////////////////////////////////////

struct TestData
{
    std::string name;
    int value{0};
};

template<typename NodeAdapter>
NodeAdapter & operator<<(NodeAdapter & node, const TestData & data)
{
    auto nameNode = node.addChild("Name");
    nameNode.addText(data.name);
    auto valueNode = node.addChild("Value");
    valueNode.addText(std::to_string(data.value));
    return node;
}

template<typename NodeAdapter>
const NodeAdapter & operator>>(const NodeAdapter & node, TestData & data)
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

TEST(FileDataHandlerEdgeCases, LoadFromFileCreatesNewFile)
{
    const std::string tempFile = "temp_new_file_test.xml";

    // Ensure file doesn't exist
    std::remove(tempFile.c_str());

    // This should create the file and return a default-constructed object
    auto result = Common::loadFromXMLFile<TestData>(tempFile, "TestData");

    // File should have been created
    std::ifstream check(tempFile);
    EXPECT_TRUE(check.good());
    check.close();

    // Result should be valid (empty but parseable)
    EXPECT_TRUE(result.has_value());

    // Cleanup
    std::remove(tempFile.c_str());
}

TEST(FileDataHandlerEdgeCases, SaveAndLoadFromFile)
{
    const std::string tempFile = "temp_save_load_test.xml";

    TestData original;
    original.name = "TestName";
    original.value = 42;

    // Save
    int saveResult = Common::saveToXMLFile(original, tempFile, "TestData");
    EXPECT_EQ(0, saveResult);

    // Load
    auto loaded = Common::loadFromXMLFile<TestData>(tempFile, "TestData");

    ASSERT_TRUE(loaded.has_value());
    EXPECT_EQ("TestName", loaded.value().name);
    EXPECT_EQ(42, loaded.value().value);

    // Cleanup
    std::remove(tempFile.c_str());
}

TEST(FileDataHandlerEdgeCases, LoadFromFileWithInvalidContent)
{
    const std::string tempFile = "temp_invalid_content_test.xml";

    // Create a file with invalid XML content
    {
        std::ofstream out(tempFile);
        out << "this is not valid xml content";
    }

    // loadFromXMLFile should return nullopt for invalid content
    auto result = Common::loadFromXMLFile<TestData>(tempFile, "TestData");

    EXPECT_FALSE(result.has_value());

    // Cleanup
    std::remove(tempFile.c_str());
}

TEST(FileDataHandlerEdgeCases, LoadFromFileWithWrongRootNode)
{
    const std::string tempFile = "temp_wrong_root_test.xml";

    // Create a file with valid XML but wrong root node
    {
        std::ofstream out(tempFile);
        out << "<WrongRoot><Name>test</Name></WrongRoot>";
    }

    // loadFromXMLFile should return nullopt for wrong root node
    auto result = Common::loadFromXMLFile<TestData>(tempFile, "TestData");

    EXPECT_FALSE(result.has_value());

    // Cleanup
    std::remove(tempFile.c_str());
}
