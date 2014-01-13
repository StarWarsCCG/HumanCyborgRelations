#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "DownloadDialog.hpp"
#include <QListWidget>

static const QString DatabaseFile("swccg.sqlite");
static const QString Title("title");
static const QString Name("name");
static const QString Id("id");
static const QString IsLight("is_light");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _database(QSqlDatabase::addDatabase("QSQLITE"))
{
    ui->setupUi(this);

    ui->cardTableWidget->setColumnCount(2);
    ui->cardTableWidget->setHorizontalHeaderItem(0,
        new QTableWidgetItem("Title"));
    ui->cardTableWidget->setHorizontalHeaderItem(1,
        new QTableWidgetItem("Type"));
    ui->cardTableWidget->verticalHeader()->setDefaultSectionSize(15);

    //if (!QFile::exists(DatabaseFile))
        //new DownloadDialog(QUrl("https://dl.dropboxusercontent.com/u/2999971/swccg.sqlite"), DatabaseFile, this);

    _database.setDatabaseName(DatabaseFile);

    if (_database.open())
    {
        int row = 0;
        QSqlQuery query("SELECT c.id, c.title, c.is_light, ct.name"
                        " FROM cards c"
                        " INNER JOIN card_types ct"
                        " ON c.card_type_id = ct.id",
                        _database);

        while (query.next())
        {
            QString title = query.value(Title).toString();
            QString typeName = query.value(Name).toString();
            auto id = query.value(Id);

            ui->cardTableWidget->setRowCount(row + 1);

            auto titleItem = new QTableWidgetItem(title);
            ui->cardTableWidget->setItem(row, 0, titleItem);

            auto typeItem = new QTableWidgetItem(typeName);
            ui->cardTableWidget->setItem(row++, 1, typeItem);

            titleItem->setData(Qt::UserRole, id);
            typeItem->setData(Qt::UserRole, id);

            bool isLight = query.value(IsLight).toBool();

            if (!isLight)
            {
                titleItem->setBackgroundColor(QColor(224, 224, 224));
                typeItem->setBackgroundColor(QColor(224, 224, 224));
            }
        }

        ui->cardTableWidget->resizeColumnsToContents();
        ui->cardTableWidget->sortItems(0);
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

void MainWindow::loadCard(const QVariant& id)
{
    qDebug() << id;

    QString content;

    QSqlQuery query(_database);
    if (query.prepare(
        "SELECT ta.name,ct.content"
        " FROM card_text ct"
        " INNER JOIN text_attributes ta"
        " ON ct.text_attribute_id = ta.id WHERE card_id = ?"))
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

void MainWindow::on_cardTableWidget_currentItemChanged(QTableWidgetItem*,
    QTableWidgetItem*)
{
    auto item = ui->cardTableWidget->currentIndex();
    auto id = item.data(Qt::UserRole);
    loadCard(id);
}
