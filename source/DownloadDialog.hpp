#ifndef DOWNLOADDIALOG_HPP
#define DOWNLOADDIALOG_HPP

#include <QProgressDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>

class DownloadDialog : public QProgressDialog
{
    Q_OBJECT

    QNetworkAccessManager _manager;
    QNetworkReply* _download;
    QFile _destination;
    bool _completed;

public:
    explicit DownloadDialog(QUrl source, QString destination, QWidget *parent = 0);
    virtual ~DownloadDialog();

signals:
    void downloadSucceeded();
    void downloadFailed();

public slots:

private slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void dispose();
    void downloadReadyRead();
};

#endif
