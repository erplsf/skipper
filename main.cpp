#include <krpc/services/krpc.hpp>
#include <iostream>
#include <krpc.hpp>

int main() {
  try {
    auto conn = krpc::connect();
    krpc::services::KRPC krpc(&conn);
    std::cout << "Connected to kRPC server version: "
              << krpc.get_status().version() << std::endl;
  } catch (...) {
    std::cout << "Couldn't connect to the server" << std::endl;
  };
}
