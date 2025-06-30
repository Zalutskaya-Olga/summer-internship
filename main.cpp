#include <QCoreApplication>
#include <QMap>
#include <QMultiMap>
#include <QDebug>
#include <QString>

void demoQMap() {
    QMap<QString, int> ageMap;

    ageMap.insert("Alice", 25);
    ageMap.insert("Bob", 30);
    ageMap.insert("Charlie", 35);
    ageMap["David"] = 40;

    qDebug() << "QMap contents:";
    for (auto it = ageMap.begin(); it != ageMap.end(); ++it) {
        qDebug() << it.key() << ":" << it.value();
    }

    auto it = ageMap.find("Bob");
    if (it != ageMap.end()) {
        qDebug() << "Found Bob, age:" << it.value();
    }


    ageMap.remove("Charlie");
    qDebug() << "After removing Charlie, size:" << ageMap.size();
}

void demoQMultiMap() {
    QMultiMap<QString, int> multiMap;

    multiMap.insert("Group1", 10);
    multiMap.insert("Group1", 20);
    multiMap.insert("Group2", 30);
    multiMap.insert("Group1", 40);
    multiMap.insert("Group3", 50);
    multiMap.insert("Group3", 60);

    qDebug() << "\nQMultiMap contents:";
    for (auto it = multiMap.begin(); it != multiMap.end(); ++it) {
        qDebug() << it.key() << ":" << it.value();
    }

    qDebug() << "All values for Group1:";
    QList<int> values = multiMap.values("Group1");
    for (int val : values) {
        qDebug() << val;
    }

    multiMap.remove("Group1");
    qDebug() << "After removing Group1, size:" << multiMap.size();
}

void demoContainerMethods() {
    QMap<QString, QString> capitalMap;
    capitalMap["Germany"] = "Berlin";
    capitalMap["France"] = "Paris";
    capitalMap["Italy"] = "Rome";

    qDebug() << "\nContains France?" << capitalMap.contains("France");

    qDebug() << "All keys:" << capitalMap.keys();

    qDebug() << "All values:" << capitalMap.values();

    capitalMap.clear();
    qDebug() << "After clear, size:" << capitalMap.size();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);


    demoQMap();


    demoQMultiMap();

    demoContainerMethods();

    return 0;
}
