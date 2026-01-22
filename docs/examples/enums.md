# Enum Serialization

FileParse supports serializing enums as human-readable strings using custom converter functions.

## Including the Required Headers

```cpp
#include <fileParse/Enum.hxx>
#include <fileParse/Vector.hxx>  // For enum vectors
#include <fileParse/Map.hxx>     // For enum map keys
#include <fileParse/Common.hxx>
#include <fileParse/StringConversion.hxx>
#include <fileParse/FileDataHandler.hxx>
```

## Defining an Enum with Converters

```cpp
enum class Priority {
    Low,
    Medium,
    High,
    Critical
};

// String array for conversion (must match enum order)
const std::array<std::string, 4> PriorityStrings = {
    "Low", "Medium", "High", "Critical"
};

// Enum to string converter
std::string priorityToString(Priority p) {
    return FileParse::enumToString(p, PriorityStrings);
}

// String to enum converter
Priority stringToPriority(std::string_view s) {
    return FileParse::enumFromString(s, PriorityStrings, Priority::Low);
}
```

## Simple Enum Field

### Structure

```cpp
struct Task {
    std::string name;
    Priority priority;
};
```

### Serialization

```cpp
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const Task& t) {
    node << FileParse::Child{"Name", t.name};
    FileParse::serializeEnum(node, t.priority, priorityToString);
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, Task& t) {
    node >> FileParse::Child{"Name", t.name};
    FileParse::deserializeEnum(node, t.priority, stringToPriority);
    return node;
}
```

### XML Output

```xml
<Task>
    <Name>Fix bug</Name>
    High
</Task>
```

## Enum in a Child Node

To wrap the enum in its own node:

```cpp
template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const Task& t) {
    node << FileParse::Child{"Name", t.name};
    auto priorityNode = node.addChild("Priority");
    FileParse::serializeEnum(priorityNode, t.priority, priorityToString);
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, Task& t) {
    node >> FileParse::Child{"Name", t.name};
    if (auto priorityNode = node.getFirstChildByName("Priority"); priorityNode.has_value()) {
        FileParse::deserializeEnum(priorityNode.value(), t.priority, stringToPriority);
    }
    return node;
}
```

### XML Output

```xml
<Task>
    <Name>Fix bug</Name>
    <Priority>High</Priority>
</Task>
```

## Vector of Enums

```cpp
struct TaskList {
    std::vector<Priority> priorities;
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const TaskList& t) {
    FileParse::serializeEnumVector(node, {"Priorities", "Priority"}, t.priorities, priorityToString);
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, TaskList& t) {
    FileParse::deserializeEnumVector(node, {"Priorities", "Priority"}, t.priorities, stringToPriority);
    return node;
}
```

### XML Output

```xml
<TaskList>
    <Priorities>
        <Priority>High</Priority>
        <Priority>Low</Priority>
        <Priority>Critical</Priority>
    </Priorities>
</TaskList>
```

## Map with Enum Keys

```cpp
struct PriorityLabels {
    std::map<Priority, std::string> labels;
};

template<typename NodeAdapter>
NodeAdapter& operator<<(NodeAdapter& node, const PriorityLabels& p) {
    FileParse::serializeEnumMap<NodeAdapter, Priority, std::string>(
        node, p.labels, priorityToString);
    return node;
}

template<typename NodeAdapter>
const NodeAdapter& operator>>(const NodeAdapter& node, PriorityLabels& p) {
    FileParse::deserializeEnumMap<NodeAdapter, Priority, std::string>(
        node, p.labels, stringToPriority);
    return node;
}
```

### XML Output

```xml
<PriorityLabels>
    <Low>Not urgent</Low>
    <High>Needs attention</High>
    <Critical>Emergency</Critical>
</PriorityLabels>
```

## Case-Insensitive Parsing

For more forgiving input parsing:

```cpp
Priority stringToPriorityCaseInsensitive(std::string_view s) {
    return FileParse::enumFromStringCaseInsensitive(s, PriorityStrings, Priority::Low);
}
```

This allows "high", "HIGH", or "High" to all parse as `Priority::High`.

## Using std::map for Enum Conversion

Alternative approach using a map:

```cpp
const std::map<Priority, std::string> PriorityMap = {
    {Priority::Low, "Low"},
    {Priority::Medium, "Medium"},
    {Priority::High, "High"},
    {Priority::Critical, "Critical"}
};

std::string priorityToString(Priority p) {
    return FileParse::enumToString(p, PriorityMap);
}

Priority stringToPriority(std::string_view s) {
    return FileParse::enumFromString(s, PriorityMap, Priority::Low);
}
```

## Notes

- The string array/map must contain entries for all enum values
- A default value is returned when parsing unknown strings
- Enum values are always serialized as strings, not integers
- Both XML and JSON use the same string representation
