/// FileFormat detection and unified load/save tests
#include <gtest/gtest.h>

#include <fileParse/FileFormat.hxx>
#include <fileParse/FileDataHandler.hxx>

#include <fstream>
#include <cstdio>
#include <filesystem>

using namespace FileParse;

//////////////////////////////////////////////////////////////////////////////
// FileFormat detection from extension tests
//////////////////////////////////////////////////////////////////////////////

TEST(FileFormat, DetectJSONExtensionLowercase)
{
    EXPECT_EQ(FileFormat::JSON, detectFileFormatFromExtension("file.json"));
    EXPECT_EQ(FileFormat::JSON, detectFileFormatFromExtension("path/to/file.json"));
    EXPECT_EQ(FileFormat::JSON, detectFileFormatFromExtension("C:\\path\\file.json"));
}

TEST(FileFormat, DetectJSONExtensionUppercase)
{
    EXPECT_EQ(FileFormat::JSON, detectFileFormatFromExtension("file.JSON"));
    EXPECT_EQ(FileFormat::JSON, detectFileFormatFromExtension("file.Json"));
}

TEST(FileFormat, DetectXMLExtensionLowercase)
{
    EXPECT_EQ(FileFormat::XML, detectFileFormatFromExtension("file.xml"));
    EXPECT_EQ(FileFormat::XML, detectFileFormatFromExtension("path/to/file.xml"));
    EXPECT_EQ(FileFormat::XML, detectFileFormatFromExtension("C:\\path\\file.xml"));
}

TEST(FileFormat, DetectXMLExtensionUppercase)
{
    EXPECT_EQ(FileFormat::XML, detectFileFormatFromExtension("file.XML"));
    EXPECT_EQ(FileFormat::XML, detectFileFormatFromExtension("file.Xml"));
}

TEST(FileFormat, DetectUnknownExtension)
{
    EXPECT_EQ(FileFormat::Unknown, detectFileFormatFromExtension("file.txt"));
    EXPECT_EQ(FileFormat::Unknown, detectFileFormatFromExtension("file.data"));
    EXPECT_EQ(FileFormat::Unknown, detectFileFormatFromExtension("file"));
    EXPECT_EQ(FileFormat::Unknown, detectFileFormatFromExtension(""));
}

//////////////////////////////////////////////////////////////////////////////
// FileFormat detection from content tests
//////////////////////////////////////////////////////////////////////////////

class FileFormatContentTest : public ::testing::Test
{
protected:
    void TearDown() override
    {
        for(const auto & file : tempFiles)
        {
            std::remove(file.c_str());
        }
    }

    std::string createTempFile(const std::string & content, const std::string & name)
    {
        std::ofstream out(name);
        out << content;
        out.close();
        tempFiles.push_back(name);
        return name;
    }

    std::vector<std::string> tempFiles;
};

TEST_F(FileFormatContentTest, DetectJSONFromContent)
{
    auto file = createTempFile(R"({"key": "value"})", "temp_json_content.dat");
    EXPECT_EQ(FileFormat::JSON, detectFileFormatFromContent(file));
}

TEST_F(FileFormatContentTest, DetectJSONFromContentWithWhitespace)
{
    auto file = createTempFile("  \n\t  {\"key\": \"value\"}", "temp_json_ws.dat");
    EXPECT_EQ(FileFormat::JSON, detectFileFormatFromContent(file));
}

TEST_F(FileFormatContentTest, DetectXMLFromContent)
{
    auto file = createTempFile("<root><child/></root>", "temp_xml_content.dat");
    EXPECT_EQ(FileFormat::XML, detectFileFormatFromContent(file));
}

TEST_F(FileFormatContentTest, DetectXMLFromContentWithWhitespace)
{
    auto file = createTempFile("  \n\t  <?xml version=\"1.0\"?><root/>", "temp_xml_ws.dat");
    EXPECT_EQ(FileFormat::XML, detectFileFormatFromContent(file));
}

TEST_F(FileFormatContentTest, DetectUnknownFromContent)
{
    auto file = createTempFile("Hello World", "temp_unknown.dat");
    EXPECT_EQ(FileFormat::Unknown, detectFileFormatFromContent(file));
}

TEST_F(FileFormatContentTest, DetectUnknownFromNonExistentFile)
{
    EXPECT_EQ(FileFormat::Unknown, detectFileFormatFromContent("nonexistent_file_12345.dat"));
}

//////////////////////////////////////////////////////////////////////////////
// Combined detection (extension + content fallback) tests
//////////////////////////////////////////////////////////////////////////////

TEST_F(FileFormatContentTest, DetectFormatUsesExtensionFirst)
{
    // Even though content is JSON, extension says XML - extension wins
    auto file = createTempFile(R"({"key": "value"})", "temp_misleading.xml");
    EXPECT_EQ(FileFormat::XML, detectFileFormat(file));
}

