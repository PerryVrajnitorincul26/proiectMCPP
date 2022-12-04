//
// Created by Iusaq on 12/2/2022.
//

#include "MovieDTO.h"
#include <QNetworkReply>
#include <QJsonParseError>
#include <QNetworkRequest>


MovieDTO::MovieDTO(QString &apiUrl) {
    this->apiUrl = new QString(apiUrl);
}

void MovieDTO::setMovie() {
    dataManager = new QNetworkAccessManager();
    auto test = connect(dataManager, &QNetworkAccessManager::finished, this, &MovieDTO::dataDownloaded);
    qDebug()<<test;
    QNetworkRequest *myReq = new QNetworkRequest({"https://api.themoviedb.org/3/movie/550?api_key=7f62067bb2dd1e52cee2dca20be9759a"});
    QNetworkReply *a;
    a = dataManager->get(*myReq);
    auto tmp = a->error();
    auto allinfo = a->readAll();
}

void MovieDTO::setImage(QString &imageApi) {
    QNetworkAccessManager *imgManager = new QNetworkAccessManager(this);
    connect(imgManager, SIGNAL(finished(QNetworkReply * )), this, SLOT(dataDownloaded(QNetworkReply * )));
    const QUrl qurl = QUrl(imageApi);
    QNetworkRequest imgRequest(qurl);
    imgManager->get(imgRequest);
};

void MovieDTO::dataDownloaded(QNetworkReply *reply) {
    QByteArray byteArray = reply->readAll();
    QJsonParseError jsonError;
    auto doc = QJsonDocument::fromJson(byteArray, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error: " << jsonError.errorString();
        //ui->ERROR LABEL TO DO
    } else {
        this->title = doc["title"].toString();
        this->rating = doc["rating"].toString();
        this->imageUrl = new QString("https://image.tmdb.org/t/p/w500");
        QString specificPath(doc["backdrop_path"].toString());
        this->imageUrl->append(specificPath);
    }
}

void MovieDTO::imageDownloaded(QNetworkReply *reply) {
    QByteArray byteArray = reply->readAll();
    this->pix = new QPixmap();
    this->pix->loadFromData(byteArray, "JPG");
}




