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
                //item->setBackgroundColor(QColor(64, 64, 64));
                //item->setTextColor(QColor(255, 255, 255));
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
    auto id = item->data(Qt::UserRole).toLongLong();
    qDebug() << id;

    QString content;

    QSqlQuery query(_database);
    if (query.prepare("SELECT ta.name,ct.content FROM card_text ct INNER JOIN text_attributes ta ON ct.text_attribute_id = ta.id WHERE card_id = ?"))
    {
        query.bindValue(0, id);
        query.exec();

        while (query.next())
        {
            content
                .append(query.value("name").toString())
                .append("\n")
                .append(query.value("content").toString())
                .append("\n\n");
        }
    }
    else
    {
        qDebug() << "Failed to prepare statement";
    }

    ui->cardTextEdit->setText(content);
}
