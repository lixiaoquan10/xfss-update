#ifndef EXPOREFILES_H
#define EXPOREFILES_H

#include <QProcess>
#include <QDialog>
#include <QMainWindow>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QToolButton>
#include <QApplication>
#include <QScrollArea>

namespace Ui {
class exportFiles;
}

class exportFiles : public QDialog
{
    Q_OBJECT
    
public:
    explicit exportFiles(QWidget *parent = 0);
    ~exportFiles();
    void copyFilesToUSB();

signals:
    void usbFilesCopied(bool success);
    
private slots:

    void on_pushButton_close_clicked();

    void on_pushButton_return_clicked();

    void on_pushButton_export_clicked();

    void onMountFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void onUnmountFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void onUsbFilesCopied(bool success);


private:
    Ui::exportFiles *ui;
    QList<QCheckBox *> checkBoxList;
    QProcess *m_process_mount; // 声明一个 QProcess 成员变量用于执行外部脚本
    QProcess *m_process_unmount; // 声明一个 QProcess 成员变量用于执行外部脚本
};

#endif // EXPOREFILES_H
