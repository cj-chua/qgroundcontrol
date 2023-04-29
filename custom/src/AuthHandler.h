#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

class AuthHandler : public QObject
{
    Q_OBJECT
public:
    explicit AuthHandler(QObject *parent = nullptr);
    ~AuthHandler();
    void getFeatures();

public slots:
    void networkReplyReadyRead();
    void networkReplyErrorOccurred();

private:
    void performGET( const QString & url );
    void parseResponse( const QByteArray & reponse );

    QNetworkAccessManager * m_networkAccessManager;
    QNetworkReply * m_networkReply;
};
