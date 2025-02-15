#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    ui->pushButton_reboot->setEnabled(false);


    // 创建 QProcess 对象并连接信号与槽
    m_process = new QProcess(this);
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(processStandardOutput()));

    m_process_restart = new QProcess(this);

    m_process_saveDevice = new QProcess(this);
    connect(m_process_saveDevice, SIGNAL(readyReadStandardOutput()), this, SLOT(processSaveDeviceStandardOutput()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_process;
    delete m_process_restart;
    delete m_process_saveDevice;
}

void MainWindow::on_pushButton_update_clicked()
{
    ui->pushButton_reboot->setEnabled(true);
    QString program = "/home/xfss/root/USBprogramUpdate/usb.sh";  // 脚本的路径
    m_process->start(program);
}

void MainWindow::on_pushButton_reboot_clicked()
{
    QString program_restart = "/home/xfss/root/USBprogramUpdate/usb_restart.sh";  // 脚本的路径
    m_process_restart->start(program_restart);
}

void MainWindow::on_pushButton_close_clicked()
{
   qApp->quit();
}

void MainWindow::processStandardOutput()
{
    QByteArray utf8Data = m_process->readAllStandardOutput();
    // 如果末尾有换行符则去掉
    if (!utf8Data.isEmpty() && utf8Data.at(utf8Data.size() - 1) == '\n') {
        utf8Data.chop(1); // 删除末尾的换行符
    }
    QString output = QString::fromUtf8(utf8Data);
    ui->textEdit->append(output);  // 将输出追加到 QTextEdit 控件中（假设控件名为 textEdit）
}

void MainWindow::processSaveDeviceStandardOutput()
{
    QByteArray utf8Data = m_process_saveDevice->readAllStandardOutput();
    // 如果末尾有换行符则去掉
    if (!utf8Data.isEmpty() && utf8Data.at(utf8Data.size() - 1) == '\n') {
        utf8Data.chop(1); // 删除末尾的换行符
    }
    QString output = QString::fromUtf8(utf8Data);
    ui->textEdit_mount->append(output);  // 将输出追加到 QTextEdit 控件中（假设控件名为 textEdit）
}

void MainWindow::on_pushButton_mount_clicked()
{
    QString program_saveDevice = "/home/xfss/root/USBprogramUpdate/saveDevice.sh";  // 脚本的路径
    m_process_saveDevice->start(program_saveDevice);
}
