#include "config.hpp"

//assigns default values
Config::Config() {
  interval = 360;
  notification_level = NotificationLevel::ALL;
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

  //updates notification_level if exists
  if (yaml["notifications"]["level"]) {
      string notification = yaml["notifications"]["level"].as<string>();
      std::transform(notification.begin(), notification.end(), notification.begin(), ::tolower);
      if (notification == "all") {
          notification_level = NotificationLevel::ALL;
      } else if (notification == "changes") {
          notification_level = NotificationLevel::CHANGES;
      } else {
          notification_level = NotificationLevel::NO_NOTIFICATION;
      }
  }

  //updates log_file if exists
  if (yaml["logging"]["log_file"]) {
    log_file = yaml["logging"]["log_file"].as<string>();
  }

  //updates log_level if exists
  if (yaml["logging"]["log_level"]) {
    string level = yaml["logging"]["log_level"].as<string>();
    std::transform(level.begin(), level.end(), level.begin(), ::tolower);
    if (level == "info") {
      log_level = LogLevel::INFO;
    } else if (level == "warn") {
      log_level = LogLevel::WARN;
    } else if (level == "error") {
      log_level = LogLevel::ERROR;
    } else if (level == "debug") {
      log_level = LogLevel::DEBUG;
    }
  }

  //updates algorithm if exists
  if (yaml["checksum"]["algorithm"]) {
    string algo = yaml["checksum"]["algorithm"].as<string>();
    std::transform(algo.begin(), algo.end(), algo.begin(), ::tolower);
    if (algo == "md5") {
      algorithm = Algorithm::MD5;
    } else if (algo == "sha256") {
      algorithm = Algorithm::SHA256;
    } else {
      algorithm = Algorithm::NONE;
    }
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

//getter method to check if notifications are level
NotificationLevel Config::get_notification_level() {
  return notification_level;
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
bool Config::update_interval(int new_interval) {
  interval = new_interval;
  return true;
}

//setter method to update the notification setting
bool Config::update_notification_level(NotificationLevel new_notification_level) {
  notification_level = new_notification_level;
  return true;
}

//setter method to update the log file path
bool Config::update_log_file(string new_log_file) {
  log_file = new_log_file;
  return true;
}

//setter method to update the log level
bool Config::update_log_level(LogLevel new_log_level) {
  log_level = new_log_level;
  return true;
}

//setter method to update the hashing algorithm
bool Config::update_algorithm(Algorithm new_algorithm) {
  algorithm = new_algorithm;
  return true;
}

Config::~Config() {}
