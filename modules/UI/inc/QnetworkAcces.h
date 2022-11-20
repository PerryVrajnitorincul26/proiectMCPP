//
// Created by Bulibas on 11/19/2022.
//

#ifndef MCPP_QNETWORKACCES_H
#define MCPP_QNETWORKACCES_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QDebug>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>

class QnetworkAcces : public QObject {
    Q_OBJECT
public:
    explicit QnetworkAcces(QObject *parent=nullptr);

    signals:

public slots:

    void get(QString location);
    void post(QString location, QByteArray data);

private slots:
    void    readyRead();
    void 	authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void 	encrypted(QNetworkReply *reply);
    void 	finished(QNetworkReply *reply);
    void 	preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
    void 	proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void 	sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

private:
     QNetworkAccessManager manager;
};


#endif //MCPP_QNETWORKACCES_H
