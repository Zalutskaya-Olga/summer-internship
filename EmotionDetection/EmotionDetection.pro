QT += core gui widgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EmotionDetection
TEMPLATE = app

SOURCES += main.cpp \
           emotiondetector.cpp \

HEADERS += emotiondetector.h \

# Тестовые файлы только для тестов
TEST_SOURCES = testemotiondetector.cpp
TEST_HEADERS = testemotiondetector.h
