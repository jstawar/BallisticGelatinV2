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
            double breakLengthUp = restLength * settings.simParams.extensionBreakCoefficient;
            double breakLengthDown = restLength * settings.simParams.compressionBreakCoefficient;
            SpringConnectionPair connectionPair( balls[current], balls[current+1], restLength, true, breakLengthUp, breakLengthDown);
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
            double breakLengthUp = restLength * settings.simParams.extensionBreakCoefficient;
            double breakLengthDown = restLength * settings.simParams.compressionBreakCoefficient;
            SpringConnectionPair connectionPair( balls[current], balls[current+settings.simParams.numXShield-1], restLength, true, breakLengthUp, breakLengthDown);
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
            double breakLengthUp = restLength * settings.simParams.extensionBreakCoefficient;
            double breakLengthDown = restLength * settings.simParams.compressionBreakCoefficient;
            SpringConnectionPair connectionPair( balls[current], balls[current+settings.simParams.numXShield], restLength, true, breakLengthUp, breakLengthDown);
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
            double breakLengthUp = restLength * settings.simParams.extensionBreakCoefficient;
            double breakLengthDown = restLength * settings.simParams.compressionBreakCoefficient;
            SpringConnectionPair connectionPair( balls[current], balls[current+settings.simParams.numXShield+1], restLength, true, breakLengthUp, breakLengthDown);
            connectionPairs[RightUp].push_back(connectionPair);
        }
    }
}

void SpringConnections::nextFrame(bool frame)
{
    for(std::map<SpringConnections::ConnectionType, std::vector<SpringConnections::SpringConnectionPair> >::iterator itOuter = connectionPairs.begin() ; itOuter != connectionPairs.end() ; ++itOuter)
    {
        std::vector<SpringConnectionPair>::iterator it = itOuter->second.begin();
        while( it != itOuter->second.end() )
        {
            // we only care about active connections
            if(false == it->isActive)
            {
                ++it;
                continue;
            }
            // check for connections that should break
            double currentLength = numerics::distance(it->start.getPosition(frame), it->finish.getPosition(frame));
            if( it->breakLengthDown < currentLength ||
                it->breakLengthUp > currentLength )
            {
                it->isActive = false;
            }
            ++it;
        }
    }
}
