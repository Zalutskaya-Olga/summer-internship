TEMPLATE = app
TARGET = EmotionDetectionTests
QT += testlib core

SOURCES += testemotiondetector.cpp \
           emotiondetector.cpp

HEADERS += emotiondetector.h \
           testemotiondetector.h

CONFIG += console
CONFIG -= app_bundle  # Важно для консольного приложения на Mac