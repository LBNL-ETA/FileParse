/// JSON value types and lists: numbers and booleans are written as JSON values, a list is
/// always written as a JSON array, and XML output keeps its text form.
#include <gtest/gtest.h>

#include <limits>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include <fileParse/Common.hxx>
#include <fileParse/FileDataHandler.hxx>
#include <fileParse/Vector.hxx>

namespace
{
    struct Item
    {
        double value{0.0};
    };

    struct Record
    {
        std::string name;
        double number{0.0};
        int count{0};
        size_t size{0u};
        bool flag{false};
        std::vector<double> numbers;
        std::vector<Item> items;
    };

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const Item & item)
    {
        node << FileParse::Child{"Value", item.value};
        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, Item & item)
    {
        node >> FileParse::Child{"Value", item.value};
        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const Record & record)
    {
        node << FileParse::Child{"Name", record.name};
        node << FileParse::Child{"Number", record.number};
        node << FileParse::Child{"Count", record.count};
        node << FileParse::Child{"Size", record.size};
        node << FileParse::Child{"Flag", record.flag};
        node << FileParse::Child{"Numbers", record.numbers};
        node << FileParse::Child{{"Items", "Item"}, record.items};
        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, Record & record)
    {
        node >> FileParse::Child{"Name", record.name};
        node >> FileParse::Child{"Number", record.number};
        node >> FileParse::Child{"Count", record.count};
        node >> FileParse::Child{"Size", record.size};
        node >> FileParse::Child{"Flag", record.flag};
        node >> FileParse::Child{"Numbers", record.numbers};
        node >> FileParse::Child{{"Items", "Item"}, record.items};
        return node;
    }

    Record sampleRecord()
    {
        return Record{.name = "102",
                      .number = 68.024248,
                      .count = -7,
                      .size = 12u,
                      .flag = true,
                      .numbers = {1.5},
                      .items = {Item{.value = 2.25}}};
    }

    nlohmann::json writtenJson(const Record & record)
    {
        return nlohmann::json::parse(Common::saveToJSONString(record, "Record")).at("Record");
    }
}   // namespace

TEST(JSONTypedValues, NumbersAreWrittenAsJsonNumbers)
{
    const auto json = writtenJson(sampleRecord());

    ASSERT_TRUE(json.at("Number").is_number_float());
    EXPECT_DOUBLE_EQ(68.024248, json.at("Number").get<double>());
    ASSERT_TRUE(json.at("Count").is_number_integer());
    EXPECT_EQ(-7, json.at("Count").get<int>());
    ASSERT_TRUE(json.at("Size").is_number_integer());
    EXPECT_EQ(12u, json.at("Size").get<size_t>());
}

TEST(JSONTypedValues, BooleanIsWrittenAsJsonBoolean)
{
    const auto json = writtenJson(sampleRecord());

    ASSERT_TRUE(json.at("Flag").is_boolean());
    EXPECT_TRUE(json.at("Flag").get<bool>());
}

TEST(JSONTypedValues, TextThatLooksLikeANumberStaysAString)
{
    const auto json = writtenJson(sampleRecord());

    ASSERT_TRUE(json.at("Name").is_string());
    EXPECT_EQ("102", json.at("Name").get<std::string>());
}

TEST(JSONTypedValues, ListWithOneItemIsWrittenAsAnArray)
{
    const auto json = writtenJson(sampleRecord());

    ASSERT_TRUE(json.at("Numbers").is_array());
    ASSERT_EQ(1u, json.at("Numbers").size());
    EXPECT_TRUE(json.at("Numbers").at(0).is_number());

    ASSERT_TRUE(json.at("Items").at("Item").is_array());
    ASSERT_EQ(1u, json.at("Items").at("Item").size());
    EXPECT_DOUBLE_EQ(2.25, json.at("Items").at("Item").at(0).at("Value").get<double>());
}

TEST(JSONTypedValues, ListWithSeveralItemsIsWrittenAsAnArray)
{
    auto record = sampleRecord();
    record.numbers = {1.5, 2.5, 3.5};
    record.items = {Item{.value = 1.0}, Item{.value = 2.0}};

    const auto json = writtenJson(record);

    EXPECT_EQ(3u, json.at("Numbers").size());
    EXPECT_EQ(2u, json.at("Items").at("Item").size());
}

