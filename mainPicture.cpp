#include "mainwindow.h"
#include "mainPicture.h"
#include "ui_mainPicture.h"
#include <QScreen>
#include <QProcess>
#include <QTimer>

mainPicture::mainPicture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainPicture)
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

    m_process = new QProcess(this);
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(processStandardOutput()));
}

mainPicture::~mainPicture()
{
    delete ui;
    delete m_process;
}



void mainPicture::processStandardOutput()
{
    QByteArray utf8Data = m_process->readAllStandardOutput();
    // 如果末尾有换行符则去掉
    if (!utf8Data.isEmpty() && utf8Data.at(utf8Data.size() - 1) == '\n') {
        utf8Data.chop(1); // 删除末尾的换行符
    }
    QString output = QString::fromUtf8(utf8Data);
    ui->textEdit_change->append(output);  // 将输出追加到 QTextEdit 控件中（假设控件名为 textEdit）
}

void mainPicture::on_pushButton_change_clicked()
{
    QString program = "/home/xfss/root/USBprogramUpdate/mainPicture.sh";  // 脚本的路径
    m_process->start(program);
}


void mainPicture::on_pushButton_close_clicked()
{
    qApp->quit();
}

void mainPicture::on_pushButton_return_clicked()
{
    this->close(); // 关闭 mainPicture 对话框窗口
    MainWindow *mainWindow = new MainWindow(); // 创建 MainWindow 对象
    mainWindow->show(); // 显示 MainWindow
}

