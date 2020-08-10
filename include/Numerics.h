#ifndef NUMERICS_H
#define NUMERICS_H

#include "Utilities.h"

#include <map>

namespace numerics
{

double distanceSquared(utilities::VectorXY const &vec1, utilities::VectorXY  const &vec2);
double distance(utilities::VectorXY  const &vec1, utilities::VectorXY  const &vec2);
// TODO template me - useful for the future
// TODO and then override operators for Color
utilities::Color linearInterpolation(std::map<double, utilities::Color> const &data, double point);

}

#endif // NUMERICS_H
