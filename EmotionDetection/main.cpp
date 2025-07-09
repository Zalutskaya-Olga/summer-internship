#include <QtTest>
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QTest>
#include "emotiondetector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Если есть аргумент --test, запускаем тесты
    if (argc > 1 && QString(argv[1]) == "--test") {
        EmotionDetector test;
        return QTest::qExec(&test, argc, argv);
    }

    // Иначе запускаем GUI приложение
    QMainWindow window;
    QWidget *centralWidget = new QWidget(&window);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *titleLabel = new QLabel("Emotion Detection System", centralWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleLabel->setFont(titleFont);

    QTextEdit *textInput = new QTextEdit(centralWidget);
    textInput->setPlaceholderText("Enter your feelings here...");

    QLabel *resultLabel = new QLabel("Your emotion will appear here", centralWidget);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setWordWrap(true);

    QPushButton *analyzeButton = new QPushButton("Analyze Emotion", centralWidget);

    layout->addWidget(titleLabel);
    layout->addWidget(textInput);
    layout->addWidget(resultLabel);
    layout->addWidget(analyzeButton);

    EmotionDetector detector;

    QObject::connect(analyzeButton, &QPushButton::clicked, [&]() {
        QString text = textInput->toPlainText();
        EmotionDetector::Emotion emotion = detector.analyzeText(text);
        QString emotionStr = EmotionDetector::emotionToString(emotion);
        resultLabel->setText(QString("Detected emotion: <b>%1</b>").arg(emotionStr));
    });

    window.setCentralWidget(centralWidget);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

