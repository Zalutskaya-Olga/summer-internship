#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QListWidget>
#include <QComboBox>
#include <QListView>
#include <QMenu>
#include <QStringListModel>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_addListButton_clicked();
    void on_removeListButton_clicked();
    void on_sortListButton_clicked();
    void on_customSortButton_clicked();
    void on_loadImageButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void on_loadFromTextButton_clicked();

    void handleRightClick(const QPoint &pos);
    void handleTableRightClick(const QPoint &pos);

    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QMenu *contextMenu;
    QMenu *tableContextMenu;
    QStringListModel *comboModel;
    QLabel *arraySizeLabel;

    void loadDataFromFile(const QString &filename);
    void saveDataToFile(const QString &filename);
    void updateComboBox();
    void updateListView();
    void displayImage(const QString &filename);
    void updateArraySize();
};
#endif // MAINWINDOW_H
