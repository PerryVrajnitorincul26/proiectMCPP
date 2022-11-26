//
// Created by Bulibas on 11/19/2022.
//

#ifndef MCPP_QNETWORKACCES_H
#define MCPP_QNETWORKACCES_H

#include "../../../../../Qt/6.4.0/mingw_64/include/QtCore/QObject"
#include "../../../../../Qt/6.4.0/mingw_64/include/QtNetwork/QNetworkAccessManager"
#include "../../../../../Qt/6.4.0/mingw_64/include/QtCore/QDebug"
#include "../../../../../Qt/6.4.0/mingw_64/include/QtNetwork/QNetworkProxy"
#include "../../../../../Qt/6.4.0/mingw_64/include/QtNetwork/QNetworkReply"
#include "../../../../../Qt/6.4.0/mingw_64/include/QtNetwork/QNetworkRequest"
#include "../../../../../Qt/6.4.0/mingw_64/include/QtNetwork/QAuthenticator"

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