TEST(JSONTypedValues, RoundTripKeepsEveryValue)
{
    auto record = sampleRecord();
    record.number = 1.5e-05;
    record.numbers = {0.25, 101325.0, 2.5e+08};
    record.items = {Item{.value = 1.0}, Item{.value = -3.75}};

    const auto loaded =
      Common::loadFromJSONString<Record>(Common::saveToJSONString(record, "Record"), "Record");

    ASSERT_TRUE(loaded.has_value());
    EXPECT_EQ(record.name, loaded->name);
    EXPECT_DOUBLE_EQ(record.number, loaded->number);
    EXPECT_EQ(record.count, loaded->count);
    EXPECT_EQ(record.size, loaded->size);
    EXPECT_EQ(record.flag, loaded->flag);
    ASSERT_EQ(record.numbers.size(), loaded->numbers.size());
    for(size_t index = 0u; index < record.numbers.size(); ++index)
    {
        EXPECT_DOUBLE_EQ(record.numbers[index], loaded->numbers[index]);
    }
    ASSERT_EQ(2u, loaded->items.size());
    EXPECT_DOUBLE_EQ(-3.75, loaded->items[1].value);
}

TEST(JSONTypedValues, SingleItemListRoundTrips)
{
    const auto record = sampleRecord();

    const auto loaded =
      Common::loadFromJSONString<Record>(Common::saveToJSONString(record, "Record"), "Record");

    ASSERT_TRUE(loaded.has_value());
    ASSERT_EQ(1u, loaded->numbers.size());
    EXPECT_DOUBLE_EQ(1.5, loaded->numbers[0]);
    ASSERT_EQ(1u, loaded->items.size());
    EXPECT_DOUBLE_EQ(2.25, loaded->items[0].value);
}

TEST(JSONTypedValues, InfinityIsWrittenAsTextAndReadsBack)
{
    auto record = sampleRecord();
    record.number = std::numeric_limits<double>::infinity();

    const auto text = Common::saveToJSONString(record, "Record");
    const auto json = nlohmann::json::parse(text).at("Record");
    const auto loaded = Common::loadFromJSONString<Record>(text, "Record");

    EXPECT_TRUE(json.at("Number").is_string());
    ASSERT_TRUE(loaded.has_value());
    EXPECT_EQ(std::numeric_limits<double>::infinity(), loaded->number);
}

// Files written before numbers, booleans and lists had their JSON form keep loading.
TEST(JSONTypedValues, EarlierTextFormStillReads)
{
    const std::string earlier = R"({"Record": {
        "Name": "102",
        "Number": "68.024248",
        "Count": "-7",
        "Size": "12",
        "Flag": "true",
        "Numbers": "1.5",
        "Items": {"Item": {"Value": "2.25"}}
    }})";

    const auto loaded = Common::loadFromJSONString<Record>(earlier, "Record");

    ASSERT_TRUE(loaded.has_value());
    EXPECT_DOUBLE_EQ(68.024248, loaded->number);
    EXPECT_EQ(-7, loaded->count);
    EXPECT_EQ(12u, loaded->size);
    EXPECT_TRUE(loaded->flag);
    ASSERT_EQ(1u, loaded->numbers.size());
    EXPECT_DOUBLE_EQ(1.5, loaded->numbers[0]);
    ASSERT_EQ(1u, loaded->items.size());
    EXPECT_DOUBLE_EQ(2.25, loaded->items[0].value);
}

TEST(JSONTypedValues, SmallNumberInAFileReadsWithAllItsDigits)
{
    const std::string json = R"({"Record": {"Number": 1.23456789e-10}})";

    const auto loaded = Common::loadFromJSONString<Record>(json, "Record");

    ASSERT_TRUE(loaded.has_value());
    EXPECT_DOUBLE_EQ(1.23456789e-10, loaded->number);
}

TEST(JSONTypedValues, XmlKeepsItsTextForm)
{
    const auto xml = Common::saveToXMLString(sampleRecord(), "Record");

    EXPECT_NE(std::string::npos, xml.find("<Name>102</Name>"));
    EXPECT_NE(std::string::npos, xml.find("<Number>68.024248</Number>"));
    EXPECT_NE(std::string::npos, xml.find("<Count>-7</Count>"));
    EXPECT_NE(std::string::npos, xml.find("<Size>12</Size>"));
    EXPECT_NE(std::string::npos, xml.find("<Flag>true</Flag>"));
    EXPECT_NE(std::string::npos, xml.find("<Numbers>1.5</Numbers>"));
    EXPECT_NE(std::string::npos, xml.find("<Value>2.25</Value>"));
}
