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
        else {algorithm = Algorithm::NONE;}
    }

    if (config["alerts"]["on_change_command"]) {
        on_change_command = config["alerts"]["on_change_command"].as<string>();
    }


    if (config["performance"]["max_threads"]) {
        max_threads = config["performance"]["max_threads"].as<int>();
    }
}

vector<path> Config::get_paths() {
    return paths;
}

int Config::get_interval() {
    return interval;
}

bool Config::get_noti_enabled() {
    return noti_enabled;
}

string Config::get_log_file() {
    return log_file;
}

string Config::get_on_change_command() {
    return on_change_command;
}

int Config::get_max_threads() {
    return max_threads;
}

LogLevel Config::get_log_level() {
    return log_level;
}

Algorithm Config::get_algorithm() {
    return algorithm;
}


