#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QProcess>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <QLCDNumber>
#include <QTimer>
#include <QDateTime>
#include<QCoreApplication>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QLCDNumber* num;
    QProcess* prcs;
    MainWindow(QWidget *parent = nullptr);
    void readNum(void);
    ~MainWindow();

private slots:
    void onTimeOut(void);
};
#endif // MAINWINDOW_H
