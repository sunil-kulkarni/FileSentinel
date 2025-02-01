#include "checksum.hpp"

bool Checksum::computeChecksum(const std::string &filePath, std::string *str) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        return false;
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        return false;
    }

    const EVP_MD *md = EVP_sha256();
    if (EVP_DigestInit_ex(mdctx, md, nullptr) != 1) {
        EVP_MD_CTX_free(mdctx);
        return false;
    }

    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        if (EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
            EVP_MD_CTX_free(mdctx);
            return false;
        }
    }
    EVP_DigestUpdate(mdctx, buffer, file.gcount());

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;
    if (EVP_DigestFinal_ex(mdctx, hash, &hashLen) != 1) {
        EVP_MD_CTX_free(mdctx);
        return false;
    }

    EVP_MD_CTX_free(mdctx);

    std::ostringstream result;
    for (unsigned int i = 0; i < hashLen; ++i) {
        result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    *str = result.str();

    return true;
}


bool compareChecksum(const std::string& filePath, const std::string& givenChecksum) {
    std::string computedChecksum;
    Checksum::computeChecksum(filePath, &computedChecksum);

    if (computedChecksum == givenChecksum) {
        return true;
    } else {
        return false;
    }
}