#ifndef OBJECT_H
#define OBJECT_H

#include "Utilities.h"

#include <cassert>

class IMovableObject
{
protected:
    utilities::Vectors mVectors[2];
    double mMass;
public:
    IMovableObject(utilities::Vectors vectors, double mass)
        : mMass(mass)
    {
        this->mVectors[0] = vectors;
    }
    double getMass() const
    {
        return mMass;
    }
    const utilities::VectorXY &getPosition(bool first) const
    {
        return mVectors[first].position;
    }
    const utilities::VectorXY &getVelocity(bool first) const
    {
        return mVectors[first].velocity;
    }
    const utilities::VectorXY &getForce(bool first) const
    {
        return mVectors[first].force;
    }
    virtual void nextStep() = 0;
    virtual ~IMovableObject()
    {
    }
};

#endif // OBJECT_H
