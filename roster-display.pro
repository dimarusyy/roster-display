QT += qml quick concurrent

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    3rdparty/nlohmann/json.hpp \
    config.h \
    fetchjson.h \
    filteredrostermodel.h \
    rosterlistmodel.h

SOURCES += \
        config.cpp \
        fetchjson.cpp \
        filteredrostermodel.cpp \
        main.cpp \
        rosterlistmodel.cpp

RESOURCES += qml.qrc
