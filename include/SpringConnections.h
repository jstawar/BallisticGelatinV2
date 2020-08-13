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
    std::vector<Ball> &balls;
    std::map<ConnectionType, std::vector<SpringConnectionPair> > connectionPairs;
    std::map<unsigned int, TriangleConnection> trianglesMap;

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
    struct TriangleConnection
    {
        bool isActiveFlag;
        std::vector<SpringConnectionPair*> pairs;
        Ball *first, *second, *third;
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
};


#endif // SPRINGCONNECTIONS_H
