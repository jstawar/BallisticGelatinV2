#ifndef SPRINGCONNECTIONS_H
#define SPRINGCONNECTIONS_H

#include "Ball.h"
#include "Settings.h"

#include <vector>
#include <map>

class SpringConnections
{
public:
    struct SpringConnectionPair;
    struct TriangleConnection;
    enum ConnectionType
    {
        Right,
        LeftUp,
        Up,
        RightUp,
        NotOriented
    };
private:
    const Settings &settings;
    // thou shall NOT alter the containers after they are initialized - altering the elements in ok but NO shuffling!!!
    std::vector<Ball> &balls;
    std::map<ConnectionType, std::vector<SpringConnectionPair> > connectionPairs;
    std::map<unsigned int, TriangleConnection> trianglesMap;
    unsigned int activeConnections;

    void addConnections();
    void addRightConnections();
    void addUpConnections();
    void addRightUpConnections();
    void addLeftUpConnections();
    void addTriangles();
public:
    struct SpringConnectionPair
    {
        Ball &start, &finish;
        double restLength; // initialized as starting length
        double displacementRatio; // used for coloring
        bool isActive;
        double breakLengthUp, breakLengthDown;
        SpringConnectionPair(Ball &start, Ball &finish, double restLength, bool isActive, double breakLengthUp, double breakLengthDown)
            : start(start),
              finish(finish),
              restLength(restLength),
              displacementRatio(0.0),
              isActive(isActive),
              breakLengthUp(breakLengthUp),
              breakLengthDown(breakLengthDown)

        {

        }
    };
    // TODO - for higher ball densities this has no visible effect - spring connections are sufficient
    // it's not used for calculation at all - only for display triangles
    struct TriangleConnection
    {
        bool isActiveFlag;
        std::vector<SpringConnectionPair*> pairs;
        Ball *first, *second, *third; // KILL ME - not checking anywhere for valid pointers (who needs that? ;) "I know what I'm doing"... I hope)
        void calcIsActive();
        bool isActive() const
        {
            return isActiveFlag;
        }
    };
    SpringConnections(const Settings &settings, std::vector<Ball> &balls);
    const std::map<ConnectionType, std::vector<SpringConnectionPair> > &getSpringConnectionPairs() const
    {
        return connectionPairs;
    }
    const std::map<unsigned int, TriangleConnection> &getTrianglesMap() const
    {
        return trianglesMap;
    }
    void nextFrame();
    unsigned int getActiveConnections() const
    {
        return activeConnections;
    }
};


#endif // SPRINGCONNECTIONS_H
