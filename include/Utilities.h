#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>

namespace utilities
{

class VectorXY
{
public:
    double x, y;
    VectorXY(double x = 0.0, double y = 0.0)
        : x(x),
          y(y)
    {

    }
    void clear()
    {
        x = 0.0;
        y = 0.0;
    }
    double normSquared() const
    {
        return x*x + y*y;
    }
    double norm() const
    {
        return sqrt(normSquared());
    }
    void translate(const VectorXY &vec)
    {
        x += vec.x;
        y += vec.y;
    }
    void scale(const VectorXY &vec)
    {
        x *= vec.x;
        y *= vec.y;
    }
};

struct Vectors
{
    VectorXY position;
    VectorXY velocity;
    VectorXY acceleration;
    Vectors(VectorXY position = VectorXY(), VectorXY velocity = VectorXY(), VectorXY acceleration = VectorXY())
        : position(position),
          velocity(velocity),
          acceleration(acceleration)
    {
    }
};

class Color
{
private:
    double red;
    double green;
    double blue;
public:
    Color(double red = 0.0, double green = 0.0, double blue = 0.0)
        : red(red),
          green(green),
          blue(blue)
    {

    }
    double getRed() const
    {
        return red;
    }
    double getGreen() const
    {
        return green;
    }
    double getBlue() const
    {
        return blue;
    }

};

}

#endif // UTILITIES_H
