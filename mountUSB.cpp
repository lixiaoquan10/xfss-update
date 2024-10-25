#include "mainwindow.h"
#include "mountUSB.h"
#include "ui_mountUSB.h"
#include <QScreen>
#include <QProcess>
#include <QTimer>

mountUSB::mountUSB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mountUSB)
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

    m_process_saveDevice = new QProcess(this);
    connect(m_process_saveDevice, SIGNAL(readyReadStandardOutput()), this, SLOT(processSaveDeviceStandardOutput()));
}

mountUSB::~mountUSB()
{
    delete ui;
    delete m_process_saveDevice;
}



void mountUSB::processSaveDeviceStandardOutput()
{
    QByteArray utf8Data = m_process_saveDevice->readAllStandardOutput();
    // 如果末尾有换行符则去掉
    if (!utf8Data.isEmpty() && utf8Data.at(utf8Data.size() - 1) == '\n') {
        utf8Data.chop(1); // 删除末尾的换行符
    }
    QString output = QString::fromUtf8(utf8Data);
    ui->textEdit_mount->append(output);  // 将输出追加到 QTextEdit 控件中（假设控件名为 textEdit）
}

void mountUSB::on_pushButton_mount_clicked()
{
    QString program_saveDevice = "/home/xfss/root/USBprogramUpdate/saveDevice.sh";  // 脚本的路径
    m_process_saveDevice->start(program_saveDevice);
}


void mountUSB::on_pushButton_close_clicked()
{
    qApp->quit();
}

void mountUSB::on_pushButton_return_clicked()
{
    this->close(); // 关闭 mountUSB 对话框窗口
    MainWindow *mainWindow = new MainWindow(); // 创建 MainWindow 对象
    mainWindow->show(); // 显示 MainWindow
}
