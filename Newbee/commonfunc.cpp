#include "commonfunc.h"

#include "TokenManager.h"  // we only use it in this file
#include <QDebug>
#include <QThread>

CommonFunc::CommonFunc(QObject* parent)
    : QObject(parent)
{
    this->userAgent = loginHandler.getRandomUserAgent();
    // 连接 TokenManager 的 tokensUpdated 信号到 CommonFunc 的 onTokensUpdated 槽
    connect(&TokenManager::instance(), &TokenManager::tokensUpdated,
            this, &CommonFunc::onTokensUpdated);
}

void CommonFunc::onTokensUpdated(const QMap<QString, QString>& userMap)
{
    m_userMap = userMap;
    qDebug() << "Purchase received updated tokens:" << m_userMap;
}

void CommonFunc::query()
{

    int page=1;// read by input
    //QString token=TokenManager::instance().getUserMap()["phone"];
    // we can get the phone by transfer
    // 登录成功以后，整个标签把号码记录下来 然后从标签里获取号码
    QString token=m_userMap["18934406177"];
    qDebug() << "tokenn:" << token;

    QString timestamp = QString::number(loginHandler.getTimeStamp13());
    QNetworkAccessManager manager;
    QUrl url(QString("https://api.newbee.net.cn/api/user_collect/getAlbumListV2?page=%1&per_page=10&timestamp=%2&type=own_valid").arg(page).arg(timestamp));

    // 设置请求头 // keeping int is also ok

    QNetworkRequest request(url);

    // if you want to change one para, just do it.
    QString signatureData = QString("api/user_collect/getAlbumListV2?page=%1&per_page=10&timestamp=%2&type=own_valid&key=6rnrdpjjv6wz2sspxqeibesov1itxddc").arg(page).arg(timestamp);

    QString signature = loginHandler.getMd5(signatureData);

    request.setHeader(QNetworkRequest::UserAgentHeader, this->userAgent);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setRawHeader("Signature", "2bd17b71495819c32b37b39388bcb2ac");
    request.setRawHeader("X-Token", signature.toUtf8());
    request.setRawHeader("Token", token.toUtf8());

    // 构造 JSON 数据
    QJsonObject jsonData;
    jsonData["page"] = page;
    jsonData["per_page"] = 10;
    jsonData["type"] = "own_valid";
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
    QString token1,token2;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (!jsonResponse.isNull() && jsonResponse.isObject()) {
            QJsonObject responseObject = jsonResponse.object();
            qDebug() << "响应数据:" << jsonResponse;

            if (responseObject["code"].toInt() == 1) {
                 QJsonObject dataObj = responseObject.value("data").toObject();
                 QJsonArray itemsArray = dataObj.value("data").toArray();

                for (const QJsonValue &value : itemsArray) {
                    QJsonObject itemObj = value.toObject();

                    int id = itemObj.value("id").toInt();
                    QString subject = itemObj.value("subject").toString();
                    int batchSaleLimit = itemObj.value("batch_sale_limit").toInt();
                    int count = itemObj.value("count").toInt();

                    // Print the fields or process them as needed
                    qDebug() << "ID:" << id
                             << "Subject:" << subject
                             << "Batch Sale Limit:" << batchSaleLimit
                             << "Count:" << count;
                }
                reply->deleteLater();
            } else {
                qDebug() << "登录失败, 错误信息:" << responseObject["msg"].toString();
            }
        } else {
            qDebug() << "解析 JSON 响应失败";
        }
    } else {
        qDebug() << "登录网络请求错误:" << reply->errorString();
    }
    reply->deleteLater();
    SellScale();
}

