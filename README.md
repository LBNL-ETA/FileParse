# FileParse

A modern C++20 header-only library for serializing and deserializing C++ objects to/from XML and JSON formats using standard library types.

## Features

- **Dual Format Support**: Seamlessly serialize to both XML and JSON using the same code
- **Automatic Format Detection**: Unified load/save functions detect format from file extension or content
- **STL Container Support**: Built-in support for `std::vector`, `std::set`, `std::array`, `std::map`, `std::unordered_map`
- **Modern C++ Types**: Full support for `std::optional` and `std::variant`
- **Enum Serialization**: Convert enums to/from strings with custom converters
- **XML Attributes**: Support for XML attributes (mapped to `@`-prefixed properties in JSON)
- **Header-Only**: Easy integration - just include the headers
- **Extensible**: Define serializers for your own custom types

## Quick Start

### Installation

FileParse is a header-only library. Simply include the headers in your project:

```cpp
#include <fileParse/FileDataHandler.hxx>
#include <fileParse/Vector.hxx>
#include <fileParse/Optional.hxx>
// ... include other headers as needed
```

### CMake Integration

```cmake
# Using FetchContent
include(FetchContent)
FetchContent_Declare(
    FileParse
    GIT_REPOSITORY https://github.com/LBNL-ETA/FileParse.git
    GIT_TAG main
)
FetchContent_MakeAvailable(FileParse)

target_link_libraries(your_target PRIVATE FileParse)
```

### Basic Example

```cpp
#include <fileParse/FileDataHandler.hxx>
#include <fileParse/Common.hxx>
#include <fileParse/Vector.hxx>

// Define your data structure
struct Person {
    std::string name;
    int age;
    std::vector<std::string> hobbies;
};

// Define serialization operators
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const Person& p) {
    node << FileParse::Child{"Name", p.name};
    node << FileParse::Child{"Age", p.age};
    node << FileParse::Child{{"Hobbies", "Hobby"}, p.hobbies};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, Person& p) {
    node >> FileParse::Child{"Name", p.name};
    node >> FileParse::Child{"Age", p.age};
    node >> FileParse::Child{{"Hobbies", "Hobby"}, p.hobbies};
    return node;
}

// Usage
int main() {
    Person person{"John", 30, {"reading", "coding"}};

    // Save to XML
    Common::saveToXMLFile(person, "person.xml", "Person");

    // Save to JSON
    Common::saveToJSONFile(person, "person.json", "Person");

    // Load from XML
    auto loadedXML = Common::loadFromXMLFile<Person>("person.xml", "Person");

    // Load from JSON
    auto loadedJSON = Common::loadFromJSONFile<Person>("person.json", "Person");

    // Or use unified functions with automatic format detection
    Common::saveToFile(person, "person.xml", "Person");   // Auto-detects XML from extension
    Common::saveToFile(person, "person.json", "Person");  // Auto-detects JSON from extension

    auto loaded = Common::loadFromFile<Person>("person.xml", "Person");  // Auto-detects format

    return 0;
}
```

**Generated XML:**
```xml
<Person>
    <Name>John</Name>
    <Age>30</Age>
    <Hobbies>
        <Hobby>reading</Hobby>
        <Hobby>coding</Hobby>
    </Hobbies>
</Person>
```

**Generated JSON:**
```json
{
    "Person": {
        "Name": "John",
        "Age": "30",
        "Hobbies": {
            "Hobby": ["reading", "coding"]
        }
    }
}
```

## Documentation

### Core Concepts

- **NodeAdapter**: Abstraction over XML/JSON nodes (`XMLNodeAdapter`, `JSONNodeAdapter`)
- **Child**: Wrapper that pairs data with a node path for navigation
- **operator<<**: Serialization (C++ object → XML/JSON)
- **operator>>**: Deserialization (XML/JSON → C++ object)

### Unified File Operations

FileParse provides unified functions that automatically detect the file format, allowing you to write format-agnostic code:

