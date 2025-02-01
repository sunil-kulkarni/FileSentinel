#include "checksum.hpp"

Checksum::Checksum(Config *user_config) {
    config = user_config;
}

//function to compute the SHA-256 checksum of a given file
bool Checksum::compute_checksum_sha(const path &filepath, string *givenChecksum) {
    ifstream file(filepath, ios::binary);
    if (!file) {
        return false; //return false if the file can't be opened
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

    ostringstream result;
    for (unsigned int i = 0; i < hashLen; ++i) {
        result << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    *givenChecksum = result.str(); //store the computed hash
    return true;
}

//function to compute the MD5 checksum of a given file
bool Checksum::compute_checksum_md(const path &filepath, string *givenChecksum) {
    ifstream file(filepath, ios::binary);
    if (!file) {
        return false;
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        return false;
    }

    const EVP_MD *md = EVP_md5();
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

    ostringstream result;
    for (unsigned int i = 0; i < hashLen; ++i) {
        result << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    *givenChecksum = result.str(); //store the computed hash
    return true;
}

//reads the file and stores its content as a string
bool Checksum::none(const path &filepath, string *givenChecksum) {
    ifstream file(filepath, ios::binary);
    if (!file) {
        return false;
    }

    ostringstream result;
    result << file.rdbuf();
    *givenChecksum = result.str();

    return true;
}

//computes checksum based on the algorithm specified in the config
bool Checksum::compute_checksum(const path &filepath, string *givenChecksum) {
    Algorithm algo = config->get_algorithm();
    switch (algo) {
        case Algorithm::MD5:
            return compute_checksum_md(filepath, givenChecksum);
        case Algorithm::SHA256:
            return compute_checksum_sha(filepath, givenChecksum);
        default:
            return none(filepath, givenChecksum);
    }
}

//function to compare a given checksum with the computed SHA-256 checksum of a file
bool Checksum::compare_checksum(const path &filepath, const string *givenChecksum) {
    string computedChecksum;
    return compute_checksum_sha(filepath, &computedChecksum) && computedChecksum == *givenChecksum;
}

Checksum::~Checksum() {}