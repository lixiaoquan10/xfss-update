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
    
private slots:
    void on_pushButton_update_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_mount_clicked();

    void on_pushButton_background_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
