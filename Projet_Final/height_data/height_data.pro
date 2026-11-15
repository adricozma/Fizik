TEMPLATE = lib

CONFIG += staticlib
QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH = ../general

SOURCES += \
    Projection.cc

HEADERS += \
    ../general/Erreur.h

