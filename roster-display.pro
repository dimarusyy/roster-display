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
    src/config.h \
    src/fetchjson.h \
    src/filteredrostermodel.h \
    src/rosterlistmodel.h

SOURCES += \
        src/config.cpp \
        src/fetchjson.cpp \
        src/filteredrostermodel.cpp \
        src/main.cpp \
        src/rosterlistmodel.cpp

RESOURCES += qml.qrc
