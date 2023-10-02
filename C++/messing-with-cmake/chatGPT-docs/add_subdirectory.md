The `add_subdirectory()` command in CMake is used to include the CMakeLists.txt files from another directory into the current project. This is particularly useful when you want to organize your project into subdirectories, each with its own CMakeLists.txt file.

Here's a basic example of how `add_subdirectory()` is used:

Assume you have the following directory structure:

```
project_root/
│
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   └── CMakeLists.txt
└── lib/
    ├── mylibrary.cpp
    └── CMakeLists.txt
```

1. **project_root/CMakeLists.txt:**

   ```cmake
   cmake_minimum_required(VERSION 3.10)
   project(MyProject)

   # Add the 'lib' subdirectory
   add_subdirectory(lib)

   # Add the 'src' subdirectory
   add_subdirectory(src)
   ```

2. **project_root/lib/CMakeLists.txt:**

   ```cmake
   # Define a library named 'MyLibrary'
   add_library(MyLibrary mylibrary.cpp)

   # You can set properties and link libraries for 'MyLibrary' here
   # For example:
   # target_include_directories(MyLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
   ```

3. **project_root/src/CMakeLists.txt:**

   ```cmake
   # Define an executable named 'MyExecutable'
   add_executable(MyExecutable main.cpp)

   # Link 'MyExecutable' with 'MyLibrary'
   target_link_libraries(MyExecutable PRIVATE MyLibrary)
   ```

In this example:

- The main `CMakeLists.txt` in the project root includes the CMakeLists.txt files from the 'lib' and 'src' subdirectories using `add_subdirectory(lib)` and `add_subdirectory(src)`.

- The 'lib' directory contains its own CMakeLists.txt file defining a library named 'MyLibrary'.

- The 'src' directory contains its own CMakeLists.txt file defining an executable named 'MyExecutable' and linking it with the 'MyLibrary' library.

This structure helps in organizing your project, keeping the build configurations separate for different parts of your codebase.

When you run CMake in the project root, it will process the CMakeLists.txt files in the subdirectories as well, ensuring that the entire project is configured and built correctly.