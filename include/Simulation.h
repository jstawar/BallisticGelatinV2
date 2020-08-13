#ifndef SIMULATION_H
#define SIMULATION_H

#include "Shield.h"
#include "Settings.h"
#include "Bullet.h"
#include "Physics.h"

class Simulation
{
private:
    Shield *shield;
    Bullet *bullet;
    physics::Collision collisions;
    bool frameForBalls; // 0 or 1
    unsigned int frameNum;
public:
    Simulation(const Settings &settings);
    void nextFrame();
    const Shield *getShield() const
    {
        return shield;
    }
    bool getFrame() const
    {
        return frameForBalls;
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
