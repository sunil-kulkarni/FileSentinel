#include <iostream>
#include <filesystem>
#include <fstream>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
#include "../config/config.hpp"

using namespace std;
using namespace std::filesystem;

#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP

class Checksum {
private:
  Config *config;
  
  //Computes the SHA-256 checksum of a given file and stores it in 'str'. 
  //Returns true if successful, false if an error occurs (e.g., file not found)
  bool compute_checksum_sha(const path&, string *);

  //Computes the MD5 checksum of a given file and stores it in 'str'. 
  //Returns true if successful, false if an error occurs (e.g., file not found)
  bool compute_checksum_md(const path&, string *);

  //Reads the string from filepath and returns the string
  bool none(const path&, string *);

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
  //computes checksum based on algo in config
  bool compute_checksum(const path&, string *);

};

#endif
