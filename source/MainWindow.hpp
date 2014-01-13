#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtSql>
#include <QListWidgetItem>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_cardTableWidget_currentItemChanged(QTableWidgetItem*,
        QTableWidgetItem*);

private:
    void loadCard(const QVariant& id);

    Ui::MainWindow *ui;
    QSqlDatabase _database;
};

#endif
