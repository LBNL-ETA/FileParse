/// RenamedChild: a renamed tag reads under every name it has had and writes under the current one.
/// Every case that can runs through real XML and JSON adapters.
#include <map>
#include <optional>
#include <set>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#include <gtest/gtest.h>

#include <fileParse/FileDataHandler.hxx>
#include <fileParse/Map.hxx>
#include <fileParse/Optional.hxx>
#include <fileParse/RenamedChild.hxx>
#include <fileParse/Set.hxx>
#include <fileParse/Variant.hxx>
#include <fileParse/Vector.hxx>

#include "test/helper/MockNodeAdapter.hxx"

namespace
{
    using FileParse::Child;
    using FileParse::FileFormat;
    using FileParse::RenamedChild;

    constexpr auto topName{"Top"};
    constexpr auto currentName{"ModelInfo"};
    constexpr auto lastName{"ModelDetails"};
    constexpr auto firstName{"ModelExposure"};

    struct Wall
    {
        double width{0.0};
        std::string name{};

        [[nodiscard]] bool operator==(const Wall & other) const = default;
    };

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, Wall & wall)
    {
        node >> Child{"Width", wall.width};
        node >> Child{"Name", wall.name};
        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const Wall & wall)
    {
        node << Child{"Width", wall.width};
        node << Child{"Name", wall.name};
        return node;
    }

    struct Shape
    {
        std::variant<double, std::string> size{0.0};

        [[nodiscard]] bool operator==(const Shape & other) const = default;
    };

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, Shape & shape)
    {
        FileParse::deserializeVariant(node, {"Number", "Text"}, shape.size);
        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const Shape & shape)
    {
        FileParse::serializeVariant(node, {"Number", "Text"}, shape.size);
        return node;
    }

    //! A record holding a renamed child, as a real serializer would.
    struct Project
    {
        Wall wall{};
        double height{0.0};

        [[nodiscard]] bool operator==(const Project & other) const = default;
    };

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, Project & project)
    {
        node >> RenamedChild{currentName, {lastName, firstName}, project.wall};
        node >> Child{"Height", project.height};
        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const Project & project)
    {
        node << RenamedChild{currentName, {lastName, firstName}, project.wall};
        node << Child{"Height", project.height};
        return node;
    }

    //! The text of a file whose top node `write` filled in.
    template<typename Write>
    std::string contentOf(const FileFormat format, Write write)
    {
        auto top{Common::createTopNode(topName, format)};
        std::visit([&write](auto & node) { write(node); }, top);
        return std::visit([](const auto & node) { return node.getContent(); }, top);
    }

    //! Hands the top node of a file's text to `read`.
    template<typename Read>
    void readFrom(const std::string & content, Read read)
    {
        const auto top{Common::getTopNodeFromString(content, topName)};
        ASSERT_TRUE(top.has_value());
        std::visit([&read](const auto & node) { read(node); }, top.value());
    }

    //! A file holding the value under the given tag, as an older version wrote it.
    template<typename T>
    std::string fileWith(const std::string & tag, const T & value, const FileFormat format)
    {
        return contentOf(format, [&](auto & node) { node << Child{tag, value}; });
    }

    template<typename T>
    T readRenamed(const std::string & content)
    {
        T value{};
        readFrom(content, [&value](const auto & node) { node >> RenamedChild{currentName, {lastName, firstName}, value}; });
        return value;
    }

    template<typename T>
    std::string writtenRenamed(const T & value, const FileFormat format)
    {
        return contentOf(format, [&value](auto & node) { node << RenamedChild{currentName, {lastName, firstName}, value}; });
    }

    template<typename T>
    void expectEveryNameReads(const T & value, const FileFormat format)
    {
        EXPECT_TRUE(readRenamed<T>(fileWith(currentName, value, format)) == value);
        EXPECT_TRUE(readRenamed<T>(fileWith(lastName, value, format)) == value);
        EXPECT_TRUE(readRenamed<T>(fileWith(firstName, value, format)) == value);
    }

    class RenamedChildFormats : public testing::TestWithParam<FileFormat>
    {};
}   // namespace

