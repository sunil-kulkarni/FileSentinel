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
        string level = config["logging"]["log_level"].as<string>();
        if (level == "INFO") {log_level = LogLevel::INFO;}
        else if (level == "WARN") {log_level = LogLevel::WARN;}
        else if (level == "ERROR") {log_level = LogLevel::ERROR;}
        else if (level == "DEBUG") {log_level = LogLevel::DEBUG;}
    }


    if (config["checksum"]["algorithm"]) {
        string algo = config["checksum"]["algorithm"].as<string>();
        if (algo == "MD5") {algorithm = Algorithm::MD5;}
        else if (algo == "SHA256") {algorithm = Algorithm::SHA256;}
        else {algorithm = Algorithm::none;}
    }

    if (config["alerts"]["on_change_command"]) {
        on_change_command = config["alerts"]["on_change_command"].as<string>();
    }


    if (config["performance"]["max_threads"]) {
        max_threads = config["performance"]["max_threads"].as<int>();
    }
}

