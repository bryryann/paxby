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
option(PAXBY_USE_SYSTEM_JSON "Use system-installed nlohmann_json" ON)

if (PAXBY_USE_SYSTEM_JSON)
    find_package(nlohmann_json QUIET)
endif()

if (NOT nlohmann_json_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

add_library(paxby_core)

add_library(paxby::paxby
    ALIAS paxby_core
)

add_subdirectory(src/core)
add_subdirectory(src/cli)
add_subdirectory(src/storage)
add_subdirectory(src/utils)
add_subdirectory(src/commands)
add_subdirectory(src/io)
add_subdirectory(src/config)

target_include_directories(paxby_core
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(paxby_core PUBLIC cxx_std_20)

add_executable(paxby
    src/main.cpp
)

target_link_libraries(paxby
    PRIVATE
        paxby_core
        nlohmann_json::nlohmann_json
)

include(GNUInstallDirs)

install(TARGETS paxby
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(TARGETS paxby_core
    EXPORT paxbyTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# warnings
if (ENABLE_WARNINGS)
    include(cmake/warnings.cmake)
endif()
