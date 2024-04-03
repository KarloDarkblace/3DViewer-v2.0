QT       += core gui opengl openglwidgets widgets

include(../libraries/qgifimage/gifimage/qtgifimage.pri)

CONFIG += c++17

SOURCES += \
    ../model/s21_affine.cc \
    ../model/s21_object.cc \
    main.cc \
    customopenglwidget.cc \
    mainwindow.cc

HEADERS += \
    ../controller/s21_controller.h \
    ../model/s21_affine.h \
    ../model/s21_object.h \
    customopenglwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
