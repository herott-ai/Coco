#ifndef LOGIN_H
#define LOGIN_H
#include <QCoreApplication>
#include <QString>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QMap>
#include <QByteArray>
#include <QJsonArray>

class Login
{
public:
    Login();
    QMap<QString, QString> submitLogin(const QString &phone, const QString &password);
public:
      QString getRandomUserAgent();
      qint64 getTimeStamp13();
      QMap<QString, QString> getCode(const QString &userAgent);
      QString passSlide(const QString &imgBase64, const QString &userAgent);
      QString getMd5(const QString &data);
};

#endif // LOGIN_H
