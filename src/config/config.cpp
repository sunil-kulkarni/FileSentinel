#include "config.hpp"

// Parses the YAML configuration file and extracts values
void Config::parse(const string& file) {
  // Load YAML file
  config = YAML::LoadFile(file);
  

  if (config["files"]["paths"]) {
  for (const auto& path : config["files"]["paths"]) {
    paths.push_back(path.as<string>());// Convert YAML node to string and add to paths vector
  }
  }
  // Parse check interval (in seconds)
  if (config["interval"]["check_interval"]) {
  interval = config["interval"]["check_interval"].as<int>();
  }


  // Parse notification setting (enabled/disabled)
  if (config["notifications"]["enabled"]) {
  noti_enabled = config["notifications"]["enabled"].as<bool>();
  }

  // Parse logging settings
  if (config["logging"]["log_file"]) {
  log_file = config["logging"]["log_file"].as<string>();
  }

  // Parse log level and map to the LogLevel enum
  if (config["logging"]["log_level"]) {
  string level = config["logging"]["log_level"].as<string>();
  if (level == "INFO") {log_level = LogLevel::INFO;}
  else if (level == "WARN") {log_level = LogLevel::WARN;}
  else if (level == "ERROR") {log_level = LogLevel::ERROR;}
  else if (level == "DEBUG") {log_level = LogLevel::DEBUG;}
  }

  // Parse checksum algorithm and map to the Algorithm enum
  if (config["checksum"]["algorithm"]) {
  string algo = config["checksum"]["algorithm"].as<string>();
  if (algo == "MD5") {algorithm = Algorithm::MD5;}
  else if (algo == "SHA256") {algorithm = Algorithm::SHA256;}
  else {algorithm = Algorithm::NONE;}
  }

  // Parse on-change command
  if (config["alerts"]["on_change_command"]) {
  on_change_command = config["alerts"]["on_change_command"].as<string>();
  }

  // Parse max number of threads allowed
  if (config["performance"]["max_threads"]) {
  max_threads = config["performance"]["max_threads"].as<int>();
  }
}

// Getters for configuration parameters
vector<path> Config::get_paths() {
  return paths;
}

// Getter method to retrieve the monitoring interval
int Config::get_interval() {
  return interval;
}

// Getter method to check if notifications are enabled
bool Config::get_noti_enabled() {
  return noti_enabled;
}

// Getter method to retrieve the log file path
string Config::get_log_file() {
  return log_file;
}

// Getter method to retrieve the command to execute on changes
string Config::get_on_change_command() {
  return on_change_command;
}

// Getter method to retrieve the max number of threads
int Config::get_max_threads() {
  return max_threads;
}

// Getter method to retrieve the current log level
LogLevel Config::get_log_level() {
  return log_level;
}

// Getter method to retrieve the selected hashing algorithm
Algorithm Config::get_algorithm() {
  return algorithm;
}

// Setter methods to update configuration parameters
void Config::update_interval(int new_interval) {
  interval = new_interval;
}

// Setter method to update the notification setting
void Config::update_noti_enabled(bool enabled) {
  noti_enabled = enabled;
}

// Setter method to update the log file path
void Config::update_log_file(string new_log_file) {
  log_file = new_log_file;
}

// Setter method to update the command to execute on changes
void Config::update_on_change_command(string new_command) {
  on_change_command = new_command;
}

// Setter method to update the max number of threads
void Config::update_max_threads(int new_max_threads) {
  max_threads = new_max_threads;
}

// Setter method to update the log level
void Config::update_log_level(LogLevel new_log_level) {
  log_level = new_log_level;
}

// Setter method to update the hashing algorithm
void Config::update_algorithm(Algorithm new_algorithm) {
  algorithm = new_algorithm;
}