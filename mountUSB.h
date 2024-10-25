#ifndef MOUNTUSB_H
#define MOUNTUSB_H

#include <QProcess>
#include <QDialog>
#include <QMainWindow>

namespace Ui {
class mountUSB;
}

class mountUSB : public QDialog
{
    Q_OBJECT
    
public:
    explicit mountUSB(QWidget *parent = 0);
    ~mountUSB();
    
private slots:

    void on_pushButton_mount_clicked();

    void processSaveDeviceStandardOutput();

    void on_pushButton_close_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::mountUSB *ui;
    QProcess *m_process_saveDevice; // 声明一个 QProcess 成员变量用于执行外部脚本
};

#endif // MOUNTUSB_H
