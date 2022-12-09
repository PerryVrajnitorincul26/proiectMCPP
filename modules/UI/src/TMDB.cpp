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
    m_naManager = new QNetworkAccessManager(this);
    this->setMovie();
}

void TMDB::setMovie() {

    QString urlStr = this->m_baseUrl;
    urlStr.append(*this->tmdb_id);
    urlStr.append(this->m_apiKey);

    qDebug() << urlStr;

    auto reply = m_naManager->get(QNetworkRequest(QUrl(urlStr)));
    connect(reply, &QNetworkReply::finished, this, &TMDB::dataFinished);
}


void TMDB::imageDownloaded(QNetworkReply *replyReceived) {

    QByteArray byteArray = replyReceived->readAll();

    this->pixmap = new QPixmap();

    this->pixmap->loadFromData(byteArray);
}

void TMDB::dataFinished() {
    auto replyReceived = qobject_cast<QNetworkReply *>(sender());
    //Note that partial reads are possible though likely unnecessary in our case
    QByteArray movieData = replyReceived->readAll();
    QJsonParseError *parseError = new QJsonParseError;
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
    qDebug() << m_posterPath;
    QString dateStr(document["release_date"].toString());
    this->m_releaseDate = QDate::fromString(dateStr, "yyyy-MM-dd");
    qDebug() << m_releaseDate;
    this->m_revenue = document["revenue"].toDouble();
    this->m_runtime = document["runtime"].toDouble();

    //Set up the next request in the chain
    QString urlStr = this->m_tmdbImagesUrl;
    urlStr.append(this->m_posterPath);

    auto imreq = m_naManager->get(QNetworkRequest(QUrl(urlStr)));
    connect(imreq, &QNetworkReply::finished, this, &TMDB::imageFinished);
    replyReceived->deleteLater();
}

void TMDB::imageFinished() {
    auto replyReceived = qobject_cast<QNetworkReply *>(sender());
    QByteArray byteArray = replyReceived->readAll();
    //replyReceived->
    delete this->pixmap;
    this->pixmap = new QPixmap();

    //replyReceived->
    this->pixmap->loadFromData(byteArray, "JPG");
    qDebug() << "you have reached the end of the request cascade";
    emit(finishedLoading());
    replyReceived->deleteLater();
}

TMDB::~TMDB() {
    delete this->pixmap;
    delete this->m_naManager;
}
