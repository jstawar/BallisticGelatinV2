#include "SpringConnections.h"
#include "Numerics.h"

#include <iostream>

// TODO - make it more generic for different cristalization methods

SpringConnections::SpringConnections(const Settings &settings, std::vector<Ball> &balls)
    : settings(settings),
      balls(balls),
      activeConnections(0)
{
    addConnections();
    addTriangles();
}

void SpringConnections::addConnections()
{
    addRightConnections();
    addLeftUpConnections();
    addUpConnections();
    addRightUpConnections();
}

void SpringConnections::TriangleConnection::calcIsActive()
{
    if(false == isActiveFlag)
        return;

    for(unsigned int i = 0 ; i < pairs.size() ; i++)
    {
        if(false == pairs[i]->isActive)
        {
            isActiveFlag = false;
            return;
        }
    }

    return;
}

void SpringConnections::addTriangles()
{
    unsigned int current = 0;
    for(unsigned int y = 0 ; y < settings.simParams.numYShield - 1 ; y++)
    {
        for(unsigned x = 0 ; x < settings.simParams.numXShield - 1 ; x++)
        {
            unsigned int index = (settings.simParams.numXShield - 1 ) * y + x;
            trianglesMap[current].pairs.push_back(&connectionPairs[Right].at(index));
            trianglesMap[current].pairs.push_back(&connectionPairs[Up].at(index+y));
            trianglesMap[current].pairs.push_back(&connectionPairs[LeftUp].at(index));

            trianglesMap[current].first = &connectionPairs[Right].at(index).start;
            trianglesMap[current].second = &connectionPairs[Right].at(index).finish;
            trianglesMap[current].third = &connectionPairs[LeftUp].at(index).finish;

            trianglesMap[current].isActiveFlag = true;

            current++;
        }
    }

    for(unsigned int y = 0 ; y < settings.simParams.numYShield - 1 ; y++)
    {
        for(unsigned x = 0 ; x < settings.simParams.numXShield - 1 ; x++)
        {
            unsigned int index = (settings.simParams.numXShield - 1 ) * y + x;
            trianglesMap[current].pairs.push_back(&connectionPairs[Right].at(index));
            trianglesMap[current].pairs.push_back(&connectionPairs[Up].at(index+1+y));
            trianglesMap[current].pairs.push_back(&connectionPairs[RightUp].at(index));

            trianglesMap[current].first = &connectionPairs[Right].at(index).start;
            trianglesMap[current].second = &connectionPairs[Right].at(index).finish;
            trianglesMap[current].third = &connectionPairs[RightUp].at(index).finish;

            trianglesMap[current].isActiveFlag = true;

            current++;
        }
    }

    // reversed
    for(unsigned int y = 0 ; y < settings.simParams.numYShield - 1 ; y++)
    {
        for(unsigned x = 0 ; x < settings.simParams.numXShield - 1 ; x++)
        {
            unsigned int index = (settings.simParams.numXShield - 1 ) * y + x;
            unsigned int indexUp = (settings.simParams.numXShield - 1 ) * (y + 1) + x;
            trianglesMap[current].pairs.push_back(&connectionPairs[Right].at(indexUp));
            trianglesMap[current].pairs.push_back(&connectionPairs[LeftUp].at(index));
            trianglesMap[current].pairs.push_back(&connectionPairs[Up].at(index+1+y));

            trianglesMap[current].first = &connectionPairs[Right].at(indexUp).start;
            trianglesMap[current].second = &connectionPairs[LeftUp].at(index).start;
            trianglesMap[current].third = &connectionPairs[Right].at(indexUp).finish;

            trianglesMap[current].isActiveFlag = true;

            current++;
        }
    }

    for(unsigned int y = 0 ; y < settings.simParams.numYShield - 1 ; y++)
    {
        for(unsigned x = 0 ; x < settings.simParams.numXShield - 1 ; x++)
        {
            unsigned int index = (settings.simParams.numXShield - 1 ) * y + x;
            unsigned int indexUp = (settings.simParams.numXShield - 1 ) * (y + 1) + x;
            trianglesMap[current].pairs.push_back(&connectionPairs[RightUp].at(index));
            trianglesMap[current].pairs.push_back(&connectionPairs[Right].at(indexUp));
            trianglesMap[current].pairs.push_back(&connectionPairs[Up].at(index+y));

            trianglesMap[current].first = &connectionPairs[RightUp].at(index).start;
            trianglesMap[current].second = &connectionPairs[RightUp].at(index).finish;
            trianglesMap[current].third = &connectionPairs[Up].at(index+y).finish;

            trianglesMap[current].isActiveFlag = true;

            current++;
        }
    }
}

