#include "checksum.hpp"

// Function to compute the SHA-256 checksum of a given file
bool Checksum::computeChecksum_sha(const std::string &filePath, std::string *str) {
    // Open the file in binary mode
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        return false; // Return false if file can't be opened
    }

    // Create a new OpenSSL digest context
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        return false; // Return false if context creation fails
    }

    // Select the SHA-256 hashing algorithm
    const EVP_MD *md = EVP_sha256();
    if (EVP_DigestInit_ex(mdctx, md, nullptr) != 1) {
        EVP_MD_CTX_free(mdctx);
        return false; // Return false if digest initialization fails
    }

    // Read file in chunks and update the hash computation
    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        if (EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
            EVP_MD_CTX_free(mdctx);
            return false; // Return false if updating digest fails
        }
    }
    EVP_DigestUpdate(mdctx, buffer, file.gcount()); // Handle the last read portion

    // Finalize the hash computation
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;
    if (EVP_DigestFinal_ex(mdctx, hash, &hashLen) != 1) {
        EVP_MD_CTX_free(mdctx);
        return false; // Return false if finalizing digest fails
    }

    // Free the digest context
    EVP_MD_CTX_free(mdctx);

    // Convert hash to a hexadecimal string
    std::ostringstream result;
    for (unsigned int i = 0; i < hashLen; ++i) {
        result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    *str = result.str(); // Store the computed hash in the provided string pointer

    return true; // Return true indicating successful checksum computation
}

// Function to compare a given checksum with the computed SHA-256 checksum of a file
bool Checksum::compareChecksum(const std::string& filePath, const std::string* givenChecksum) {
    std::string computedChecksum;
    return computeChecksum_sha(filePath, &computedChecksum) && computedChecksum == *givenChecksum;
}

// Function to compute the MD5 checksum of a given file
bool Checksum::computeChecksum_md(const std::string &filePath, std::string *str) {
    // Open the file in binary mode
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        return false; // Return false if file can't be opened
    }

    // Create a new OpenSSL digest context
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        return false; // Return false if context creation fails
    }

    // Select the MD5 hashing algorithm
    const EVP_MD *md = EVP_md5();
    if (EVP_DigestInit_ex(mdctx, md, nullptr) != 1) {
        EVP_MD_CTX_free(mdctx);
        return false; // Return false if digest initialization fails
    }

    // Read file in chunks and update the hash computation
    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        if (EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
            EVP_MD_CTX_free(mdctx);
            return false; // Return false if updating digest fails
        }
    }
    EVP_DigestUpdate(mdctx, buffer, file.gcount()); // Handle the last read portion

    // Finalize the hash computation
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;
    if (EVP_DigestFinal_ex(mdctx, hash, &hashLen) != 1) {
        EVP_MD_CTX_free(mdctx);
        return false; // Return false if finalizing digest fails
    }

    // Free the digest context
    EVP_MD_CTX_free(mdctx);

    // Convert hash to a hexadecimal string
    std::ostringstream result;
    for (unsigned int i = 0; i < hashLen; ++i) {
        result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    *str = result.str(); // Store the computed hash in the provided string pointer

    return true; // Return true indicating successful checksum computation
}
