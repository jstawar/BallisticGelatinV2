#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>

#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QPainter>

#include "Settings.h"
#include "Simulation.h"
#include "SpringConnections.h"
#include "Numerics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void paintEvent(QPaintEvent *event);

    // TODO move all OpenGL stuff to another class and pass objects there
    // TODO also make resize not applicable
    void coordinateSystemGL();
    void arrowGL();
    void ballGL(const Ball &ball);
    void plotShieldGL(const Shield &shield);
    void connectionPairGL(const SpringConnections &connections);
    void bulletGL(const Bullet &bullet);
    void printText();

private:

    QOpenGLContext *context;
    QOpenGLFunctions *openGLfunctions;

    Settings *settings;
    Simulation *simulation;

    bool animationON;

    void setAnimating(bool enabled);
};
#endif // MAINWINDOW_H
