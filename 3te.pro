#-------------------------------------------------
#
# Project created by QtCreator 2018-05-10T15:18:39
#
#-------------------------------------------------

QT       -= core gui

TARGET = 3te
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lSPM

SOURCES += frame.cpp \
    vector.cpp \
    kinematic.cpp \
    rigidbody.cpp \
    tickcounter.cpp \
    timer.cpp \
    mesh.cpp \
    meshvertex.cpp \
    vector3d.cpp \
    model.cpp \
    afcontainer.cpp \
    capability.cpp \
    object.cpp \
    ivector.cpp \
    debug.cpp


HEADERS += frame.h \
    vector.h \
    kinematic.h \
    rigidbody.h \
    tickcounter.h \
    timer.h \
    mesh.h \
    meshvertex.h \
    vector3d.h \
    model.h \
    afcontainer.h \
    capability.h \
    object.h \
    ivector.h \
    debug.h



unix {
    target.path = /usr/lib
    INSTALLS += target
}
