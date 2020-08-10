#include "Numerics.h"

namespace numerics
{

double distanceSquared(utilities::VectorXY const &vec1, utilities::VectorXY const &vec2)
{
    return (vec2.getX() - vec1.getX()) * (vec2.getX() - vec1.getX()) + (vec2.getY() - vec1.getY()) * (vec2.getY() - vec1.getY());
}

double distance(utilities::VectorXY const &vec1, utilities::VectorXY const &vec2)
{
    return sqrt( distanceSquared(vec1, vec2) );
}

utilities::Color linearInterpolation(std::map<double, utilities::Color> const &data, double point)
{
    std::map<double, utilities::Color>::const_iterator it = data.upper_bound(point);
    // if outside - return edge
    if( it == data.end() )
    {
        return (--it)->second;
    }
    if( it == data.begin() )
    {
        return it->second;
    }

    // linear interpolation part
    std::map<double, utilities::Color>::const_iterator it_1 = it;
    --it_1;

    const double delta = ( point - it_1->first ) / (it->first - it_1->first);
    double redVal =  it_1->second.getRed() + delta * (it->second.getRed() - it_1->second.getRed());
    double greenVal = it_1->second.getGreen() + delta * (it->second.getGreen() - it_1->second.getGreen());
    double blueVal = it_1->second.getBlue() + delta * (it->second.getBlue() - it_1->second.getBlue());

    return utilities::Color(redVal, greenVal, blueVal);
}

}
