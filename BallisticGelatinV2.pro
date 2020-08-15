QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 -Wall -Wextra -Wpedantic

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include

SOURCES += \
    main.cpp \
    source/Ball.cpp \
    source/Bullet.cpp \
    source/Bullets.cpp \
    source/Numerics.cpp \
    source/Physics.cpp \
    source/Recorder.cpp \
    source/Settings.cpp \
    source/Shield.cpp \
    source/Simulation.cpp \
    source/SpringConnections.cpp \
    source/mainwindow.cpp

HEADERS += \
    include/Ball.h \
    include/Bullet.h \
    include/Bullets.h \
    include/Numerics.h \
    include/Physics.h \
    include/Recorder.h \
    include/Settings.h \
    include/Shield.h \
    include/Simulation.h \
    include/SpringConnections.h \
    include/Utilities.h \
    include/mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
