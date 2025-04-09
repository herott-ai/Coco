#include "newbee.h"
#include "ui_newbee.h"
#include "TokenManager.h"
#include "commonfunc.h"

Newbee::Newbee(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Newbee)
{
    ui->setupUi(this);
    connect(ui->btnLogin, &QPushButton::clicked, this, &Newbee::handleLogin);
}

Newbee::~Newbee()
{
    delete ui;
}


void Newbee::handleLogin() {
        // 获取输入框内容
        QString phone = ui->phoneEdit->text();
        QString password = ui->passwordEdit->text();

        // 验证输入是否为空
        if (phone.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "警告", "账号或密码不能为空！");
            return;
        }

        // 调用 Login 类的登录功能
        //Login loginHandler; 如果是局部变量，每次点击登录按钮都会重新创建这个对象

        QMap<QString, QString> userMap = loginHandler.submitLogin(phone, password);
        qDebug()<<"sss"<<userMap[phone];
        if(userMap[phone] != "null")
        {
            // ttttzxcvbnm0tt
            // Because signal and slot are registered in construct funtion, so we
            // need to have object first. Then the signal and slot will work.
            // Later, I prepare to bind this obj to a button and a lable for each user.
            CommonFunc c;
            TokenManager::instance().setTokens(phone, userMap[phone]);
            QMessageBox::information(this, "登录成功", "Token: " + userMap[phone]);
            c.query();
        }
        else QMessageBox::critical(this, "登录失败", "请检查您的账号或密码！");
}
