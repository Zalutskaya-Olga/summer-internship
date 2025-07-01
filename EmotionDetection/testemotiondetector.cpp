#include "testemotiondetector.h"

void TestEmotionDetector::initTestCase()
{
    detector = new EmotionDetector();
}

void TestEmotionDetector::cleanupTestCase()
{
    delete detector;
}

void TestEmotionDetector::testTextAnalysis_data()
{
    QTest::addColumn<QString>("text");
    QTest::addColumn<EmotionDetector::Emotion>("expected");

    QTest::newRow("empty") << "" << EmotionDetector::Neutral;
    QTest::newRow("happy") << "I'm so happy today!" << EmotionDetector::Happy;
    QTest::newRow("sad") << "Feeling very sad and lonely" << EmotionDetector::Sad;
    QTest::newRow("angry") << "I hate this! It makes me angry!" << EmotionDetector::Angry;
    QTest::newRow("excited") << "Wow! This is so exciting!" << EmotionDetector::Excited;
    QTest::newRow("neutral") << "Just a regular day, nothing special." << EmotionDetector::Neutral;
}

void TestEmotionDetector::testTextAnalysis()
{
    QFETCH(QString, text);
    QFETCH(EmotionDetector::Emotion, expected);

    EmotionDetector::Emotion result = detector->analyzeText(text);
    QCOMPARE(result, expected);
}

void TestEmotionDetector::testParametersAnalysis_data()
{
    QTest::addColumn<QVector<double>>("parameters");
    QTest::addColumn<EmotionDetector::Emotion>("expected");

    QTest::newRow("empty") << QVector<double>() << EmotionDetector::Neutral;
    QTest::newRow("happy") << QVector<double>{85, 8, 37.0} << EmotionDetector::Happy;
    QTest::newRow("sad") << QVector<double>{60, 3, 35.8} << EmotionDetector::Sad;
    QTest::newRow("angry") << QVector<double>{95, 9, 37.2} << EmotionDetector::Angry;
    QTest::newRow("calm") << QVector<double>{70, 5, 36.6} << EmotionDetector::Calm;
    QTest::newRow("excited") << QVector<double>{80, 7, 36.8} << EmotionDetector::Excited;
}

void TestEmotionDetector::testParametersAnalysis()
{
    QFETCH(QVector<double>, parameters);
    QFETCH(EmotionDetector::Emotion, expected);

    EmotionDetector::Emotion result = detector->analyzeParameters(parameters);
    QCOMPARE(result, expected);
}

void TestEmotionDetector::testCombinedAnalysis_data()
{
    QTest::addColumn<QString>("text");
    QTest::addColumn<QVector<double>>("parameters");
    QTest::addColumn<EmotionDetector::Emotion>("expected");

    QTest::newRow("both happy")
        << "I'm feeling great!"
        << QVector<double>{85, 8, 37.0}
        << EmotionDetector::Happy;

    QTest::newRow("conflict text happy params sad")
        << "Everything is terrible"
        << QVector<double>{85, 8, 37.0}
        << EmotionDetector::Neutral;

    QTest::newRow("no text")
        << ""
        << QVector<double>{60, 3, 35.8}
        << EmotionDetector::Sad;

    QTest::newRow("no params")
        << "This is amazing!"
        << QVector<double>()
        << EmotionDetector::Happy;
}

void TestEmotionDetector::testCombinedAnalysis()
{
    QFETCH(QString, text);
    QFETCH(QVector<double>, parameters);
    QFETCH(EmotionDetector::Emotion, expected);

    EmotionDetector::Emotion result = detector->combinedAnalysis(text, parameters);
    QCOMPARE(result, expected);
}

void TestEmotionDetector::testEmotionToString()
{
    QCOMPARE(EmotionDetector::emotionToString(EmotionDetector::Happy), "Happy");
    QCOMPARE(EmotionDetector::emotionToString(EmotionDetector::Sad), "Sad");
    QCOMPARE(EmotionDetector::emotionToString(EmotionDetector::Neutral), "Neutral");
    QCOMPARE(EmotionDetector::emotionToString(EmotionDetector::Angry), "Angry");
    QCOMPARE(EmotionDetector::emotionToString(EmotionDetector::Excited), "Excited");
    QCOMPARE(EmotionDetector::emotionToString(EmotionDetector::Calm), "Calm");
    QCOMPARE(EmotionDetector::emotionToString(EmotionDetector::Fear), "Fear");
    QCOMPARE(EmotionDetector::emotionToString(EmotionDetector::Disgust), "Disgust");
    QCOMPARE(EmotionDetector::emotionToString(EmotionDetector::Surprise), "Surprise");
}

QTEST_APPLESS_MAIN(TestEmotionDetector)
