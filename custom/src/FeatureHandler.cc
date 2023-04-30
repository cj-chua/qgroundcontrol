#include "FeatureHandler.h"
#include <QDebug>
#include <QVariantMap>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>

#include <QTimer>

FeatureHandler::FeatureHandler(QObject *parent)
    : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager( this );

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &FeatureHandler::getFeatures);
    m_featureA = false;
    m_featureB = false;
    m_timer->start(1000);
}

FeatureHandler::~FeatureHandler()
{
    m_networkAccessManager->deleteLater();
}

bool FeatureHandler::featureA() const
{
    return m_featureA;
}

bool FeatureHandler::featureB() const
{
    return m_featureB;
}

void FeatureHandler::getFeatures()
{
    QString featuresEndpoint = "http://localhost:8080/api/features";

    performGET( featuresEndpoint );
}

void FeatureHandler::networkReplyReadyRead()
{
    QByteArray response = m_networkReply->readAll();

    m_networkReply->deleteLater();

    parseResponse( response );
}

void FeatureHandler::networkReplyErrorOccurred()
{
    qDebug() << "error occurred";
    m_featureA = false;
    m_featureB = false;
}

void FeatureHandler::performGET(const QString &url)
{
    QNetworkRequest newRequest( (QUrl( url )) );
    newRequest.setHeader( QNetworkRequest::ContentTypeHeader, QString( "application/json"));
    m_networkReply = m_networkAccessManager->get( newRequest );
    connect( m_networkReply, &QNetworkReply::readyRead, this, &FeatureHandler::networkReplyReadyRead );
    connect( m_networkReply, &QNetworkReply::errorOccurred, this, &FeatureHandler::networkReplyErrorOccurred );
}

void FeatureHandler::parseResponse(const QByteArray &response)
{
    qDebug() << response;
    QJsonDocument jsonDocument = QJsonDocument::fromJson( response );
    bool a = jsonDocument.object().value("a").toBool();
    bool b = jsonDocument.object().value("b").toBool();
    qDebug() << "A is: " << a;
    qDebug() << "B is: " << b;
    m_featureA = a;
    m_featureB = b;
    emit featureAUpdated(m_featureA);
    emit featureBUpdated(m_featureB);
}