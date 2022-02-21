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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QProcess* prcs;
    QLCDNumber* num;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void onTimeOut(void);
};
#endif // MAINWINDOW_H
