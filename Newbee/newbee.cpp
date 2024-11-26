#include "newbee.h"
#include "ui_newbee.h"

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

        QString token = loginHandler.submitLogin(phone, password);

        // 检查登录结果
        if (token != "null") { // 假设返回 "1" 表示失败
            QMessageBox::information(this, "登录成功", "Token: " + token);
        } else {
            QMessageBox::critical(this, "登录失败", "请检查您的账号或密码！");
        }
}
