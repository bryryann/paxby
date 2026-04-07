#pragma once

#include "core/context.h"

#include <filesystem>

namespace config {

struct Config {
    core::FileType storage_file_type;
};

Config load_config(const std::filesystem::path& config_path);

}