TEST_F(FileFormatContentTest, DetectFormatFallsBackToContent)
{
    // Unknown extension, so content detection is used
    auto jsonFile = createTempFile(R"({"key": "value"})", "temp_fallback.dat");
    EXPECT_EQ(FileFormat::JSON, detectFileFormat(jsonFile));

    auto xmlFile = createTempFile("<root/>", "temp_fallback2.dat");
    EXPECT_EQ(FileFormat::XML, detectFileFormat(xmlFile));
}

//////////////////////////////////////////////////////////////////////////////
// Unified loadFromFile/saveToFile tests
//////////////////////////////////////////////////////////////////////////////

struct SimpleData
{
    std::string name;
    int value{0};
};

template<typename NodeAdapter>
NodeAdapter & operator<<(NodeAdapter & node, const SimpleData & data)
{
    auto nameNode = node.addChild("Name");
    nameNode.addText(data.name);
    auto valueNode = node.addChild("Value");
    valueNode.addText(std::to_string(data.value));
    return node;
}

template<typename NodeAdapter>
const NodeAdapter & operator>>(const NodeAdapter & node, SimpleData & data)
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

class UnifiedFileOperationsTest : public ::testing::Test
{
protected:
    void TearDown() override
    {
        for(const auto & file : tempFiles)
        {
            std::remove(file.c_str());
        }
    }

    void addTempFile(const std::string & name)
    {
        tempFiles.push_back(name);
    }

    std::vector<std::string> tempFiles;
};

TEST_F(UnifiedFileOperationsTest, SaveAndLoadJSON)
{
    const std::string fileName = "temp_unified_test.json";
    addTempFile(fileName);

    SimpleData original{"TestName", 42};
    int saveResult = Common::saveToFile(original, fileName, "Root");
    EXPECT_EQ(0, saveResult);

    auto loaded = Common::loadFromFile<SimpleData>(fileName, "Root");
    ASSERT_TRUE(loaded.has_value());
    EXPECT_EQ("TestName", loaded->name);
    EXPECT_EQ(42, loaded->value);
}

TEST_F(UnifiedFileOperationsTest, SaveAndLoadXML)
{
    const std::string fileName = "temp_unified_test.xml";
    addTempFile(fileName);

    SimpleData original{"XMLTest", 99};
    int saveResult = Common::saveToFile(original, fileName, "Root");
    EXPECT_EQ(0, saveResult);

    auto loaded = Common::loadFromFile<SimpleData>(fileName, "Root");
    ASSERT_TRUE(loaded.has_value());
    EXPECT_EQ("XMLTest", loaded->name);
    EXPECT_EQ(99, loaded->value);
}

TEST_F(UnifiedFileOperationsTest, SaveWithUnknownExtensionFails)
{
    const std::string fileName = "temp_unified_test.txt";
    addTempFile(fileName);

    SimpleData original{"Test", 1};
    int saveResult = Common::saveToFile(original, fileName, "Root");
    EXPECT_EQ(-1, saveResult);
}

TEST_F(UnifiedFileOperationsTest, LoadFromNonExistentFileWithUnknownExtension)
{
    auto loaded = Common::loadFromFile<SimpleData>("nonexistent.txt", "Root");
    EXPECT_FALSE(loaded.has_value());
}

TEST_F(UnifiedFileOperationsTest, LoadFromFileWithContentDetection)
{
    // Create a JSON file with non-standard extension
    const std::string fileName = "temp_content_detect.dat";
    addTempFile(fileName);

    // Write JSON content directly
    {
        std::ofstream out(fileName);
        out << R"({"Root": {"Name": "ContentDetect", "Value": "123"}})";
    }

    // loadFromFile should detect JSON from content
    auto loaded = Common::loadFromFile<SimpleData>(fileName, "Root");
    ASSERT_TRUE(loaded.has_value());
    EXPECT_EQ("ContentDetect", loaded->name);
    EXPECT_EQ(123, loaded->value);
}

TEST_F(UnifiedFileOperationsTest, ExplicitFunctionsStillWork)
{
    // Verify that explicit functions work with any extension
    const std::string jsonFileName = "temp_explicit.txt";
    const std::string xmlFileName = "temp_explicit.data";
    addTempFile(jsonFileName);
    addTempFile(xmlFileName);

    SimpleData original{"Explicit", 77};

    // Save JSON to .txt file using explicit function
    int jsonResult = Common::saveToJSONFile(original, jsonFileName, "Root");
    EXPECT_EQ(0, jsonResult);

    // Save XML to .data file using explicit function
    int xmlResult = Common::saveToXMLFile(original, xmlFileName, "Root");
    EXPECT_EQ(0, xmlResult);

    // Load using explicit functions
    auto jsonLoaded = Common::loadFromJSONFile<SimpleData>(jsonFileName, "Root");
    ASSERT_TRUE(jsonLoaded.has_value());
    EXPECT_EQ("Explicit", jsonLoaded->name);

    auto xmlLoaded = Common::loadFromXMLFile<SimpleData>(xmlFileName, "Root");
    ASSERT_TRUE(xmlLoaded.has_value());
    EXPECT_EQ("Explicit", xmlLoaded->name);
}
