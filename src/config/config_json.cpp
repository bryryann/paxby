#include "config/config_json.h"

#include <nlohmann/json.hpp>
#include <fstream>

namespace config {

Config load_config(const std::filesystem::path& config_path) {
    if (!std::filesystem::exists(config_path)) {
        throw std::runtime_error("config.json not found");
    }

    std::ifstream file(config_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config.json");
    }

    nlohmann::json json;
    file >> json;

    Config cfg;

    if (json.contains("storage_file_type")) {
        std::string type = json["storage_file_type"];

        if (type == "binary") {
            cfg.storage_file_type = core::FileType::Binary;
        }
        else if (type == "json") {
            cfg.storage_file_type = core::FileType::Json;
        }
        else {
            throw std::runtime_error("Invalid storage_file_type");
        }
    }

    return cfg;
}

}
