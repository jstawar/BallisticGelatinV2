#ifndef BULLET_H
#define BULLET_H

#include "Ball.h"
#include "Settings.h"
#include "Physics.h"

#include <vector>

class Bullet
{
protected:
    const Settings &settings;
    std::vector<Ball> balls;
    double mass; // joint mass of all constituents
    utilities::VectorXY velocity; // average velocity of all constituents
    utilities::VectorXY k1v, k2v, k3v, k4v, k1x, k2x, k3x, k4x; // very non-thread safe (not a problem for now)
public:
    Bullet(const Settings &settings)
        : settings(settings)
    {

    }
    virtual void nextFrame() = 0;
    virtual void initialize() = 0;
    const std::vector<Ball> &getBalls() const
    {
        return balls;
    }
    std::vector<Ball> &getBalls()
    {
        return balls;
    }
    virtual ~Bullet()
    {
        // so far nothing allocated
    }
    double getMass() const
    {
        return mass;
    }
    void calcVelocity()
    {
        velocity.clear();
        for(unsigned int i = 0 ; i < balls.size() ; i++)
        {
            velocity.translate(balls[i].getVelocity());
        }
        double scale = balls.size();
        velocity.scale(utilities::VectorXY(1.0/scale, 1.0/scale));
    }
    const utilities::VectorXY &getVelocity() const
    {
        return velocity;
    }
    double getEnergy() const
    {
        return mass * velocity.normSquared() / 2.0;
    }
};

class BulletBall: public Bullet
{
public:
    BulletBall(const Settings &settings);
    virtual void initialize() override;
    virtual void nextFrame() override;
};

#endif // BULLET_H
