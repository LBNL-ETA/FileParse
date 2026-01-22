# Custom Types

FileParse is designed to be extensible. You can create serializers for any custom type by defining the appropriate operators.

## Including the Required Headers

```cpp
#include <fileParse/Common.hxx>
#include <fileParse/Vector.hxx>
#include <fileParse/Optional.hxx>
#include <fileParse/FileDataHandler.hxx>
```

## Basic Custom Type

### Structure Definition

```cpp
struct Point {
    double x;
    double y;
    double z;
};
```

### Serialization Operators

```cpp
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const Point& p) {
    node << FileParse::Child{"X", p.x};
    node << FileParse::Child{"Y", p.y};
    node << FileParse::Child{"Z", p.z};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, Point& p) {
    node >> FileParse::Child{"X", p.x};
    node >> FileParse::Child{"Y", p.y};
    node >> FileParse::Child{"Z", p.z};
    return node;
}
```

### XML Output

```xml
<Point>
    <X>1.5</X>
    <Y>2.5</Y>
    <Z>3.5</Z>
</Point>
```

## Nested Custom Types

Custom types can contain other custom types:

```cpp
struct Line {
    Point start;
    Point end;
    std::string label;
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const Line& l) {
    node << FileParse::Child{"Start", l.start};
    node << FileParse::Child{"End", l.end};
    node << FileParse::Child{"Label", l.label};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, Line& l) {
    node >> FileParse::Child{"Start", l.start};
    node >> FileParse::Child{"End", l.end};
    node >> FileParse::Child{"Label", l.label};
    return node;
}
```

### XML Output

```xml
<Line>
    <Start>
        <X>0</X>
        <Y>0</Y>
        <Z>0</Z>
    </Start>
    <End>
        <X>10</X>
        <Y>10</Y>
        <Z>10</Z>
    </End>
    <Label>Diagonal</Label>
</Line>
```

## Collections of Custom Types

Once you define serializers for a type, it automatically works with containers:

```cpp
struct Shape {
    std::string name;
    std::vector<Point> vertices;
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const Shape& s) {
    node << FileParse::Child{"Name", s.name};
    node << FileParse::Child{{"Vertices", "Point"}, s.vertices};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, Shape& s) {
    node >> FileParse::Child{"Name", s.name};
    node >> FileParse::Child{{"Vertices", "Point"}, s.vertices};
    return node;
}
```

### XML Output

```xml
<Shape>
    <Name>Triangle</Name>
    <Vertices>
        <Point>
            <X>0</X>
            <Y>0</Y>
            <Z>0</Z>
        </Point>
        <Point>
            <X>1</X>
            <Y>0</Y>
            <Z>0</Z>
        </Point>
        <Point>
            <X>0.5</X>
            <Y>1</Y>
            <Z>0</Z>
        </Point>
    </Vertices>
</Shape>
```

## Complex Example: Configuration File

```cpp
struct DatabaseConfig {
    std::string host;
    int port;
    std::string username;
    std::optional<std::string> password;
};

struct LoggingConfig {
    std::string level;
    std::string outputPath;
    bool enabled;
};

struct AppConfig {
    std::string appName;
    std::string version;
    DatabaseConfig database;
    LoggingConfig logging;
    std::vector<std::string> features;
};

// DatabaseConfig serializers
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const DatabaseConfig& d) {
    node << FileParse::Child{"Host", d.host};
    node << FileParse::Child{"Port", d.port};
    node << FileParse::Child{"Username", d.username};
    node << FileParse::Child{"Password", d.password};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, DatabaseConfig& d) {
    node >> FileParse::Child{"Host", d.host};
    node >> FileParse::Child{"Port", d.port};
    node >> FileParse::Child{"Username", d.username};
    node >> FileParse::Child{"Password", d.password};
    return node;
}

// LoggingConfig serializers
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const LoggingConfig& l) {
    node << FileParse::Child{"Level", l.level};
    node << FileParse::Child{"OutputPath", l.outputPath};
    node << FileParse::Child{"Enabled", l.enabled};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, LoggingConfig& l) {
    node >> FileParse::Child{"Level", l.level};
    node >> FileParse::Child{"OutputPath", l.outputPath};
    node >> FileParse::Child{"Enabled", l.enabled};
    return node;
}

// AppConfig serializers
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const AppConfig& a) {
    node << FileParse::Child{"AppName", a.appName};
    node << FileParse::Child{"Version", a.version};
    node << FileParse::Child{"Database", a.database};
    node << FileParse::Child{"Logging", a.logging};
    node << FileParse::Child{{"Features", "Feature"}, a.features};
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, AppConfig& a) {
    node >> FileParse::Child{"AppName", a.appName};
    node >> FileParse::Child{"Version", a.version};
    node >> FileParse::Child{"Database", a.database};
    node >> FileParse::Child{"Logging", a.logging};
    node >> FileParse::Child{{"Features", "Feature"}, a.features};
    return node;
}
```

### Usage

```cpp
AppConfig config{
    "MyApp",
    "1.0.0",
    {"localhost", 5432, "admin", "secret123"},
    {"DEBUG", "/var/log/myapp.log", true},
    {"feature1", "feature2", "feature3"}
};

// Save to both formats
Common::saveToXMLFile(config, "config.xml", "AppConfig");
Common::saveToJSONFile(config, "config.json", "AppConfig");

// Load from either format
auto xmlConfig = Common::loadFromXMLFile<AppConfig>("config.xml", "AppConfig");
auto jsonConfig = Common::loadFromJSONFile<AppConfig>("config.json", "AppConfig");
```

### XML Output

```xml
<AppConfig>
    <AppName>MyApp</AppName>
    <Version>1.0.0</Version>
    <Database>
        <Host>localhost</Host>
        <Port>5432</Port>
        <Username>admin</Username>
        <Password>secret123</Password>
    </Database>
    <Logging>
        <Level>DEBUG</Level>
        <OutputPath>/var/log/myapp.log</OutputPath>
        <Enabled>true</Enabled>
    </Logging>
    <Features>
        <Feature>feature1</Feature>
        <Feature>feature2</Feature>
        <Feature>feature3</Feature>
    </Features>
</AppConfig>
```

### JSON Output

```json
{
    "AppConfig": {
        "AppName": "MyApp",
        "Version": "1.0.0",
        "Database": {
            "Host": "localhost",
            "Port": "5432",
            "Username": "admin",
            "Password": "secret123"
        },
        "Logging": {
            "Level": "DEBUG",
            "OutputPath": "/var/log/myapp.log",
            "Enabled": "true"
        },
        "Features": {
            "Feature": ["feature1", "feature2", "feature3"]
        }
    }
}
```

## Best Practices

1. **Keep serializers close to types**: Define serialization operators in the same header as the struct
2. **Use const references**: Pass structures by const reference in operator<<
3. **Template on NodeAdapter**: This allows the same code to work with both XML and JSON
4. **Handle optional fields gracefully**: Use std::optional for fields that may not be present
5. **Consistent naming**: Use consistent XML/JSON element names across your project
6. **Test both formats**: If you support both XML and JSON, test serialization/deserialization for both

## Notes

- Once operators are defined, the type works with all FileParse features (vectors, maps, optional, etc.)
- The same serialization code works for both XML and JSON
- Nested structures serialize recursively
- Always test round-trip serialization (save and reload) to verify correctness
