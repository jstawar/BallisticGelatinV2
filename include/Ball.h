#ifndef BALL_H
#define BALL_H

#include "Utilities.h"

class Ball
{
protected:
    utilities::Vectors vectors[2];
    double mass;
    double radius;
public:
    Ball(utilities::Vectors vectors, double mass, double radius)
        : mass(mass),
          radius(radius)
    {
        this->vectors[0] = vectors;
    }
    utilities::Vectors &getVectors(bool frame)
    {
        return vectors[frame];
    }
    double getMass() const
    {
        return mass;
    }
    const utilities::VectorXY &getPosition(bool frame) const
    {
        return vectors[frame].position;
    }
    const utilities::VectorXY &getVelocity(bool frame) const
    {
        return vectors[frame].velocity;
    }
    const utilities::VectorXY &getForce(bool frame) const
    {
        return vectors[frame].force;
    }
    double getRadius() const
    {
        return radius;
    }
};

#endif // BALL_H
