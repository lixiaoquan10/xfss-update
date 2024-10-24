#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_update_clicked();

    void on_pushButton_reboot_clicked();

    void on_pushButton_close_clicked();

    void processStandardOutput();

    void on_pushButton_mount_clicked();

    void processSaveDeviceStandardOutput();

private:
    Ui::MainWindow *ui;
    QProcess *m_process; // 声明一个 QProcess 成员变量用于执行外部脚本
    QProcess *m_process_restart; // 声明一个 QProcess 成员变量用于执行外部脚本
    QProcess *m_process_saveDevice; // 声明一个 QProcess 成员变量用于执行外部脚本
};

#endif // MAINWINDOW_H
