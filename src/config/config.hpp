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
enum  LogLevel {
    INFO,  
    WARN, 
    ERROR, 
    DEBUG  
};
enum  Algorithm {
    MD5,    
    SHA256,
    NONE
};
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
    void parse(const string&);
    vector<path> get_paths();
    int get_interval();
    bool get_noti_enabled();
    string get_log_file();
    string get_on_change_command();
    int get_max_threads();
    LogLevel get_log_level();
    Algorithm get_algorithm();
};

#endif

