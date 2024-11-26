# Coco
## Issues

### TLS initialization failed

```
qt.network.ssl: QSslSocket::connectToHostEncrypted: TLS initialization failed 
HTTP GET请求失败： "TLS initialization failed"
```

需要用到 QNetworkManager 访问 https 开头的网址。 https://www.cnblogs.com/FBsharl/p/18171746

但是遇到了QT缺乏 openssl 的相关问题，找了大半天资源，但是1.1.1版本官网已经不再提供下载链接了。（虽然可以把请求中 https 改为 http，但是有一些情况服务器可能认为这是错误的请求，于是回复错误的应答）

现在免费开源共享给大家。（包含Win32和Win64）百度网盘链接：

链接: https://pan.baidu.com/s/1SLhNDmRC-tmm86lDnEvNmw?pwd=abcd

提取码: `abcd`

**安装之后：**

安装过程和后续如何在QT中使用，主要是在openssl_test.pro最下面添加：

```cmake
INCLUDEPATH += C:\Users\oceanstar\source\others\OpenSSL-Win64\include

LIBS    += C:\Users\oceanstar\source\others\OpenSSL-Win64\lib\libssl.lib \
           C:\Users\oceanstar\source\others\OpenSSL-Win64\lib\libcrypto.lib
```

另外，还要把动态库(.dll文件)放到exe所在的debug目录，或者在环境变量中添加动态库的路径。

 检测效果：

```cpp
#include <QNetworkAccessManager>

//看看是否配置了ssl
QNetworkAccessManager *manager = new QNetworkAccessManager(this);
qDebug() << manager->supportedSchemes();
```

多出https，即代表加载成功。

详细教程：https://blog.csdn.net/zhizhengguan/article/details/112848095

The OpenSSL binaries(/bin) directory.

OpenSSL-Win64\bin 目录下的libcrypto-1_1-x64.dll和libssl-1_1-x64.dll复制到项目debug目录下和exe文件在一起。

QT项目编译以后选择64位的MinGw。

## QT network

请求完成后有两种方式拿到请求结果（或者说请求结束后的需要进行的动作）。已知QNetworkReply::finished为请求完成时发出的信号，一是：使用信号槽的机制来进行请求后所需要的动作；二是：使用QEventLoop事件循环等待请求事件结束后，再进行所需的动作。

https://www.cnblogs.com/LyShark/p/18068071

https://juejin.cn/post/7405458683533082634
