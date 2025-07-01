#include "emotiondetector.h"
#include <QRegularExpression>
#include <QDebug>
#include <cmath>

EmotionDetector::EmotionDetector(QObject *parent) : QObject(parent)
{
}

EmotionDetector::Emotion EmotionDetector::analyzeText(const QString &text) const
{
    if (text.isEmpty()) return Neutral;

    double score = calculateTextScore(text);

    if (score > 0.7) return Happy;
    if (score > 0.3) return Excited;
    if (score < -0.7) return Sad;
    if (score < -0.3) return Angry;

    return Neutral;
}

EmotionDetector::Emotion EmotionDetector::analyzeParameters(const QVector<double> meters) const
{
    if (meters.isEmpty()) return Neutral;

    double score = calculateParametersScore(meters);

    if (score > 0.6) return Happy;
    if (score > 0.2) return Excited;
    if (score < -0.6) return Sad;
    if (score < -0.2) return Angry;

    return Calm;
}

EmotionDetector::Emotion EmotionDetector::combinedAnalysis(const QString &text, const QVector<double> meters) const
{
    if (text.isEmpty() && meters.isEmpty()) return Neutral;

    double textScore = text.isEmpty() ? 0 : calculateTextScore(text);
    double paramScore = meters.isEmpty() ? 0 : calculateParametersScore(meters);

    double combinedScore = (textScore + paramScore) / 2.0;

    if (combinedScore > 0.65) return Happy;
    if (combinedScore > 0.3) return Excited;
    if (combinedScore < -0.65) return Sad;
    if (combinedScore < -0.3) return Angry;

    return Neutral;
}

QString EmotionDetector::emotionToString(EmotionDetector::Emotion emotion)
{
    switch (emotion) {
    case Happy: return "Happy";
    case Sad: return "Sad";
    case Angry: return "Angry";
    case Excited: return "Excited";
    case Calm: return "Calm";
    case Fear: return "Fear";
    case Disgust: return "Disgust";
    case Surprise: return "Surprise";
    default: return "Neutral";
    }
}

double EmotionDetector::calculateTextScore(const QString &text) const
{
    QString lowerText = text.toLower();

    int positive = 0;
    positive += lowerText.count(QRegularExpression("\\bhappy\\b"));
    positive += lowerText.count(QRegularExpression("\\bjoy\\b"));
    positive += lowerText.count(QRegularExpression("\\blove\\b"));
    positive += lowerText.count(QRegularExpression("\\bexcited\\b"));
    positive += lowerText.count(QRegularExpression("\\bwonderful\\b"));

    int negative = 0;
    negative += lowerText.count(QRegularExpression("\\bsad\\b"));
    negative += lowerText.count(QRegularExpression("\\bangry\\b"));
    negative += lowerText.count(QRegularExpression("\\bhate\\b"));
    negative += lowerText.count(QRegularExpression("\\bupset\\b"));
    negative += lowerText.count(QRegularExpression("\\bterrible\\b"));

    int exclamations = lowerText.count('!');

    int questions = lowerText.count('?');

    double score = (positive - negative) / 10.0;
    score += exclamations * 0.1;
    score -= questions * 0.05;

    return qBound(-1.0, score, 1.0);
}

double EmotionDetector::calculateParametersScore(const QVector<double> meters) const
{
    if (meters.size() < 3) return 0.0;

    double heartRate = meters[0];
    double gsr = meters[1];
    double temperature = meters[2];

    double normHeartRate = (heartRate - 70) / 30.0;
    double normGsr = (gsr - 5) / 5.0;
    double normTemp = (temperature - 36.6) / 1.0;

    double score = (normHeartRate * 0.4 + normGsr * 0.4 + normTemp * 0.2);

    return qBound(-1.0, score, 1.0);
}
