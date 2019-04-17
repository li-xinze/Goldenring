QT       += core gui
QT       += network
QT       += opengl
LIBS += -lopengl32\
          -lglu32\
          -lglut32\
           -lglut


CONFIG += resources_big
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
FORMS += \
    mainwindow.ui \
    game_status.ui \
    widget.ui

HEADERS += \
    bitmap.h \
    mainwindow.h \
    ob.h \
    reference.h \
    sky.h \
    glwidget.h \
    game_status.h \
    qanimationstackedwidget.h \
    widget.h \
    send_status.h \
    status_reciver.h \
    MathLib.h \
    MDLFormat.h \
    MDLModel.h \
    CMDLOBJ.h \
    DynamicMDL.h \
    Vector.h \
    glfont.h

SOURCES += \
    bitmap.cpp \
    main.cpp \
    mainwindow.cpp \
    ob.cpp \
    sky.cpp \
    glwidget.cpp \
    game_status.cpp \
    qanimationstackedwidget.cpp \
    widget.cpp \
    send_status.cpp \
    status_reciver.cpp \
    glew.c \
    MathLib.cpp \
    MDLModel.cpp \
    CMDLOBJ.cpp \
    DynamicMDL.cpp \
    Vector.cpp \
    glfont.cpp
TARGET = GoldenRing

TEMPLATE = app

RESOURCES += \
    resource.qrc