INSTANTIATE_TEST_SUITE_P(BothFormats,
                         RenamedChildFormats,
                         testing::Values(FileFormat::XML, FileFormat::JSON),
                         [](const testing::TestParamInfo<FileFormat> & info) {
                             return info.param == FileFormat::XML ? "XML" : "JSON";
                         });

TEST_P(RenamedChildFormats, AStructureReadsUnderEveryName)
{
    expectEveryNameReads(Wall{.width = 0.2, .name = "Stucco"}, GetParam());
}

TEST_P(RenamedChildFormats, ANumberReadsUnderEveryName)
{
    const double number{21.5};
    expectEveryNameReads(number, GetParam());
}

TEST_P(RenamedChildFormats, TextReadsUnderEveryName)
{
    expectEveryNameReads(std::string{"Sill"}, GetParam());
}

TEST_P(RenamedChildFormats, AVectorReadsUnderEveryName)
{
    expectEveryNameReads(std::vector<double>{1.5, 2.5, 3.5}, GetParam());
}

TEST_P(RenamedChildFormats, AnOptionalReadsUnderEveryName)
{
    expectEveryNameReads(std::optional<double>{4.5}, GetParam());
}

TEST_P(RenamedChildFormats, AMapReadsUnderEveryName)
{
    expectEveryNameReads(std::map<std::string, std::string>{{"Width", "20"}, {"Height", "5"}}, GetParam());
}

TEST_P(RenamedChildFormats, ASetReadsUnderEveryName)
{
    expectEveryNameReads(std::set<double>{1.5, 2.5}, GetParam());
}

TEST_P(RenamedChildFormats, AVariantInsideARecordReadsUnderEveryName)
{
    expectEveryNameReads(Shape{.size = std::string{"Square"}}, GetParam());
    expectEveryNameReads(Shape{.size = 12.5}, GetParam());
}

//! Files normally hold one name; if one holds two, the current name is the one meant.
TEST_P(RenamedChildFormats, TheCurrentNameWinsOverALegacyName)
{
    const double older{1.0};
    const double newer{2.0};
    const auto content{contentOf(GetParam(), [&](auto & node) {
        node << Child{firstName, older};
        node << Child{currentName, newer};
    })};

    EXPECT_DOUBLE_EQ(readRenamed<double>(content), newer);
}

TEST_P(RenamedChildFormats, LegacyNamesAreTriedInTheirOrder)
{
    const double oldest{1.0};
    const double older{2.0};
    const auto content{contentOf(GetParam(), [&](auto & node) {
        node << Child{firstName, oldest};
        node << Child{lastName, older};
    })};

    EXPECT_DOUBLE_EQ(readRenamed<double>(content), older);
}

TEST_P(RenamedChildFormats, AnAbsentTagLeavesTheDataAsChildDoes)
{
    const double unrelated{1.0};
    double number{7.5};
    std::optional<double> optional{};
    std::vector<double> values{1.0};
    double plainNumber{7.5};
    std::optional<double> plainOptional{};
    std::vector<double> plainValues{1.0};

    readFrom(fileWith("SomethingElse", unrelated, GetParam()), [&](const auto & node) {
        node >> RenamedChild{currentName, {firstName}, number};
        node >> RenamedChild{currentName, {firstName}, optional};
        node >> RenamedChild{currentName, {firstName}, values};
        node >> Child{currentName, plainNumber};
        node >> Child{currentName, plainOptional};
        node >> Child{currentName, plainValues};
    });

    EXPECT_EQ(number, plainNumber);
    EXPECT_EQ(optional, plainOptional);
    EXPECT_EQ(values, plainValues);
}

TEST_P(RenamedChildFormats, WritingUsesOnlyTheCurrentName)
{
    const auto content{writtenRenamed(Wall{.width = 0.2, .name = "Stucco"}, GetParam())};

    EXPECT_NE(content.find(currentName), std::string::npos);
    EXPECT_EQ(content.find(lastName), std::string::npos);
    EXPECT_EQ(content.find(firstName), std::string::npos);
}

