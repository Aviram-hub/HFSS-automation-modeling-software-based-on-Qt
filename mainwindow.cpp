#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include "project_type.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口标题
    this->setWindowTitle("HFSS自动化建模");
    //设置窗口大小
    this->resize(1000, 700);
    //设置主窗口icon
    this->setWindowIcon(QIcon(":/image/mainIcon2.png"));

    this->layout = new QVBoxLayout(this);

    this->container = new QWidget(this);

    QLayout *existingLayout = container->layout();
    if (existingLayout != nullptr) {
        // 删除已有的布局
        delete existingLayout;
    }

    container->setLayout(layout);

    ui->scrollArea->setWidget(container);

    layout->setAlignment(Qt::AlignCenter);
    //this->dialog = new myDialog(this, this);
    //建模操作下拉框添加选项
//    ui->comboBox->addItem("长方体");
//    ui->comboBox->addItem("圆柱体");
//    ui->comboBox->addItem("棱柱体");


    connect(ui->pushButton, &QPushButton::clicked, [=]() { //添加操作按钮
        if (this->new_project_flag) {
            project_type dialog(this, this);
            connect(&dialog, &project_type::play_projectName, [=]() {
                ui->label_2->setText(this->project_name);
            });
            dialog.exec(); //阻塞，模态对话框的需要
        }

        if (this->exit) {
            this->exit = false;
            return;
        }
        myDialog dlg(this, this);
        dlg.resize(650, 400); //尺寸太小会报一个警告，所以resize一下
        this->dialog = &dlg;

        connect(this->dialog, &myDialog::set_widget, [=]() {
            //qDebug() << "此处setWidget";
            this->action_label->setParent(ui->scrollArea);
            //ui->scrollArea->setWidget(this->action_label);
            this->layout->addWidget(this->action_label);
            qDebug() << "add one widget in layout";
        });

        dlg.exec(); //阻塞，模态对话框的需要
    });

    connect(ui->pushButton_2, &QPushButton::clicked, [=]() { //生成文件按钮
        //qDebug() << this->res;
        if (this->flag == true) {
            QString path_name = QFileDialog::getSaveFileName(this,
                                                             "打开文件",
                                                             "D:\\HfssFile\\born_hfss_file",
                                                             "Text Files (*.py)");
            //qDebug() << path_name;
            //FILE* fp = fopen(path_name.toUtf8().data(), "x");
            //file = QFile(path_name);
            if (path_name.isEmpty()) {
                return;
            } else {
                this->new_project_flag = true; //需要打开新项目
                this->flag = false; //没有已保存好的操作
                QFile file(path_name);
                file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

                file.write(this->res.toUtf8().data());
                file.close();
                this->res.clear();
                //fclose(fp);
                for (int i = 0; i < 30; i++) {
                    this->func_define[i] = false;
                }

                QLayoutItem *child;
                while ((child = this->layout->takeAt(0)) != nullptr) {
                    delete child->widget();  // 删除布局项中的控件
                    delete child;            // 删除布局项
                }
                ui->label_2->setText("无");
                QMessageBox::information(this, "提示", "生成成功！");
            }
        } else {
            QMessageBox::critical(this, "提示", "当前没有已保存的操作！");
        }
    });

    connect(ui->pushButton_3, &QPushButton::clicked, [=]() { //清空操作按钮
        if (QMessageBox::Yes == QMessageBox::question(this, "question", "确认清空？", QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Cancel))
        {
            //qDebug() << "选择的是确认";
            QLayoutItem *child;
            while ((child = this->layout->takeAt(0)) != nullptr) {
                delete child->widget();  // 删除布局项中的控件
                delete child;            // 删除布局项
            }

            flag = false;

            res.clear();

            new_project_flag = true;

            for (int i = 0; i < 30; i++) {
                this->func_define[i] = false;
            }

            ui->label_2->setText("无");

            //信息对话框
            QMessageBox::information(this, "information", "清空成功！");
        } else {
            //qDebug() << "选择的是取消";
        }

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
