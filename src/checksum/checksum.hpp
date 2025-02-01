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
    bool computeChecksum_sha(const std::string& filePath, std::string* str);
    bool compareChecksum(const std::string& filePath, const std::string *);
    static bool computeChecksum_md(const std::string &filePath, std::string *str);

    /* Computes the SHA-256 checksum of a given file and stores it in 'str'. Returns true if successful, false if an error occurs (e.g., file not found).*/
bool computeChecksum_sha(const std::string& filePath, std::string* str);

/*Compares the computed SHA-256 checksum of a file with a given checksum. Returns true if they match, false otherwise.*/
bool compareChecksum(const std::string& filePath, const std::string *givenChecksum);

/*Computes the MD5 checksum of a given file and stores it in 'str'. Returns true if successful, false if an error occurs (e.g., file not found).*/
static bool computeChecksum_md(const std::string &filePath, std::string *str);

};
#endif