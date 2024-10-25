#ifndef EXPORTDATABASE_H
#define EXPORTDATABASE_H

#include <QProcess>
#include <QDialog>
#include <QMainWindow>

namespace Ui {
class exportDatabase;
}

class exportDatabase : public QDialog
{
    Q_OBJECT
    
public:
    explicit exportDatabase(QWidget *parent = 0);
    ~exportDatabase();
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

    void on_pushButton_exportDatabase_clicked();

private:
    Ui::exportDatabase *ui;
    QProcess *m_process_mount; // 声明一个 QProcess 成员变量用于执行外部脚本
    QProcess *m_process_unmount; // 声明一个 QProcess 成员变量用于执行外部脚本
};

#endif //   EXPORTDATABASE_H
