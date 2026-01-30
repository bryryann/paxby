cmake_minimum_required(VERSION 4.1)

project(
    paxby
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

# libraries and subdirectories
find_package(nlohmann_json REQUIRED)

add_library(paxby)

add_library(paxby::paxby
    ALIAS paxby
)

add_subdirectory(src/core)
add_subdirectory(src/cli)
add_subdirectory(src/storage)
add_subdirectory(src/utils)
add_subdirectory(src/commands)

target_include_directories(paxby
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(paxby PUBLIC cxx_std_20)

add_executable(paxby-app 
    src/main.cpp
)

target_link_libraries(paxby-app 
    PRIVATE
        paxby
        nlohmann_json::nlohmann_json
)

# warnings
if (ENABLE_WARNINGS)
    include(cmake/warnings.cmake)
endif()
