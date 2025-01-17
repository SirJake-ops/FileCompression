# File Compression Project

## Overview
The File Compression Project is a C++ application that provides functionality for compressing and decompressing files. It supports various compression formats and includes a user interface for managing compressed files.

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
    ```

2. Install dependencies using vcpkg:
    ```sh
    ./vcpkg install boost zlib bzip2 glfw3
    ```

3. Configure and build the project:
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

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

## Contact
For any questions or suggestions, please contact `jacob.pagan10@gmail.com`.
