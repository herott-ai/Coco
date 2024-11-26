#ifndef NEWBEE_H
#define NEWBEE_H

#include <QMainWindow>
#include <QMessageBox>
#include "login.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Newbee; }
QT_END_NAMESPACE

class Newbee : public QMainWindow
{
    Q_OBJECT

public:
    Newbee(QWidget *parent = nullptr);
    ~Newbee();

private:
    Ui::Newbee *ui;

    // 作为成员变量，多次点击登录按钮，复用这个而不是一开始就创建好的对象
    Login loginHandler;  // 它根本没有成员变量，自然也不用显式的调用它的构造函数
private slots:
    void handleLogin();
};
#endif // NEWBEE_H
