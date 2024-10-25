#include "mainwindow.h"
#include "exportFiles.h"
#include "ui_exportFiles.h"

exportFiles::exportFiles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportFiles)
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

    QScrollArea *scrollArea = new QScrollArea(ui->groupBox);
    scrollArea->setWidgetResizable(true); // 设置滚动区域的大小自适应内部控件

    // 创建一个小部件来容纳复选框
    QWidget *scrollWidget = new QWidget();
    scrollWidget->setLayout(new QVBoxLayout());


    QString rootPath = "/home/xfss/root";

    // 创建 QDir 对象，指定 root 文件夹路径
    QDir rootDir(rootPath);

    // 判断 root 文件夹是否存在
    if (!rootDir.exists()) {
        qDebug() << "Root directory does not exist.";
        return;
    }

    // 获取 root 文件夹中的文件列表
    QStringList fileList = rootDir.entryList(QDir::Files);


    // 遍历文件列表并创建复选框
    foreach (QString fileName, fileList) {
        if(fileName == "Monitor" || fileName == "libBService.so.1.0.0")
            continue;
        QCheckBox *checkBox = new QCheckBox(fileName);
        checkBoxList.append(checkBox);
        scrollWidget->layout()->addWidget(checkBox);
    }

    // 将滚动小部件设置为滚动区域的窗口部件
    scrollArea->setWidget(scrollWidget);

    // 将滚动区域添加到 groupBox 的布局中
    QVBoxLayout *groupBoxLayout = new QVBoxLayout(ui->groupBox);
    groupBoxLayout->addWidget(scrollArea); // 将滚动区域添加到 groupBox 的布局中

    // 遍历文件列表并输出文件名
    qDebug() << "Files in root directory:";
    foreach (QString fileName, fileList) {
        qDebug() << fileName;
    }

    m_process_mount = new QProcess(this);
    // 连接挂载完成信号与槽
    connect(m_process_mount, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onMountFinished(int,QProcess::ExitStatus)));
    m_process_unmount = new QProcess(this);
    // 连接卸载完成信号与槽
    connect(m_process_unmount, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onUnmountFinished(int,QProcess::ExitStatus)));

    connect(this, SIGNAL(usbFilesCopied(bool success)), this, SLOT(onUsbFilesCopied(bool success)));
}

exportFiles::~exportFiles()
{
    delete ui;
    delete m_process_mount;
    delete m_process_unmount;
}


void exportFiles::on_pushButton_export_clicked()
{
    QString program_mount = "/home/xfss/root/USBprogramUpdate/mountUSB.sh";  // 脚本的路径
    m_process_mount->start(program_mount);
}

void exportFiles::onUsbFilesCopied(bool success)
{
    if(success) {
        // USB 设备上的文件复制完成后，执行卸载操作
        QString program_unmount = "/home/xfss/root/USBprogramUpdate/unmountUSB.sh";
        m_process_unmount->start(program_unmount);
    } else {
        // 处理文件复制失败的情况
    }
}

void exportFiles::onMountFinished(int exitCode, QProcess::ExitStatus exitStatus)
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

void exportFiles::onUnmountFinished(int exitCode, QProcess::ExitStatus exitStatus)
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

void exportFiles::copyFilesToUSB()
{
    QStringList fileList;
    for(int i=0; i<checkBoxList.count(); i++)
    {
        QCheckBox *checkbox = checkBoxList.at(i);
        if(checkbox->isChecked())
        {
            fileList.append(checkbox->text());
        }
    }
    // 获取源文件路径
    QString sourceDir = "/home/xfss/root"; // 源文件夹路径
    QString destDir = "/mnt/usb"; // 目标文件夹路径

    // 遍历 fileList 中的文件
    foreach (QString fileName, fileList) {
        QString sourceFilePath = sourceDir + "/" + fileName;
        QString destFilePath = destDir + "/" + fileName;

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
                QString str = "File copied successfully: " + fileName;
                qDebug() << str;
                ui->textEdit->append(str);
            } else {
                QString str = "Failed to copy file: " + fileName;
                qDebug() << str;
                ui->textEdit->append(str);
            }
        } else {
            QString str = "Source file not found: " + fileName;
            qDebug() << str;
            ui->textEdit->append(str);
        }
    }
    emit onUsbFilesCopied(true);
}

void exportFiles::on_pushButton_close_clicked()
{
    qApp->quit();
}

void exportFiles::on_pushButton_return_clicked()
{
    this->close(); // 关闭 exportFiles 对话框窗口
    MainWindow *mainWindow = new MainWindow(); // 创建 MainWindow 对象
    mainWindow->show(); // 显示 MainWindow
}

