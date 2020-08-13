#ifndef BALL_H
#define BALL_H

#include "Utilities.h"

class Ball
{
protected:
    utilities::Vectors vectors;
    double mass;
    double radius;
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
    const utilities::VectorXY &getForce() const
    {
        return vectors.force;
    }
    double getRadius() const
    {
        return radius;
    }
};

#endif // BALL_H
