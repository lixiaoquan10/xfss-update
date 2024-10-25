#include "mainwindow.h"
#include "exportDatabase.h"
#include "ui_exportDatabase.h"
#include <QScreen>
#include <QProcess>
#include <QTimer>
#include <QDateTime>

exportDatabase::exportDatabase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportDatabase)
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

    m_process_mount = new QProcess(this);
    // 连接挂载完成信号与槽
    connect(m_process_mount, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onMountFinished(int,QProcess::ExitStatus)));
    m_process_unmount = new QProcess(this);
    // 连接卸载完成信号与槽
    connect(m_process_unmount, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onUnmountFinished(int,QProcess::ExitStatus)));

    connect(this, SIGNAL(usbFilesCopied(bool success)), this, SLOT(onUsbFilesCopied(bool success)));

}

exportDatabase::~exportDatabase()
{
    delete ui;
    delete m_process_mount;
    delete m_process_unmount;
}



void exportDatabase::on_pushButton_export_clicked()
{
    QString program_mount = "/home/xfss/root/USBprogramUpdate/mountUSB.sh";  // 脚本的路径
    m_process_mount->start(program_mount);
}

void exportDatabase::onUsbFilesCopied(bool success)
{
    if(success) {
        // USB 设备上的文件复制完成后，执行卸载操作
        QString program_unmount = "/home/xfss/root/USBprogramUpdate/unmountUSB.sh";
        m_process_unmount->start(program_unmount);
    } else {
        // 处理文件复制失败的情况
    }
}

void exportDatabase::onMountFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(exitStatus == QProcess::NormalExit && exitCode == 0)
    {
        QString str = "USB device mounted successfully";
        qDebug() << str;
        ui->textEdit->append(str);
        copyFilesToUSB(); // USB 设备挂载成功后复制文件
    } else {
        QString str = "Failed to mount USB device";
        qDebug() << str;
        ui->textEdit->append(str);
        // 处理挂载失败的情况
    }
}

void exportDatabase::onUnmountFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(exitStatus == QProcess::NormalExit && exitCode == 0) {
        QString str = "USB device unmounted successfully";
        qDebug() << str;
        ui->textEdit->append(str);
    } else {
        QString str = "Failed to unmount USB device";
        qDebug() << str;
        ui->textEdit->append(str);
        // 处理卸载失败的情况
    }
}

void exportDatabase::copyFilesToUSB()
{
    // 获取当前日期时间
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 当前日期时间格式化为字符串，例如：20240708-154523（年月日-时分秒）
    QString formattedDateTime = currentDateTime.toString("yyyyMMdd-hhmmss");

    // 获取源文件路径
    QString sourceDir = "/home/xfss/root"; // 源文件夹路径
    QString destDir = "/mnt/usb/" + formattedDateTime; // 目标文件夹路径

    QString sourceFilePath = sourceDir + "/ESSQLiteCE100.db";
    QString destFilePath = destDir + "/ESSQLiteCE100.db";

    // 检查源文件是否存在
    if (QFile::exists(sourceFilePath))
    {
        // 创建目标文件夹（如果不存在）
        QDir destFolder(destDir);
        if (!destFolder.exists()) {
            destFolder.mkpath(".");
        }

        // 复制文件
        if (QFile::copy(sourceFilePath, destFilePath)) {
            QString str = "ESSQLiteCE100.db copied successfully!";
            qDebug() << str;
            ui->textEdit->append(str);
        } else {
            QString str = "Failed to copy ESSQLiteCE100.db!";
            qDebug() << str;
            ui->textEdit->append(str);
        }
    } else {
        QString str = "ESSQLiteCE100.db not found!";
        qDebug() << str;
        ui->textEdit->append(str);
    }
    emit onUsbFilesCopied(true);
}


void exportDatabase::on_pushButton_close_clicked()
{
    qApp->quit();
}

void exportDatabase::on_pushButton_return_clicked()
{
    this->close(); // 关闭 mainPicture 对话框窗口
    MainWindow *mainWindow = new MainWindow(); // 创建 MainWindow 对象
    mainWindow->show(); // 显示 MainWindow
}

void exportDatabase::on_pushButton_exportDatabase_clicked()
{
    QString program_mount = "/home/xfss/root/USBprogramUpdate/mountUSB.sh";  // 脚本的路径
    m_process_mount->start(program_mount);
}
