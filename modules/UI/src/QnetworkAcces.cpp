//
// Created by Bulibas on 11/19/2022.
//

#include "QnetworkAcces.h"

QnetworkAcces::QnetworkAcces(QObject *parent) : QObject(parent) {
    connect(&manager, &QNetworkAccessManager::authenticationRequired, this, &QnetworkAcces::authenticationRequired);
    connect(&manager, &QNetworkAccessManager::encrypted, this, &QnetworkAcces::encrypted);
    connect(&manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this,
            &QnetworkAcces::preSharedKeyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::proxyAuthenticationRequired, this,
            &QnetworkAcces::proxyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &QnetworkAcces::sslErrors);
}

void QnetworkAcces::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator) {


}

void QnetworkAcces::encrypted(QNetworkReply *reply) {

}

void QnetworkAcces::finished(QNetworkReply *reply) {

}

void
QnetworkAcces::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator) {

}

void QnetworkAcces::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator) {

}

void QnetworkAcces::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors) {

}

void QnetworkAcces::readyRead() {
qInfo()<<"ReadyRead";
QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
if(reply) qInfo()<<reply->readAll();
}

void QnetworkAcces::get(QString location) {
    qInfo() << "Getting from server...";
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(location)));
    connect(reply, &QNetworkReply::readyRead, this, &QnetworkAcces::readyRead);
}

void QnetworkAcces::post(QString location, QByteArray data) {
    qInfo() << "Post to server...";
    QNetworkRequest request = QNetworkRequest(QUrl(location));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

    QNetworkReply *reply = manager.post(request, data);
    connect(reply, &QNetworkReply::readyRead, this, &QnetworkAcces::readyRead);
}
