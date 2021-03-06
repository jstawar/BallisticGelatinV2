#ifndef PHYSICS_H
#define PHYSICS_H

#include "Utilities.h"
#include "Settings.h"
#include "Ball.h"

#include <vector>

namespace physics
{

class Collision
{
private:
    // used in internal calculation - not thread safe! (for now it's not a problem)
    // TODD - for threads, most probably each thread will have it's own copy of Collusion class
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

class OptimisedCollisions
{
private:
    const Settings &settings;
    unsigned int numBuckets;
    const double dlX;
    const double dlY;
    std::vector<Ball*> **buckets;
    std::vector<Ball*> ballsPointers;
    void fillBuckets();
    Collision collision;
public:
    OptimisedCollisions(const Settings &settings, unsigned int numBuckets, double maxX, double maxY);
    void addBalls(std::vector<Ball> &balls);
    void nextFrame();
    ~OptimisedCollisions();
};

}

#endif // PHYSICS_H
