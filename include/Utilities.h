#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>

namespace utilities
{

class VectorXY
{
    double x, y;
public:
    VectorXY(double x = 0.0, double y = 0.0)
        : x(x),
          y(y)
    {

    }
    double getX() const
    {
        return x;
    }
    double getY() const
    {
        return y;
    }
    void setX(double newX)
    {
        x = newX;
    }
    void setY(double newY)
    {
        y = newY;
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
    VectorXY force;
    Vectors(VectorXY position = VectorXY(), VectorXY velocity = VectorXY(), VectorXY force = VectorXY())
        : position(position),
          velocity(velocity),
          force(force)
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
