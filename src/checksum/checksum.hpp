#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>

class Checksum {
public:
    /* Computes the SHA-256 checksum of a given file and stores it in 'str'. 
       Returns true if successful, false if an error occurs (e.g., file not found). */
    bool computeChecksum_sha(const std::string& filePath, std::string* str);

    /* Compares the computed SHA-256 checksum of a file with a given checksum. 
       Returns true if they match, false otherwise. */
    bool compareChecksum(const std::string& filePath, const std::string* givenChecksum);

    /* Computes the MD5 checksum of a given file and stores it in 'str'. 
       Returns true if successful, false if an error occurs (e.g., file not found). */
    static bool computeChecksum_md(const std::string& filePath, std::string* str);
};

#endif // CHECKSUM_HPP
