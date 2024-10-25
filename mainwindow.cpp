#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "softwareUpdate.h"
#include "exportFiles.h"
#include "mainPicture.h"
#include <QScreen>
#include <QProcess>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 获取屏幕的大小
    int screenWidth = 1366;
    int screenHeight = 768;

    // 获取窗口的大小
    int windowWidth = this->width();
    int windowHeight = this->height();

    // 计算窗口在屏幕中央的位置
    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;

    // 将窗口移动到屏幕中央
    this->move(x, y);
    setWindowFlags(Qt::WindowCloseButtonHint);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_update_clicked()
{
    this->hide();
    softwareUpdate softwareupdate;
    softwareupdate.exec();
}


void MainWindow::on_pushButton_close_clicked()
{
   qApp->quit();
}


void MainWindow::on_pushButton_mount_clicked()
{
    this->hide();
    exportFiles exportfiles;
    exportfiles.exec();
}

void MainWindow::on_pushButton_background_clicked()
{
    this->hide();
    mainPicture picture;
    picture.exec();
}
