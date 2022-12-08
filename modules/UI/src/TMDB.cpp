//
// Created by Iusaq on 12/8/2022.
//

#include <QObject>
#include <QNetworkReply>
#include <QJsonDocument>
#include "TMDB.h"

TMDB::TMDB(const long long int &movieId) {
    this->m_movieId = QString::number(movieId);

}

void TMDB::setMovie() {
    QString movieDataAccessUrl(m_baseUrl);
    movieDataAccessUrl.append(this->m_movieId);
    movieDataAccessUrl.append(this->m_apiKey);

    this->m_naManager = new QNetworkAccessManager();
    auto test = connect(m_naManager, &QNetworkAccessManager::finished, this, &TMDB::movieDataReceived);
    qDebug()<<test;
    QNetworkRequest *request = new QNetworkRequest(QUrl(movieDataAccessUrl));

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

    qDebug()<<"adult:"<<document["adult"];
    qDebug()<<"budget:"<<document["budget"];
    qDebug()<<"overview:"<<document["overview"];
    qDebug()<<"popularity:"<<document["popularity"];
    qDebug()<<"poster_path:"<<document["poster_path"];
    qDebug()<<"release_date:"<<document["release_date"];
    qDebug()<<"revenue:"<<document["revenue"];
    qDebug()<<"runtime:"<<document["runtime"];
}

void TMDB::imageDownloaded(QNetworkReply *reply) {

}

