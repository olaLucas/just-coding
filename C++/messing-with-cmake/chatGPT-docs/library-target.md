In CMake, a library target is a conceptual entity representing a library that your project is building. A library can be a static library (compiled into your program) or a shared library (a separate binary that your program links to at runtime).

When you use the `add_library()` command in CMake, you are creating a library target. Here's a breakdown of what a library target is and how it is used:

1. **Creating a Library Target:**
   The `add_library()` command is used to create a library target. It takes the name of the library and a list of source files as arguments. For example:

   ```cmake
   add_library(MyLibrary my_source_file.cpp another_source_file.cpp)
   ```

   This command tells CMake to create a library named `MyLibrary` using the specified source files.

2. **Setting Properties and Options:**
   After creating the library target, you can set various properties and options for it. For example, you might specify include directories, compile features, compile options, or define certain preprocessor symbols. This is done using commands like `target_include_directories()`, `target_compile_features()`, `target_compile_options()`, and `target_compile_definitions()`.

   ```cmake
   target_include_directories(MyLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
   target_compile_features(MyLibrary PRIVATE cxx_std_11)
   target_compile_options(MyLibrary PRIVATE -Wall -Wextra)
   ```

3. **Linking with Other Libraries:**
   If your library depends on other libraries, you use the `target_link_libraries()` command to specify these dependencies. This ensures that when your library is used in another target (executable or another library), the necessary linking is done.

   ```cmake
   target_link_libraries(MyLibrary PUBLIC SomeOtherLibrary)
   ```

4. **Usage in Other Targets:**
   Once you have defined your library target, you can link it with other targets in your project. For example, if you have an executable, you can link it with your library:

   ```cmake
   add_executable(MyExecutable main.cpp)
   target_link_libraries(MyExecutable PRIVATE MyLibrary)
   ```

   This tells CMake that `MyExecutable` depends on `MyLibrary`, and it should link them appropriately.

In summary, a library target in CMake is a representation of a library in your project. It encapsulates the information needed to build the library, including source files, compile options, include directories, and dependencies on other libraries. Library targets facilitate modularity and clean dependency management in CMake projects.