#include <iostream>
#include <filesystem>
#include <fstream>
#include <openssl/evp.h>
#include <sqlite3.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <map>
#include <iomanip>
#include <sstream>

#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP

class Checksum {
public:
    bool computeChecksum(const std::string& filePath, std::string* str);
};

#endif