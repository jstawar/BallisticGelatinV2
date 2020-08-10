#include "SpringConnections.h"
#include "Numerics.h"

#include <iostream>

// TODO - make it more generic for different cristalization methods

SpringConnections::SpringConnections(const Settings &settings, const std::vector<Ball> &balls)
    : settings(settings),
      balls(balls)
{
    addConnections();
}

void SpringConnections::addConnections()
{
    addRightConnections();
    addLeftUpConnections();
    addUpConnections();
    addRightUpConnections();
}

void SpringConnections::addRightConnections()
{
    for(unsigned int i = 0 ; i < settings.simParams.numYShield ; i++)
    {
        for(unsigned int j = 0 ; j < settings.simParams.numXShield - 1 ; j++)
        {
            unsigned int current = settings.simParams.numXShield * i + j;
            double restLength = numerics::distance(current, current+1);
            SpringConnectionPair connectionPair( balls[current], balls[current+1], restLength, true);
            connectionPairs[Right].push_back(connectionPair);
        }
    }
}

void SpringConnections::addLeftUpConnections()
{
    for(unsigned int i = 0 ; i < settings.simParams.numYShield - 1 ; i++)
    {
        for(unsigned int j = 1 ; j < settings.simParams.numXShield; j++)
        {
            unsigned int current = settings.simParams.numXShield * i + j;
            double restLength = numerics::distance(current, current+settings.simParams.numXShield-1);
            SpringConnectionPair connectionPair( balls[current], balls[current+settings.simParams.numXShield-1], restLength, true);
            connectionPairs[LeftUp].push_back(connectionPair);
        }
    }
}

void SpringConnections::addUpConnections()
{
    for(unsigned int i = 0 ; i < settings.simParams.numYShield - 1 ; i++)
    {
        for(unsigned int j = 0 ; j < settings.simParams.numXShield ; j++)
        {
            unsigned int current = settings.simParams.numXShield * i + j;
            double restLength = numerics::distance(current, current+settings.simParams.numXShield);
            SpringConnectionPair connectionPair( balls[current], balls[current+settings.simParams.numXShield], restLength, true);
            connectionPairs[Up].push_back(connectionPair);
        }
    }
}

void SpringConnections::addRightUpConnections()
{
    for(unsigned int i = 0 ; i < settings.simParams.numYShield - 1 ; i++)
    {
        for(unsigned int j = 0 ; j < settings.simParams.numXShield - 1; j++)
        {
            unsigned int current = settings.simParams.numXShield * i + j;
            double restLength = numerics::distance(current, current+settings.simParams.numXShield+1);
            SpringConnectionPair connectionPair( balls[current], balls[current+settings.simParams.numXShield+1], restLength, true);
            connectionPairs[RightUp].push_back(connectionPair);
        }
    }
}
