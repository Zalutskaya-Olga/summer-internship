#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QKeyEvent>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Настройка таблицы
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"Фамилия", "Время разговора", "IP адрес"});
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Настройка списка
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    // Настройка ComboBox
    comboModel = new QStringListModel(this);
    ui->comboBox->setModel(comboModel);
    updateComboBox();

    // Настройка ListView
    updateListView();

    // Контекстное меню для списка
    contextMenu = new QMenu(this);
    contextMenu->addAction("Удалить", this, [this]() {
        if (ui->listWidget->currentRow() >= 0) {
            delete ui->listWidget->takeItem(ui->listWidget->currentRow());
        }
    });

    // Контекстное меню для таблицы
    tableContextMenu = new QMenu(this);
    tableContextMenu->addAction("Удалить строку", this, [this]() {
        if (ui->tableWidget->currentRow() >= 0) {
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());
            updateComboBox();
            updateListView();
            updateArraySize();
        }
    });

    // Подключение обработчиков правой кнопки мыши
    connect(ui->listWidget, &QListWidget::customContextMenuRequested, this, &MainWindow::handleRightClick);
    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this, &MainWindow::handleTableRightClick);

    // Установка контекстного меню
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    // Настройка отображения размера массива
    arraySizeLabel = new QLabel(this);
    ui->statusbar->addWidget(arraySizeLabel);
    updateArraySize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateArraySize()
{
    int size = ui->tableWidget->rowCount();
    arraySizeLabel->setText(QString("Записей: %1").arg(size));
}

void MainWindow::on_addButton_clicked()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    QTableWidgetItem *lastNameItem = new QTableWidgetItem("Иванов");
    QTableWidgetItem *timeItem = new QTableWidgetItem("30");
    QTableWidgetItem *ipItem = new QTableWidgetItem("192.168.1.1");

    ui->tableWidget->setItem(row, 0, lastNameItem);
    ui->tableWidget->setItem(row, 1, timeItem);
    ui->tableWidget->setItem(row, 2, ipItem);

    updateComboBox();
    updateListView();
    updateArraySize();
}

void MainWindow::on_removeButton_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        ui->tableWidget->removeRow(currentRow);
        updateComboBox();
        updateListView();
        updateArraySize();
    }
}

void MainWindow::on_addListButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Добавить элемент", "Введите текст:", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        ui->listWidget->addItem(text);
    }
}

void MainWindow::on_removeListButton_clicked()
{
    if (ui->listWidget->currentRow() >= 0) {
        delete ui->listWidget->takeItem(ui->listWidget->currentRow());
    }
}

void MainWindow::on_sortListButton_clicked()
{
    ui->listWidget->sortItems();
}

void MainWindow::on_customSortButton_clicked()
{
    QList<QListWidgetItem*> items;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        items.append(ui->listWidget->item(i));
    }

    std::sort(items.begin(), items.end(), [](QListWidgetItem *a, QListWidgetItem *b) {
        return a->text().length() < b->text().length();
    });

    for (int i = 0; i < items.count(); ++i) {
        ui->listWidget->insertItem(i, items.at(i)->clone());
        delete items.at(i);
    }
}

void MainWindow::on_loadImageButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите изображение", "", "Images (*.png *.jpg *.bmp)");
    if (!filename.isEmpty()) {
        displayImage(filename);
    }
}

void MainWindow::on_saveButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить данные", "", "Text files (*.txt)");
    if (!filename.isEmpty()) {
        saveDataToFile(filename);
    }
}

void MainWindow::on_loadButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Загрузить данные", "", "Text files (*.txt)");
    if (!filename.isEmpty()) {
        loadDataFromFile(filename);
    }
}

void MainWindow::on_loadFromTextButton_clicked()
{
    QString text = ui->plainTextEdit->toPlainText();
    QStringList lines = text.split("\n");

    ui->tableWidget->setRowCount(0);
    for (const QString &line : lines) {
        QStringList parts = line.split(",");
        if (parts.size() == 3) {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(parts[0]));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(parts[1]));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(parts[2]));
        }
    }
    updateComboBox();
    updateListView();
    updateArraySize();
}

void MainWindow::handleRightClick(const QPoint &pos)
{
    if (ui->listWidget->itemAt(pos)) {
        contextMenu->exec(ui->listWidget->mapToGlobal(pos));
    }
}

void MainWindow::handleTableRightClick(const QPoint &pos)
{
    if (ui->tableWidget->itemAt(pos)) {
        tableContextMenu->exec(ui->tableWidget->mapToGlobal(pos));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // Обработка Delete для Mac (обычный Backspace или Fn+Backspace)
    if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) {
        if (ui->tableWidget->hasFocus() && ui->tableWidget->currentRow() >= 0) {
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());
            updateComboBox();
            updateListView();
            updateArraySize();
        } else if (ui->listWidget->hasFocus() && ui->listWidget->currentRow() >= 0) {
            delete ui->listWidget->takeItem(ui->listWidget->currentRow());
        }
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::loadDataFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    ui->tableWidget->setRowCount(0);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() == 3) {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(parts[0]));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(parts[1]));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(parts[2]));
        }
    }
    file.close();
    updateComboBox();
    updateListView();
    updateArraySize();
}

void MainWindow::saveDataToFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи");
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QString lastName = ui->tableWidget->item(i, 0)->text();
        QString time = ui->tableWidget->item(i, 1)->text();
        QString ip = ui->tableWidget->item(i, 2)->text();
        out << lastName << "," << time << "," << ip << "\n";
    }
    file.close();
}

void MainWindow::updateComboBox()
{
    QStringList items;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        items << ui->tableWidget->item(i, 0)->text();
    }
    comboModel->setStringList(items);
}

void MainWindow::updateListView()
{
    QStringListModel *model = new QStringListModel(this);
    QStringList items;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        items << QString("%1 - %2 мин - %3")
                     .arg(ui->tableWidget->item(i, 0)->text())
                     .arg(ui->tableWidget->item(i, 1)->text())
                     .arg(ui->tableWidget->item(i, 2)->text());
    }
    model->setStringList(items);
    ui->listView->setModel(model);
}

void MainWindow::displayImage(const QString &filename)
{
    QPixmap pixmap(filename);
    if (!pixmap.isNull()) {
        ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio));
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить изображение");
    }
}
