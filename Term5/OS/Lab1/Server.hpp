#pragma once

#include <boost/asio.hpp>
using namespace boost;

class Server {
  asio::io_context context;
  asio::ip::tcp::acceptor acceptor;

public:
  explicit Server(uint16_t port):
  acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {}

  void start() {
    std::cout << "Starting the server..." << std::endl;
    asio::ip::tcp::socket socket(context);
    system::error_code ec;

    while(acceptor.is_open()) {
      acceptor.accept(socket);
      system::error_code ignored_error;
      std::cout << "Writing to the buffer" << std::endl;
      asio::write(socket, asio::buffer("Test"), ignored_error);
    }
  }

  void stop() {
    std::cout << "Server have been stopped" << std::endl;
    acceptor.cancel();
  }
};