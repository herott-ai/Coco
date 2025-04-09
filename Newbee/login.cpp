#include "login.h"


// 定义 User-Agent 列表
const QVector<QString> USER_AGENTS = {
    "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2228.0 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2227.1 Safari/537.36",
    "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2227.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2227.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2226.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.4; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2225.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2225.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2224.3 Safari/537.36",
    "Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/40.0.2214.93 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2062.124 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2049.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 4.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2049.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/36.0.1985.67 Safari/537.36",
    "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/36.0.1985.67 Safari/537.36",
    "Mozilla/5.0 (X11; OpenBSD i386) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/36.0.1985.125 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/36.0.1944.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.3319.102 Safari/537.36",
    "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.2309.372 Safari/537.36",
    "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.2117.157 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.47 Safari/537.36",
    "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1866.237 Safari/537.36",
    "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.137 Safari/4E423F",
    "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.116 Safari/537.36 Mozilla/5.0 (iPad; U; CPU OS 3_2 like Mac OS X; en-us) AppleWebKit/531.21.10 (KHTML, like Gecko) Version/4.0.4 Mobile/7B334b Safari/531.21.10",
    "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/33.0.1750.517 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.2; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1667.0 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1664.3 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_8_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1664.3 Safari/537.36",
    "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.16 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1623.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/30.0.1599.17 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.62 Safari/537.36",
    "Mozilla/5.0 (X11; CrOS i686 4319.74.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.57 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.2 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1468.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1467.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1464.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1500.55 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.93 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.93 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.93 Safari/537.36",
    "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.93 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/26.0.1410.43 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/26.0.1410.43 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/26.0.1403.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/26.0.1403.0 Safari/537.36",
    "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/26.0.1403.0 Safari/537.36"
};

QString Login::getMd5(const QString &data) {
    // 计算 MD5 签名
    QByteArray hash = QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Md5);
    return hash.toHex();
}

QString Login::getRandomUserAgent() {
    int index = QRandomGenerator::global()->bounded(USER_AGENTS.count());
    return USER_AGENTS[index];
}

qint64 Login::getTimeStamp13() {
//    // 获取当前时间
//    QDateTime currentDateTime = QDateTime::currentDateTime();

//    // 获取自1970年1月1日以来的秒数
//    qint64 seconds = currentDateTime.toSecsSinceEpoch();

//    // 获取当前微秒（精确到6位）
//    int microseconds = currentDateTime.time().microSecondsSinceStartOfDay();

//    // 将微秒的前3位数提取出来
//    QString microSecondsStr = QString::number(microseconds).left(3);

//    // 拼接秒数和微秒
//    QString timestampStr = QString::number(seconds) + microSecondsStr;

//    return timestampStr.toLongLong();
    // 获取当前时间
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 获取自1970年1月1日以来的秒数
    qint64 seconds = currentDateTime.toSecsSinceEpoch();

    // 获取当前微秒，并取前三位
    int microseconds = currentDateTime.time().msec(); // 获取毫秒部分（0-999）
    QString microSecondsStr = QString::number(microseconds).rightJustified(3, '0'); // 转为字符串并确保3位

    // 拼接秒数和毫秒字符串
    QString timestampStr = QString::number(seconds) + microSecondsStr;

    // 转为整数并返回
    return timestampStr.toLongLong();
}

// 获取验证码
QMap<QString, QString> Login::getCode(const QString &userAgent) {
    QMap<QString, QString> slideDict;

    // 时间戳
    qint64 timestamp = getTimeStamp13();

    // URL
    QString url = QString("https://api.newbee.net.cn/api/sms/getCode?timestamp=%1").arg(timestamp);

    // 签名数据
    QString signatureData = QString("api/sms/getcode?timestamp=%1&key=6rnrdpjjv6wz2sspxqeibesov1itxddc").arg(timestamp);
    QString signature = getMd5(signatureData);

    // 设置请求头
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("user-agent", userAgent.toUtf8());
    request.setRawHeader("Signature", "2bd17b71495819c32b37b39388bcb2ac");
    request.setRawHeader("Token", "null");
    request.setRawHeader("X-Token", signature.toUtf8());

    // 发送 GET 请求
    QNetworkAccessManager manager;
    qDebug() << manager.supportedSchemes();
    QNetworkReply *reply = manager.get(request);

    // 等待响应完成
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // 解析响应
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            if (jsonObj["code"].toInt() == 1) {
                QJsonObject dataObj = jsonObj["data"].toObject();
                QString imgBase64 = dataObj["base64"].toString().split(",").last();
                QString slideId = dataObj["id"].toString();

                slideDict.insert("imgBase64", imgBase64);
                slideDict.insert("slideId", slideId);
                qDebug() << "验证码获取成功";
            } else {
                qDebug() << "验证码获取失败";
            }
        }
    } else {
        qDebug() << "验证码获取网络请求错误:" << reply->errorString();
    }

    reply->deleteLater();
    return slideDict;
}


