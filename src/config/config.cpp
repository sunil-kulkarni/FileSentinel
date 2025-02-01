#include "config.hpp"

void Config::parse(const string& file) {

    config = YAML::LoadFile(file);

    if (config["files"]["paths"]) {
        for (const auto& path : config["files"]["paths"]) {
            paths.push_back(path.as<string>());
        }
    }

    if (config["interval"]["check_interval"]) {
        interval = config["interval"]["check_interval"].as<int>();
    }


    if (config["notifications"]["enabled"]) {
        noti_enabled = config["notifications"]["enabled"].as<bool>();
    }

    if (config["logging"]["log_file"]) {
        log_file = config["logging"]["log_file"].as<string>();
    }


    if (config["logging"]["log_level"]) {
        log_level = config["logging"]["log_level"].as<string>();
    }


    if (config["checksum"]["algorithm"]) {
        algorithm = config["checksum"]["algorithm"].as<string>();
    }


    if (config["alerts"]["on_change_command"]) {
        on_change_command = config["alerts"]["on_change_command"].as<string>();
    }


    if (config["performance"]["max_threads"]) {
        max_threads = config["performance"]["max_threads"].as<int>();
    }
}

