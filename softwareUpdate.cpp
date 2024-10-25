#include "mainwindow.h"
#include "softwareUpdate.h"
#include "ui_softwareUpdate.h"
#include <QScreen>
#include <QProcess>
#include <QTimer>

softwareUpdate::softwareUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::softwareUpdate)
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
}

softwareUpdate::~softwareUpdate()
{
    delete ui;
    delete m_process;
    delete m_process_restart;
}

void softwareUpdate::on_pushButton_update_clicked()
{
    ui->pushButton_reboot->setEnabled(true);
    QString program = "/home/xfss/root/USBprogramUpdate/start_usb.sh";  // 脚本的路径
    m_process->start(program);
}

void softwareUpdate::on_pushButton_reboot_clicked()
{
    QString program_restart = "/home/xfss/root/USBprogramUpdate/restart.sh";  // 脚本的路径
    m_process_restart->start(program_restart);
}

void softwareUpdate::on_pushButton_return_clicked()
{
    this->close(); // 关闭 mountUSB 对话框窗口
    MainWindow *mainWindow = new MainWindow(); // 创建 MainWindow 对象
    mainWindow->show(); // 显示 MainWindow
}

void softwareUpdate::on_pushButton_close_clicked()
{
   qApp->quit();
}

void softwareUpdate::processStandardOutput()
{
    QByteArray utf8Data = m_process->readAllStandardOutput();
    // 如果末尾有换行符则去掉
    if (!utf8Data.isEmpty() && utf8Data.at(utf8Data.size() - 1) == '\n') {
        utf8Data.chop(1); // 删除末尾的换行符
    }
    QString output = QString::fromUtf8(utf8Data);
    ui->textEdit->append(output);  // 将输出追加到 QTextEdit 控件中（假设控件名为 textEdit）
}



