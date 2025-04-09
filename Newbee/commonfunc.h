#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <QObject>
#include <QMap>
#include <QString>
#include "login.h"
class CommonFunc: public QObject
{
public:
    explicit CommonFunc(QObject* parent = nullptr);

    void query();
    void SellScale();
    void actualSell(int product_id, int cid, int item_id, const QString& sn);
public slots:
    // 用于接收 tokensUpdated 信号的槽函数
    void onTokensUpdated(const QMap<QString, QString>& userMap);

private:
    QMap<QString, QString> m_userMap;
    QString userAgent;
    Login loginHandler;
};

#endif // COMMONFUNC_H
