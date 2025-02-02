#include "checksum/checksum.hpp"
#include "config/config.hpp"
#include "database/database.hpp"
#include <cstdlib>
#include <iostream>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::seconds

#include <curl/curl.h>

void sendRequestToServer(const std::string& serverAddress) {
    if (serverAddress.empty()) {
        std::cerr << "Server address cannot be empty!" << std::endl;
        return;
    }

    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);  // Initialize libcurl
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, serverAddress.c_str());

        // Optional: Follow redirects if any
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Request successfully sent to " << serverAddress << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

using namespace std;
using namespace std::filesystem;

int main(int argc, char *argv[]) {
  Config config;
  config.parse("../config.yaml");
  Database db("database.db");
  Checksum cs(&config);

  path p = "../test_file.txt";
  string checksum;
  cs.compute_checksum(p, &checksum);
  cout << checksum << endl;
  db.saveData(p, checksum, "E");

  while (true) {
    cout << "ittr" << endl;
    string temp;
  /*/cs.compute_checksum(p, &temp);/*/
    if (! cs.compare_checksum(p, &checksum)) {
      /*system("notify-send 'File changed'");*/
      sendRequestToServer("http://127.0.0.1:3001");
      cs.compute_checksum(p, &checksum);
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(config.get_interval()));
  }
  
}
