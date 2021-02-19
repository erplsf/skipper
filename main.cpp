#include <cmath>
#include <iostream>
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>
#include <units/physical/si/derived/speed.h>
#include <units/format.h>
#include <units/quantity_io.h>
#include "calc.cpp"

int main() {
    using namespace units;
    using namespace si::literals;
    using namespace units::physical::si::unit_constants;

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

    auto vessel = sc.active_vessel();
    Length auto periapsis = si::length<si::metre>(vessel.orbit().periapsis());
    auto kerbin = sc.bodies().at("Kerbin");
    GravitationalParameter auto gp = gravitational_parameter<gravitational_parameter_unit>(kerbin.gravitational_parameter());
    auto htp = HohmannTransferParameters(gp,
                                         gp,
                                         periapsis, periapsis + 150_q_km);
    std::cout << fmt::format("members: {}, {}, {}, {}\n", htp.mu_1, htp.mu_2, htp.r_1, htp.r_2);
    std::cout << fmt::format("dV required at Per: {}\n", htp.dVPer());
    std::cout << fmt::format("dV required at Apo: {}\n", htp.dVApo());
    std::cout << fmt::format("dV required total : {}\n", htp.dVTotal());
}
