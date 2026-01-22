# Containers

FileParse supports standard C++ containers: `std::vector`, `std::set`, `std::array`, `std::map`, and `std::unordered_map`.

## Including the Required Headers

```cpp
#include <fileParse/Vector.hxx>
#include <fileParse/Set.hxx>
#include <fileParse/Array.hxx>
#include <fileParse/Map.hxx>
#include <fileParse/Common.hxx>
#include <fileParse/FileDataHandler.hxx>
```

## Vector

### Structure

```cpp
struct VectorData {
    std::vector<double> values;
    std::vector<std::string> names;
};
```

### Serialization

```cpp
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const VectorData& v) {
    // The path {"Values", "Value"} creates: <Values><Value>...</Value><Value>...</Value></Values>
    node << FileParse::Child{{"Values", "Value"}, v.values};
    node << FileParse::Child{{"Names", "Name"}, v.names};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, VectorData& v) {
    node >> FileParse::Child{{"Values", "Value"}, v.values};
    node >> FileParse::Child{{"Names", "Name"}, v.names};
    return node;
}
```

### XML Output

```xml
<VectorData>
    <Values>
        <Value>1.5</Value>
        <Value>2.7</Value>
        <Value>3.9</Value>
    </Values>
    <Names>
        <Name>Alice</Name>
        <Name>Bob</Name>
    </Names>
</VectorData>
```

### JSON Output

```json
{
    "VectorData": {
        "Values": {
            "Value": ["1.5", "2.7", "3.9"]
        },
        "Names": {
            "Name": ["Alice", "Bob"]
        }
    }
}
```

## Set

Sets work identically to vectors:

```cpp
struct SetData {
    std::set<int> uniqueIds;
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const SetData& s) {
    node << FileParse::Child{{"UniqueIds", "Id"}, s.uniqueIds};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, SetData& s) {
    node >> FileParse::Child{{"UniqueIds", "Id"}, s.uniqueIds};
    return node;
}
```

## Array

Fixed-size arrays with `std::array`:

```cpp
struct ArrayData {
    std::array<double, 3> coordinates;  // Fixed size of 3
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const ArrayData& a) {
    node << FileParse::Child{{"Coordinates", "Coord"}, a.coordinates};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, ArrayData& a) {
    node >> FileParse::Child{{"Coordinates", "Coord"}, a.coordinates};
    return node;
}
```

## Map with String Keys

Maps with string keys serialize naturally:

```cpp
struct MapData {
    std::map<std::string, double> properties;
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const MapData& m) {
    node << FileParse::Child{"Properties", m.properties};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, MapData& m) {
    node >> FileParse::Child{"Properties", m.properties};
    return node;
}
```

### XML Output

```xml
<MapData>
    <Properties>
        <Height>1.75</Height>
        <Weight>70.5</Weight>
    </Properties>
</MapData>
```

### JSON Output

```json
{
    "MapData": {
        "Properties": {
            "Height": "1.75",
            "Weight": "70.5"
        }
    }
}
```

## Map with Structured Keys

For maps with complex key types, use `serializeMapAsChilds` and `deserializeMapAsChilds`:

```cpp
struct ComplexMapData {
    std::map<std::string, double> items;
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const ComplexMapData& m) {
    FileParse::MapStructure mapStruct{"Item", "Key", "Value"};
    FileParse::serializeMapAsChilds(node, mapStruct, m.items);
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, ComplexMapData& m) {
    FileParse::MapStructure mapStruct{"Item", "Key", "Value"};
    FileParse::deserializeMapAsChilds(node, mapStruct, m.items);
    return node;
}
```

### XML Output

```xml
<ComplexMapData>
    <Item>
        <Key>temperature</Key>
        <Value>23.5</Value>
    </Item>
    <Item>
        <Key>humidity</Key>
        <Value>65.0</Value>
    </Item>
</ComplexMapData>
```

## Notes

- Vector/Set/Array elements are created as repeated child nodes
- The node path `{"Parent", "Child"}` creates nested structure
- Empty containers result in no elements being written
- Maps with string keys use the key as the XML tag name
