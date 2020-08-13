#include "Bullets.h"

namespace bullets
{

BulletAK47::BulletAK47(const Settings &settings)
    : Bullet(settings)
{
    initialize();
}

// TODO

void BulletAK47::initialize()
{
    unsigned int nX = 10;
    unsigned int nY = 11;

    double radius = 0.002;
    double dx = 0.02;
    double dy = 0.02;
    double y0 = -1.0 * (dy * (nY-1)/2.0);
    double x0 = 0.0;
    double mass = 0.01;

    for(unsigned int i = 0 ; i < nY ; i++)
    {
        for(unsigned int j = 0 ; j < nX ; j++)
        {
            utilities::Vectors vectors;
            vectors.position.x = x0 + dx * j;
            vectors.position.y = y0 + dy * i;
            Ball current(vectors, mass, radius);
            balls.push_back(current);
        }
    }

  /*  unsigned int nXtip = 15;
    double xMaxTip = 0.25;
    x0 = dx * nX;
    dx = xMaxTip / nXtip;
    y0 = dy * (nY - 1) / 2.0;

    for(unsigned int i = 0; i < nXtip ; i++)
    {
        utilities::Vectors vectors;
        double x = x0 + dx * i;
        vectors.position.setX(x);
        double y = sqrt( pow(x/4, 2.0) -  );
        vectors.position.setY(y0);
        Ball current(vectors, mass, radius);
        balls.push_back(current);
    }
*/

    // TODO
    // we are considering only cross-section in our simulation by we should count all the hypothetical shperes that represent 3D bullet?
    // Symmetry is on our favour but we need to know how many balls can be stoed in certain wolume (given the simples cristalization - cube mesh)

}

}
