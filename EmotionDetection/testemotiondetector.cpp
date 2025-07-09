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
    QTest::newRow("happy") << "I'm so happy today! This is amazing!" << EmotionDetector::Happy;
    QTest::newRow("excited") << "I'm excited about this wonderful news!" << EmotionDetector::Excited;
    QTest::newRow("sad") << "Feeling very sad and lonely" << EmotionDetector::Sad;
    QTest::newRow("angry") << "I hate this! It makes me angry!" << EmotionDetector::Angry;
    QTest::newRow("neutral") << "Just a regular day, nothing special." << EmotionDetector::Neutral;
    //QTest::newRow("mixed") << "I'm happy but also a bit upset" << EmotionDetector::Neutral;
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
    QTest::newRow("happy") << QVector<double>{90, 12, 37.0} << EmotionDetector::Happy;
    QTest::newRow("excited") << QVector<double>{85, 10, 37.0} << EmotionDetector::Excited;
    QTest::newRow("sad") << QVector<double>{60, 3, 35.5} << EmotionDetector::Sad;  // Низкий пульс, низкая GSR
    QTest::newRow("calm") << QVector<double>{70, 5, 36.5} << EmotionDetector::Calm;
    QTest::newRow("neutral") << QVector<double>{75, 7, 36.8} << EmotionDetector::Calm;
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

    // Тесты для комбинированного анализа
    QTest::newRow("both happy")
        << "I'm feeling great!"
        << QVector<double>{90, 12, 37.0}
        << EmotionDetector::Happy;

    /*QTest::newRow("text happy params sad")
        << "Everything is wonderful!"
        << QVector<double>{60, 3, 35.5}
        << EmotionDetector::Happy;  // Текст имеет приоритет*/

    QTest::newRow("text neutral params happy")
        << "Just normal day"
        << QVector<double>{90, 12, 37.0}
        << EmotionDetector::Happy;  // Параметры решают, если текст нейтральный

    QTest::newRow("no text")
        << ""
        << QVector<double>{60, 3, 35.8}
        << EmotionDetector::Sad;

    QTest::newRow("conflicting strong")
        << "I hate everything!"
        << QVector<double>{90, 12, 37.0}
        << EmotionDetector::Angry;  // Сильный текст перевешивает
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

    // Проверка для несуществующего значения (должно вернуть Neutral)
    QCOMPARE(EmotionDetector::emotionToString(static_cast<EmotionDetector::Emotion>(999)), "Neutral");
}

QTEST_APPLESS_MAIN(TestEmotionDetector)
