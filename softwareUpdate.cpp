#include "mainwindow.h"
#include "softwareUpdate.h"
#include "ui_softwareUpdate.h"
#include <QScreen>
#include <QProcess>
#include <QTimer>
#include <QMessageBox>

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
    QFont font;
    font.setPointSize(12); // 设置字体大小为12像素
    // 在QMessageBox中设置字体
    QMessageBox messageBox;
    messageBox.setFont(font);
    QString styleSheet = "QMessageBox { border: 1px solid #333333; }";
    messageBox.setStyleSheet(styleSheet);
    messageBox.setIcon(QMessageBox::NoIcon);
    messageBox.setWindowTitle("信息");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    messageBox.setDefaultButton(QMessageBox::Cancel);
    QString log;
    log = "是否同时更新数据库?" + tr("\n") + "Yes:是" + tr("\n") + "No:否" + tr("\n") + "Cancel:取消";
    messageBox.setText(log);
    int ret = messageBox.exec();
    QString enable;
    if(ret == QMessageBox::Cancel)
    {
        return;
    }
    else if(ret == QMessageBox::Yes)
    {
        enable = "True";
    }
    else if(ret == QMessageBox::No)
    {
        enable = "False";
    }
    ui->pushButton_reboot->setEnabled(true);
    QStringList arguments;
    arguments << enable;

    QString program = "/home/xfss/root/USBprogramUpdate/start_update.sh";  // 脚本的路径
    // 启动 shell 脚本文件并传递参数
    m_process->start("bash", QStringList() << program << arguments);
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



