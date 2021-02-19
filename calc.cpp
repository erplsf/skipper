#pragma once

#include <units/physical/si/derived/speed.h>
#include <units/physical/si/si.h>

#include <units/concepts.h>
#include <units/math.h> // NOLINT(modernize-deprecated-headers)

using namespace units;
using namespace units::physical;

// coherent unit must apply to the system rules (in this case SI)
struct gravitational_parameter_unit : unit<gravitational_parameter_unit> {
};

// new derived dimensions
struct dim_gravitational_parameter
        : derived_dimension<dim_gravitational_parameter, gravitational_parameter_unit,
                exponent<si::dim_length, 3>, exponent<si::dim_time, -2>> {
};

// a quantity of our dimension
template<UnitOf <dim_gravitational_parameter> U, QuantityValue Rep = double>
using gravitational_parameter = quantity<dim_gravitational_parameter, U, Rep>;

// a concept matching the above quantity
template<typename T>
concept GravitationalParameter = QuantityOf<T, dim_gravitational_parameter>;

class HohmannTransferParameters {
public:
    gravitational_parameter<gravitational_parameter_unit> mu_1;
    gravitational_parameter<gravitational_parameter_unit> mu_2;
    si::length<si::metre> r_1;
    si::length<si::metre> r_2;

    // TODO: Add invariants and constructors

    HohmannTransferParameters(GravitationalParameter auto mu_1, GravitationalParameter auto mu_2, Length auto r_1,
                              Length auto r_2) :
            mu_1(mu_1),
            mu_2(mu_2),
            r_1(r_1),
            r_2(r_2) {};

    Speed auto dVPer() const {
        return sqrt(mu_1 / r_1) *
               (sqrt((2 * r_2 / r_1) / (1 + r_2 / r_1)) - 1);
    }

    Speed auto dVApo() const {
        return sqrt(mu_1 / r_2) *
               (1 - sqrt(2 / (1 + r_2 / r_1)));
    }

    Speed auto dVTotal() const {
        return dVPer() + dVApo();
    }
};
