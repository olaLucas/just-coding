cmake_minimum_required(VERSION 3.10)
project(MyGtkmmApp)

# Find the GTKmm package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

# Set the source files for your application
set(SOURCES
    main.cpp
)

# Include directories for GTKmm
include_directories(${GTKMM_INCLUDE_DIRS})

# Compile the application
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against GTKmm libraries
target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})