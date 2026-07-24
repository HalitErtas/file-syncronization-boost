# File Synchronization Boost

A C++17 desktop application for comparing and synchronizing directories.

## Features

* Scan files and directories
* Compare two directories
* Detect:

  * Added files
  * Removed files
  * Unchanged files
* Built with modern C++17 and CMake

## Project Structure

```

include/
├── DirectoryComparer.hpp
├── FileScanner.hpp
└── structs/
    ├── ComparisonEntry.hpp
    ├── ComparisonStatus.hpp
    ├── FileInfo.hpp
    └── FileType.hpp

src/
├── DirectoryComparer.cpp
├── FileScanner.cpp
└── main.cpp
```

## Build

```bash
make
```

or

```bash
make build
```

## Run

```bash
make run
```

## Implemented Features

* File scanning
* Directory comparison
* Detection of added files
* Detection of removed files
* Detection of unchanged files

## License

This project is for learning and experimentation.
