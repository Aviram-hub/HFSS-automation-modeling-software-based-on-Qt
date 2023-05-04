#include "project_type.h"
#include "ui_project_type.h"
#include <QComboBox>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>

project_type::project_type(QWidget *parent, MainWindow* mainWindow) :
    QDialog(parent),
    mainWindow_(mainWindow),
    ui(new Ui::project_type)
{

    ui->setupUi(this);
    this->setWindowTitle("输入项目名");

    ui->comboBox->addItem("操作已有项目");
    //ui->comboBox->addItem("打开新项目");
    //只能输入大小写字母和数字和下划线
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9_]*$"), ui->lineEdit);
    ui->lineEdit->setValidator(validator);

//    connect(this, &project_type::closeEvent, [=]() {
//        this->mainWindow_->exit = true;
//    });
    connect(ui->pushButton_2, &QPushButton::clicked, [=]() { //取消按钮
        this->mainWindow_->exit = true;
        this->close();
    });

    connect(ui->pushButton, &QPushButton::clicked, [=]() { //确定按钮
        if (ui->lineEdit->text().isEmpty()) {
            QMessageBox::critical(this, "提示", "请输入项目名字");
            return;
        }

        this->mainWindow_->project_name = ui->lineEdit->text();

        //if (ui->comboBox->currentText() == "操作已有项目") {
            //this->mainWindow_->new_pro_flag = false;
            this->mainWindow_->res += QString("import ScriptEnv\n\
ScriptEnv.Initialize(\"Ansoft.ElectronicsDesktop\")\n\
oDesktop.RestoreWindow()\n\
oProject = oDesktop.SetActiveProject(\"%1\")\n\
oDesign = oProject.SetActiveDesign(\"HFSSDesign1\")\n\
oEditor = oDesign.SetActiveEditor(\"3D Modeler\")\n").arg(ui->lineEdit->text());
        //}
//        else { //打开新项目
//            QString project_file_path = QFileDialog::getExistingDirectory(this,
//                                                                          "选择项目文件(.aedt)存放位置",
//                                                                          ".");
//            if (project_file_path.isEmpty()) {
//                return;
//            }

//            QString real_path = project_file_path + "/" + ui->lineEdit->text() + ".aedt";
//            QString str = QString("import ScriptEnv\n\
//ScriptEnv.Initialize(\"Ansoft.ElectronicsDesktop\")\n\
//oDesktop.RestoreWindow()\n\
//oDesktop.OpenProject(\"%1\")\n\
//oProject = oDesktop.SetActiveProject(\"%2\")\n\
//oDesign = oProject.SetActiveDesign(\"HFSSDesign1\")\n\
//oEditor = oDesign.SetActiveEditor(\"3D Modeler\")\n").arg(real_path).arg(ui->lineEdit->text());
//            this->mainWindow_->res += str;
//            //this->mainWindow_->new_pro_flag = true;
//        }
        this->mainWindow_->new_project_flag = false; //表示下次不弹出项目名窗口
        emit this->play_projectName(); //显示项目名
        //this->mainWindow_->exit != this->mainWindow_->exit;
        this->should_call = false; //表示不跳过参数输入框
        this->close();
    });
}

void project_type::closeEvent(QCloseEvent *event) {
    if (should_call) {
        this->mainWindow_->exit = true;
    }

    QWidget::closeEvent(event);
}

project_type::~project_type()
{
    delete ui;
}
