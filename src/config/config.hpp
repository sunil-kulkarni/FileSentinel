#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>

using namespace std;

using namespace std::filesystem; 

// Enumeration for logging levels
enum  LogLevel {
  INFO,  
  WARN, 
  ERROR, 
  DEBUG  
};

// Enumeration for supported hashing algorithms
enum  Algorithm {
  MD5,  
  SHA256,
  NONE
};

// Configuration class for managing settings from a YAML file
class Config {
private:
  YAML::Node config;
  vector<path> paths;
  int interval;
  bool noti_enabled;
  string log_file;
  string on_change_command;
  int max_threads;
  LogLevel log_level;
  Algorithm algorithm; 
public:
  // Parses the configuration file and loads settings
  void parse(const string&);

  // Getters for configuration parameters
  vector<path> get_paths();
  int get_interval();
  bool get_noti_enabled();
  string get_log_file();
  string get_on_change_command();
  int get_max_threads();
  LogLevel get_log_level();
  Algorithm get_algorithm();

  void update_interval(int);
  void update_noti_enabled(bool);
  void update_log_file(string);
  void update_on_change_command(string);
  void update_max_threads(int);
  void update_log_level(LogLevel);
  void update_algorithm(Algorithm);
  
  Config() {
  interval = 0;
  noti_enabled = false;
  log_file = "";
  on_change_command = "";
  max_threads = 0;
  log_level = LogLevel::INFO;
  algorithm = Algorithm::NONE;
  }
};

#endif 