void SpringConnections::addRightConnections()
{
    for(unsigned int i = 0 ; i < settings.simParams.numYShield ; i++)
    {
        for(unsigned int j = 0 ; j < settings.simParams.numXShield - 1 ; j++)
        {
            unsigned int current = settings.simParams.numXShield * i + j;
            double restLength = numerics::distance(balls[current].getPosition(), balls[current+1].getPosition());
            double breakLengthUp = restLength * settings.simParams.extensionBreakCoefficient;
            double breakLengthDown = restLength * settings.simParams.compressionBreakCoefficient;
            SpringConnectionPair connectionPair( balls[current], balls[current+1], restLength, true, breakLengthUp, breakLengthDown);
            connectionPairs[Right].push_back(connectionPair);
            activeConnections++;
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
            double restLength = numerics::distance(balls[current].getPosition(), balls[current+settings.simParams.numXShield-1].getPosition());
            double breakLengthUp = restLength * settings.simParams.extensionBreakCoefficient;
            double breakLengthDown = restLength * settings.simParams.compressionBreakCoefficient;
            SpringConnectionPair connectionPair( balls[current], balls[current+settings.simParams.numXShield-1], restLength, true, breakLengthUp, breakLengthDown);
            connectionPairs[LeftUp].push_back(connectionPair);
            activeConnections++;
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
            double restLength = numerics::distance(balls[current].getPosition(), balls[current+settings.simParams.numXShield].getPosition());
            double breakLengthUp = restLength * settings.simParams.extensionBreakCoefficient;
            double breakLengthDown = restLength * settings.simParams.compressionBreakCoefficient;
            SpringConnectionPair connectionPair( balls[current], balls[current+settings.simParams.numXShield], restLength, true, breakLengthUp, breakLengthDown);
            connectionPairs[Up].push_back(connectionPair);
            activeConnections++;
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
            double restLength = numerics::distance(balls[current].getPosition(), balls[current+settings.simParams.numXShield+1].getPosition());
            double breakLengthUp = restLength * settings.simParams.extensionBreakCoefficient;
            double breakLengthDown = restLength * settings.simParams.compressionBreakCoefficient;
            SpringConnectionPair connectionPair( balls[current], balls[current+settings.simParams.numXShield+1], restLength, true, breakLengthUp, breakLengthDown);
            connectionPairs[RightUp].push_back(connectionPair);
            activeConnections++;
        }
    }
}

void SpringConnections::nextFrame()
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
            double currentLength = numerics::distance(it->start.getPosition(), it->finish.getPosition());
            if( it->breakLengthUp < currentLength ||
                it->breakLengthDown > currentLength )
            {
                it->isActive = false;
                activeConnections--;
            }
            else
            {
                // now add spring forces to balls
                double dLength = currentLength - it->restLength;
                double maxdL = dLength < 0.0 ? (settings.simParams.compressionBreakCoefficient - 1.0) : (settings.simParams.extensionBreakCoefficient - 1.0);
                maxdL *= it->restLength;
                it->displacementRatio = dLength / maxdL;
                double sinTheta = (it->start.getPosition().x - it->finish.getPosition().x)/currentLength;
                double cosTheta = (it->start.getPosition().y - it->finish.getPosition().y)/currentLength;
                // k * dL * angle
                double forceX = settings.simParams.springCoefficient * dLength * sinTheta;
                double forceY = settings.simParams.springCoefficient * dLength * cosTheta;

                it->start.getVectors().acceleration.x -= forceX / it->start.getMass();
                it->start.getVectors().acceleration.y -= forceY / it->start.getMass();
                it->finish.getVectors().acceleration.x += forceX / it->finish.getMass();
                it->finish.getVectors().acceleration.y += forceY / it->finish.getMass();
            }
            ++it;
        }
    }

    // Triangles - check for active
    for(std::map<unsigned int, TriangleConnection>::iterator it = trianglesMap.begin() ; it != trianglesMap.end() ; ++it)
    {
        it->second.calcIsActive();
    }
}
