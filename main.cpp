#include <iostream>
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <signal.h>
#include "principia.hpp"

int main() {
  krpc::Client conn;

  try {
    conn = krpc::connect("skipper");
  } catch (const std::system_error &e) {
    std::cout
        << "Couldn't connect to the server, got the following error code: "
        << std::endl
        << '\t' << e.what() << std::endl
        << "Exiting." << std ::endl;
    exit(1);
  }

  krpc::services::KRPC krpc(&conn);
  std::cout << "Connected to kRPC server version: "
            << krpc.get_status().version() << std::endl;

  krpc::services::Principia prp(&conn);
  std::cout << "Is Principia available -> " << prp.available() << std::endl;
}
