#include <iostream>
#include <filesystem>
#include <fstream>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
#include "../config/config.hpp"

#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP

class Checksum {
private:
  Config *config;

public:
  Checksum(Config *); //constructor

  //Computes the SHA-256 checksum of a given file and stores it in 'str'. 
  //Returns true if successful, false if an error occurs (e.g., file not found)
  bool computeChecksum_sha(const std::string& filePath, std::string* str);

  //Computes the MD5 checksum of a given file and stores it in 'str'. 
  //Returns true if successful, false if an error occurs (e.g., file not found)
  bool computeChecksum_md(const std::string& filePath, std::string* str);

  //Reads the string from filepath and returns the string
  bool none(const std::string &filePath, std::string *str);

  //Compares the computed SHA-256 checksum of a file with a given checksum. 
  //Returns true if they match, false otherwise
  bool compareChecksum(const std::string& filePath, const std::string* givenChecksum);

  //destructor
  ~Checksum();
};

#endif // CHECKSUM_HPP
