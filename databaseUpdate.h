#ifndef DATABASEUPDATE_H
#define DATABASEUPDATE_H

#include <QProcess>
#include <QDialog>
#include <QMainWindow>

namespace Ui {
class databaseUpdate;
}

class databaseUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit databaseUpdate(QWidget *parent = 0);
    ~databaseUpdate();

private slots:
    void on_pushButton_update_clicked();

    void on_pushButton_reboot_clicked();

    void on_pushButton_close_clicked();

    void processStandardOutput();

    void on_pushButton_return_clicked();

private:
    Ui::databaseUpdate *ui;
    QProcess *m_process; // 声明一个 QProcess 成员变量用于执行外部脚本
    QProcess *m_process_restart; // 声明一个 QProcess 成员变量用于执行外部脚本
};

#endif // DATABASEUPDATE_H