QString Login::passSlide(const QString &imgBase64, const QString &userAgent) {
    QNetworkAccessManager manager;
    QUrl url("http://124.220.169.77:5000/passSlideNewBee_V1");
    QNetworkRequest request(url);

    // 设置请求头
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 构造 JSON 数据
    QJsonObject jsonData;
    jsonData["imgBase64"] = imgBase64;

    QJsonDocument jsonDoc(jsonData);
    QByteArray postData = jsonDoc.toJson();

    // 发送 POST 请求并等待完成
    QNetworkReply *reply = manager.post(request, postData);

    // 等待请求完成
    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 检查请求结果
    if (reply->error() == QNetworkReply::NoError) {
        // 解析 JSON 响应
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (!jsonResponse.isNull() && jsonResponse.isObject()) {
            QJsonObject responseObject = jsonResponse.object();
            if (responseObject["code"].toInt() == 1) {
                QString captcha = responseObject["result"].toString();
                qDebug() << "验证码识别成功:" << captcha;
                reply->deleteLater(); // 释放资源
                return captcha;
            } else {
                qDebug() << "验证码识别失败: 错误代码" << responseObject["code"].toInt();
            }
        } else {
            qDebug() << "解析 JSON 响应失败";
        }
    } else {
        qDebug() << "解析验证码网络请求错误:" << reply->errorString();
    }

    reply->deleteLater(); // 释放资源
    return QString();
}

QMap<QString, QString>  Login::submitLogin(const QString &phone, const QString &password) {
    QString userAgent = getRandomUserAgent();
    QMap<QString,QString> slideDict = getCode(userAgent);
    QString captcha = passSlide(slideDict["imgBase64"], userAgent);
    QString slideId = slideDict["slideId"];

    QNetworkAccessManager manager;
    QUrl url("https://api.newbee.net.cn/api/user/login");
    QNetworkRequest request(url);

    // 设置请求头 // keeping int is also ok
    QString timestamp = QString::number(getTimeStamp13());
    QString signatureData = QString("api/user/login?captcha=%1&id=%2&mobile=%3&password=%4&timestamp=%5&key=6rnrdpjjv6wz2sspxqeibesov1itxddc")
            .arg(captcha)
            .arg(slideId)
            .arg(phone)
            .arg(password)
            .arg(timestamp);
    QString signature = getMd5(signatureData);

    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Signature", "2bd17b71495819c32b37b39388bcb2ac");
    request.setRawHeader("X-Token", signature.toUtf8());
    request.setRawHeader("Token", "");

    // 构造 JSON 数据
    QJsonObject jsonData;
    jsonData["captcha"] = captcha;
    jsonData["id"] = slideId;
    jsonData["mobile"] = phone;
    jsonData["password"] = password;
    jsonData["timestamp"] = timestamp;

    QJsonDocument jsonDoc(jsonData);
    QByteArray postData = jsonDoc.toJson();

    // 发送 POST 请求并等待完成
    QNetworkReply *reply = manager.post(request, postData);

    // 使用事件循环等待请求完成
    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 解析响应
    QMap<QString, QString> userMap;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (!jsonResponse.isNull() && jsonResponse.isObject()) {
            QJsonObject responseObject = jsonResponse.object();
            qDebug() << "响应数据:" << jsonResponse;

            if (responseObject["code"].toInt() == 1) {
                QJsonObject userInfo = responseObject["data"].toObject()["userinfo"].toObject();
                QString token = userInfo["token"].toString();
                int userId = userInfo["user_id"].toInt();
                qDebug() << "登录成功, token:" << token << "user_id:" << userId;
                reply->deleteLater();
                userMap[phone] = token;
                return userMap;
            } else {
                qDebug() << "登录失败, 错误信息:" << responseObject["msg"].toString();
            }
        } else {
            qDebug() << "解析 JSON 响应失败";
        }
    } else {
        qDebug() << "登录网络请求错误:" << reply->errorString();
    }
    userMap[phone] = "null";
    reply->deleteLater();
    return userMap;
}
Login::Login()
{

}
