#include "calc.hpp"
#include <cmath>
#include <iostream>
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

#include <units/physical/si/derived/speed.h>

using namespace units::physical::si;

int main() {
    krpc::Client conn;

    try {
        conn = krpc::connect("skipper");
    } catch (const std::system_error &e) {
        std::cout
                << "Couldn't connect to the server, got the following error code: "
                << std::endl
                << '\t' << e.what() << std::endl
                << "Exiting." << std::endl;
        exit(1);
    }

    krpc::services::KRPC krpc(&conn);
    std::cout << "Connected to kRPC server version: "
              << krpc.get_status().version() << std::endl;

    krpc::services::SpaceCenter sc(&conn);

    auto sun = sc.bodies().at("Sun");
    auto kerbin = sc.bodies().at("Kerbin");
    GravitationalParameter auto gp = gravitational_parameter<gravitational_parameter_unit>(sun.gravitational_parameter());
    auto htp = HohmannTransferParameters(gp,
                                         gp,
                                         1000_q_km, 2000_q_km);
    const Speed auto dV = htp.dV_apo();
    std::cout << dV << std::endl;
}
