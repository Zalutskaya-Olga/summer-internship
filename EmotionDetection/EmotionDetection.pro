
QT += testlib  # Добавьте это для тестов
QT += widgets  # Для GUI-приложения
QT += core gui widgets
TARGET = EmotionDetection
SOURCES += \
    main.cpp \
    emotiondetector.cpp
HEADERS += \
    emotiondetector.h
