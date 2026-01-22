# Optional and Variant Types

FileParse provides support for `std::optional` and `std::variant` types, enabling flexible data structures.

## Including the Required Headers

```cpp
#include <fileParse/Optional.hxx>
#include <fileParse/Variant.hxx>
#include <fileParse/Common.hxx>
#include <fileParse/FileDataHandler.hxx>
```

## Optional Values

Optional values are only serialized when they contain a value. When deserializing, missing elements leave the optional empty.

### Structure

```cpp
struct UserProfile {
    std::string username;
    std::optional<std::string> email;
    std::optional<int> age;
    std::optional<std::vector<std::string>> tags;
};
```

### Serialization

```cpp
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const UserProfile& u) {
    node << FileParse::Child{"Username", u.username};
    node << FileParse::Child{"Email", u.email};
    node << FileParse::Child{"Age", u.age};
    node << FileParse::Child{{"Tags", "Tag"}, u.tags};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, UserProfile& u) {
    node >> FileParse::Child{"Username", u.username};
    node >> FileParse::Child{"Email", u.email};
    node >> FileParse::Child{"Age", u.age};
    node >> FileParse::Child{{"Tags", "Tag"}, u.tags};
    return node;
}
```

### Usage

```cpp
// With all optional values set
UserProfile full{"john_doe", "john@example.com", 30, {{"admin", "user"}}};
Common::saveToXMLFile(full, "full_profile.xml", "UserProfile");

// With some optional values empty
UserProfile partial{"jane_doe", std::nullopt, 25, std::nullopt};
Common::saveToXMLFile(partial, "partial_profile.xml", "UserProfile");
```

### XML Output (Full)

```xml
<UserProfile>
    <Username>john_doe</Username>
    <Email>john@example.com</Email>
    <Age>30</Age>
    <Tags>
        <Tag>admin</Tag>
        <Tag>user</Tag>
    </Tags>
</UserProfile>
```

### XML Output (Partial)

```xml
<UserProfile>
    <Username>jane_doe</Username>
    <Age>25</Age>
</UserProfile>
```

Note: Empty optional values are simply omitted from the output.

## Variant Types

Variants allow a field to hold one of several types. Each type in the variant is associated with a unique node name.

### Structure

```cpp
struct Temperature {
    double celsius;
};

struct Humidity {
    double percentage;
};

struct SensorReading {
    std::string sensorId;
    std::variant<Temperature, Humidity> value;
};
```

### Serialization for Variant Members

First, define serializers for each variant type:

```cpp
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const Temperature& t) {
    node << FileParse::Child{"Celsius", t.celsius};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, Temperature& t) {
    node >> FileParse::Child{"Celsius", t.celsius};
    return node;
}

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const Humidity& h) {
    node << FileParse::Child{"Percentage", h.percentage};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, Humidity& h) {
    node >> FileParse::Child{"Percentage", h.percentage};
    return node;
}
```

### Serialization for the Parent Structure

```cpp
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const SensorReading& s) {
    node << FileParse::Child{"SensorId", s.sensorId};
    // Node names for each variant type: Temperature, Humidity
    FileParse::serializeVariant(node, {"Temperature", "Humidity"}, s.value);
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, SensorReading& s) {
    node >> FileParse::Child{"SensorId", s.sensorId};
    FileParse::deserializeVariant(node, {"Temperature", "Humidity"}, s.value);
    return node;
}
```

### Usage

```cpp
SensorReading tempReading{"sensor-001", Temperature{23.5}};
SensorReading humidReading{"sensor-002", Humidity{65.0}};

Common::saveToXMLFile(tempReading, "temp.xml", "SensorReading");
Common::saveToXMLFile(humidReading, "humid.xml", "SensorReading");
```

### XML Output (Temperature)

```xml
<SensorReading>
    <SensorId>sensor-001</SensorId>
    <Temperature>
        <Celsius>23.5</Celsius>
    </Temperature>
</SensorReading>
```

### XML Output (Humidity)

```xml
<SensorReading>
    <SensorId>sensor-002</SensorId>
    <Humidity>
        <Percentage>65</Percentage>
    </Humidity>
</SensorReading>
```

## Optional Variants

You can combine optional and variant:

```cpp
struct FlexibleData {
    std::optional<std::variant<int, std::string>> flexValue;
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const FlexibleData& f) {
    FileParse::serializeOptionalVariant(node, {"IntValue", "StringValue"}, f.flexValue);
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, FlexibleData& f) {
    FileParse::deserializeOptionalVariant(node, {"IntValue", "StringValue"}, f.flexValue);
    return node;
}
```

## Notes

- Optional values are omitted entirely when empty (not serialized as null)
- Variant node names must match the order of types in the variant declaration
- When deserializing a variant, the library checks for each possible node name in order
- Only one variant type should be present in the serialized data
