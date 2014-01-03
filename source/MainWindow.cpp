#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "DownloadDialog.hpp"

static const QString DatabaseFile("swccg.sqlite");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _database(QSqlDatabase::addDatabase("QSQLITE"))
{
    ui->setupUi(this);

    //if (!QFile::exists(DatabaseFile))
        //new DownloadDialog(QUrl("https://dl.dropboxusercontent.com/u/2999971/swccg.sqlite"), DatabaseFile, this);

    _database.setDatabaseName(DatabaseFile);

    if (_database.open())
    {
        _queryModel = new QSqlQueryModel(this);
        _queryModel->setQuery("SELECT * FROM cards");
        ui->tableView->setModel(_queryModel);
    }
    else
    {
        qDebug() << "Failed to open database.";
    }
}

MainWindow::~MainWindow()
{
    _database.close();
    delete ui;
}
