# JSON Support Implementation Notes

## Overview

Added JSON serialization/deserialization support to FileParse using the nlohmann/json library (v3.11.3), following the same patterns as XMLNodeAdapter.

## What Was Implemented

### New Files

1. **`include/fileParse/JSONNodeAdapter.hxx`** - Header file
   - `JSONNodeAdapter` class implementing `INodeAdapter<JSONNodeAdapter>` interface
   - Factory functions for creating and parsing JSON

2. **`include/fileParse/JSONNodeAdapter.cxx`** - Implementation file
   - Full implementation with pimpl pattern for ABI stability
   - Automatic array handling for duplicate child names

3. **`test/units/JSONNodeAdapter.unit.cxx`** - Unit tests
   - 31 comprehensive tests covering all interface methods

### Modified Files

1. **`CMakeLists.txt`** - Added nlohmann/json dependency via FetchContent
2. **`include/fileParse/CMakeLists.txt`** - Added new source files and linked nlohmann_json
3. **`test/CMakeLists.txt`** - Added unit test file

## Design Decisions

### JSON Structure Mapping

| XML Concept | JSON Mapping |
|-------------|--------------|
| Tag name | Object key (stored in `key_` member) |
| Text content | JSON value (string/number/bool) |
| Child elements | Object properties |
| Multiple same-name children | JSON array (automatic conversion) |
| Attributes | Regular object properties (no prefix) |
| Root element | Wrapper object: `{"RootName": {...}}` |

### Key Implementation Details

- **Pimpl Pattern**: Used `std::shared_ptr<Impl>` for implementation hiding
- **Root Ownership**: Root nodes own the JSON data via `std::shared_ptr<nlohmann::json>`
- **Array Handling**: When `addChild()` is called with an existing key, the value is automatically converted to an array
- **Text Values**: Stored as JSON strings; serializers handle type conversion

### Factory Functions

```cpp
// Create a new JSON document
JSONNodeAdapter createJSONTopNode(std::string_view topNodeName);

// Parse from file
std::optional<JSONNodeAdapter> getJSONTopNodeFromFile(std::string_view fileName,
                                                       std::string_view topNodeName);

// Parse from string
std::optional<JSONNodeAdapter> getJSONTopNodeFromString(std::string_view json,
                                                         std::string_view topNodeName);
```

## Example Usage

### Serialization
```cpp
auto node = createJSONTopNode("Person");
auto nameNode = node.addChild("Name");
nameNode.addText("John");
auto ageNode = node.addChild("Age");
ageNode.addText("30");
node.writeToFile("person.json");
```

Produces:
```json
{
    "Person": {
        "Name": "John",
        "Age": "30"
    }
}
```

### Deserialization
```cpp
auto node = getJSONTopNodeFromFile("person.json", "Person");
if (node) {
    auto name = node->getFirstChildByName("Name");
    if (name) {
        std::string nameStr = name->getText();
    }
}
```

### Arrays (Multiple Children with Same Name)
```cpp
auto node = createJSONTopNode("Data");
auto v1 = node.addChild("Value");
v1.addText("1");
auto v2 = node.addChild("Value");  // Automatically creates array
v2.addText("2");
auto v3 = node.addChild("Value");
v3.addText("3");
```

Produces:
```json
{
    "Data": {
        "Value": ["1", "2", "3"]
    }
}
```

## Test Results

All 254 tests pass:
- 31 new JSONNodeAdapter tests
- 223 existing tests (unchanged behavior)

## TODO: Next Steps

The following work is planned to complete JSON support parity with XML:

### 1. Add JSON Integration Tests (Similar to XML Tests)

Create JSON versions of existing XML integration tests:
- `helper/files/AttributesJSON.hxx/.cxx`
- `helper/files/BaseElementJSON.hxx/.cxx`
- `helper/files/SetElementJSON.hxx/.cxx`
- `helper/files/EnumElementJSON.hxx/.cxx`
- `helper/files/MapElementJSON.hxx/.cxx`
- `helper/files/VariantElementJSON.hxx/.cxx`
- `helper/files/VectorElementJSON.hxx/.cxx`

### 2. Add JSON Serializer Tests

Create JSON versions of existing XML serializer tests:
- `units/BaseSerializersJSON.unit.cxx`
- `units/VectorSerializersJSON.unit.cxx`
- `units/SetSerializersJSON.unit.cxx`
- `units/MapSerializersJSON.unit.cxx` (including EnumMap, StringMap, DoubleMap)
- `units/EnumSerializersJSON.unit.cxx`
- `units/VariantSerializersJSON.unit.cxx`
- `units/AttributesSerializersJSON.unit.cxx`

### 3. Add FileDataHandler JSON Support

Add JSON equivalents of `loadFromXMLFile` and `saveToXMLFile`:
- `loadFromJSONFile<T>()`
- `saveToJSONFile<T>()`

### 4. Test Data Files

Create JSON test data files in `test/data/` directory corresponding to existing XML test files.

## Dependencies

- **nlohmann/json v3.11.3** - Fetched via CMake FetchContent
  - Repository: https://github.com/nlohmann/json.git
