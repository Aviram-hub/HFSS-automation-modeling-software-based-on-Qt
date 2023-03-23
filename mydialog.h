#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class myDialog;
}

class MainWindow;  // 添加这行前置声明语句

class myDialog : public QDialog
{
    Q_OBJECT

public:
    explicit myDialog(QWidget *parent = 0, MainWindow *mainWindow = 0);
    ~myDialog();

    bool have_empty();

    QString get_code(int index);

    void validator_config();

    void generate_code(int index);
signals:
    //void play_projectName();

    void set_widget();
private:
    Ui::myDialog *ui;
    MainWindow* mainWindow_;
};

#endif // MYDIALOG_H
