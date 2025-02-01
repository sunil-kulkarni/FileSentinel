#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <filesystem>
#include <sqlite3.h>

class Database {
private:
    sqlite3* db;

    void initDB();

public:
    //Constructor & Destructor
    explicit Database(const std::string& dbPath = "checksums.db");
    ~Database();

    //Database operations
    int saveData(const std::string& filePath, const std::string& hash, const std::string& timestamp);
    void retrieveDataByID(int id);
    void retrieveDataByPath(const std::filesystem::path& path);
};

#endif //DATABASE_HPP
