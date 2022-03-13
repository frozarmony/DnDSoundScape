# General Config
CONFIG += C++11

# Add more folders to ship with the application, here
# For qml
folder_01.source = qml/DnDSoundScape
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# For test Data
testData.source = dndData
testData.target = .
DEPLOYMENTFOLDERS += testData

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# Others FrameWork & Lib
QT += multimedia
QT += xml

LIBS += -Llame/libmp3lame-static.lib -lmp3lame

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    backend.cpp \
    soundmodel.cpp \
    soundModels/oneshotsoundmodel.cpp \
    soundModels/ambiantsoundmodel.cpp \
    soundModels/musicsoundmodel.cpp \
    panelmodel.cpp \
    mastervolumemodel.cpp \
    soundModels/placesoundmodel.cpp \
    panellistmodel.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    backend.h \
    soundmodel.h \
    soundModels/oneshotsoundmodel.h \
    soundModels/ambiantsoundmodel.h \
    soundModels/musicsoundmodel.h \
    panelmodel.h \
    mastervolumemodel.h \
    soundModels/placesoundmodel.h \
    panellistmodel.h

RC_FILE = DnDSoundScape.rc
