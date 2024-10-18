QT       += core gui serialport

FORMS += \
    hsvajustdialog.ui \
    myserial.ui \
    qrcode.ui \
    scancolor.ui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
#
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    btneffect.cpp \
    camera.cpp \
    hsvajustdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mode.cpp \
    modemanager.cpp \
    myserial.cpp \
    mytimer.cpp \
    qrcode.cpp \
    scancolor.cpp \
    workthread.cpp

HEADERS += \
    btneffect.h \
    camera.h \
    hsvajustdialog.h \
    mainwindow.h \
    mode.h \
    modemanager.h \
    myserial.h \
    mytimer.h \
    qrcode.h \
    scancolor.h \
    workthread.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Ltem_Sorting_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
# ����ͷ�ļ�·��
INCLUDEPATH += /usr/local/include/opencv4

# ���� OpenCV �Ŀ�·����Ҫ���ӵĿ�
LIBS += -L/usr/local/lib \
        -lopencv_core \
        -lopencv_imgcodecs \
        -lopencv_videoio \
        -lopencv_highgui \
        -lopencv_imgproc \
        -lopencv_objdetect \
        -lopencv_features2d \
        -lopencv_dnn \
        -lopencv_video

RESOURCES += \
    Resource.qrc

