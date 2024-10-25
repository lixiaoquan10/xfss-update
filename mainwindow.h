#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QScreen>
#include <QTimer>
#include <QDir>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void controlDisplayPower(bool on) ;
    
private slots:
    void on_pushButton_update_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_mount_clicked();

    void on_pushButton_background_clicked();

    void on_pushButton_mountDatabase_clicked();

private:
    Ui::MainWindow *ui;
    QProcess *m_process_light; // 声明一个 QProcess 成员变量用于执行外部脚本
};

#endif // MAINWINDOW_H
