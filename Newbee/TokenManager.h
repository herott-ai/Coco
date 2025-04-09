#ifndef TOKENMANAGER_H
#define TOKENMANAGER_H
#include <QObject>
#include <QMap>
#include <QString>
#include <QDebug>
class TokenManager : public QObject {
    Q_OBJECT
public:
    static TokenManager& instance() {
        static TokenManager instance;
        return instance;
    }

    void setTokens(QString& phone, const QString& token) {
        qDebug() <<phone<<token;
        userMap[phone] = token;
        qDebug() << "ddd"<<userMap[phone];
        emit tokensUpdated(userMap);
    }

    QMap<QString, QString> getUserMap() const { return userMap; }

signals:
    void tokensUpdated(const QMap<QString, QString>& userMap);

private:
    TokenManager() {}  // 私有构造函数，确保单例模式
    QMap<QString, QString> userMap;
};

#endif // TOKENMANAGER_H
