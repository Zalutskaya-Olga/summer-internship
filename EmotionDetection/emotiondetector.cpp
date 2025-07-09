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

    QString lowerText = text.toLower();

    if (lowerText.contains("happy") || lowerText.contains("joy") || lowerText.contains("love"))
        return Happy;
    if (lowerText.contains("excited") || lowerText.contains("wonderful"))
        return Excited;
    if (lowerText.contains("sad") || lowerText.contains("lonely"))
        return Sad;
    if (lowerText.contains("angry") || lowerText.contains("hate"))
        return Angry;

    return Neutral;
}

EmotionDetector::Emotion EmotionDetector::analyzeParameters(const QVector<double> meters) const
{
    if (meters.isEmpty() || meters.size() < 3) return Neutral;

    double heartRate = meters[0];
    double gsr = meters[1];
    double temperature = meters[2];

    if (heartRate > 85 && gsr > 8) return Happy;
    if (heartRate > 80 && gsr > 7) return Excited;
    if (heartRate < 65 && gsr < 5) return Sad;
    if (heartRate > 90 && gsr > 10) return Angry;

    return Calm;
}

EmotionDetector::Emotion EmotionDetector::combinedAnalysis(const QString &text, const QVector<double> meters) const
{
    if (text.isEmpty() && meters.isEmpty()) return Neutral;

    if (text.isEmpty()) return analyzeParameters(meters);
    if (meters.isEmpty()) return analyzeText(text);

    Emotion textEmotion = analyzeText(text);
    if (textEmotion != Neutral) return textEmotion;

    return analyzeParameters(meters);
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
