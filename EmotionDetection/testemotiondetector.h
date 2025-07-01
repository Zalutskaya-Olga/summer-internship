#ifndef TESTEMOTIONDETECTOR_H
#define TESTEMOTIONDETECTOR_H

#include <QObject>
#include <QtTest/QtTest>
#include "emotiondetector.h"

class TestEmotionDetector : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testTextAnalysis_data();
    void testTextAnalysis();

    void testParametersAnalysis_data();
    void testParametersAnalysis();

    void testCombinedAnalysis_data();
    void testCombinedAnalysis();

    void testEmotionToString();

private:
    EmotionDetector *detector;
};

#endif // TESTEMOTIONDETECTOR_H
