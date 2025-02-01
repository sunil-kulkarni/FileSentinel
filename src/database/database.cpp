#include "database.hpp"
#include <filesystem>
#include <iostream>

//Method to initialize the database and create the 'checksums' table if it doesn't exist
void Database::initDB() {
    const char* createTableSQL =
        "CREATE TABLE IF NOT EXISTS checksums ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "  //Unique ID for each file entry
        "filepath TEXT UNIQUE, "                  //File path (unique constraint ensures no duplicates)
        "hash TEXT, "                             //Hash of the file (checksum)
        "timestamp TEXT);";                       //Timestamp of last recorded change
    
    char* errMsg = nullptr;
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

//Constructor: Opens the SQLite database and initializes it
Database::Database(const path& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        initDB();  //Ensure the table is set up
    }
}

//Destructor:Closes the database connection
Database::~Database() {
    sqlite3_close(db);
}

//Method to save data (file path, hash and timestamp) into the database
int Database::saveData(const path& filePath, const string& hash, const string& timestamp) {
    const char* insertSQL =
        "INSERT INTO checksums (filepath, hash, timestamp) VALUES (?, ?, ?) "
        "ON CONFLICT(filepath) DO UPDATE SET hash = excluded.hash, timestamp = excluded.timestamp "
        "RETURNING id;";  //Inserts or updates the record and returns its ID
    
    sqlite3_stmt* stmt;
    int id = -1;

    //Prepare the SQL statement
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        //Bind values to placeholders in the SQL query
        sqlite3_bind_text(stmt, 1, filePath.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, hash.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, timestamp.c_str(), -1, SQLITE_STATIC);

        //Execute the statement
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            id = sqlite3_column_int(stmt, 0);  //Retrieve the returned ID
        }
    } else {
        std::cerr << "SQL error (saveData): " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);  //Free the prepared statement
    return id;
}

//Method to retrieve file details from the database using the ID
void Database::retrieveDataByID(int id, path *path, string *hash_, string *timestamp_) {
    const char* selectSQL = "SELECT filepath, hash, timestamp FROM checksums WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);  // Bind the ID to the SQL query

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            //Retrieve values from the result row
            const char* filePath = (const char*)sqlite3_column_text(stmt, 0);
            const char* hash = (const char*)sqlite3_column_text(stmt, 1);
            const char* timestamp = (const char*)sqlite3_column_text(stmt, 2);

            //Print retrieved values
            /*std::cout << "File Path: " << filePath << std::endl;*/
            /*std::cout << "Hash: " << hash << std::endl;*/
            /*std::cout << "Timestamp: " << timestamp << std::endl;*/
            *path = filePath;
            *hash_ = hash;
            *timestamp_ = timestamp;
        } else {
            std::cerr << "No record found with ID: " << id << std::endl;
        }
    } else {
        std::cerr << "SQL error (retrieveDataByID): " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);  //Free the statement
}

//Method to retrieve file details from the database using the file path
int Database::retrieveDataByPath(const path& path, string *hash_, string *timestamp_) {
    const char* selectSQL = "SELECT filepath, hash, timestamp FROM checksums WHERE filepath = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        std::string filePathStr = path.string();  //Convert filesystem path to string
        sqlite3_bind_text(stmt, 1, filePathStr.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            //Retrieve values from the result row
            /*const char* filePath = (const char*)sqlite3_column_text(stmt, 0);*/
            const char* hash = (const char*)sqlite3_column_text(stmt, 1);
            const char* timestamp = (const char*)sqlite3_column_text(stmt, 2);

            //Print retrieved values
            /*std::cout << "File Path: " << filePath << std::endl;*/
            /*std::cout << "Hash: " << hash << std::endl;*/
            /*std::cout << "Timestamp: " << timestamp << std::endl;*/
            *hash_ = hash;
            *timestamp_ = timestamp;

        } else {
            std::cerr << "No record found for path: " << filePathStr << std::endl;
        }
    } else {
        std::cerr << "SQL error (retrieveDataByPath): " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);  //Free the statement
    return 0;
}
