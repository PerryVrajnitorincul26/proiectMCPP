//
// Created by Iusaq on 12/2/2022.
//

#ifndef MCPP_MOVIEDTO_H
#define MCPP_MOVIEDTO_H


#include <QPixmap>
#include <QJsonValue>
#include <QNetworkReply>

class MovieDTO : public QObject {
Q_OBJECT
    QPixmap *pix = nullptr;

    QString rating;
    QString title;
    QJsonValue genres;

    QString *apiUrl = nullptr;
    QString *imageUrl = nullptr;

    QNetworkAccessManager *dataManager;

public:
    void setMovie();

    void setImage(QString &imageApi);

private slots:

    void dataDownloaded(QNetworkReply *reply);

    void imageDownloaded(QNetworkReply *reply);

public:
    MovieDTO(QString &apiUrl);


};


#endif //MCPP_MOVIEDTO_H
