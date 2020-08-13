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
    Shield *shield;
    Bullet *bullet;
    physics::Collision collisions;
    unsigned int frameNum;
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
    ~Simulation()
    {
        delete bullet;
    }
};

#endif // SIMULATION_H
