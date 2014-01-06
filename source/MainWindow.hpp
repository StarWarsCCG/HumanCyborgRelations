#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtSql>

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
    void on_cardListWidget_clicked(const QModelIndex &index);

private:
    void loadCard(qint64 id);

    Ui::MainWindow *ui;
    QSqlDatabase _database;
};

#endif
