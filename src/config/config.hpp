#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <yaml-cpp/yaml.h>

using namespace std;

using namespace std::filesystem; 

//enumeration for logging levels
enum LogLevel {
  INFO, //normal log level
  WARN, //log only warning
  ERROR, //log only error
  DEBUG, //log only debug info
};

//enumeration for supported hashing algorithms
enum Algorithm {
  MD5, //use MD5 algo for hashing
  SHA256, //use SHA256 algo for hashing
  NONE, //no hashing
};

enum NotificationLevel {
  ALL, //notify for all changes
  CHANGES, //notify only for changes
  NO_NOTIFICATION, //no notification
};

//configuration class for managing settings from a YAML file
class Config {
private:
  YAML::Node yaml; //YAML object
  vector<path> paths; //vector of paths to check
  int interval; //time interval
  NotificationLevel notification_level; //notification level
  path log_file; //path to log file
  LogLevel log_level; //log level
  Algorithm algorithm; //algo used for hashing
 
public:
  Config(); //constructor
 
  void parse(const path&); //parse given yaml

  //getters for configuration parameters
  vector<path> get_paths();
  int get_interval();
  NotificationLevel get_notification_level();
  string get_log_file();
  string get_on_change_command();
  int get_max_threads();
  LogLevel get_log_level();
  Algorithm get_algorithm();

  //setters for configuration parameters
  bool update_interval(int);
  bool update_notification_level(NotificationLevel);
  bool update_log_file(string);
  bool update_on_change_command(string);
  bool update_max_threads(int);
  bool update_log_level(LogLevel);
  bool update_algorithm(Algorithm);

  ~Config(); //destructor
  
};

#endif
