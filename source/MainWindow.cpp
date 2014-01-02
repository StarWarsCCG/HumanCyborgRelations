#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "DownloadDialog.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DownloadDialog* dd = new DownloadDialog(this);
    dd->begin(QUrl("https://dl.dropboxusercontent.com/u/2999971/swccg.sqlite"),
              "swccg.sqlite");
}

MainWindow::~MainWindow()
{
    delete ui;
}
