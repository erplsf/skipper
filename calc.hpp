#ifndef __CALC_HPP__
#define __CALC_HPP__

#include <units/physical/si/derived/speed.h>
#include <units/concepts.h>

using namespace units;
using namespace units::physical;

using m = si::metre;

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
    gravitational_parameter<gravitational_parameter_unit> mu_1;
    gravitational_parameter<gravitational_parameter_unit> mu_2;
    si::length<m> r_1;
    si::length<m> r_2;

    // TODO: Add invariants and constructors
public:
    HohmannTransferParameters(GravitationalParameter auto mu_1, GravitationalParameter auto mu_2, Length auto r_1,
                              Length auto r_2);

    [[nodiscard]] Speed auto dV_apo() const;
};

#endif
