In CMake, the `add_library()` command is used to define a new library target. This can be a static library (`.lib` on Windows, `.a` on Unix-like systems) or a shared library (`.dll` on Windows, `.so` on Unix-like systems). Here's a basic example of how to use `add_library()` in a `CMakeLists.txt` file:

```cmake
# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Declare your project
project(YourProjectName)

# Add source files to your library
set(SOURCES
    source_file1.cpp
    source_file2.cpp
    # Add more source files as needed
)

# Create a library target
add_library(YourLibraryName ${SOURCES})

# You can also set properties for the library, for example:
# target_compile_features(YourLibraryName PRIVATE cxx_std_11)

# Specify include directories if needed
target_include_directories(YourLibraryName PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Specify compile options if needed
# target_compile_options(YourLibraryName PRIVATE -Wall -Wextra)

# If your library depends on other libraries, link them here
# target_link_libraries(YourLibraryName PUBLIC SomeOtherLibrary)

# Optionally, if your library requires additional compiler or linker flags:
# target_compile_definitions(YourLibraryName PRIVATE SOME_DEFINE)

# Add an executable and link it with your library
add_executable(YourExecutableName main.cpp)
target_link_libraries(YourExecutableName PRIVATE YourLibraryName)
```

Here's a breakdown of the commands used in this example:

- `add_library()`: Creates a library target named `YourLibraryName` using the specified source files.

- `target_include_directories()`: Specifies the include directories for the library. In this example, it includes the `include` directory.

- `target_compile_options()`: Specifies compile options for the library. This is optional, and you can add compiler options as needed.

- `target_link_libraries()`: Specifies libraries to link against. In this case, if `YourLibraryName` depends on another library (`SomeOtherLibrary`), you would link against it here.

- `add_executable()`: Creates an executable target named `YourExecutableName` using the specified source files.

- `target_link_libraries(YourExecutableName PRIVATE YourLibraryName)`: Links the executable with the library, so that symbols from the library are available to the executable.

Adjust the names and paths according to your project structure and requirements. This is a basic example, and you might need to add additional configurations based on the specifics of your project and the libraries you are using.# adicionando um diretorio para as bibliotecas
#add_subdirectory(libs)