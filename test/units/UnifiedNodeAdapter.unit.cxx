/// UnifiedNodeAdapter tests - Tests for the variant-based NodeAdapter functions
#include <gtest/gtest.h>

#include <fileParse/FileDataHandler.hxx>
#include <fileParse/Common.hxx>

#include <fstream>
#include <cstdio>

//////////////////////////////////////////////////////////////////////////////
// createTopNode tests
//////////////////////////////////////////////////////////////////////////////

TEST(UnifiedNodeAdapter, CreateTopNodeXML)
{
    auto node = Common::createTopNode("TestRoot", FileParse::FileFormat::XML);

    EXPECT_TRUE(std::holds_alternative<XMLNodeAdapter>(node));

    std::visit(
      [](auto & adapter)
      {
          EXPECT_FALSE(adapter.isEmpty());
          EXPECT_EQ("TestRoot", adapter.getCurrentTag());
      },
      node);
}

TEST(UnifiedNodeAdapter, CreateTopNodeJSON)
{
    auto node = Common::createTopNode("TestRoot", FileParse::FileFormat::JSON);

    EXPECT_TRUE(std::holds_alternative<JSONNodeAdapter>(node));

    std::visit(
      [](auto & adapter)
      {
          EXPECT_FALSE(adapter.isEmpty());
          EXPECT_EQ("TestRoot", adapter.getCurrentTag());
      },
      node);
}

TEST(UnifiedNodeAdapter, CreateTopNodeUnknownDefaultsToXML)
{
    const auto node = Common::createTopNode("TestRoot", FileParse::FileFormat::Unknown);

    EXPECT_TRUE(std::holds_alternative<XMLNodeAdapter>(node));
}

TEST(UnifiedNodeAdapter, CreateTopNodeAndAddChildren)
{
    auto xmlNode = Common::createTopNode("Root", FileParse::FileFormat::XML);
    auto jsonNode = Common::createTopNode("Root", FileParse::FileFormat::JSON);

    // Test adding children works for both types
    std::visit(
      [](auto & adapter)
      {
          auto child = adapter.addChild("Child");
          child.addText("content");

          EXPECT_TRUE(adapter.hasChildNode("Child"));
          auto retrieved = adapter.getFirstChildByName("Child");
          ASSERT_TRUE(retrieved.has_value());
          EXPECT_EQ("content", retrieved.value().getText());
      },
      xmlNode);

    std::visit(
      [](auto & adapter)
      {
          auto child = adapter.addChild("Child");
          child.addText("content");

          EXPECT_TRUE(adapter.hasChildNode("Child"));
          auto retrieved = adapter.getFirstChildByName("Child");
          ASSERT_TRUE(retrieved.has_value());
          EXPECT_EQ("content", retrieved.value().getText());
      },
      jsonNode);
}

//////////////////////////////////////////////////////////////////////////////
// getTopNodeFromFile tests
//////////////////////////////////////////////////////////////////////////////

TEST(UnifiedNodeAdapter, GetTopNodeFromFileXML)
{
    const std::string tempFile = "temp_unified_xml_test.xml";
    {
        std::ofstream out(tempFile);
        out << "<Root><Child>xml content</Child></Root>";
    }

    auto node = Common::getTopNodeFromFile(tempFile, "Root");

    ASSERT_TRUE(node.has_value());
    EXPECT_TRUE(std::holds_alternative<XMLNodeAdapter>(*node));

    std::visit(
      [](auto & adapter)
      {
          EXPECT_EQ("Root", adapter.getCurrentTag());
          auto child = adapter.getFirstChildByName("Child");
          ASSERT_TRUE(child.has_value());
          EXPECT_EQ("xml content", child.value().getText());
      },
      *node);

    std::remove(tempFile.c_str());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromFileJSON)
{
    const std::string tempFile = "temp_unified_json_test.json";
    {
        std::ofstream out(tempFile);
        out << R"({"Root": {"Child": "json content"}})";
    }

    const auto node = Common::getTopNodeFromFile(tempFile, "Root");

    ASSERT_TRUE(node.has_value());
    EXPECT_TRUE(std::holds_alternative<JSONNodeAdapter>(*node));

    std::visit(
      [](auto & adapter)
      {
          EXPECT_EQ("Root", adapter.getCurrentTag());
          auto child = adapter.getFirstChildByName("Child");
          ASSERT_TRUE(child.has_value());
          EXPECT_EQ("json content", child.value().getText());
      },
      *node);

    std::remove(tempFile.c_str());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromFileNonExistent)
{
    auto node = Common::getTopNodeFromFile("this_file_does_not_exist_12345.xml", "Root");

    EXPECT_FALSE(node.has_value());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromFileInvalidXML)
{
    const std::string tempFile = "temp_unified_invalid.xml";
    {
        std::ofstream out(tempFile);
        out << "this is not valid xml";
    }

    const auto node = Common::getTopNodeFromFile(tempFile, "Root");

    EXPECT_FALSE(node.has_value());

    std::remove(tempFile.c_str());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromFileInvalidJSON)
{
    const std::string tempFile = "temp_unified_invalid.json";
    {
        std::ofstream out(tempFile);
        out << "this is not valid json";
    }

    auto node = Common::getTopNodeFromFile(tempFile, "Root");

    EXPECT_FALSE(node.has_value());

    std::remove(tempFile.c_str());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromFileWrongRootXML)
{
    const std::string tempFile = "temp_unified_wrong_root.xml";
    {
        std::ofstream out(tempFile);
        out << "<WrongRoot><Child>content</Child></WrongRoot>";
    }

    auto node = Common::getTopNodeFromFile(tempFile, "ExpectedRoot");

    EXPECT_FALSE(node.has_value());

    std::remove(tempFile.c_str());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromFileWrongRootJSON)
{
    const std::string tempFile = "temp_unified_wrong_root.json";
    {
        std::ofstream out(tempFile);
        out << R"({"WrongRoot": {"Child": "content"}})";
    }

    const auto node = Common::getTopNodeFromFile(tempFile, "ExpectedRoot");

    EXPECT_FALSE(node.has_value());

    std::remove(tempFile.c_str());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromFileUnknownExtensionDetectsFromContent)
{
    const std::string tempFile = "temp_unified_unknown.dat";
    {
        std::ofstream out(tempFile);
        out << "<Root><Child>content</Child></Root>";
    }

    const auto node = Common::getTopNodeFromFile(tempFile, "Root");

    // Unknown extension falls back to content detection, which finds XML
    ASSERT_TRUE(node.has_value());
    EXPECT_TRUE(std::holds_alternative<XMLNodeAdapter>(*node));

    std::visit(
      [](const auto & adapter)
      {
          EXPECT_EQ("Root", adapter.getCurrentTag());
          auto child = adapter.getFirstChildByName("Child");
          ASSERT_TRUE(child.has_value());
          EXPECT_EQ("content", child.value().getText());
      },
      *node);

    std::remove(tempFile.c_str());
}

