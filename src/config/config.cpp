#include "config.hpp"

//assigns default values
Config::Config() {
  interval = 360;
  notification_enabled = false;
  log_file = "";
  log_level = LogLevel::INFO;
  algorithm = Algorithm::NONE;
}

//parses the YAML configuration file and extracts values
void Config::parse(const path& file) {
  //load YAML file
  yaml = YAML::LoadFile(file);
  
  //updates paths
  if (yaml["files"]["paths"]) {
    for (const auto& path : yaml["files"]["paths"]) {
      paths.push_back(path.as<string>()); //convert YAML node to string and add to paths vector
    }
  }

  //updates interval if exists
  if (yaml["interval"]["check_interval"]) {
    interval = yaml["interval"]["check_interval"].as<int>();
  }

  //updates notification_enabled if exists
  if (yaml["notifications"]["enabled"]) {
    notification_enabled = yaml["notifications"]["enabled"].as<bool>();
  }

  //updates log_file if exists
  if (yaml["logging"]["log_file"]) {
    log_file = yaml["logging"]["log_file"].as<string>();
  }

  //updates log_level if exists
  if (yaml["logging"]["log_level"]) {
    string level = yaml["logging"]["log_level"].as<string>();
    if (level == "INFO") {
      log_level = LogLevel::INFO;
    } else if (level == "WARN") {
      log_level = LogLevel::WARN;
    } else if (level == "ERROR") {
      log_level = LogLevel::ERROR;
    } else if (level == "DEBUG") {
      log_level = LogLevel::DEBUG;
    }
  }

  //updates algorithm if exists
  if (yaml["checksum"]["algorithm"]) {
    string algo = yaml["checksum"]["algorithm"].as<string>();
    if (algo == "MD5") {
      algorithm = Algorithm::MD5;
    } else if (algo == "SHA256") {
      algorithm = Algorithm::SHA256;
    } else {algorithm = Algorithm::NONE;}
  }
}

//getters for configuration parameters
vector<path> Config::get_paths() {
  return paths;
}

//getter method to retrieve the monitoring interval
int Config::get_interval() {
  return interval;
}

//getter method to check if notifications are enabled
bool Config::get_noti_enabled() {
  return notification_enabled;
}

//getter method to retrieve the log file path
string Config::get_log_file() {
  return log_file;
}

//getter method to retrieve the current log level
LogLevel Config::get_log_level() {
  return log_level;
}

//getter method to retrieve the selected hashing algorithm
Algorithm Config::get_algorithm() {
  return algorithm;
}

//setter methods to update configuration parameters
void Config::update_interval(int new_interval) {
  interval = new_interval;
}

//setter method to update the notification setting
void Config::update_noti_enabled(bool enabled) {
  notification_enabled = enabled;
}

//setter method to update the log file path
void Config::update_log_file(string new_log_file) {
  log_file = new_log_file;
}

//setter method to update the log level
void Config::update_log_level(LogLevel new_log_level) {
  log_level = new_log_level;
}

//setter method to update the hashing algorithm
void Config::update_algorithm(Algorithm new_algorithm) {
  algorithm = new_algorithm;
}

Config::~Config() {}

