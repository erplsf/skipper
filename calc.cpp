#include <cmath>
#include "calc.hpp"

double dV_apo(const double mu, const double r_1, const double r_2) {
  return std::sqrt(mu / r_1) * (std::sqrt((2 * r_2 / r_1) / (1 + r_2 / r_1)) - 1);
}
