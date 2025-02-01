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
class Config {
private:
    YAML::Node config;
    vector<path> paths;
    int interval = 0;
    bool noti_enabled = false;
    string log_file = "";
    string log_level = "";
    string algorithm = "";
    string on_change_command = "";
    int max_threads = 1;
public:
    void parse(const string&);
};

#endif