void CommonFunc::SellScale()
{
    int page=1;// read by input
    int product_id=14698;
    //QString token=TokenManager::instance().getUserMap()["phone"];
    QString token=m_userMap["18934406177"];

    QString timestamp = QString::number(loginHandler.getTimeStamp13());
    QNetworkAccessManager manager;
    QUrl url(QString("https://api.newbee.net.cn/api/user_collect?page=%1&per_page=50&product_id=%2&product_type=virtual&timestamp=%3&type=own_valid").arg(page).arg(product_id).arg(timestamp));

    // 设置请求头 // keeping int is also ok

    QNetworkRequest request(url);

    // if you want to change one para, just do it.
    QString signatureData = QString("api/user_collect?page=%1&per_page=50&product_id=%2&product_type=virtual&timestamp=%3&type=own_valid&key=6rnrdpjjv6wz2sspxqeibesov1itxddc").arg(page).arg(product_id).arg(timestamp);

    QString signature = loginHandler.getMd5(signatureData);

    request.setHeader(QNetworkRequest::UserAgentHeader, this->userAgent);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setRawHeader("Signature", "2bd17b71495819c32b37b39388bcb2ac");
    request.setRawHeader("X-Token", signature.toUtf8());
    request.setRawHeader("Token", token.toUtf8());

    // 构造 JSON 数据
    QJsonObject jsonData;
    jsonData["page"] = page;
    jsonData["per_page"] = 50;
    jsonData["product_id"] = product_id;
    jsonData["product_type"] = "virtual";
    jsonData["type"] = "own_valid";
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
    QString token1,token2;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (!jsonResponse.isNull() && jsonResponse.isObject()) {
            QJsonObject responseObject = jsonResponse.object();
            qDebug() << "响应数据:" << jsonResponse;

            if (responseObject["code"].toInt() == 1) {
                 QJsonObject dataObj = responseObject.value("data").toObject();
                 QJsonArray itemsArray = dataObj.value("data").toArray();

                for (const QJsonValue &value : itemsArray) {
                    QJsonObject itemObj = value.toObject();

                    int cid = itemObj.value("id").toInt();
                    int item_id = itemObj.value("item_id").toInt();
                    QJsonObject snObj = itemObj.value("item").toObject();

                    QString sn = snObj.value("sn").toString();

                    // Print the fields or process them as needed
                    qDebug() << "cid:" << cid
                             << "item_id:" << item_id
                             << "sn:" << sn;
                    actualSell(product_id, cid, item_id, sn);
                    QThread::sleep(3);
                }
                reply->deleteLater();
            } else {
                qDebug() << "登录失败, 错误信息:" << responseObject["msg"].toString();
            }
        } else {
            qDebug() << "解析 JSON 响应失败";
        }
    } else {
        qDebug() << "登录网络请求错误:" << reply->errorString();
    }
    reply->deleteLater();
}


void CommonFunc::actualSell(int product_id, int cid, int item_id, const QString& sn)
{
    QString token=m_userMap["18934406177"];
    int price=5;
    QString timestamp = QString::number(loginHandler.getTimeStamp13());
    QNetworkAccessManager manager;
    QUrl url(QString("https://api.newbee.net.cn/api/user_collect/onSaleNew"));

    // 设置请求头 // keeping int is also ok

    QNetworkRequest request(url);

    // if you want to change one para, just do it.
    QString signatureData = QString("https://api.newbee.net.cn/api/user_collect/onSaleNew&key=6rnrdpjjv6wz2sspxqeibesov1itxddc");

    QString signature = loginHandler.getMd5(signatureData);

    request.setHeader(QNetworkRequest::UserAgentHeader, this->userAgent);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setRawHeader("Signature", "2bd17b71495819c32b37b39388bcb2ac");
    request.setRawHeader("X-Token", signature.toUtf8());
    request.setRawHeader("Token", token.toUtf8());

    // 构造 JSON 数据
    //https://api.newbee.net.cn/api/user_collect/onSaleNew
    /*
    amount: "20"     price by you input
    cid: 165337337
    item_id: 193810540
    pay_password: "778899"
    paytypes: "140"
    product_id: 12725
    sn: "2024101272510972221"
    timestamp: 1741614238127
     * */
    QJsonObject jsonData;
    jsonData["amount"] = price;
    jsonData["cid"] = cid;
    jsonData["item_id"] = item_id;
    jsonData["pay_password"] = "336699";
    jsonData["paytypes"] = "140";
    jsonData["product_id"] = product_id;
    jsonData["sn"] = sn;
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
    QString token1,token2;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (!jsonResponse.isNull() && jsonResponse.isObject()) {
            QJsonObject responseObject = jsonResponse.object();
            qDebug() << "响应数据:" << jsonResponse;


        } else {
            qDebug() << "解析 JSON 响应失败";
        }
    } else {
        qDebug() << "登录网络请求错误:" << reply->errorString();
    }
    reply->deleteLater();
}

