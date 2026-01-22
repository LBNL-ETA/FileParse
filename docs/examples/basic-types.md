# Basic Types

FileParse provides built-in support for serializing primitive types: `std::string`, `int`, `double`, `size_t`, and `bool`.

## Including the Required Headers

```cpp
#include <fileParse/Base.hxx>
#include <fileParse/Common.hxx>
#include <fileParse/FileDataHandler.hxx>
```

## Defining a Structure with Basic Types

```cpp
struct Settings {
    std::string name;
    int count;
    double value;
    bool enabled;
};
```

## Serialization Operators

```cpp
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const Settings& s) {
    node << FileParse::Child{"Name", s.name};
    node << FileParse::Child{"Count", s.count};
    node << FileParse::Child{"Value", s.value};
    node << FileParse::Child{"Enabled", s.enabled};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, Settings& s) {
    node >> FileParse::Child{"Name", s.name};
    node >> FileParse::Child{"Count", s.count};
    node >> FileParse::Child{"Value", s.value};
    node >> FileParse::Child{"Enabled", s.enabled};
    return node;
}
```

## Usage

```cpp
Settings settings{"MyApp", 42, 3.14159, true};

// Save to XML
Common::saveToXMLFile(settings, "settings.xml", "Settings");

// Save to JSON
Common::saveToJSONFile(settings, "settings.json", "Settings");

// Load from file
auto loaded = Common::loadFromXMLFile<Settings>("settings.xml", "Settings");
if (loaded.has_value()) {
    std::cout << "Name: " << loaded->name << std::endl;
}
```

## Output Examples

### XML Output

```xml
<Settings>
    <Name>MyApp</Name>
    <Count>42</Count>
    <Value>3.14159</Value>
    <Enabled>true</Enabled>
</Settings>
```

### JSON Output

```json
{
    "Settings": {
        "Name": "MyApp",
        "Count": "42",
        "Value": "3.14159",
        "Enabled": "true"
    }
}
```

## Double Precision Configuration

You can configure how double values are formatted:

```cpp
// Set precision to 10 digits, use scientific notation for very small/large numbers
FileParse::setSerializerConfiguration(10, 0.0001, 1000000);

// Reset to defaults
FileParse::resetSerializerConfigurationToDefaults();
```

## Notes

- Boolean values are serialized as `"true"` or `"false"` strings
- All numeric types are converted to strings in the output
- The `Child` wrapper specifies the XML/JSON node name for each field
