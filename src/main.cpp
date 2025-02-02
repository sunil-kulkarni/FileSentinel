#include "checksum/checksum.hpp"
#include "config/config.hpp"
#include "database/database.hpp"
#include <cstdlib>
#include <iostream>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::seconds

#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int req() {
    try {
        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "3001");

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::string message = "Hello, Server!";
        boost::asio::write(socket, boost::asio::buffer(message));

        char data[512];
        size_t length = socket.read_some(boost::asio::buffer(data));
        std::cout << "Received from server: " << std::string(data, length) << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
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
      req()
      cs.compute_checksum(p, &checksum);
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(config.get_interval()));
  }
  
}
