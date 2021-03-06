#ifndef SHIELD_H
#define SHIELD_H

#include "Utilities.h"
#include "Ball.h"
#include "Settings.h"
#include "SpringConnections.h"

#include <vector>

class Shield
{
private:
    const Settings &settings;
    // TODO - please make me const - thou shall NOT alter the container after fully initialized! altering the elements is ok but NO shuffling!!!
    std::vector<Ball> balls;
    SpringConnections *springConnections;
    void initialize();
public:
    Shield(const Settings &settings);
    const std::vector<Ball> &getBalls() const
    {
        return balls;
    }
    std::vector<Ball> &getBalls()
    {
        return balls;
    }
    const SpringConnections *getSpringConnections() const
    {
        return springConnections;
    }
    void nextFrame();
};

#endif // SHIELD_H
