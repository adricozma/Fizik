TEMPLATE = lib

CONFIG = staticlib
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    ObjetMobile.cc \
    Vecteur.cc \
    ChampForces.cc \
    constantes.cc \
    Integrateur.cc \
    Obstacle.cc \
    Systeme.cc \
    Balle.cc \
    Boulet.cc \
    Ressort.cc \
    Pendule.cc \
    PenduleSpherique.cc \
    ObjetCompose.cc

HEADERS += \
    ObjetMobile.h \
    Dessinable.h \
    Vecteur.h \
    ChampForces.h \
    constantes.h \
    Integrateur.h \
    Obstacle.h \
    Systeme.h \
    support_a_dessin.h \
    Erreur.h \
    ObjetCompose.h
