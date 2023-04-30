#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

#include <QTimer>

class FeatureHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool featureA READ featureA NOTIFY featureAUpdated)
    Q_PROPERTY(bool featureB READ featureB NOTIFY featureBUpdated)

public:
    explicit FeatureHandler(QObject *parent = nullptr);
    ~FeatureHandler();

    // features
    bool featureA() const;
    bool featureB() const;

signals:
    void featureAUpdated(bool featureA);
    void featureBUpdated(bool featureB);

public slots:
    void networkReplyReadyRead();
    void networkReplyErrorOccurred();

    void getFeatures();

private:
    void performGET( const QString & url );
    void parseResponse( const QByteArray & reponse );

    QNetworkAccessManager * m_networkAccessManager;
    QNetworkReply * m_networkReply;

     // features
    QTimer *m_timer;
    bool m_featureA;
    bool m_featureB;
};
