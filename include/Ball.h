#ifndef BALL_H
#define BALL_H

#include "Utilities.h"

class Ball
{
protected:
    utilities::Vectors vectors;
    double mass;
    double radius;
    // TODO - color of a ball? different radius for display and collision
    // maybe a blend of all the connections and if no connections then = 1?
public:
    Ball(utilities::Vectors vectors, double mass, double radius)
        : vectors(vectors),
          mass(mass),
          radius(radius)
    {

    }
    utilities::Vectors &getVectors()
    {
        return vectors;
    }
    double getMass() const
    {
        return mass;
    }
    const utilities::VectorXY &getPosition() const
    {
        return vectors.position;
    }
    const utilities::VectorXY &getVelocity() const
    {
        return vectors.velocity;
    }
    const utilities::VectorXY &getAcceleration() const
    {
        return vectors.acceleration;
    }
    double getRadius() const
    {
        return radius;
    }
};

#endif // BALL_H
