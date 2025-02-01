#include <cstdio>
#include <string>
#include <filesystem>
#include <sqlite3.h>

#ifndef DATABASE_HPP
#define DATABASE_HPP

using namespace std;
using namespace std::filesystem;

class Database {
private:
    sqlite3* db;

    void initDB();

public:
    //Constructor & Destructor
    Database(const path&);
    ~Database();

    //Database operations
    int saveData(const path&, const string&, const string&);
    void retrieveDataByID(int id, path *, string *, string *);
    int retrieveDataByPath(const path&, string *, string *);
};

#endif
