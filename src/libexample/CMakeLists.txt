add_library(cpp-project-template
    library.cpp
)

add_library(cpp-project-template::cpp-project-template
    ALIAS cpp-project-template
)

target_include_directories(cpp-project-template
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(cpp-project-template
    PUBLIC cxx_std_20
)