//! Handing over to Child is the point: the output is byte for byte what Child writes.
TEST_P(RenamedChildFormats, WritingMatchesAPlainChild)
{
    const Wall wall{.width = 0.2, .name = "Stucco"};
    const std::vector<double> values{1.5, 2.5};
    const std::optional<double> absent{};
    const std::map<std::string, std::string> entries{{"Width", "20"}};
    const std::set<double> numbers{1.5, 2.5};

    EXPECT_EQ(writtenRenamed(wall, GetParam()), fileWith(currentName, wall, GetParam()));
    EXPECT_EQ(writtenRenamed(values, GetParam()), fileWith(currentName, values, GetParam()));
    EXPECT_EQ(writtenRenamed(absent, GetParam()), fileWith(currentName, absent, GetParam()));
    EXPECT_EQ(writtenRenamed(entries, GetParam()), fileWith(currentName, entries, GetParam()));
    EXPECT_EQ(writtenRenamed(numbers, GetParam()), fileWith(currentName, numbers, GetParam()));
}

TEST_P(RenamedChildFormats, WithNoLegacyNamesItIsAPlainChild)
{
    const double written{1.5};
    double value{0.0};

    const auto content{contentOf(GetParam(), [&](auto & node) { node << RenamedChild{currentName, {}, written}; })};
    readFrom(content, [&value](const auto & node) { node >> RenamedChild{currentName, {}, value}; });

    EXPECT_DOUBLE_EQ(value, written);
}

//! The real case: a file from an older version opens, and saving moves it to the new name.
TEST_P(RenamedChildFormats, AnOlderFileMovesToTheCurrentNameWhenSaved)
{
    const Wall wall{.width = 0.2, .name = "Stucco"};
    const double height{3.0};
    const Project expected{.wall = wall, .height = height};
    const auto older{contentOf(GetParam(), [&](auto & node) {
        node << Child{firstName, wall};
        node << Child{"Height", height};
    })};

    Project project{};
    readFrom(older, [&project](const auto & node) { node >> project; });
    EXPECT_TRUE(project == expected);

    const auto saved{contentOf(GetParam(), [&project](auto & node) { node << project; })};
    EXPECT_NE(saved.find(currentName), std::string::npos);
    EXPECT_EQ(saved.find(firstName), std::string::npos);

    Project again{};
    readFrom(saved, [&again](const auto & node) { node >> again; });
    EXPECT_TRUE(again == expected);
}

//! The form to use: each field says what it is.
TEST_P(RenamedChildFormats, DesignatedInitializersReadAndWrite)
{
    const double written{1.5};
    double value{0.0};
    const auto older{fileWith(firstName, written, GetParam())};

    readFrom(older, [&value](const auto & node) {
        node >> RenamedChild<double>{.current = currentName, .legacy = {lastName, firstName}, .data = value};
    });
    const auto saved{contentOf(GetParam(), [&written](auto & node) {
        node << RenamedChild<const double>{.current = currentName, .legacy = {lastName, firstName}, .data = written};
    })};

    EXPECT_DOUBLE_EQ(value, written);
    EXPECT_EQ(saved, fileWith(currentName, written, GetParam()));
}

TEST(RenamedChild, TheDataTypeKeepsItsConstness)
{
    Wall wall{};
    const Wall fixed{};

    RenamedChild reading{"Current", {"Older"}, wall};
    RenamedChild writing{"Current", {"Older"}, fixed};

    static_assert(std::is_same_v<decltype(reading), RenamedChild<Wall>>);
    static_assert(std::is_same_v<decltype(writing), RenamedChild<const Wall>>);
}

TEST(RenamedChild, TheNameInFileFollowsWhatTheFileCarries)
{
    Helper::MockNode top{"Top"};
    top.addChild("Older").text = "1";
    const Helper::MockNodeAdapter adapter{&top};
    double value{0.0};

    EXPECT_EQ(FileParse::nameInFile(adapter, RenamedChild{"Current", {"Oldest", "Older"}, value}), "Older");
    EXPECT_EQ(FileParse::nameInFile(adapter, RenamedChild{"Older", {"Current"}, value}), "Older");
    EXPECT_EQ(FileParse::nameInFile(adapter, RenamedChild{"Current", {"Oldest"}, value}), "Current");
}
