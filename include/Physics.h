#ifndef PHYSICS_H
#define PHYSICS_H

#include "Utilities.h"
#include "Settings.h"
#include "Ball.h"

namespace physics
{

utilities::VectorXY gravityForce(double gAcc, double mass);
utilities::VectorXY springForce(double k, double mass, double length, double restLength);

class Collision
{
private:
    // used in internal calculation - not thread safe! (for now it's not a problem)
    double x21, y21, r12, d, m21, vx21, vy21, gammav, gammaxy;
    double dgamma, dr, alpha, a, dvx2;
    const double pi2;
public:
    Collision()
     : pi2(2.0*acos(-1.0E0)) // TODO maybe move to some numerics?
    {
    }
    void groundCheck(Ball &ball);
    void collision(Ball &ball1, Ball &ball2);
};

}

#endif // PHYSICS_H
