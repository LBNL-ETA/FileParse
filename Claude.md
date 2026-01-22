# FileParse

A C++ header-only library for parsing and serializing structured data (primarily XML) to/from C++ objects.

## Quick Reference

- **Version**: 1.0.5
- **Language**: C++20 (library), C++17 (tests)
- **Build System**: CMake 3.5+
- **Testing**: GoogleTest v1.16.0
- **External Dependency**: XMLParser v1.0.3

## Build Instructions

```bash
# Configure
cmake -S . -B build -DBUILD_FILEPARSELIB_TESTS=ON

# Build
cmake --build build

# Run tests
ctest --test-dir build
```

## Directory Structure

```
FileParse/
├── include/fileParse/     # Header-only library
├── test/
│   ├── data/              # XML test files
│   ├── helper/            # Test utilities, mock adapters, structures
│   └── units/             # Unit test suites
├── .github/workflows/     # CI configuration (Ubuntu, Windows, macOS)
├── CMakeLists.txt         # Root build config
└── .clang-format          # Code style (clang-format)
```

## Core Components

| File | Purpose |
|------|---------|
| `Base.hxx` | Core serialization for primitives (bool, int, double, string) |
| `Vector.hxx` | `std::vector` serialization |
| `Set.hxx` | `std::set` serialization |
| `Map.hxx` | `std::map`/`std::unordered_map` serialization |
| `Array.hxx` | `std::array` serialization |
| `Variant.hxx` | `std::variant` serialization |
| `Optional.hxx` | `std::optional` support |
| `Enum.hxx` | Enum serialization with converters |
| `Attributes.hxx` | XML attribute handling |
| `XMLNodeAdapter.hxx` | XML node manipulation (wraps XMLParser) |
| `INodeAdapter.hxx` | Abstract interface for node adapters |
| `FileDataHandler.hxx` | File I/O operations |

## Architecture

### Operator Overloading Pattern

The library uses `operator<<` for serialization and `operator>>` for deserialization:

```cpp
// Serialization (object to XML)
nodeAdapter << myObject;

// Deserialization (XML to object)
nodeAdapter >> myObject;
```

### Template-Based Design

All serialization functions are templated to support various types:
- Primitives: `bool`, `int`, `double`, `std::string`
- Containers: `std::vector`, `std::set`, `std::map`, `std::array`
- Utilities: `std::optional`, `std::variant`
- Custom types via user-defined operators

### Adapter Pattern

`INodeAdapter` defines the abstract interface for node manipulation. `XMLNodeAdapter` implements this interface for XML using the XMLParser library. This allows potential support for other formats.

## Testing

Tests are organized by component in `test/units/`. Each test file corresponds to a library header:
- `Base_tests.cpp` - primitive type tests
- `Vector_tests.cpp` - vector serialization tests
- `Map_tests.cpp` - map serialization tests
- etc.

Test helper structures are defined in `test/helper/` with mock adapters and sample data structures.

## License
I would adopt license from other package:
*** Copyright Notice ***

"Berkeley Lab WINDOW Calc Engine (CalcEngine)" Copyright (c) 2016, The Regents of the University of California, through Lawrence Berkeley National Laboratory (subject to receipt of any required approvals from the U.S. Dept. of Energy).  All rights reserved.

If you have questions about your rights to use or distribute this software, please contact Berkeley Lab's Innovation & Partnerships Office at  IPO@lbl.gov.

NOTICE.  This Software was developed under funding from the U.S. Department of Energy and the U.S. Government consequently retains certain rights.  As such, the U.S. Government has been granted for itself and others acting on its behalf a paid-up, nonexclusive, irrevocable, worldwide license in the Software to reproduce, distribute copies to the public, prepare derivative works, and perform publicly and display publicly, and to permit other to do so. 

****************************
 

*** License Agreement ***

"Berkeley Lab WINDOW Calc Engine (CalcEngine)" Copyright (c) 2026, The Regents of the University of California, through Lawrence Berkeley National Laboratory (subject to receipt of any required approvals from the U.S. Dept. of Energy).  All rights reserved. 

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

(1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

(2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

(3) Neither the name of the University of California, Lawrence Berkeley National Laboratory, U.S. Dept. of Energy nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

You are under no obligation whatsoever to provide any bug fixes, patches, or upgrades to the features, functionality or performance of the source code ("Enhancements") to anyone; however, if you choose to make your Enhancements available either publicly, or directly to Lawrence Berkeley National Laboratory, without imposing a separate written license agreement for such Enhancements, then you hereby grant the following license: a  non-exclusive, royalty-free perpetual license to install, use, modify, prepare derivative works, incorporate into other computer software, distribute, and sublicense such enhancements or derivative works thereof, in binary and source code form.  

****************************

## Code Style

- Follows `.clang-format` configuration
- Header files use `.hxx` extension
- Implementation files use `.cxx` extension
- Test files use `_tests.cpp` suffix

## Documentation Style

Use Doxygen-style triple-slash comments (`///`) for all public API documentation.

### File Header

Every header file should start with a file description:

```cpp
/// File: FileName.hxx
/// @brief Short description of what this file provides.
///        Additional details can span multiple lines.
```

### Function/Operator Documentation

Document all public functions with:
- Brief description of what the function does
- `@tparam` for each template parameter
- `@param` for each function parameter
- `@return` describing the return value

```cpp
/// Brief description of what the function does.
/// @tparam NodeAdapter The type of the node adapter.
/// @tparam T The type of elements being processed.
/// @param node The node to operate on.
/// @param data The data to serialize/deserialize.
/// @return Reference to the node (for chaining).
template<typename NodeAdapter, typename T>
NodeAdapter & operator<<(NodeAdapter & node, const T & data);
```

### Key Terms

- **Serialize**: Convert C++ object to node representation (operator<<)
- **Deserialize**: Convert node representation to C++ object (operator>>)
- **NodeAdapter**: Abstraction over XML/JSON node (XMLNodeAdapter, JSONNodeAdapter)
- **Child**: Wrapper that pairs data with node path (hierarchy of tag names)
