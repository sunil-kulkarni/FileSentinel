#include "checksum.hpp"

Checksum::Checksum(Config *user_config) {
  *config = *user_config;
}

//function to compute the SHA-256 checksum of a given file
bool Checksum::computeChecksum_sha(const std::string &filePath, std::string *str) {
  //open the file in binary mode
  std::ifstream file(filePath, std::ios::binary);
  if (!file) {
    return false; //return false if file can't be opened
  }

  //create a new OpenSSL digest context
  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  if (!mdctx) {
    return false; //return false if context creation fails
  }

  //select the SHA-256 hashing algorithm
  const EVP_MD *md = EVP_sha256();
  if (EVP_DigestInit_ex(mdctx, md, nullptr) != 1) {
    EVP_MD_CTX_free(mdctx);
    return false; //return false if digest initialization fails
  }

  //read file in chunks and update the hash computation
  char buffer[4096];
  while (file.read(buffer, sizeof(buffer))) {
    if (EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
      EVP_MD_CTX_free(mdctx);
      return false; //return false if updating digest fails
    }
  }
  EVP_DigestUpdate(mdctx, buffer, file.gcount()); //handle the last read portion

  //finalize the hash computation
  unsigned char hash[EVP_MAX_MD_SIZE];
  unsigned int hashLen;
  if (EVP_DigestFinal_ex(mdctx, hash, &hashLen) != 1) {
    EVP_MD_CTX_free(mdctx);
    return false; //return false if finalizing digest fails
  }

  //free the digest context
  EVP_MD_CTX_free(mdctx);

  //convert hash to a hexadecimal string
  std::ostringstream result;
  for (unsigned int i = 0; i < hashLen; ++i) {
    result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
  }
  *str = result.str(); //store the computed hash in the provided string pointer

  return true; //return true indicating successful checksum computation
}

//function to compute the MD5 checksum of a given file
bool Checksum::computeChecksum_md(const std::string &filePath, std::string *str) {
  //open the file in binary mode
  std::ifstream file(filePath, std::ios::binary);
  if (!file) {
    return false; //return false if file can't be opened
  }

  //create a new OpenSSL digest context
  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  if (!mdctx) {
    return false; //return false if context creation fails
  }

  //select the MD5 hashing algorithm
  const EVP_MD *md = EVP_md5();
  if (EVP_DigestInit_ex(mdctx, md, nullptr) != 1) {
    EVP_MD_CTX_free(mdctx);
    return false; //return false if digest initialization fails
  }

  //read file in chunks and update the hash computation
  char buffer[4096];
  while (file.read(buffer, sizeof(buffer))) {
    if (EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
      EVP_MD_CTX_free(mdctx);
      return false; //return false if updating digest fails
    }
  }
  EVP_DigestUpdate(mdctx, buffer, file.gcount()); //handle the last read portion

  //finalize the hash computation
  unsigned char hash[EVP_MAX_MD_SIZE];
  unsigned int hashLen;
  if (EVP_DigestFinal_ex(mdctx, hash, &hashLen) != 1) {
    EVP_MD_CTX_free(mdctx);
    return false; //return false if finalizing digest fails
  }

  //free the digest context
  EVP_MD_CTX_free(mdctx);

  //convert hash to a hexadecimal string
  std::ostringstream result;
  for (unsigned int i = 0; i < hashLen; ++i) {
    result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
  }
  *str = result.str(); //store the computed hash in the provided string pointer

  return true; //return true indicating successful checksum computation
}

//Reads the string from filepath and returns the string
bool none(const std::string &filePath, std::string *str) {
  //open the file in binary mode
  std::ifstream file(filePath, std::ios::binary);

  //check if the file was successfully opened
  if (!file) {
    return false; //return false if the file can't be opened
  }

  //read the file contents into a stringstream
  std::ostringstream result;
  result << file.rdbuf(); //read the entire file into the stringstream

  //convert the file contents to a string and store it in the provided string pointer
  *str = result.str();

  //return true indicating successful checksum computation (here it's just the file content as string)
  return true;
}

// Function to compare a given checksum with the computed SHA-256 checksum of a file
bool Checksum::compareChecksum(const std::string& filePath, const std::string* givenChecksum) {
  std::string computedChecksum;
  return computeChecksum_sha(filePath, &computedChecksum) && computedChecksum == *givenChecksum;
}


Checksum::~Checksum() {}
