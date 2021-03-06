#ifndef BULLET_H
#define BULLET_H

#include "Ball.h"
#include "Settings.h"
#include "Physics.h"
#include "SpringConnections.h"

#include <vector>

class Bullet
{
protected:
    const Settings &settings;
    const std::string type;
    // TODO - please make me const - thou shall NOT alter the container after fully initialized! altering the elements is ok but NO shuffling!!!
    std::vector<Ball> balls;
    double mass; // joint mass of all constituents
    utilities::VectorXY velocity; // average velocity of all constituents
    SpringConnections *springConnections;
    virtual void initialize() = 0;
public:
    Bullet(const Settings &settings, const std::string &type)
        : settings(settings),
          type(type),
          springConnections(nullptr)
    {

    }
    virtual void nextFrame();
    const std::string &getType() const
    {
        return type;
    }
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
        delete springConnections;
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
    const SpringConnections *getSpringConnections() const
    {
        return springConnections;
    }
};

class BulletBall: public Bullet
{
public:
    BulletBall(const Settings &settings);
    virtual void initialize() override;
};

#endif // BULLET_H
