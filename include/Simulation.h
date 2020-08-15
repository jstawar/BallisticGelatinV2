#ifndef SIMULATION_H
#define SIMULATION_H

#include "Shield.h"
#include "Settings.h"
#include "Bullet.h"
#include "Bullets.h"
#include "Physics.h"

class Simulation
{
private:
    const Settings &settings;
    Shield *shield;
    Bullet *bullet;
    physics::Collision collisions;
    physics::OptimisedCollisions optimisedCollisions;
    unsigned int frameNum;
    unsigned int totalBalls;
    double currentTime;
    void countActiveConnections();
public:
    Simulation(const Settings &settings);
    void nextFrame();
    const Shield *getShield() const
    {
        return shield;
    }
    const Bullet *getBullet() const
    {
        return bullet;
    }
    unsigned int getFrameNum() const
    {
        return frameNum;
    }
    unsigned int getTotalBalls() const
    {
        return totalBalls;
    }
    unsigned int getNumActiveConnections() const
    {
        unsigned int active = 0;
        if( shield && shield->getSpringConnections() )
        {
            active += shield->getSpringConnections()->getActiveConnections();
        }
        if( bullet && bullet->getSpringConnections() )
        {
            active += bullet->getSpringConnections()->getActiveConnections();
        }
        return active;
    }
    double getCurrentTime() const
    {
        return currentTime;
    }
    ~Simulation()
    {
        delete bullet;
        delete shield;
    }
};

#endif // SIMULATION_H
