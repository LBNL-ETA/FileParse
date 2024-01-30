#include <gtest/gtest.h>

#include "FP_Map.hxx"

#include "test/helper/Utility.hxx"

#include "test/helper/structures/StructureMap.hxx"
#include "test/helper/MockNodeAdapter.hxx"

class EnumMapSerializerTest : public testing::Test
{};

TEST_F(EnumMapSerializerTest, DeserializingEnumAsKey_String)
{
    auto mockData = []() {
        Helper::MockNode node{"MapEnumElement"};

        addChildNode(node, "Friday", "Happy");
        addChildNode(node, "Saturday", "Relax");
        addChildNode(node, "Monday", "Back to Work");

        return node;
    };
    auto elementNode(mockData());
    const Helper::MockNodeAdapter adapter{&elementNode};

    using Helper::Day;

    std::map<Day, std::string> elements;
    FileParse::deserializeEnumMap<Helper::MockNodeAdapter, Helper::Day>(
      adapter, elements, Helper::toDay);

    const std::map<Day, std::string> correct{
      {Day::Friday, "Happy"}, {Day::Saturday, "Relax"}, {Day::Monday, "Back to Work"}};

    Helper::checkMapEquality(correct, elements);
}

TEST_F(EnumMapSerializerTest, SerializingEnumAsKey_String)
{
    using Helper::Day;
    std::map<Helper::Day, std::string> days{{Day::Monday, "Value1"},
                                            {Day::Tuesday, "Value2"},
                                            {Day::Wednesday, "Value3"},
                                            {Day::Thursday, "Value4"},
                                            {Day::Friday, "Value5"}};

    Helper::MockNode elementNode("MapElement");
    Helper::MockNodeAdapter adapter{&elementNode};

    FileParse::serializeEnumMap<Helper::MockNodeAdapter, Helper::Day>(
      adapter, days, Helper::toDayString);

    // Note that map will reorder elements according to key values
    auto correctNodes = []() {
        Helper::MockNode node{"MapElement"};

        addChildNode(node, "Friday", "Value5");
        addChildNode(node, "Monday", "Value1");
        addChildNode(node, "Thursday", "Value4");
        addChildNode(node, "Tuesday", "Value2");
        addChildNode(node, "Wednesday", "Value3");

        return node;
    };

    EXPECT_TRUE(Helper::compareNodes(adapter.getNode(), correctNodes()));
}
//
// TEST_F(EnumMapSerializerTest, ReadingEnumAsKey_Double)
//{
//    const std::string fileContent{Helper::testMapElementDayDoubleDatabase()};
//    const std::string fileName{"TestRead.xml"};
//
//    File::createFileFromString(fileName, fileContent);
//
//    const auto mapEl{Helper::loadMapElementEnumDouble(fileName)};
//
//    using Helper::Day;
//
//    const std::map<Day, double> correct{
//      {Day::Monday, 47.8621}, {Day::Thursday, 83.2934}, {Day::Saturday, 12.7845}};
//
//    Helper::checkMapEquality(correct, mapEl.days);
//
//    std::remove(fileName.c_str());
//}
//
// TEST_F(EnumMapSerializerTest, WritingEnumAsKey_Double)
//{
//    using Helper::Day;
//    Helper::MapElementEnumDouble mapEl;
//    mapEl.days = {{Day::Monday, 21.5394},
//                  {Day::Tuesday, 76.2843},
//                  {Day::Wednesday, 43.9172},
//                  {Day::Thursday, 95.0328},
//                  {Day::Friday, 58.4627}};
//
//    const std::string fileName{"TestWrite.xml"};
//
//    std::remove(fileName.c_str());
//
//    const auto result{Helper::saveMapElementEnumDouble(mapEl, fileName)};
//    EXPECT_EQ(result, 0);
//
//    const auto loadedMap{Helper::loadMapElementEnumDouble(fileName)};
//
//    Helper::checkMapEquality(mapEl.days, loadedMap.days);
//
//    std::remove(fileName.c_str());
//}