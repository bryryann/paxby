cmake_minimum_required(VERSION 4.1)

project(
    cpp-project-template
    VERSION 1.0.0
    LANGUAGES CXX
)

# globals
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# options
option(ENABLE_WARNINGS "Enable compiler warnings" ON)

# subdirectories
add_subdirectory(src/libexample)

add_executable(cpp-project-template-app 
    src/main.cpp
)

target_link_libraries(cpp-project-template-app 
    PRIVATE
        cpp-project-template
)

# warnings
if (ENABLE_WARNINGS)
    include(cmake/warnings.cmake)
endif()
