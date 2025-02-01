#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <sqlite3.h>

class Database {
private:
    sqlite3* db;

    void initDB();

public:
    // Constructor
    Database(const std::string& dbPath = "checksums.db");

    ~Database();
    int saveData(const std::string& filePath, const std::string& hash, const std::string& timestamp);

    void retrieveDataByID(int id);
};

#endif