//////////////////////////////////////////////////////////////////////////////
// getTopNodeFromString tests
//////////////////////////////////////////////////////////////////////////////

TEST(UnifiedNodeAdapter, GetTopNodeFromStringXML)
{
    const std::string xml = "<Root><Child>xml value</Child></Root>";

    const auto node = Common::getTopNodeFromString(xml, "Root", FileParse::FileFormat::XML);

    ASSERT_TRUE(node.has_value());
    EXPECT_TRUE(std::holds_alternative<XMLNodeAdapter>(*node));

    std::visit(
      [](auto & adapter)
      {
          EXPECT_EQ("Root", adapter.getCurrentTag());
          auto child = adapter.getFirstChildByName("Child");
          ASSERT_TRUE(child.has_value());
          EXPECT_EQ("xml value", child.value().getText());
      },
      *node);
}

TEST(UnifiedNodeAdapter, GetTopNodeFromStringJSON)
{
    const std::string json = R"({"Root": {"Child": "json value"}})";

    const auto node = Common::getTopNodeFromString(json, "Root", FileParse::FileFormat::JSON);

    ASSERT_TRUE(node.has_value());
    EXPECT_TRUE(std::holds_alternative<JSONNodeAdapter>(*node));

    std::visit(
      [](auto & adapter)
      {
          EXPECT_EQ("Root", adapter.getCurrentTag());
          auto child = adapter.getFirstChildByName("Child");
          ASSERT_TRUE(child.has_value());
          EXPECT_EQ("json value", child.value().getText());
      },
      *node);
}

TEST(UnifiedNodeAdapter, GetTopNodeFromStringInvalidXML)
{
    const std::string invalidXml = "not valid xml";

    const auto node = Common::getTopNodeFromString(invalidXml, "Root", FileParse::FileFormat::XML);

    EXPECT_FALSE(node.has_value());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromStringInvalidJSON)
{
    const std::string invalidJson = "not valid json";

    const auto node = Common::getTopNodeFromString(invalidJson, "Root", FileParse::FileFormat::JSON);

    EXPECT_FALSE(node.has_value());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromStringEmptyXML)
{
    const auto node = Common::getTopNodeFromString("", "Root", FileParse::FileFormat::XML);

    EXPECT_FALSE(node.has_value());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromStringEmptyJSON)
{
    const auto node = Common::getTopNodeFromString("", "Root", FileParse::FileFormat::JSON);

    EXPECT_FALSE(node.has_value());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromStringWrongRootXML)
{
    const std::string xml = "<WrongRoot><Child>value</Child></WrongRoot>";

    const auto node = Common::getTopNodeFromString(xml, "ExpectedRoot", FileParse::FileFormat::XML);

    EXPECT_FALSE(node.has_value());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromStringWrongRootJSON)
{
    const std::string json = R"({"WrongRoot": {"Child": "value"}})";

    const auto node = Common::getTopNodeFromString(json, "ExpectedRoot", FileParse::FileFormat::JSON);

    EXPECT_FALSE(node.has_value());
}

TEST(UnifiedNodeAdapter, GetTopNodeFromStringUnknownFormat)
{
    const std::string data = "<Root><Child>value</Child></Root>";

    const auto node = Common::getTopNodeFromString(data, "Root", FileParse::FileFormat::Unknown);

    EXPECT_FALSE(node.has_value());
}

