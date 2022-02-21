#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("时钟显示2");
    this->resize(300,100);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    num = new QLCDNumber(this);
    // 设置能显示的位数
    num->setDigitCount(21);
    // 设置显示的模式为十进制
    num->setMode(QLCDNumber::Dec);
    // 设置显示外观
    num->setSegmentStyle(QLCDNumber::Flat);
    // 设置样式
    num->setStyleSheet("border: 1px solid green; color: yellow; background: silver;");
    num->resize(300,100);

    //构建一个定时器，每隔一秒来定时刷新QLCDnumber中的内容
    QTimer *pTimer = new QTimer(this);
    // 设置定时间隔
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    // 启动定时器
    pTimer->start();
}

void MainWindow::onTimeOut()
{
    // 获取系统当前时间
    QDateTime dateTime = QDateTime::currentDateTime();
    // 显示的内容
    num->display(dateTime.toString("yyyy-MM-dd HH:mm:ss"));
}

MainWindow::~MainWindow()
{
}

