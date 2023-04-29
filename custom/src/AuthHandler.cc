#include "AuthHandler.h"
#include <QDebug>
#include <QVariantMap>
#include <QNetworkRequest>
#include <QJsonObject>

AuthHandler::AuthHandler(QObject *parent)
    : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager( this );
}

AuthHandler::~AuthHandler()
{
    m_networkAccessManager->deleteLater();
}

void AuthHandler::getFeatures()
{
    QString featuresEndpoint = "http://localhost:10117";

    performGET( featuresEndpoint );
}

void AuthHandler::networkReplyReadyRead()
{
    qDebug() << "response";
    QByteArray response = m_networkReply->readAll();

    m_networkReply->deleteLater();

    parseResponse( response );
}

void AuthHandler::networkReplyErrorOccurred()
{
    qDebug() << "error occurred";
}

void AuthHandler::performGET(const QString &url)
{
    qDebug() << "perform GET";
    QNetworkRequest newRequest( (QUrl( url )) );
    newRequest.setHeader( QNetworkRequest::ContentTypeHeader, QString( "application/json"));
    m_networkReply = m_networkAccessManager->get( newRequest );
    connect( m_networkReply, &QNetworkReply::readyRead, this, &AuthHandler::networkReplyReadyRead );
    connect( m_networkReply, &QNetworkReply::errorOccurred, this, &AuthHandler::networkReplyErrorOccurred );
    qDebug() << "done perform GET";
}

void AuthHandler::parseResponse(const QByteArray &response)
{
    qDebug() << "parsing response";
    qDebug() << response;
    // QJsonDocument jsonDocument = QJsonDocument::fromJson( response );
    // if ( jsonDocument.object().contains("error") )
    // {
    //     qDebug() << "Error occured!" << response;
    // }
    // else if ( jsonDocument.object().contains("kind"))
    // {
    //     QString idToken = jsonDocument.object().value("idToken").toString();
    //     //qDebug() << "Obtained user ID Token: " << idToken;
    //     qDebug() << "User signed in successfully!";
    //     m_idToken = idToken;
    //     emit userSignedIn();
    // }
    // else
    //     qDebug() << "The response was: " << response;
}