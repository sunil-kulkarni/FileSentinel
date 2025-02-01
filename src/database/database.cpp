#include "database.hpp"
#include <iostream>

void Database::initDB() {
    const char* createTableSQL =
        "CREATE TABLE IF NOT EXISTS checksums ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "filepath TEXT UNIQUE, "
        "hash TEXT, "
        "timestamp TEXT);";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

Database::Database(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database" << std::endl;
    }
    initDB();
}

Database::~Database() {
    sqlite3_close(db);
}

int Database::saveData(const std::string& filePath, const std::string& hash, const std::string& timestamp) {
    const char* insertSQL =
        "INSERT INTO checksums (filepath, hash, timestamp) VALUES (?, ?, ?) "
        "ON CONFLICT(filepath) DO UPDATE SET hash = excluded.hash, timestamp = excluded.timestamp "
        "RETURNING id;";
    sqlite3_stmt* stmt;
    int id = -1;

    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, filePath.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, hash.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, timestamp.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            id = sqlite3_column_int(stmt, 0);
        }
    } else {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return id;
}

void Database::retrieveDataByID(int id) {
    const char* selectSQL = "SELECT filepath, hash, timestamp FROM checksums WHERE id = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* filePath = (const char*)sqlite3_column_text(stmt, 0);
            const char* hash = (const char*)sqlite3_column_text(stmt, 1);
            const char* timestamp = (const char*)sqlite3_column_text(stmt, 2);

            std::cout << "File Path: " << filePath << std::endl;
            std::cout << "Hash: " << hash << std::endl;
            std::cout << "Timestamp: " << timestamp << std::endl;
        } else {
            std::cout << "No record found with ID: " << id << std::endl;
        }
    } else {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}