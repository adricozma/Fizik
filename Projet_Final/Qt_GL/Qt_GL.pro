QT += core gui opengl widgets
QMAKE_CXXFLAGS += -std=c++11

win32:LIBS += -lopengl32


TARGET = Simulations

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc \
    vue_opengl.cc \
    glsphere.cc \
    ../general/Dessinable.cc \
    ../general/Vecteur.cc \
    ../general/Integrateur.cc \
    ../general/ChampForces.cc \
    ../general/constantes.cc \
    ../general/Systeme.cc \
    ../general/ObjetMobile.cc \
    ../general/Obstacle.cc \
    ../general/Balle.cc \
    ../general/Boulet.cc \
    ../general/Ressort.cc \
    ../general/Pendule.cc \
    ../general/PenduleSpherique.cc \
    ../general/ObjetCompose.cc

HEADERS += \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    glsphere.h \
    ../general/Dessinable.h \
    ../general/support_a_dessin.h \
    ../general/Vecteur.h \
    ../general/Integrateur.h \
    ../general/ChampForces.h \
    ../general/constantes.h \
    ../general/Systeme.h \
    ../general/Obstacle.h \
    ../general/ObjetMobile.h \
    ../general/Erreur.h \
    ../general/ObjetCompose.h

RESOURCES += \
    resource.qrc
