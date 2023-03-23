#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include "mydialog.h"
#include "action_label.h"
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class myDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool flag = false; //表示当前有无保存好的操作，false表示没有

    QString res; //保存代码结果的字符串

    //QFile file;

    //bool new_pro_flag = false;

    QString project_name;

    bool exit = false;        //为true时，不弹出添加操作截面

    bool new_project_flag = true;   //为true时会弹出编辑项目名的对话框，初始为true，添加第一个操作后变false，生成文件后变true

    bool func_define[30] = {false}; //防止函数重复定义的bool数组

    myDialog* dialog;

    Action_Label* action_label;

    QVBoxLayout *layout;

    QWidget* container;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
