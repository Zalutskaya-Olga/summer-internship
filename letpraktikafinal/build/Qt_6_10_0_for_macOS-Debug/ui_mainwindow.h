/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *centralwidget_2;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *loadImageButton;
    QComboBox *comboBox;
    QListView *listView;
    QLabel *imageLabel;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *addListButton;
    QPushButton *removeListButton;
    QPushButton *sortListButton;
    QPushButton *customSortButton;
    QVBoxLayout *verticalLayout_2;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPlainTextEdit *plainTextEdit;
    QPushButton *loadFromTextButton;
    QMenuBar *menubar_2;
    QStatusBar *statusbar_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 683);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget_2 = new QWidget(centralwidget);
        centralwidget_2->setObjectName("centralwidget_2");
        centralwidget_2->setGeometry(QRect(10, 10, 726, 849));
        gridLayout = new QGridLayout(centralwidget_2);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(centralwidget_2);
        tableWidget->setObjectName("tableWidget");

        gridLayout->addWidget(tableWidget, 0, 0, 1, 3);

        addButton = new QPushButton(centralwidget_2);
        addButton->setObjectName("addButton");

        gridLayout->addWidget(addButton, 1, 0, 1, 1);

        removeButton = new QPushButton(centralwidget_2);
        removeButton->setObjectName("removeButton");

        gridLayout->addWidget(removeButton, 1, 1, 1, 1);

        loadImageButton = new QPushButton(centralwidget_2);
        loadImageButton->setObjectName("loadImageButton");

        gridLayout->addWidget(loadImageButton, 1, 2, 1, 1);

        comboBox = new QComboBox(centralwidget_2);
        comboBox->setObjectName("comboBox");

        gridLayout->addWidget(comboBox, 2, 0, 1, 1);

        listView = new QListView(centralwidget_2);
        listView->setObjectName("listView");

        gridLayout->addWidget(listView, 2, 1, 1, 1);

        imageLabel = new QLabel(centralwidget_2);
        imageLabel->setObjectName("imageLabel");
        imageLabel->setFrameShape(QFrame::Shape::Box);
        imageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(imageLabel, 2, 2, 1, 1);

        listWidget = new QListWidget(centralwidget_2);
        listWidget->setObjectName("listWidget");

        gridLayout->addWidget(listWidget, 3, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        addListButton = new QPushButton(centralwidget_2);
        addListButton->setObjectName("addListButton");

        verticalLayout->addWidget(addListButton);

        removeListButton = new QPushButton(centralwidget_2);
        removeListButton->setObjectName("removeListButton");

        verticalLayout->addWidget(removeListButton);

        sortListButton = new QPushButton(centralwidget_2);
        sortListButton->setObjectName("sortListButton");

        verticalLayout->addWidget(sortListButton);

        customSortButton = new QPushButton(centralwidget_2);
        customSortButton->setObjectName("customSortButton");

        verticalLayout->addWidget(customSortButton);


        gridLayout->addLayout(verticalLayout, 3, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        saveButton = new QPushButton(centralwidget_2);
        saveButton->setObjectName("saveButton");

        verticalLayout_2->addWidget(saveButton);

        loadButton = new QPushButton(centralwidget_2);
        loadButton->setObjectName("loadButton");

        verticalLayout_2->addWidget(loadButton);


        gridLayout->addLayout(verticalLayout_2, 3, 2, 1, 1);

        plainTextEdit = new QPlainTextEdit(centralwidget_2);
        plainTextEdit->setObjectName("plainTextEdit");

        gridLayout->addWidget(plainTextEdit, 4, 0, 1, 2);

        loadFromTextButton = new QPushButton(centralwidget_2);
        loadFromTextButton->setObjectName("loadFromTextButton");

        gridLayout->addWidget(loadFromTextButton, 4, 2, 1, 1);

        menubar_2 = new QMenuBar(centralwidget);
        menubar_2->setObjectName("menubar_2");
        menubar_2->setGeometry(QRect(10, 10, 800, 21));
        statusbar_2 = new QStatusBar(centralwidget);
        statusbar_2->setObjectName("statusbar_2");
        statusbar_2->setGeometry(QRect(10, 10, 3, 27));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        removeButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        loadImageButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        imageLabel->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        addListButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262 \321\201\320\277\320\270\321\201\320\276\320\272", nullptr));
        removeListButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\270\320\267 \321\201\320\277\320\270\321\201\320\272\320\260", nullptr));
        sortListButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272", nullptr));
        customSortButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\201\320\276\320\261\320\260\321\217 \321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\272\320\260", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        plainTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\260\320\275\320\275\321\213\320\265 \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265: \320\244\320\260\320\274\320\270\320\273\320\270\321\217,\320\222\321\200\320\265\320\274\321\217,IP (\320\272\320\260\320\266\320\264\320\260\321\217 \320\267\320\260\320\277\320\270\321\201\321\214 \321\201 \320\275\320\276\320\262\320\276\320\271 \321\201\321\202\321\200\320\276\320\272\320\270)", nullptr));
        loadFromTextButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267 \321\202\320\265\320\272\321\201\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
