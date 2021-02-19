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

    krpc::Client conn;

    try {
        conn = krpc::connect("smok");
    } catch (const std::system_error &e) {
        std::cout
                << "Couldn't connect to the server, got the following error code: "
                << std::endl
                << '\t' << e.what() << std::endl
                << "Exiting." << std::endl;
        exit(1);
    }

//    krpc::services::KRPC krpc(&conn);
//    std::cout << "Connected to kRPC server version: "
//              << krpc.get_status().version() << std::endl;

    krpc::services::SpaceCenter sc(&conn);

    auto vessel = sc.active_vessel();
    Length auto periapsis = si::length<si::metre>(vessel.orbit().periapsis());
    auto celestialBody = vessel.orbit().body();
    GravitationalParameter auto gp = gravitational_parameter<metre_cub_per_second_sq>(celestialBody.gravitational_parameter());
    auto ht = HohmannTransfer(gp,
                              gp,
                              periapsis, periapsis + 200_q_km);
    std::cout << fmt::format("Orbiting: ", celestialBody.name());
    std::cout << fmt::format("r_1: {}\n", ht.r_1);
    std::cout << fmt::format("r_2: {}\n", ht.r_2);
    std::cout << fmt::format("dV required at Per: {}\n", ht.dV_P);
    std::cout << fmt::format("dV required at Apo: {}\n", ht.dV_A);
    std::cout << fmt::format("dV required total : {}\n", ht.dV_T);
}