/*
{
    "code": 1,
    "msg": "我的",
    "time": "1741615800",
    "data": {
        "per_page": "50",
        "current_page": 1,
        "has_more": false,
        "next_item": null,
        "data": [
            {
                "id": 165337337,  cid
                "oldid": 0,
                "user_id": 2663272,
                "author_id": 58,
                "product_id": 12725,
                "item_id": 193810540,
                "amount": 0,
                "marketamount": 0,
                "priceunit": "CNY",
                "orderid": null,
                "createtime": 1729691712,
                "updatetime": 1729691712,
                "givelimit": 0,
                "txhash": null,
                "status": "2",
                "sort": 0,
                "origin": 4,
                "merge_origin": 0,
                "operation_id": "0",
                "block_height": 0,
                "status_yi": 0,
                "func_name": null,
                "from": 0,
                "scene": 4,
                "scene_type": "空投",
                "product": {
                    "id": 12725,
                    "subject": "星辉·月光宝盒*1空投券",
                    "image": "\/uploads\/20241023\/48f7fcc7c683b12bf0f27d86cb64837e.jpg",
                    "type": "virtual",
                    "tag": "",
                    "author_id": 58,
                    "transferdaylimit": 0,
                    "createtime": 1729664316,
                    "starttime": null,
                    "selltime": 1893427200,
                    "quick_image": 0,
                    "quick_image_sec": 0,
                    "author": {
                        "id": 58,
                        "name": "NewBee",
                        "contract": null,
                        "intro": "NewBee是一个文创属性强烈、运营理念超前的综合性数字艺术电商平台，国内最早一批进军Web3.0数字藏品行业的领军企业之一。目前拥有超260万的庞大用户群体，与国内上百家IP艺术机构与博物馆等展开深度合作，累计发行超百万件藏品。截止至今，NewBee战绩斐然，在国内市场占据头部地位。与多家机构、企业达成合作，平台数字藏品涵盖文博、红色文化、品牌IP、非遗、新锐艺术、动漫影业、体育、音乐、科技等类。通过收藏激励、藏品赋能、虚实结合等丰富的产品功能，探索数字藏品、文化传播与实体经济三者的有机融合。",
                        "flag": "",
                        "avatar": "\/uploads\/20240408\/b9f2168eaed0875bc144de9c1038bb24.jpg"
                    }
                },
                "item": {
                    "id": 193810540,
                    "batchid": 12752,
                    "oldid": 0,
                    "sn": "2024101272510972221",
                    "oldsn": "",
                    "author_id": 58,
                    "product_id": 12725,
                    "token_id": null,
                    "block_category_id": "0",
                    "nft_id": "",
                    "operation_id": "",
                    "subject": null,
                    "image": null,
                    "amount": 0,
                    "priceunit": "CNY",
                    "createtime": 1729682475,
                    "updatetime": 1729691712,
                    "deletetime": null,
                    "status": "2",
                    "use_type": 0,
                    "is_blockchain": 0,
                    "txhash": "0",
                    "status_yi": 0,
                    "block_height": 0
                },
                "ai_image": "",
                "today_ai_image": 0
            },
            {
                "id": 165337336,
                "oldid": 0,
                "user_id": 2663272,
                "author_id": 58,
                "product_id": 12725,
                "item_id": 193522245,
                "amount": 0,
                "marketamount": 0,
                "priceunit": "CNY",
                "orderid": null,
                "createtime": 1729691712,
                "updatetime": 1729691712,
                "givelimit": 0,
                "txhash": null,
                "status": "2",
                "sort": 0,
                "origin": 4,
                "merge_origin": 0,
                "operation_id": "0",
                "block_height": 0,
                "status_yi": 0,
                "func_name": null,
                "from": 0,
                "scene": 4,
                "scene_type": "空投",
                "product": {
                    "id": 12725,
                    "subject": "星辉·月光宝盒*1空投券",
                    "image": "\/uploads\/20241023\/48f7fcc7c683b12bf0f27d86cb64837e.jpg",
                    "type": "virtual",
                    "tag": "",
                    "author_id": 58,
                    "transferdaylimit": 0,
                    "createtime": 1729664316,
                    "starttime": null,
                    "selltime": 1893427200,
                    "quick_image": 0,
                    "quick_image_sec": 0,
                    "author": {
                        "id": 58,
                        "name": "NewBee",
                        "contract": null,
                        "intro": "NewBee是一个文创属性强烈、运营理念超前的综合性数字艺术电商平台，国内最早一批进军Web3.0数字藏品行业的领军企业之一。目前拥有超260万的庞大用户群体，与国内上百家IP艺术机构与博物馆等展开深度合作，累计发行超百万件藏品。截止至今，NewBee战绩斐然，在国内市场占据头部地位。与多家机构、企业达成合作，平台数字藏品涵盖文博、红色文化、品牌IP、非遗、新锐艺术、动漫影业、体育、音乐、科技等类。通过收藏激励、藏品赋能、虚实结合等丰富的产品功能，探索数字藏品、文化传播与实体经济三者的有机融合。",
                        "flag": "",
                        "avatar": "\/uploads\/20240408\/b9f2168eaed0875bc144de9c1038bb24.jpg"
                    }
                },
                "item": {
                    "id": 193522245,
                    "batchid": 12738,
                    "oldid": 0,
                    "sn": "2024101272510683926",
                    "oldsn": "",
                    "author_id": 58,
                    "product_id": 12725,
                    "token_id": null,
                    "block_category_id": "0",
                    "nft_id": "",
                    "operation_id": "",
                    "subject": null,
                    "image": null,
                    "amount": 0,
                    "priceunit": "CNY",
                    "createtime": 1729682471,
                    "updatetime": 1729691712,
                    "deletetime": null,
                    "status": "2",
                    "use_type": 0,
                    "is_blockchain": 0,
                    "txhash": "0",
                    "status_yi": 0,
                    "block_height": 0
                },
                "ai_image": "",
                "today_ai_image": 0
            }
        ]
    },
    "test": 0
}

*/


