//
// Created by Iusaq on 12/8/2022.
//

#include <QObject>
#include <QNetworkReply>
#include <QJsonDocument>
#include "TMDB.h"
#include <QDebug>


TMDB::TMDB(const long long int &movieId) {
    this->m_movieId = QString::number(movieId);
    this->setMovie();

}

void TMDB::setMovie() {
    QString movieDataAccessUrl(m_baseUrl);
    movieDataAccessUrl.append(this->m_movieId);
    movieDataAccessUrl.append(this->m_apiKey);

    this->m_naManager = new QNetworkAccessManager();
    bool success = connect(m_naManager, &QNetworkAccessManager::finished, this, &TMDB::movieDataReceived);
    qDebug()<<success;
    QUrl reqUrl = QUrl(movieDataAccessUrl);
    QNetworkRequest *request = new QNetworkRequest(reqUrl);

    QNetworkReply *replyReceived = m_naManager->get(*request);

}


void TMDB::movieDataReceived(QNetworkReply *replyReceived) {

    QByteArray movieData = replyReceived->readAll();

    QJsonParseError *parseError;
    QJsonDocument document = QJsonDocument::fromJson(movieData, parseError);

    if (parseError->error != QJsonParseError::NoError) {
        qCritical() << "Error parsing JSON:" << parseError->errorString();
        return;
    }

    this->m_adult=document["adult"].toBool();
    this->m_budget=document["budget"].toInt();
    this->m_overview=document["overview"].toString();
    this->m_popularity=document["popularity"].toDouble();
    this->m_posterPath = document["posterPath"].toString();
    QString dateStr(document["release_date"].toString());
    this->m_releaseDate = QDate::fromString(dateStr, "yyyy-MM-dd");
    qDebug()<<m_releaseDate;
    this->m_revenue = document["revenue"].toDouble();
    this->m_runtime = document["runtime"].toDouble();
}

void TMDB::imageDownloaded(QNetworkReply *reply) {

}

