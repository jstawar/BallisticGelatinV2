#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *)
{
    this->setWidth(800);
    this->setHeight(800);
    setSurfaceType(QWindow::OpenGLSurface);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);
    setFormat(format);

    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);

    openGLfunctions = context->functions();

    Settings::CalculationParameters calcParams;
    Settings::SimulationParameters simParams;
    settings = new Settings(calcParams, simParams);
    simulation = new Simulation(*settings);
    recorder = new Recorder(*settings);

    animationON = false;
    plotShield = true;
    plotTriangles = true;
    plotConnections = true;
    plotBullet = true;

    setAnimating(animationON);
}

MainWindow::~MainWindow()
{
    delete context;
    delete settings;
    delete simulation;
}

void MainWindow::arrowGL()
{
    glPushMatrix();
        glBegin(GL_LINES);
            glVertex2d(0.0, 0.0);
            glVertex2d(0.0, 0.5);
        glEnd();
        glBegin(GL_LINES);
            glVertex2d(0.0, 0.5);
            glVertex2d(-0.1, 0.35);
        glEnd();
        glBegin(GL_LINES);
            glVertex2d(0.0, 0.5);
            glVertex2d(0.1, 0.35);
        glEnd();
    glPopMatrix();
}

void MainWindow::coordinateSystemGL()
{
    glPushMatrix();
        glScaled(0.2, 0.2, 0.2);
        glColor3d(0.0,1.0,1.0); // X axis
        arrowGL();
        glColor3d(0.0,1.0,0.0);
        glRotated(-90.0,0.0,0.0,1.0);
        arrowGL(); // Y axis
    glPopMatrix();
}

void MainWindow::ballGL(const Ball &ball)
{
    const int sides = 20;

    glPushMatrix();
        glColor3d(1.0,1.0,1.0);
        glTranslated(ball.getPosition().x, ball.getPosition().y, 0.0);
        glBegin(GL_LINE_LOOP);
            for (int a = 0; a < 360; a += 360 / sides)
            {
                double heading = a * 3.1415926535897932384626433832795 / 180;
                glVertex2d(cos(heading) * ball.getRadius(), sin(heading) * ball.getRadius());
            }
        glEnd();
    glPopMatrix();
}

void MainWindow::plotShieldGL(const Shield &shield)
{
    const std::vector<Ball> &balls = shield.getBalls();

    glPushMatrix();
    for(unsigned int i = 0 ; i < balls.size() ; i++)
    {
        ballGL(balls[i]);
    }
    glPopMatrix();
}

void MainWindow::connectionPairGL(const SpringConnections &connections)
{
    const std::map<SpringConnections::ConnectionType, std::vector<SpringConnections::SpringConnectionPair> > &connectionPairs = connections.getSpringConnectionPairs();
    glPushMatrix();
        for(std::map<SpringConnections::ConnectionType, std::vector<SpringConnections::SpringConnectionPair> >::const_iterator it = connectionPairs.begin() ; it != connectionPairs.end() ; ++it)
        {
            const std::vector<SpringConnections::SpringConnectionPair> &currentVec = it->second;
            for(unsigned int i = 0 ; i < currentVec.size() ; i++)
            {
                const SpringConnections::SpringConnectionPair &current = currentVec[i];
                if(false == current.isActive)
                    continue;

                glPushMatrix();
                glBegin(GL_LINES);
                    utilities::Color color = numerics::linearInterpolation(settings->calcParams.colorMap, current.displacementRatio);
                    glColor3d(color.getRed(), color.getGreen(), color.getBlue());
                    glVertex2d(current.start.getPosition().x, current.start.getPosition().y);
                    glVertex2d(current.finish.getPosition().x, current.finish.getPosition().y);
                glEnd();
                glPopMatrix();
            }
        }
    glPopMatrix();
}

void MainWindow::bulletGL(const Bullet &bullet)
{
    const std::vector<Ball> &balls = bullet.getBalls();

    glPushMatrix();
    for(unsigned int i = 0 ; i < balls.size() ; i++)
    {
        ballGL(balls[i]);
    }
    glPopMatrix();
}

void MainWindow::trianglesGL(const SpringConnections &connections)
{
    const std::map<unsigned int, SpringConnections::TriangleConnection> &triangles = connections.getTrianglesMap();
    glPushMatrix();
        for(std::map<unsigned int, SpringConnections::TriangleConnection>::const_iterator it = triangles.begin() ; it != triangles.end() ; ++it)
        {
            if(false == it->second.isActive())
                continue;

            glPushMatrix();
            glBegin(GL_TRIANGLES);
                utilities::Color color = numerics::linearInterpolation(settings->calcParams.colorMap, it->second.pairs[0]->displacementRatio);
                glColor3d(color.getRed(), color.getGreen(), color.getBlue());
                glVertex2d(it->second.first->getPosition().x,it->second.first->getPosition().y);

                color = numerics::linearInterpolation(settings->calcParams.colorMap, it->second.pairs[1]->displacementRatio);
                glColor3d(color.getRed(), color.getGreen(), color.getBlue());
                glVertex2d(it->second.second->getPosition().x,it->second.second->getPosition().y);

                color = numerics::linearInterpolation(settings->calcParams.colorMap, it->second.pairs[2]->displacementRatio);
                glColor3d(color.getRed(), color.getGreen(), color.getBlue());
                glVertex2d(it->second.third->getPosition().x,it->second.third->getPosition().y);
            glEnd();
            glPopMatrix();
        }
    glPopMatrix();
}

