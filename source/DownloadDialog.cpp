#include "DownloadDialog.hpp"
#include <QNetworkRequest>
#include <QLabel>
#include <QDebug>

DownloadDialog::DownloadDialog(QWidget *parent)
    : QProgressDialog("Downloading", "Cancel", 0, 100, parent)
    , _download(nullptr)
    , _completed(false)
{
    setValue(0);
    setWindowTitle("File Download");
}

DownloadDialog::~DownloadDialog()
{
    dispose();
}

bool DownloadDialog::begin(QUrl source, QString destination)
{
    bool result = false;

    if (!_download)
    {
        _completed = false;
        _destination.setFileName(destination);
        _destination.remove();

        if (_destination.open(QIODevice::WriteOnly))
        {
            QNetworkRequest request(source);
            request.setRawHeader("User-Agent", "Mozilla Firefox");
            _download = _manager.get(request);

            //qDebug() << _download->error();

            connect(_download, SIGNAL(downloadProgress(qint64,qint64)),
                    SLOT(downloadProgress(qint64,qint64)));
            connect(_download, SIGNAL(finished()), SLOT(dispose()));
            connect(_download, SIGNAL(readyRead()), SLOT(downloadReadyRead()));
            connect(this, SIGNAL(canceled()), SLOT(dispose()));

            setLabelText("Downloading " + destination);
            show();

            result = true;
        }
    }

    return result;
}

void DownloadDialog::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    //qDebug() << "dP";
    int result = 100;

    if (bytesTotal > 0)
    {
        result = bytesReceived * qint64(100) / bytesTotal;

        if (bytesReceived == bytesTotal) _completed = true;
    }

    setValue(result);
}

void DownloadDialog::dispose()
{
    _destination.close();

    if (_download)
    {
        if (_download->error())
            qDebug() << _download->errorString();

        _download->deleteLater();
        _download = nullptr;
    }
}

void DownloadDialog::downloadReadyRead()
{
    //qDebug() << "dRR";
    _destination.write(_download->readAll());
}