//////////////////////////////////////////////////////////////////////////////
// Round-trip tests using std::visit
//////////////////////////////////////////////////////////////////////////////

struct UnifiedTestData
{
    std::string name;
    int value{0};
};

template<typename NodeAdapter>
inline NodeAdapter & operator<<(NodeAdapter & node, const UnifiedTestData & data)
{
    using FileParse::Child;
    node << Child{"Name", data.name};
    node << Child{"Value", data.value};
    return node;
}

template<typename NodeAdapter>
inline const NodeAdapter & operator>>(const NodeAdapter & node, UnifiedTestData & data)
{
    using FileParse::Child;
    node >> Child{"Name", data.name};
    node >> Child{"Value", data.value};
    return node;
}

TEST(UnifiedNodeAdapter, RoundTripXMLWithVisit)
{
    UnifiedTestData original{"TestXML", 42};

    // Serialize using variant
    auto writeNode = Common::createTopNode("TestData", FileParse::FileFormat::XML);
    std::visit([&original](auto & adapter) { adapter << original; }, writeNode);

    // Get content
    std::string content;
    std::visit([&content](auto & adapter) { content = adapter.getContent(); }, writeNode);

    EXPECT_FALSE(content.empty());
    EXPECT_NE(std::string::npos, content.find("TestXML"));

    // Deserialize
    auto readNode = Common::getTopNodeFromString(content, "TestData", FileParse::FileFormat::XML);
    ASSERT_TRUE(readNode.has_value());

    UnifiedTestData loaded;
    std::visit([&loaded](auto & adapter) { adapter >> loaded; }, *readNode);

    EXPECT_EQ("TestXML", loaded.name);
    EXPECT_EQ(42, loaded.value);
}

TEST(UnifiedNodeAdapter, RoundTripJSONWithVisit)
{
    UnifiedTestData original{"TestJSON", 123};

    // Serialize using variant
    auto writeNode = Common::createTopNode("TestData", FileParse::FileFormat::JSON);
    std::visit([&original](auto & adapter) { adapter << original; }, writeNode);

    // Get content
    std::string content;
    std::visit([&content](auto & adapter) { content = adapter.getContent(); }, writeNode);

    EXPECT_FALSE(content.empty());
    EXPECT_NE(std::string::npos, content.find("TestJSON"));

    // Deserialize
    auto readNode = Common::getTopNodeFromString(content, "TestData", FileParse::FileFormat::JSON);
    ASSERT_TRUE(readNode.has_value());

    UnifiedTestData loaded;
    std::visit([&loaded](auto & adapter) { adapter >> loaded; }, *readNode);

    EXPECT_EQ("TestJSON", loaded.name);
    EXPECT_EQ(123, loaded.value);
}

TEST(UnifiedNodeAdapter, FileRoundTripXML)
{
    const std::string tempFile = "temp_unified_roundtrip.xml";

    UnifiedTestData original{"FileXML", 456};

    // Serialize to file
    auto writeNode = Common::createTopNode("TestData", FileParse::FileFormat::XML);
    std::visit([&original](auto & adapter) { adapter << original; }, writeNode);

    int writeResult = 0;
    std::visit([&tempFile, &writeResult](auto & adapter) { writeResult = adapter.writeToFile(tempFile); },
               writeNode);
    EXPECT_EQ(0, writeResult);

    // Read back using auto-detect
    auto readNode = Common::getTopNodeFromFile(tempFile, "TestData");
    ASSERT_TRUE(readNode.has_value());
    EXPECT_TRUE(std::holds_alternative<XMLNodeAdapter>(*readNode));

    UnifiedTestData loaded;
    std::visit([&loaded](auto & adapter) { adapter >> loaded; }, *readNode);

    EXPECT_EQ("FileXML", loaded.name);
    EXPECT_EQ(456, loaded.value);

    std::remove(tempFile.c_str());
}

TEST(UnifiedNodeAdapter, FileRoundTripJSON)
{
    const std::string tempFile = "temp_unified_roundtrip.json";

    UnifiedTestData original{"FileJSON", 789};

    // Serialize to file
    auto writeNode = Common::createTopNode("TestData", FileParse::FileFormat::JSON);
    std::visit([&original](auto & adapter) { adapter << original; }, writeNode);

    int writeResult = 0;
    std::visit([&tempFile, &writeResult](auto & adapter) { writeResult = adapter.writeToFile(tempFile); },
               writeNode);
    EXPECT_EQ(0, writeResult);

    // Read back using auto-detect
    auto readNode = Common::getTopNodeFromFile(tempFile, "TestData");
    ASSERT_TRUE(readNode.has_value());
    EXPECT_TRUE(std::holds_alternative<JSONNodeAdapter>(*readNode));

    UnifiedTestData loaded;
    std::visit([&loaded](auto & adapter) { adapter >> loaded; }, *readNode);

    EXPECT_EQ("FileJSON", loaded.name);
    EXPECT_EQ(789, loaded.value);

    std::remove(tempFile.c_str());
}
