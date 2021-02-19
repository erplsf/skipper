#include "calc.hpp"
#include <cmath>
#include <units/math.h>
#include <units/physical/si/derived/speed.h>

using namespace units;

HohmannTransferParameters::HohmannTransferParameters(GravitationalParameter auto mu_1, GravitationalParameter auto mu_2,
                                                     Length auto r_1, Length auto r_2) :
        mu_1(mu_1),
        mu_2(mu_2),
        r_1(r_1),
        r_2(r_2) {}

Speed auto HohmannTransferParameters::dV_apo() const {
    return units::sqrt(mu_1 / r_1) *
           (units::sqrt((2 * r_2 / r_1) / (1 + r_2 / r_1)) - 1);
}
