#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "DownloadDialog.hpp"
#include <QListWidget>
#include <QListWidgetItem>

static const QString DatabaseFile("swccg.sqlite");
static const QString Title("title");
static const QString Id("id");
static const QString IsLight("is_light");

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
        QSqlQuery query("SELECT * FROM cards", _database);

        while (query.next())
        {
            QString title = query.value(Title).toString();
            auto id = query.value(Id).toLongLong();

            QListWidgetItem* item =
                new QListWidgetItem(title, ui->cardListWidget);

            item->setData(Qt::UserRole, id);

            bool isLight = query.value(IsLight).toBool();

            if (!isLight)
            {
                item->setBackgroundColor(QColor(224, 224, 224));
            }
        }

        ui->cardListWidget->sortItems();
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

void MainWindow::on_cardListWidget_clicked(const QModelIndex &index)
{
    (void)index;
    auto item = ui->cardListWidget->currentItem();
    qDebug() << item->data(Qt::UserRole).toLongLong();
}
