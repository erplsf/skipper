#ifndef __CALC_H_
#define __CALC_H_

#include <units/physical/si/derived/speed.h>
#include <units/concepts.h>
#include <units/math.h> // NOLINT(modernize-deprecated-headers)

using namespace units;
using namespace units::physical;

// coherent unit must apply to the system rules (in this case SI)
struct metre_cub_per_second_sq : unit<metre_cub_per_second_sq> {
};

// new derived dimensions
struct dim_gravitational_parameter
        : derived_dimension<dim_gravitational_parameter, metre_cub_per_second_sq,
                exponent<si::dim_length, 3>, exponent<si::dim_time, -2>> {
};

// a quantity of our dimension
template<UnitOf <dim_gravitational_parameter> U, QuantityValue Rep = double>
using gravitational_parameter = quantity<dim_gravitational_parameter, U, Rep>;

// a concept matching the above quantity
template<typename T>
concept GravitationalParameter = QuantityOf<T, dim_gravitational_parameter>;

class HohmannTransfer {
    const gravitational_parameter<metre_cub_per_second_sq> mu_1;
    const gravitational_parameter<metre_cub_per_second_sq> mu_2;

    Speed auto dVPer() const {
        return units::sqrt(mu_1 / r_1) *
               (units::sqrt((2 * r_2 / r_1) / (1 + r_2 / r_1)) - 1);
    }

    Speed auto dVApo() const {
        return units::sqrt(mu_1 / r_2) *
               (1 - units::sqrt(2 / (1 + r_2 / r_1)));
    }

public:
    const si::length<si::metre> r_1;
    const si::length<si::metre> r_2;
    const si::speed<si::metre_per_second> dV_A;
    const si::speed<si::metre_per_second> dV_P;
    const si::speed<si::metre_per_second> dV_T;

    HohmannTransfer(GravitationalParameter auto mu_1, GravitationalParameter auto mu_2, Length auto r_1,
                    Length auto r_2) :
            mu_1(mu_1),
            mu_2(mu_2),
            r_1(r_1),
            r_2(r_2),
            dV_A(dVApo()),
            dV_P(dVPer()),
            dV_T(dV_A + dV_P) {};
};

#endif