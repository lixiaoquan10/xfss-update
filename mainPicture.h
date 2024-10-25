#ifndef MAINPICTURE_H
#define MAINPICTURE_H

#include <QProcess>
#include <QDialog>
#include <QMainWindow>

namespace Ui {
class mainPicture;
}

class mainPicture : public QDialog
{
    Q_OBJECT
    
public:
    explicit mainPicture(QWidget *parent = 0);
    ~mainPicture();
    
private slots:

    void processStandardOutput();

    void on_pushButton_close_clicked();

    void on_pushButton_return_clicked();

    void on_pushButton_change_clicked();

private:
    Ui::mainPicture *ui;
    QProcess *m_process; // 声明一个 QProcess 成员变量用于执行外部脚本
};

#endif // MAINPICTURE_H