```cpp
#include <fileParse/FileDataHandler.hxx>

// Save - format determined by file extension (.xml or .json)
Common::saveToFile(myObject, "data.xml", "Root");   // Saves as XML
Common::saveToFile(myObject, "data.json", "Root");  // Saves as JSON

// Load - format detected from extension first, then file content
auto obj1 = Common::loadFromFile<MyType>("data.xml", "Root");   // Loads XML
auto obj2 = Common::loadFromFile<MyType>("data.json", "Root");  // Loads JSON
```

**Format Detection Behavior:**

| Function | Detection Method |
|----------|-----------------|
| `saveToFile` | File extension only (`.xml` or `.json`) |
| `loadFromFile` | Extension first, then content inspection as fallback |

For loading, if the file extension is not recognized, the library inspects the file content:
- First non-whitespace character `{` → JSON
- First non-whitespace character `<` → XML

**When to Use Format-Specific Functions:**

Use `saveToXMLFile`/`saveToJSONFile` and `loadFromXMLFile`/`loadFromJSONFile` when:
- Working with non-standard file extensions (e.g., `.config`, `.data`)
- You need explicit control over the format regardless of extension
- Performance is critical (skips format detection)

```cpp
// Non-standard extension - must specify format explicitly
Common::saveToXMLFile(config, "settings.config", "Settings");
auto config = Common::loadFromXMLFile<Config>("settings.config", "Settings");
```

**Unified String Operations:**

For string-based serialization with explicit format control:

```cpp
#include <fileParse/FileDataHandler.hxx>
#include <fileParse/FileFormat.hxx>

// Serialize to string with explicit format
std::string xml = Common::saveToString(myObject, "Root", FileParse::FileFormat::XML);
std::string json = Common::saveToString(myObject, "Root", FileParse::FileFormat::JSON);

// Deserialize from string with explicit format
auto obj1 = Common::loadFromString<MyType>(xmlData, "Root", FileParse::FileFormat::XML);
auto obj2 = Common::loadFromString<MyType>(jsonData, "Root", FileParse::FileFormat::JSON);
```

### Detailed Examples

| Topic | Description |
|-------|-------------|
| [Basic Types](docs/examples/basic-types.md) | Serializing strings, integers, doubles, and booleans |
| [Containers](docs/examples/containers.md) | Working with vector, set, array, and map |
| [Optional & Variant](docs/examples/optional-variant.md) | Handling optional values and variant types |
| [Enums](docs/examples/enums.md) | Enum serialization with string conversion |
| [Attributes](docs/examples/attributes.md) | XML attributes and their JSON equivalent |
| [Custom Types](docs/examples/custom-types.md) | Creating serializers for your own structures |

## Supported Types

| C++ Type | XML Representation | JSON Representation |
|----------|-------------------|---------------------|
| `std::string` | Element text | String value |
| `int`, `double`, `bool` | Element text | String value |
| `std::vector<T>` | Repeated child elements | Array |
| `std::set<T>` | Repeated child elements | Array |
| `std::array<T, N>` | Repeated child elements | Array |
| `std::map<K, V>` | Child elements with key as tag | Object properties |
| `std::optional<T>` | Present/absent element | Present/absent property |
| `std::variant<Ts...>` | One of several element types | One of several properties |
| Enums | String representation | String representation |
| XML Attributes | `attribute="value"` | `"@attribute": "value"` |

## Building Tests

```bash
cmake -S . -B build -DBUILD_FILEPARSELIB_TESTS=ON
cmake --build build
ctest --test-dir build
```

## Requirements

- C++20 compatible compiler
- CMake 3.10+
- [XMLParser](https://github.com/LBNL-ETA/XMLParser) (fetched automatically)
- [nlohmann/json](https://github.com/nlohmann/json) (fetched automatically for JSON support)

## License

Berkeley Lab WINDOW Calc Engine License - See LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests.
