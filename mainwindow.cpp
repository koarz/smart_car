#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString.h>
#include <Qstring>
#include <iostream>
#include <QTime>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

