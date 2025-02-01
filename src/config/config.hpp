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
};

#endif

