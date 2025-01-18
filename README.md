# File Compression Project

## Overview

The File Compression Project is a C++ application that provides functionality for compressing and decompressing files.
It supports various compression formats and includes a user interface for managing compressed files.
Project is still ongoing.

## Features

- **File Compression**: Compress files into various formats (e.g., ZIP, TAR).
- **File Decompression**: Decompress files from various formats.
- **Archive Content Viewer**: View the contents of a compressed file without decompressing it.
- **File Deletion from Archive**: Delete files from a compressed archive.
- **File Addition to Archive**: Add files to an existing compressed archive.

## Requirements

- CMake 3.30 or higher
- C++20 compatible compiler
- Boost libraries
- Zlib
- BZip2
- OpenGL
- GLFW
- ImGui

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/FileCompressionProject.git
    cd FileCompressionProject
    git submodule update --init --recursive --remote
    ```

   download boost from website [Boost Downloads](https://www.boost.org/users/download/)
2. Install dependencies using vcpkg:
    ```sh
    ./vcpkg install boost zlib bzip2 glfw3
    ```
   Install dependencies Linux:
   ```sh
   ./bootstrap.sh
   ./b2 --with-iostreams
   sudo apt update
   sudo apt install libboost-all-dev libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
   ```

4. Configure and build the project:
    ```sh
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

## Usage

1. Run the executable:
    ```sh
    ./FileCompressionProject
    ```

2. Use the user interface to select files for compression or decompression.

## Project Structure

- `main.cpp`: Entry point of the application.
- `FileManipulation/`: Contains classes and methods for file operations.
- `external/`: Contains external libraries and dependencies.
- `test/`: Contains unit tests for the project.

## Common Issues with Building and Running application

- Troubleshooting
  Missing GLFW/glfw3.h Header File
  Ensure that the GLFW include directory is added to your include paths in CMakeLists.txt:

```sh
  include_directories(${GLFW_INCLUDE_DIRS})
```

- Could Not Find glfw3Config.cmake
  Ensure that GLFW is installed on your system. If you built GLFW from source, specify the path to the glfw3Config.cmake
  file in your CMakeLists.txt:

```sh
   set(GLFW_DIR /path/to/glfw/build)
  find_package(glfw3 REQUIRED CONFIG PATHS ${GLFW_DIR})
```

- Undefined Reference to GLFW Functions Ensure that the GLFW library is linked correctly in your CMakeLists.txt:

```sh
   target_link_libraries(FileCompressionProject PRIVATE glfw OpenGL::GL)
```

- Undefined Reference to Boost iostreams Functions
  Ensure that the Boost iostreams library is linked correctly in your CMakeLists.txt:

```sh
  find_package(Boost REQUIRED COMPONENTS iostreams)
  target_link_libraries(FileCompressionProject PRIVATE Boost::iostreams)
```

-

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Contact

For any questions or suggestions, please contact `jacob.pagan10@gmail.com`.
