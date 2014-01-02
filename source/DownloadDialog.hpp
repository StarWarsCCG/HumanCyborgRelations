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
    explicit DownloadDialog(QWidget *parent = 0);
    virtual ~DownloadDialog();

    bool begin(QUrl source, QString destination);

    bool completed() const { return _completed; }

signals:

public slots:

private slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void dispose();
    void downloadReadyRead();
};

#endif
