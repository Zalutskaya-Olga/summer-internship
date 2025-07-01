#ifndef EMOTIONDETECTOR_H
#define EMOTIONDETECTOR_H

#include <QObject>
#include <QVector>

class EmotionDetector : public QObject
{
    Q_OBJECT

public:
    enum Emotion {
        Neutral,
        Happy,
        Sad,
        Angry,
        Excited,
        Calm,
        Fear,
        Disgust,
        Surprise
    };
    Q_ENUM(Emotion)

    explicit EmotionDetector(QObject *parent = nullptr);

    Emotion analyzeText(const QString &text) const;

    Emotion analyzeParameters(const QVector<double> meters) const;

    Emotion combinedAnalysis(const QString &text, const QVector<double> meters) const;

    static QString emotionToString(Emotion emotion);

private:
    double calculateTextScore(const QString &text) const;
    double calculateParametersScore(const QVector<double> meters) const;
};

#endif // EMOTIONDETECTOR_H