void MainWindow::resizeEvent(QResizeEvent *)
{

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_P)
    {
        animationON = !animationON;
        setAnimating(animationON);
    }
    else if(e->key() == Qt::Key_S)
    {
        plotShield = !plotShield;
    }
    else if(e->key() == Qt::Key_C)
    {
        plotConnections = !plotConnections;
    }
    else if(e->key() == Qt::Key_T)
    {
        plotTriangles = !plotTriangles;
    }
    else if(e->key() == Qt::Key_B)
    {
        plotBullet = !plotBullet;
    }
    else if(e->key() == Qt::Key_F) // TODO - just for testing frame by frame
    {
        simulation->nextFrame();
    }
}

void MainWindow::setAnimating(bool enabled)
{
    if (enabled) {
        connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
        update();
    } else {
        disconnect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    }
}

void MainWindow::printTextGL()
{
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 16));
    if( simulation->getBullet() )
    {
        double energy = simulation->getBullet()->getEnergy();
        double velocity = simulation->getBullet()->getVelocity().norm();
        painter.drawText(QPointF(100.0, 50.0), QString(QStringLiteral("E_k = %1 [J]").arg(energy) ) );
        painter.drawText(QPointF(100.0, 70.0), QString(QStringLiteral("V = %1 [m/s]").arg(velocity) ) );
    }
    painter.drawText(QPointF(100.0, 90.0), QString(QStringLiteral("time = %1 [s]").arg(simulation->getCurrentTime()) ) );
    painter.drawText(QPointF(100.0, 110.0), QString(QStringLiteral("#balls = %1 []").arg(simulation->getTotalBalls() ) ) );
    painter.drawText(QPointF(100.0, 130.0), QString(QStringLiteral("k = %1 [N/m]").arg(settings->simParams.shieldParams.springParams.springCoefficient ) ) );
    painter.drawText(QPointF(100.0, 150.0), QString(QStringLiteral("#AC = %1 []").arg(simulation->getNumActiveConnections() ) ) );
    painter.end();
}

void MainWindow::plotColorMapGL()
{
    glPushMatrix();
    glTranslated(0.0, -0.3, 0.0);
    unsigned int num = 25;
    double dx = 1.0/static_cast<double>(num);
    double current = 0.0;
    double height = 0.1;
    for(unsigned int i = 0 ; i < num ; i++)
    {
        current = i * dx;
        glPushMatrix();
        glBegin(GL_QUADS);
            utilities::Color color = numerics::linearInterpolation(settings->calcParams.colorMap, current);
            glColor3d(color.getRed(), color.getGreen(), color.getBlue());
            glVertex2d(current,height);
            glVertex2d(current,0.0);
            color = numerics::linearInterpolation(settings->calcParams.colorMap, current+dx);
            glColor3d(color.getRed(), color.getGreen(), color.getBlue());
            glVertex2d(current+dx,0.0);
            glVertex2d(current+dx,height);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
}

// TODO - create some ENGINE function - this is ugly
// TODO - add Plotting of V(t), V(x), Ek(t), Ek(x), p(t), p(x)
void MainWindow::paintEvent(QPaintEvent *)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        glTranslated(-0.25,-0.25,0.0);
        coordinateSystemGL();
        if(plotShield && simulation->getShield())
            plotShieldGL(*simulation->getShield());
        if(plotConnections && simulation->getShield() && simulation->getShield()->getSpringConnections())
            connectionPairGL(*simulation->getShield()->getSpringConnections());
        if(plotBullet && simulation->getBullet())
            bulletGL(*simulation->getBullet());
        if(plotTriangles && simulation->getShield())
            trianglesGL(*simulation->getShield()->getSpringConnections());
        printTextGL();
        plotColorMapGL();
    glPopMatrix();

    if( recorder && simulation->getFrameNum() % settings->recorderParams.captureEveryNth == 0 )
    {
        // pass the pixels info to the function
        recorder->captureFrame();
    }

    if(simulation->getCurrentTime() > settings->calcParams.tMax)
    {
        animationON = false;
        setAnimating(false);
    }

    simulation->nextFrame();
}
