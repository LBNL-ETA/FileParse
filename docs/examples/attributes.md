# XML Attributes

FileParse supports XML attributes for compact data representation. In JSON, attributes are stored with an `@` prefix to distinguish them from child elements.

## Including the Required Headers

```cpp
#include <fileParse/Attributes.hxx>
#include <fileParse/Common.hxx>
#include <fileParse/FileDataHandler.hxx>
```

## Basic Attributes

### Structure

```cpp
struct Element {
    std::string id;
    int version;
    double scale;
    std::string content;
};
```

### Serialization

```cpp
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const Element& e) {
    // Save as attributes
    FileParse::saveAttribute(node, "id", e.id);
    FileParse::saveAttribute(node, "version", e.version);
    FileParse::saveAttribute(node, "scale", e.scale);
    // Save as child element
    node << FileParse::Child{"Content", e.content};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, Element& e) {
    // Load attributes
    FileParse::loadAttribute(node, "id", e.id);
    FileParse::loadAttribute(node, "version", e.version);
    FileParse::loadAttribute(node, "scale", e.scale);
    // Load child element
    node >> FileParse::Child{"Content", e.content};
    return node;
}
```

### XML Output

```xml
<Element id="elem-001" version="2" scale="1.5">
    <Content>Hello World</Content>
</Element>
```

### JSON Output

```json
{
    "Element": {
        "@id": "elem-001",
        "@version": "2",
        "@scale": "1.5",
        "Content": "Hello World"
    }
}
```

Note the `@` prefix for attributes in JSON, which prevents collision with child elements that might have the same name.

## Optional Attributes

Attributes can be optional - they're only written when the value is present:

```cpp
struct ConfigurableElement {
    std::string name;
    std::optional<int> priority;
    std::optional<std::string> description;
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const ConfigurableElement& c) {
    FileParse::saveAttribute(node, "name", c.name);
    FileParse::saveAttribute(node, "priority", c.priority);
    FileParse::saveAttribute(node, "description", c.description);
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, ConfigurableElement& c) {
    FileParse::loadAttribute(node, "name", c.name);
    FileParse::loadAttribute(node, "priority", c.priority);
    FileParse::loadAttribute(node, "description", c.description);
    return node;
}
```

### XML Output (with optional values)

```xml
<ConfigurableElement name="MyElement" priority="5" description="A sample element" />
```

### XML Output (without optional values)

```xml
<ConfigurableElement name="MyElement" />
```

## Enum Attributes

Enums can be stored as attributes using converter functions:

```cpp
enum class Status { Active, Inactive, Pending };

const std::array<std::string, 3> StatusStrings = {"Active", "Inactive", "Pending"};

std::string statusToString(Status s) {
    return FileParse::enumToString(s, StatusStrings);
}

Status stringToStatus(std::string_view s) {
    return FileParse::enumFromString(s, StatusStrings, Status::Pending);
}

struct StatusElement {
    std::string name;
    Status status;
    std::optional<Status> previousStatus;
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const StatusElement& s) {
    FileParse::saveAttribute(node, "name", s.name);
    FileParse::saveAttribute(node, "status", s.status, statusToString);
    FileParse::saveAttribute(node, "previousStatus", s.previousStatus, statusToString);
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, StatusElement& s) {
    FileParse::loadAttribute(node, "name", s.name);
    FileParse::loadAttribute(node, "status", s.status, stringToStatus);
    FileParse::loadAttribute(node, "previousStatus", s.previousStatus, stringToStatus);
    return node;
}
```

### XML Output

```xml
<StatusElement name="Task1" status="Active" previousStatus="Pending" />
```

### JSON Output

```json
{
    "StatusElement": {
        "@name": "Task1",
        "@status": "Active",
        "@previousStatus": "Pending"
    }
}
```

## Mixing Attributes and Child Elements

A common pattern is using attributes for metadata and child elements for content:

```cpp
struct Document {
    // Metadata as attributes
    std::string id;
    std::string author;
    int version;

    // Content as child elements
    std::string title;
    std::string body;
    std::vector<std::string> tags;
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const Document& d) {
    // Attributes
    FileParse::saveAttribute(node, "id", d.id);
    FileParse::saveAttribute(node, "author", d.author);
    FileParse::saveAttribute(node, "version", d.version);

    // Child elements
    node << FileParse::Child{"Title", d.title};
    node << FileParse::Child{"Body", d.body};
    node << FileParse::Child{{"Tags", "Tag"}, d.tags};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, Document& d) {
    // Attributes
    FileParse::loadAttribute(node, "id", d.id);
    FileParse::loadAttribute(node, "author", d.author);
    FileParse::loadAttribute(node, "version", d.version);

    // Child elements
    node >> FileParse::Child{"Title", d.title};
    node >> FileParse::Child{"Body", d.body};
    node >> FileParse::Child{{"Tags", "Tag"}, d.tags};
    return node;
}
```

### XML Output

```xml
<Document id="doc-001" author="John" version="1">
    <Title>My Document</Title>
    <Body>This is the content.</Body>
    <Tags>
        <Tag>important</Tag>
        <Tag>draft</Tag>
    </Tags>
</Document>
```

### JSON Output

```json
{
    "Document": {
        "@id": "doc-001",
        "@author": "John",
        "@version": "1",
        "Title": "My Document",
        "Body": "This is the content.",
        "Tags": {
            "Tag": ["important", "draft"]
        }
    }
}
```

## Supported Attribute Types

| Type | Support |
|------|---------|
| `std::string` | Direct |
| `int` | Converted to string |
| `double` | Converted to string |
| `float` | Converted to string |
| `size_t` | Converted to string |
| `std::optional<T>` | Written only if has value |
| Enums | Via converter functions |

## Notes

- Attributes are ideal for metadata, IDs, and simple configuration values
- In JSON, the `@` prefix ensures attributes don't conflict with child nodes of the same name
- Missing attributes during deserialization leave variables unchanged (for optional) or at default values
- Attributes cannot contain complex nested structures - use child elements for those
