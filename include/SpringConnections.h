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
    const std::vector<Ball> &balls;
    std::map<ConnectionType, std::vector<SpringConnectionPair> > connectionPairs;

    void addConnections();
    void addRightConnections();
    void addUpConnections();
    void addRightUpConnections();
    void addLeftUpConnections();
public:
    struct SpringConnectionPair
    {
        const Ball &start, &finish;
        double restLength; // initialized as starting length
        double displacementRatio; // used for coloring
        bool isActive;
        double breakLengthUp, breakLengthDown;
        SpringConnectionPair(const Ball &start, const Ball &finish, double restLength, bool isActive, double breakLengthUp, double breakLengthDown)
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
    SpringConnections(const Settings &settings, const std::vector<Ball> &balls);
    const std::map<ConnectionType, std::vector<SpringConnectionPair> > &getSpringConnectionPairs() const
    {
        return connectionPairs;
    }
    void nextFrame();
};


#endif // SPRINGCONNECTIONS_H
