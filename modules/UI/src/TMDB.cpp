//
// Created by Iusaq on 12/8/2022.
//

#include <QObject>
#include <QNetworkReply>
#include <QJsonDocument>
#include "TMDB.h"
#include <QPixmap>
#include <QEventLoop>


TMDB::TMDB(const long long int &movieId) {
    this->tmdb_id = new QString(QString::number(movieId));
    this->setMovie();
}

void TMDB::setMovie() {

    QString urlStr = this->m_baseUrl;
    urlStr.append(*this->tmdb_id);
    urlStr.append(this->m_apiKey);

    qDebug()<<urlStr;


    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &TMDB::movieDataReceived);

    manager->get(QNetworkRequest(QUrl(urlStr)));

}



void TMDB::setImage() {
    QString urlStr = this->m_tmdbImagesUrl;
    urlStr.append(this->m_posterPath);
    qDebug()<<urlStr;

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &TMDB::imageDownloaded);

    manager->get(QNetworkRequest(QUrl(urlStr)));

}


void TMDB::movieDataReceived(QNetworkReply *replyReceived) {

    QByteArray movieData = replyReceived->readAll();

    QJsonParseError *parseError;
    QJsonDocument document = QJsonDocument::fromJson(movieData, parseError);

    if (parseError->error != QJsonParseError::NoError) {
        qCritical() << "Error parsing JSON:" << parseError->errorString();
        return;
    }

    this->m_adult = document["adult"].toBool();
    this->m_budget = document["budget"].toInt();
    this->m_overview = document["overview"].toString();
    this->m_popularity = document["popularity"].toInt();
    this->m_posterPath = document["poster_path"].toString();
    qDebug()<<m_posterPath;
    QString dateStr(document["release_date"].toString());
    this->m_releaseDate = QDate::fromString(dateStr, "yyyy-MM-dd");
    qDebug() << m_releaseDate;
    this->m_revenue = document["revenue"].toDouble();
    this->m_runtime = document["runtime"].toDouble();

    this->setImage();

}

void TMDB::imageDownloaded(QNetworkReply *replyReceived) {

    QByteArray byteArray = replyReceived->readAll();

    this->pixmap = new QPixmap();

    this->pixmap->loadFromData(byteArray);

}