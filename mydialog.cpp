#include "mydialog.h"
#include "ui_mydialog.h"
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QComboBox>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QCompleter>
#include "action_label.h"

//判断当前stackWidget页内的lineEdit有无空的，有空的返回true
bool myDialog::have_empty() {
    QList<QLineEdit *> lineEdits = ui->stackedWidget->widget(ui->stackedWidget->currentIndex())->findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit->text().isEmpty()) {
            return true;
        }
    }
    return false;
}

myDialog::myDialog(QWidget *parent, MainWindow *mainWindow) :
    QDialog(parent),
    ui(new Ui::myDialog),
    mainWindow_(mainWindow)
    //mainWindow_(mainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("选择参数");

    ui->label_8->setText(this->mainWindow_->project_name);

    connect(ui->pushButtonOK, &QPushButton::clicked, [=]() { //输入参数截面确定按钮
        if (this->have_empty()) {
            QMessageBox::critical(this, "提示", "请输入完整的参数！");
            return;
        }
//        if (this->mainWindow_->flag == false) { //false表示之前没有保存好的操作，本次是第一个
//            this->mainWindow_->flag == true;

//        } else {

//        }
        if (this->mainWindow_->func_define[ui->stackedWidget->currentIndex()] == false) {
            this->mainWindow_->res += this->get_code(ui->stackedWidget->currentIndex());
        }
        //QString execute = "my_CreateBox(\"" + ui->lineEdit_219->text() + "\", \"" + ui->lineEdit_223->text() + "\", \"" + ui->lineEdit_224->text() + "\", \"" + ui->lineEdit_225->text() + "\", \"" + ui->lineEdit_217->text() + "\", \"" + ui->lineEdit_222->text() + "\", \"" + i->lineEdit_221->text() + "\", \"(" +
//        QString s1 = ui->lineEdit_219->text();
//        QString s2 = ui->lineEdit_223->text();
//        QString s3 = ui->lineEdit_224->text();
//        QString s4 = ui->lineEdit_225->text();
//        QString s5 = ui->lineEdit_226->text();
//        QString s6 = ui->lineEdit_227->text();
//        QString s7 = ui->lineEdit_228->text();
//        int i8 = ui->spinBox_2->value();
//        int i9 = ui->spinBox->value();
//        int i10 = ui->spinBox_3->value();
//        QString s11 = ui->lineEdit_220->text();
//        double i12 = ui->doubleSpinBox->value();
//        QString execute = QString("my_CreateBox(\"%1\", \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"%6mm\", \"%7mm\", \"(%8 %9 %10)\", \"\\\"%11\\\"\", %12);\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(s7).arg(i8).arg(i9).arg(i10).arg(s11).arg(i12);
//        this->mainWindow_->res += execute;
        generate_code(ui->stackedWidget->currentIndex());
        //qDebug() << this->mainWindow_->res;

        //QFile file("D:/HfssFile/HFSS.py/code.py");
        //file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        //file.write(this->mainWindow_->res.toUtf8().data());
        //file.close();
        QMessageBox::information(this, "提示", "添加成功！");
        this->mainWindow_->flag = true; //表示有保存好的操作
        this->mainWindow_->func_define[ui->stackedWidget->currentIndex()] = true; //不重复定义函数

        //this->mainWindow_->dialog = nullptr;
        this->close();
        //this->mainWindow_->res
        //qDebug() << name.toUtf8().data();
        //QString str = QFileDialog::getOpenFileName(this, "打开文件", "D:\\Desktop", "(*.py)");
    });

    connect(ui->pushButtonNO, &QPushButton::clicked, [=]() {
        this->mainWindow_->res.clear();

        this->close();
    });

    ui->comboBox->addItem("长方体");
    ui->comboBox->addItem("圆柱体");
    ui->comboBox->addItem("棱柱体");
    ui->comboBox->addItem("圆锥体");
    ui->comboBox->addItem("球体");
    ui->comboBox->addItem("圆环体");
    ui->comboBox->addItem("接合线");
    ui->comboBox->addItem("长方形");
    ui->comboBox->addItem("圆形");
    ui->comboBox->addItem("多边形");
    ui->comboBox->addItem("椭圆");
    ui->comboBox->addItem("区域");
    ui->comboBox->addItem("点");
    ui->comboBox->addItem("截面");

    //单选框默认选中建模
    ui->radioButton->setChecked(true);
    //设置两个stackWidget的默认值
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);

    void (QComboBox:: *Singal)(int) = &QComboBox::currentIndexChanged;
    connect(ui->comboBox, Singal, [=](int index) { //切换建模模型时，切换输入框
        ui->stackedWidget->setCurrentIndex(index);
    });

    connect(ui->comboBox_2, Singal, [=](int index) {
        ui->stackedWidget->setCurrentIndex(index + 14);
    });

    ui->comboBox_2->addItem("移动");
    ui->comboBox_2->addItem("旋转");
    ui->comboBox_2->addItem("镜像");
    ui->comboBox_2->addItem("沿线复制");
    ui->comboBox_2->addItem("沿轴复制");
    ui->comboBox_2->addItem("镜像复制");
    ui->comboBox_2->addItem("合并");
    ui->comboBox_2->addItem("减去");
    ui->comboBox_2->addItem("相交");
    ui->comboBox_2->addItem("分裂");
    ui->comboBox_2->addItem("标记");
    ui->comboBox_2->addItem("沿向量扫");
    ui->comboBox_2->addItem("沿轴扫");
    ui->comboBox_2->addItem("沿路径扫");
    ui->comboBox_2->addItem("圆角处理");
    ui->comboBox_2->addItem("去直角边");

    ui->comboBox_3->addItem("X");
    ui->comboBox_3->addItem("Y");
    ui->comboBox_3->addItem("Z");

    ui->comboBox_4->addItem("X");
    ui->comboBox_4->addItem("Y");
    ui->comboBox_4->addItem("Z");

    ui->comboBox_5->addItem("X");
    ui->comboBox_5->addItem("Y");
    ui->comboBox_5->addItem("Z");

    ui->comboBox_6->addItem("Round");
    ui->comboBox_6->addItem("Chamfer");
    ui->comboBox_6->addItem("None");

    ui->comboBox_7->addItem("Round");
    ui->comboBox_7->addItem("Chamfer");
    ui->comboBox_7->addItem("None");

    ui->comboBox_8->addItem("Round");
    ui->comboBox_8->addItem("Chamfer");
    ui->comboBox_8->addItem("None");

    ui->comboBox_9->addItem("XY");
    ui->comboBox_9->addItem("XZ");
    ui->comboBox_9->addItem("YZ");

    ui->comboBox_10->addItem("Symmetric");
    ui->comboBox_10->addItem("Left");
    ui->comboBox_10->addItem("Right");
    ui->comboBox_10->addItem("Asymmetric");

    connect(ui->radioButton, &QRadioButton::clicked, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->stackedWidget->setCurrentIndex(ui->comboBox->currentIndex());
    });

    //发送一个按下信号
    emit ui->radioButton->clicked();

    connect(ui->radioButton_2, &QRadioButton::clicked, [=]() {
        ui->stackedWidget_2->setCurrentIndex(1);
        ui->stackedWidget->setCurrentIndex(ui->comboBox_2->currentIndex() + 14);
    });

    validator_config();
}

myDialog::~myDialog()
{
    delete ui;
}

void myDialog::generate_code(int index) {
    if (index == 0) {
        QString s1 = ui->lineEdit_219->text();
        QString s2 = ui->lineEdit_223->text();
        QString s3 = ui->lineEdit_224->text();
        QString s4 = ui->lineEdit_225->text();
        QString s5 = ui->lineEdit_226->text();
        QString s6 = ui->lineEdit_227->text();
        QString s7 = ui->lineEdit_228->text();
        int i8 = ui->spinBox_2->value();
        int i9 = ui->spinBox->value();
        int i10 = ui->spinBox_3->value();
        QString s11 = ui->lineEdit_220->text();
        double i12 = ui->doubleSpinBox->value();
        QString execute = QString("my_CreateBox(\"%1\", \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"%6mm\", \"%7mm\", \"(%8 %9 %10)\", \"\\\"%11\\\"\", %12);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(s7).arg(i8).arg(i9).arg(i10).arg(s11).arg(i12);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 1) {
        QString s1 = ui->lineEdit_209->text();
        QString s2 = ui->lineEdit_214->text();
        QString s3 = ui->lineEdit_215->text();
        QString s4 = ui->lineEdit_216->text();
        QString s5 = ui->lineEdit_206->text();
        QString s6 = ui->lineEdit_212->text();

        int i8 = ui->spinBox_7->value();
        int i9 = ui->spinBox_8->value();
        int i10 = ui->spinBox_9->value();

        QString s11 = ui->lineEdit_211->text();
        double i12 = ui->doubleSpinBox_2->value();
        QString execute = QString("my_CreateCylinder(\"%1\", \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"%6mm\", \"(%7 %8 %9)\", \"\\\"%10\\\"\", %11);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(i8).arg(i9).arg(i10).arg(s11).arg(i12);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 2) {
        QString s1 = ui->lineEdit_54->text();
        QString s2 = ui->lineEdit_53->text();
        QString s3 = ui->lineEdit_59->text();
        QString s4 = ui->lineEdit_61->text();
        QString s5 = ui->lineEdit_52->text();
        QString s6 = ui->lineEdit_60->text();
        QString s7 = ui->lineEdit_58->text();
        QString s8 = ui->lineEdit_72->text();
        int i9 = ui->spinBox_46->value();
        int i10 = ui->spinBox_47->value();
        int i11 = ui->spinBox_48->value();
        QString s12 = ui->lineEdit_56->text();
        double i13 = ui->doubleSpinBox_3->value();
        QString execute = QString("my_CreateRegularPolyhedron(\"%1\", \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"%6mm\", \"%7mm\", \"%8\", \"(%9 %10 %11)\", \"\\\"%12\\\"\", %13);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(s7).arg(s8).arg(i9).arg(i10).arg(i11).arg(s12).arg(i13);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 3) { //圆锥体
        QString s1 = ui->lineEdit_64->text();
        QString s2 = ui->lineEdit_63->text();
        QString s3 = ui->lineEdit_69->text();
        QString s4 = ui->lineEdit_71->text();
        QString s5 = ui->lineEdit_62->text();
        QString s6 = ui->lineEdit_70->text();
        QString s7 = ui->lineEdit_68->text();
        int i8 = ui->spinBox_10->value();
        int i9 = ui->spinBox_11->value();
        int i10 = ui->spinBox_12->value();
        QString s11 = ui->lineEdit_66->text();
        double i12 = ui->doubleSpinBox_4->value();
        QString execute = QString("my_CreateCone(\"%1\", \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"%6mm\", \"%7mm\", \"(%8 %9 %10)\", \"\\\"%11\\\"\", %12);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(s7).arg(i8).arg(i9).arg(i10).arg(s11).arg(i12);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 4) { //球体
        QString s1 = ui->lineEdit_75->text();
        QString s2 = ui->lineEdit_74->text();
        QString s3 = ui->lineEdit_73->text();
        QString s4 = ui->lineEdit_82->text();
        QString s5 = ui->lineEdit_79->text();
        int i6 = ui->spinBox_13->value();
        int i7 = ui->spinBox_14->value();
        int i8 = ui->spinBox_15->value();
        QString s9 = ui->lineEdit_77->text();
        double i10 = ui->doubleSpinBox_5->value();
        QString execute = QString("my_CreateSphere(\"%1\", \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"(%8 %9 %10)\", \"\\\"%11\\\"\", %12);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(i6).arg(i7).arg(i8).arg(s9).arg(i10);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 5) { //圆环体
        QString s1 = ui->lineEdit_83->text();
        QString s2 = ui->lineEdit_81->text();
        QString s3 = ui->lineEdit_88->text();
        QString s4 = ui->lineEdit_90->text();
        QString s5 = ui->lineEdit_80->text();
        QString s6 = ui->lineEdit_87->text();

        int i8 = ui->spinBox_16->value();
        int i9 = ui->spinBox_17->value();
        int i10 = ui->spinBox_18->value();

        QString s11 = ui->lineEdit_85->text();
        double i12 = ui->doubleSpinBox_6->value();
        QString execute = QString("my_CreateCylinder(\"%1\", \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"%6mm\", \"(%7 %8 %9)\", \"\\\"%10\\\"\", %11);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(i8).arg(i9).arg(i10).arg(s11).arg(i12);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 6) { //接合线
        QString s1 = ui->lineEdit_92->text();
        QString s2 = ui->lineEdit_39->text();
        QString s3 = ui->lineEdit_40->text();
        QString s4 = ui->lineEdit_94->text();
        QString s5 = ui->lineEdit_91->text();
        QString s6 = ui->lineEdit_89->text();
        QString s7 = ui->lineEdit_93->text();
        QString s8 = ui->lineEdit_97->text();
        QString s9 = ui->lineEdit_98->text();
        QString s10 = ui->lineEdit_95->text();
        QString s11 = ui->lineEdit_99->text();
        QString s12 = ui->lineEdit_96->text();
        QString s13 = ui->lineEdit->text();
        int i14 = ui->spinBox_21->value();
        int i15 = ui->spinBox_19->value();
        int i16 = ui->spinBox_20->value();
        QString s17 = ui->lineEdit_36->text();
        double i18 = ui->doubleSpinBox_7->value();
        QString execute = QString("my_CreateBondwire(\"%1\", \"%2mm\", \"%3\", \"%4mm\", \"%5mm\", \"%6mm\", \"%7mm\", \"%8mm\", \"%9mm\", \"%10mm\", \"%11mm\", \"%12mm\", \"%13\", \"(%14 %15 %16)\", \"\\\"%17\\\"\", %18);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(s7).arg(s8).arg(s9).arg(s10).arg(s11).arg(s12).arg(s13).arg(i14).arg(i15).arg(i16).arg(s17).arg(i18);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 7) {
        QString s1 = ui->lineEdit_102->text();
        QString s2 = ui->lineEdit_101->text();
        QString s3 = ui->lineEdit_107->text();
        QString s4 = ui->lineEdit_109->text();
        QString s5 = ui->lineEdit_100->text();
        QString s6 = ui->lineEdit_106->text();

        int i8 = ui->spinBox_22->value();
        int i9 = ui->spinBox_23->value();
        int i10 = ui->spinBox_24->value();

        QString s11 = ui->lineEdit_104->text();
        double i12 = ui->doubleSpinBox_8->value();
        QString execute = QString("my_CreateRectangle(\"%1\", \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"%6mm\", \"(%7 %8 %9)\", \"\\\"%10\\\"\", %11);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(i8).arg(i9).arg(i10).arg(s11).arg(i12);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 8) { //圆形
        QString s1 = ui->lineEdit_111->text();
        QString s2 = ui->lineEdit_110->text();
        QString s3 = ui->lineEdit_115->text();
        QString s4 = ui->lineEdit_118->text();
        QString s5 = ui->lineEdit_108->text();
        int i6 = ui->spinBox_25->value();
        int i7 = ui->spinBox_26->value();
        int i8 = ui->spinBox_27->value();
        QString s9 = ui->lineEdit_113->text();
        double i10 = ui->doubleSpinBox_10->value();
        QString execute = QString("my_CreateCircle(\"%1\", \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"(%8 %9 %10)\", \"\\\"%11\\\"\", %12);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(i6).arg(i7).arg(i8).arg(s9).arg(i10);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 9) { //多边形
        QString s1 = ui->lineEdit_119->text();
        QString s2 = ui->lineEdit_117->text();
        QString s3 = ui->lineEdit_124->text();
        QString s4 = ui->lineEdit_126->text();
        QString s5 = ui->lineEdit_116->text();
        QString s6 = ui->lineEdit_125->text();
        QString s7 = ui->lineEdit_123->text();
        QString s8 = ui->lineEdit_127->text();
        int i9 = ui->spinBox_28->value();
        int i10 = ui->spinBox_29->value();
        int i11 = ui->spinBox_30->value();
        QString s12 = ui->lineEdit_121->text();
        double i13 = ui->doubleSpinBox_11->value();
        QString execute = QString("my_CreateRegularPolygon(\"%1\", \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"%6mm\", \"%7mm\", \"%8\", \"(%9 %10 %11)\", \"\\\"%12\\\"\", %13);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(s7).arg(s8).arg(i9).arg(i10).arg(i11).arg(s12).arg(i13);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 10) { //椭圆
        QString s1 = ui->lineEdit_130->text();
        QString s2 = ui->lineEdit_129->text();
        QString s3 = ui->lineEdit_135->text();
        QString s4 = ui->lineEdit_137->text();
        QString s5 = ui->lineEdit_128->text();
        QString s6 = ui->lineEdit_136->text();
        QString s7 = ui->lineEdit_134->text();
        int i8 = ui->spinBox_31->value();
        int i9 = ui->spinBox_32->value();
        int i10 = ui->spinBox_33->value();
        QString s11 = ui->lineEdit_132->text();
        double i12 = ui->doubleSpinBox_12->value();
        QString execute = QString("my_CreateEllipse(\"%1\", \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"%6\", \"%7\", \"(%8 %9 %10)\", \"\\\"%11\\\"\", %12);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(s7).arg(i8).arg(i9).arg(i10).arg(s11).arg(i12);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 11) { //区域
        QString s1 = ui->lineEdit_2->text();
        QString s2 = ui->lineEdit_3->text();
        QString s3 = ui->lineEdit_4->text();
        QString s4 = ui->lineEdit_147->text();
        QString s5 = ui->lineEdit_5->text();
        QString s6 = ui->lineEdit_152->text();
        QString s7 = ui->lineEdit_6->text();
        int i8 = ui->spinBox_34->value();
        int i9 = ui->spinBox_35->value();
        int i10 = ui->spinBox_36->value();
        QString s11 = ui->lineEdit_140->text();
        double i12 = ui->doubleSpinBox_13->value();
        QString execute = QString("my_CreateRegion(\"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"(%8 %9 %10)\", \"\\\"%11\\\"\", %12);\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(s7).arg(i8).arg(i9).arg(i10).arg(s11).arg(i12);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 12) {
        QString s1 = ui->lineEdit_141->text();
        QString s2 = ui->lineEdit_145->text();
        QString s3 = ui->lineEdit_139->text();
        QString s4 = ui->lineEdit_138->text();

        int i8 = ui->spinBox_37->value();
        int i9 = ui->spinBox_38->value();
        int i10 = ui->spinBox_39->value();

        QString execute = QString("my_CreatePoint(\"%1\", \"%2\", \"%3\", \"%4\", \"(%5 %6 %7)\");\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(i8).arg(i9).arg(i10);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 13) { //区域
        QString s1 = ui->lineEdit_149->text();
        QString s2 = ui->lineEdit_151->text();
        QString s3 = ui->lineEdit_148->text();
        QString s4 = ui->lineEdit_142->text();
        QString s5 = ui->lineEdit_150->text();
        QString s6 = ui->lineEdit_154->text();
        QString s7 = ui->lineEdit_155->text();
        int i8 = ui->spinBox_40->value();
        int i9 = ui->spinBox_41->value();
        int i10 = ui->spinBox_42->value();

        QString execute = QString("my_CreateRegion(\"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"(%8 %9 %10)\");\n\n").arg(s1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(s7).arg(i8).arg(i9).arg(i10);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 14) { //移动
        QString nameList = ui->lineEdit_157->text();
        QString s2 = ui->lineEdit_22->text();
        QString s3 = ui->lineEdit_156->text();
        QString s4 = ui->lineEdit_153->text();
        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument1 = "[\"" + strList.join("\", \"") + "\"]";
        QString execute = QString("my_move(%1, \"%2mm\", \"%3mm\", \"%4mm\");\n\n").arg(argument1).arg(s2).arg(s3).arg(s4);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, nameList, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 15) { //旋转
        QString nameList = ui->lineEdit_160->text();
        QString s2 = ui->comboBox_3->currentText();
        QString s3 = ui->lineEdit_159->text();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument1 = "[\"" + strList.join("\", \"") + "\"]";
        QString execute = QString("my_rotate(%1, \"%2\", \"%3deg\");\n\n").arg(argument1).arg(s2).arg(s3);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, nameList, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 16) {
        QString nameList = ui->lineEdit_162->text();
        QString s2 = ui->lineEdit_23->text();
        QString s3 = ui->lineEdit_161->text();
        QString s4 = ui->lineEdit_158->text();
        QString s5 = ui->lineEdit_163->text();
        QString s6 = ui->lineEdit_166->text();
        QString s7 = ui->lineEdit_167->text();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument1 = "[\"" + strList.join("\", \"") + "\"]";
        QString execute = QString("my_mirror(%1, \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"%6mm\", \"%7mm\");\n\n").arg(argument1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(s7);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, nameList, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 17) { //沿线复制
        QString nameList = ui->lineEdit_168->text();
        QString s2 = ui->lineEdit_24->text();
        QString s3 = ui->lineEdit_165->text();
        QString s4 = ui->lineEdit_164->text();
        QString s5 = ui->lineEdit_169->text();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument1 = "[\"" + strList.join("\", \"") + "\"]";
        QString execute = QString("my_duplicateAlongLine(%1, \"%2mm\", \"%3mm\", \"%4mm\", \"%5\");\n\n").arg(argument1).arg(s2).arg(s3).arg(s4).arg(s5);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, nameList, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 18) { //沿轴复制
        QString nameList = ui->lineEdit_172->text();
        QString s2 = ui->comboBox_4->currentText();
        QString s3 = ui->lineEdit_171->text();
        QString s4 = ui->lineEdit_170->text();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument1 = "[\"" + strList.join("\", \"") + "\"]";
        QString execute = QString("my_duplicateAroundAxis(%1, \"%2\", \"%3deg\", \"%4\");\n\n").arg(argument1).arg(s2).arg(s3).arg(s4);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, nameList, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 19) { //镜像复制
        QString nameList = ui->lineEdit_175->text();
        QString s2 = ui->lineEdit_25->text();
        QString s3 = ui->lineEdit_174->text();
        QString s4 = ui->lineEdit_173->text();
        QString s5 = ui->lineEdit_176->text();
        QString s6 = ui->lineEdit_179->text();
        QString s7 = ui->lineEdit_180->text();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument1 = "[\"" + strList.join("\", \"") + "\"]";
        QString execute = QString("my_duplicateMirror(%1, \"%2mm\", \"%3mm\", \"%4mm\", \"%5mm\", \"%6mm\", \"%7mm\");\n\n").arg(argument1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6).arg(s7);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, nameList, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 20) { //合并
        QString nameList = ui->lineEdit_181->text();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument1 = "[\"" + strList.join("\", \"") + "\"]";
        QString execute = QString("my_unite(%1);\n\n").arg(argument1);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, nameList, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 21) { //减去
        QString nameList1 = ui->lineEdit_26->text();
        QString nameList2 = ui->lineEdit_178->text();
        QStringList strList1 = nameList1.split(",");
        QStringList strList2 = nameList2.split(",");
        strList1.removeAll("");
        strList2.removeAll("");
        QString argument1 = "[\"" + strList1.join("\", \"") + "\"]";
        QString argument2 = "[\"" + strList2.join("\", \"") + "\"]";
        QString execute = QString("my_subtract(%1, %2);\n\n").arg(argument1).arg(argument2);
        this->mainWindow_->res += execute;
        QString str = nameList1 + " - " + nameList2;
        Action_Label* act_label = new Action_Label(this->mainWindow_, str, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 22) { //相交
        QString nameList = ui->lineEdit_183->text();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument1 = "[\"" + strList.join("\", \"") + "\"]";
        QString execute = QString("my_intersect(%1);\n\n").arg(argument1);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, nameList, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 23) { //分裂
        QString nameList = ui->lineEdit_27->text();
        QString s2 = ui->comboBox_9->currentText();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument1 = "[\"" + strList.join("\", \"") + "\"]";
        QString execute = QString("my_split(%1, \"%2\");\n\n").arg(argument1).arg(s2);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, nameList, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 24) { //标记
        QString nameList1 = ui->lineEdit_28->text();
        QString nameList2 = ui->lineEdit_184->text();
        QStringList strList1 = nameList1.split(",");
        QStringList strList2 = nameList2.split(",");
        strList1.removeAll("");
        strList2.removeAll("");
        QString argument1 = "[\"" + strList1.join("\", \"") + "\"]";
        QString argument2 = "[\"" + strList2.join("\", \"") + "\"]";
        QString execute = QString("my_imprint(%1, %2);\n\n").arg(argument1).arg(argument2);
        this->mainWindow_->res += execute;
        QString str = nameList1 + "," + nameList2;
        Action_Label* act_label = new Action_Label(this->mainWindow_, str, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 25) { //沿向量扫
        QString nameList = ui->lineEdit_29->text();
        QString s2 = ui->lineEdit_185->text();
        QString s3 = ui->comboBox_6->currentText();
        QString s4 = ui->lineEdit_188->text();
        QString s5 = ui->lineEdit_192->text();
        QString s6 = ui->lineEdit_189->text();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument1 = "[\"" + strList.join("\", \"") + "\"]";
        QString execute = QString("my_sweepAlongVector(%1, \"%2deg\", \"%3\", \"%4mm\", \"%5mm\", \"%6mm\");\n\n").arg(argument1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, nameList, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 26) { //沿轴扫
        QString nameList = ui->lineEdit_30->text();
        QString s2 = ui->lineEdit_187->text();
        QString s3 = ui->comboBox_7->currentText();
        QString s4 = ui->comboBox_5->currentText();
        QString s5 = ui->lineEdit_195->text();
        QString s6 = ui->lineEdit_196->text();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument1 = "[\"" + strList.join("\", \"") + "\"]";
        QString execute = QString("my_sweepAroundAxis(%1, \"%2deg\", \"%3\", \"%4\", \"%5deg\", \"%6\");\n\n").arg(argument1).arg(s2).arg(s3).arg(s4).arg(s5).arg(s6);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, nameList, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 27) { //沿路径扫
        QString nameList1 = ui->lineEdit_31->text();
        QString nameList2 = ui->lineEdit_191->text();
        QString s3 = ui->lineEdit_190->text();
        QString s4 = ui->comboBox_8->currentText();
        QString s5 = ui->lineEdit_199->text();
        QStringList strList1 = nameList1.split(",");
        QStringList strList2 = nameList2.split(",");
        strList1.removeAll("");
        strList2.removeAll("");
        QString argument1 = "[\"" + strList1.join("\", \"") + "\"]";
        QString argument2 = "[\"" + strList2.join("\", \"") + "\"]";
        QString execute = QString("my_sweepAlongPath(%1, %2, \"%3deg\", \"%4\", \"%5deg\");\n\n").arg(argument1).arg(argument2).arg(s3).arg(s4).arg(s5);
        this->mainWindow_->res += execute;
        QString str = nameList1 + "," + nameList2;
        Action_Label* act_label = new Action_Label(this->mainWindow_, str, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else if (index == 28) {
        QString s1 = ui->lineEdit_198->text();
        QString nameList = ui->lineEdit_32->text();

        QString s3 = ui->lineEdit_193->text();
        QString s4 = ui->lineEdit_200->text();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument2 = "[" + strList.join(", ") + "]";
        QString execute = QString("my_fillet(\"%1\", %2, \"%3mm\", \"%4mm\");\n\n").arg(s1).arg(argument2).arg(s3).arg(s4);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    } else {
        QString s1 = ui->lineEdit_203->text();
        QString nameList = ui->lineEdit_33->text();

        QString s3 = ui->lineEdit_201->text();
        QString s4 = ui->lineEdit_204->text();
        QString s5 = ui->comboBox_10->currentText();

        QStringList strList = nameList.split(",");
        strList.removeAll("");
        QString argument2 = "[" + strList.join(", ") + "]";
        QString execute = QString("my_fillet(\"%1\", %2, \"%3mm\", \"%4mm\", \"%5\");\n\n").arg(s1).arg(argument2).arg(s3).arg(s4).arg(s5);
        this->mainWindow_->res += execute;
        Action_Label* act_label = new Action_Label(this->mainWindow_, s1, ui->stackedWidget->currentIndex());
        this->mainWindow_->action_label = act_label;
        //qDebug() << "此处发送set_widget信号";
        emit set_widget();
    }
}

void myDialog::validator_config() {
    //validator1：只能数字、小数点，两位小数，没有负号
    QRegularExpressionValidator* validator1 = new QRegularExpressionValidator(QRegularExpression("[0-9]+(\\.[0-9]{1,2})?"), ui->lineEdit_226);
    ui->lineEdit_226->setValidator(validator1);
    ui->lineEdit_227->setValidator(validator1);
    ui->lineEdit_228->setValidator(validator1);
    ui->lineEdit_206->setValidator(validator1);
    ui->lineEdit_212->setValidator(validator1);
    ui->lineEdit_79->setValidator(validator1);
    ui->lineEdit_80->setValidator(validator1);
    ui->lineEdit_87->setValidator(validator1);
    ui->lineEdit_39->setValidator(validator1);
    ui->lineEdit_94->setValidator(validator1);
    ui->lineEdit_91->setValidator(validator1);
    ui->lineEdit_89->setValidator(validator1);
    ui->lineEdit_95->setValidator(validator1);
    ui->lineEdit_99->setValidator(validator1);
    ui->lineEdit_96->setValidator(validator1);
    ui->lineEdit_100->setValidator(validator1);
    ui->lineEdit_106->setValidator(validator1);
    ui->lineEdit_108->setValidator(validator1);
    ui->lineEdit_128->setValidator(validator1);
    ui->lineEdit_193->setValidator(validator1);
    ui->lineEdit_201->setValidator(validator1);
    ui->lineEdit_204->setValidator(validator1);
    //validator2：只能数字、小数点，两位小数，有负号
    QRegularExpressionValidator* validator2 = new QRegularExpressionValidator(QRegularExpression("-?\\d*\\.?\\d{0,2}"), ui->lineEdit_223);
    ui->lineEdit_223->setValidator(validator2);
    ui->lineEdit_224->setValidator(validator2);
    ui->lineEdit_225->setValidator(validator2);
    ui->lineEdit_214->setValidator(validator2);
    ui->lineEdit_215->setValidator(validator2);
    ui->lineEdit_216->setValidator(validator2);
    ui->lineEdit_53->setValidator(validator2);
    ui->lineEdit_59->setValidator(validator2);
    ui->lineEdit_61->setValidator(validator2);
    ui->lineEdit_52->setValidator(validator2);
    ui->lineEdit_60->setValidator(validator2);
    ui->lineEdit_58->setValidator(validator2);
    ui->lineEdit_63->setValidator(validator2);
    ui->lineEdit_69->setValidator(validator2);
    ui->lineEdit_71->setValidator(validator2);
    ui->lineEdit_74->setValidator(validator2);
    ui->lineEdit_73->setValidator(validator2);
    ui->lineEdit_82->setValidator(validator2);
    ui->lineEdit_81->setValidator(validator2);
    ui->lineEdit_88->setValidator(validator2);
    ui->lineEdit_90->setValidator(validator2);
    ui->lineEdit_93->setValidator(validator2);
    ui->lineEdit_97->setValidator(validator2);
    ui->lineEdit_98->setValidator(validator2);
    ui->lineEdit_101->setValidator(validator2);
    ui->lineEdit_107->setValidator(validator2);
    ui->lineEdit_109->setValidator(validator2);
    ui->lineEdit_110->setValidator(validator2);
    ui->lineEdit_115->setValidator(validator2);
    ui->lineEdit_118->setValidator(validator2);
    ui->lineEdit_117->setValidator(validator2);
    ui->lineEdit_124->setValidator(validator2);
    ui->lineEdit_116->setValidator(validator2);
    ui->lineEdit_126->setValidator(validator2);
    ui->lineEdit_125->setValidator(validator2);
    ui->lineEdit_123->setValidator(validator2);
    ui->lineEdit_129->setValidator(validator2);
    ui->lineEdit_135->setValidator(validator2);
    ui->lineEdit_137->setValidator(validator2);
    ui->lineEdit_136->setValidator(validator2);
    ui->lineEdit_3->setValidator(validator2);
    ui->lineEdit_4->setValidator(validator2);
    ui->lineEdit_5->setValidator(validator2);
    ui->lineEdit_6->setValidator(validator2);
    ui->lineEdit_147->setValidator(validator2);
    ui->lineEdit_152->setValidator(validator2);
    ui->lineEdit_145->setValidator(validator2);
    ui->lineEdit_139->setValidator(validator2);
    ui->lineEdit_138->setValidator(validator2);
    ui->lineEdit_151->setValidator(validator2);
    ui->lineEdit_150->setValidator(validator2);
    ui->lineEdit_148->setValidator(validator2);
    ui->lineEdit_154->setValidator(validator2);
    ui->lineEdit_142->setValidator(validator2);
    ui->lineEdit_155->setValidator(validator2);
    ui->lineEdit_22->setValidator(validator2);
    ui->lineEdit_156->setValidator(validator2);
    ui->lineEdit_153->setValidator(validator2);
    ui->lineEdit_159->setValidator(validator2);
    ui->lineEdit_23->setValidator(validator2);
    ui->lineEdit_161->setValidator(validator2);
    ui->lineEdit_163->setValidator(validator2);
    ui->lineEdit_166->setValidator(validator2);
    ui->lineEdit_158->setValidator(validator2);
    ui->lineEdit_167->setValidator(validator2);
    ui->lineEdit_24->setValidator(validator2);
    ui->lineEdit_165->setValidator(validator2);
    ui->lineEdit_164->setValidator(validator2);
    ui->lineEdit_171->setValidator(validator2);
    ui->lineEdit_25->setValidator(validator2);
    ui->lineEdit_176->setValidator(validator2);
    ui->lineEdit_174->setValidator(validator2);
    ui->lineEdit_179->setValidator(validator2);
    ui->lineEdit_173->setValidator(validator2);
    ui->lineEdit_180->setValidator(validator2);
    ui->lineEdit_185->setValidator(validator2);
    ui->lineEdit_188->setValidator(validator2);
    ui->lineEdit_192->setValidator(validator2);
    ui->lineEdit_189->setValidator(validator2);
    ui->lineEdit_187->setValidator(validator2);
    ui->lineEdit_195->setValidator(validator2);
    ui->lineEdit_199->setValidator(validator2);
    ui->lineEdit_190->setValidator(validator2);
    ui->lineEdit_200->setValidator(validator2);
    //validator3：只能输入大小写字母和数字和下划线，且不能以数字开头
    QRegularExpressionValidator* validator3 = new QRegularExpressionValidator(QRegularExpression("^(?![0-9])\\w*$"), ui->lineEdit_219);
    ui->lineEdit_219->setValidator(validator3);
    ui->lineEdit_209->setValidator(validator3);
    ui->lineEdit_54->setValidator(validator3);
    ui->lineEdit_64->setValidator(validator3);
    ui->lineEdit_62->setValidator(validator3);
    ui->lineEdit_70->setValidator(validator3);
    ui->lineEdit_68->setValidator(validator3);
    ui->lineEdit_75->setValidator(validator3);
    ui->lineEdit_83->setValidator(validator3);
    ui->lineEdit_92->setValidator(validator3);
    ui->lineEdit_102->setValidator(validator3);
    ui->lineEdit_111->setValidator(validator3);
    ui->lineEdit_119->setValidator(validator3);
    ui->lineEdit_130->setValidator(validator3);
    ui->lineEdit_2->setValidator(validator3);
    ui->lineEdit_141->setValidator(validator3);
    ui->lineEdit_149->setValidator(validator3);
    ui->lineEdit_198->setValidator(validator3);
    ui->lineEdit_203->setValidator(validator3);
    //validator4：只能输入小写字母，顺便配置了材料框的一下智能提示
    QRegularExpressionValidator* validator4 = new QRegularExpressionValidator(QRegularExpression("^[a-z]+$"), ui->lineEdit_220);
    QStringList wordList = {"air", "vacuum", "copper", "aluminum", "gold", "silver", "tungsten", "steel", "alumina", "al2o3", "aluminum oxide"};
    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_220->setValidator(validator4);
    ui->lineEdit_220->setCompleter(completer);

    ui->lineEdit_211->setValidator(validator4);
    ui->lineEdit_211->setCompleter(completer);

    ui->lineEdit_56->setValidator(validator4);
    ui->lineEdit_56->setCompleter(completer);

    ui->lineEdit_66->setValidator(validator4);
    ui->lineEdit_66->setCompleter(completer);

    ui->lineEdit_77->setValidator(validator4);
    ui->lineEdit_77->setCompleter(completer);
    ui->lineEdit_85->setValidator(validator4);
    ui->lineEdit_85->setCompleter(completer);
    ui->lineEdit_36->setValidator(validator4);
    ui->lineEdit_36->setCompleter(completer);
    ui->lineEdit_104->setValidator(validator4);
    ui->lineEdit_104->setCompleter(completer);
    ui->lineEdit_113->setValidator(validator4);
    ui->lineEdit_113->setCompleter(completer);
    ui->lineEdit_121->setValidator(validator4);
    ui->lineEdit_121->setCompleter(completer);
    ui->lineEdit_132->setValidator(validator4);
    ui->lineEdit_132->setCompleter(completer);
    ui->lineEdit_140->setValidator(validator4);
    ui->lineEdit_140->setCompleter(completer);
    //validator5：只能输入正整数
    QRegularExpressionValidator* validator5 = new QRegularExpressionValidator(QRegularExpression("^[1-9]\\d*$"), ui->lineEdit_72);
    ui->lineEdit_72->setValidator(validator5);
    ui->lineEdit_40->setValidator(validator5);
    ui->lineEdit->setValidator(validator5);
    ui->lineEdit_127->setValidator(validator5);
    ui->lineEdit_134->setValidator(validator5);
    ui->lineEdit_169->setValidator(validator5);
    ui->lineEdit_170->setValidator(validator5);
    ui->lineEdit_196->setValidator(validator5);
    //validator6：只能输入大小写字母、数字、下划线、逗号，逗号不能放在开头或结尾
    QRegularExpressionValidator* validator6 = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9]+([_,][a-zA-Z0-9]+)*$"), ui->lineEdit_183);
    ui->lineEdit_183->setValidator(validator6);
    ui->lineEdit_157->setValidator(validator6);
    ui->lineEdit_160->setValidator(validator6);
    ui->lineEdit_162->setValidator(validator6);
    ui->lineEdit_168->setValidator(validator6);
    ui->lineEdit_172->setValidator(validator6);
    ui->lineEdit_175->setValidator(validator6);
    ui->lineEdit_181->setValidator(validator6);
    ui->lineEdit_26->setValidator(validator6);
    ui->lineEdit_178->setValidator(validator6);
    ui->lineEdit_27->setValidator(validator6);
    ui->lineEdit_28->setValidator(validator6);
    ui->lineEdit_184->setValidator(validator6);
    ui->lineEdit_29->setValidator(validator6);
    ui->lineEdit_30->setValidator(validator6);
    ui->lineEdit_31->setValidator(validator6);
    //validator7：只能输入正整数、逗号，逗号不能放在开头和末尾
    QRegularExpressionValidator* validator7 = new QRegularExpressionValidator(QRegularExpression("^[1-9]\\d*(,[1-9]\\d*)*(,[1-9]\\d*)?$"), ui->lineEdit_191);
    ui->lineEdit_191->setValidator(validator7);
    ui->lineEdit_32->setValidator(validator7);
    //ui->lineEdit_197->setValidator(validator7);
    ui->lineEdit_33->setValidator(validator7);
    //ui->lineEdit_202->setValidator(validator7);
}

QString myDialog::get_code(int index) {
    if (index == 0) { //长方体
        return QString("# Box\n\
# example of use:\n\
# my_CreateBox(\"Box1\", \"0mm\", \"0mm\", \"0mm\", \"1mm\", \"1mm\", \"1mm\", \"(143 175 143)\", \"\\\"vacuum\\\"\", 0)\n\
def my_CreateBox(name, xPos = \"0mm\", yPos = \"0mm\", zPos = \"0mm\", xSize = \"1mm\", ySize = \"1mm\", zSize = \"1mm\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateBox(\n\
        [\n\
            \"NAME:BoxParameters\",\n\
            \"XPosition:=\"\t\t, xPos,\n\
            \"YPosition:=\"\t\t, yPos,\n\
            \"ZPosition:=\"\t\t, zPos,\n\
            \"XSize:=\"\t\t, xSize,\n\
            \"YSize:=\"\t\t, ySize,\n\
            \"ZSize:=\"\t\t, zSize\n\
        ], \n\
        [\n\
            \"NAME:Attributes\",\n\
            \"Name:=\"\t\t, name,\n\
            \"Flags:=\"\t\t, \"\",\n\
            \"Color:=\"\t\t, color,\n\
            \"Transparency:=\"\t, transparency,\n\
            \"PartCoordinateSystem:=\", \"Global\",\n\
            \"UDMId:=\"\t\t, \"\",\n\
            \"MaterialValue:=\"\t, materialValue,\n\
            \"SurfaceMaterialValue:=\"\t, \"\\\"\\\"\",\n\
            \"SolveInside:=\"\t\t, True,\n\
            \"ShellElement:=\"\t, False,\n\
            \"ShellElementThickness:=\", \"0mm\",\n\
            \"IsMaterialEditable:=\"\t, True,\n\
            \"UseMaterialAppearance:=\"\t, False,\n\
            \"IsLightweight:=\"\t, False\n\
        ])\n");
    } else if (index == 1) { //圆柱体
        return QString("def my_CreateCylinder(name, xCen = \"0mm\", yCen = \"0mm\", zCen = \"0mm\", radius = \"0.5mm\", height = \"0.5mm\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateCylinder(\n\
        [\n\
            \"NAME:CylinderParameters\",\n\
            \"XCenter:=\"\t\t, xCen,\n\
            \"YCenter:=\"\t\t, yCen,\n\
            \"ZCenter:=\"\t\t, zCen,\n\
            \"Radius:=\"\t\t, radius,\n\
            \"Height:=\"\t\t, height,\n\
            \"WhichAxis:=\"\t\t, \"Z\",\n\
            \"NumSides:=\"\t\t, \"0\"\n\
        ], \n\
        [\n\
            \"NAME:Attributes\",\n\
            \"Name:=\"\t\t, name,\n\
            \"Flags:=\"\t\t, \"\",\n\
            \"Color:=\"\t\t, color,\n\
            \"Transparency:=\"	, transparency,\n\
            \"PartCoordinateSystem:=\", \"Global\",\n\
            \"UDMId:=\"\t\t, \"\",\n\
            \"MaterialValue:=\"	, materialValue,\n\
            \"SurfaceMaterialValue:=\", \"\\\"\\\"\",\n\
            \"SolveInside:=\"\t\t, True,\n\
            \"ShellElement:=\"\t, False,\n\
            \"ShellElementThickness:=\", \"0mm\",\n\
            \"IsMaterialEditable:=\"\t, True,\n\
            \"UseMaterialAppearance:=\", False,\n\
            \"IsLightweight:=\"\t, False\n\
        ])\n");
    } else if (index == 2) { //棱柱体
        return QString("def my_CreateRegularPolyhedron(name, xCen = \"0mm\", yCen = \"0mm\", zCen = \"0mm\", xStart = \"-0.5mm\", yStart = \"0.5mm\", zStart = \"0mm\", height = \"0.5mm\", numSides = \"12\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateRegularPolyhedron(\n\
        [\n\
            \"NAME:PolyhedronParameters\",\n\
            \"XCenter:=\"\t\t, xCen,\n\
            \"YCenter:=\"\t\t, yCen,\n\
            \"ZCenter:=\"\t\t, zCen,\n\
            \"XStart:=\"\t\t, xStart,\n\
            \"YStart:=\"\t\t, yStart,\n\
            \"ZStart:=\"\t\t, zStart,\n\
            \"Height:=\"\t\t, height,\n\
            \"NumSides:=\"\t\t, numSides,\n\
            \"WhichAxis:=\"\t\t, \"Z\"\n\
        ], \n\
        [\n\
            \"NAME:Attributes\",\n\
            \"Name:=\"\t\t, name,\n\
            \"Flags:=\"\t\t, \"\",\n\
            \"Color:=\"\t\t, color,\n\
            \"Transparency:=\"\t, transparency,\n\
            \"PartCoordinateSystem:=\", \"Global\",\n\
            \"UDMId:=\"\t\t, \"\",\n\
            \"MaterialValue:=\"\t, materialValue,\n\
            \"SurfaceMaterialValue:=\", \"\\\"\\\"\",\n\
            \"SolveInside:=\"\t\t, True,\n\
            \"ShellElement:=\"\t, False,\n\
            \"ShellElementThickness:=\", \"0mm\",\n\
            \"IsMaterialEditable:=\"\t, True,\n\
            \"UseMaterialAppearance:=\", False,\n\
            \"IsLightweight:=\"\t, False\n\
        ])\n");
    } else if (index == 3) { //圆锥体
        return QString("def my_CreateCone(name, xCen = \"0mm\", yCen = \"0mm\", zCen = \"0mm\", height = \"0.5mm\", bottomRadius = \"0.2mm\", topRadius = \"0.4mm\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateCone(\n\
    [\n\
        \"NAME:ConeParameters\",\n\
        \"XCenter:=\"		, xCen,\n\
        \"YCenter:=\"		, yCen,\n\
        \"ZCenter:=\"		, zCen,\n\
        \"WhichAxis:=\"		, \"Z\",\n\
        \"Height:=\"		, height,\n\
        \"BottomRadius:=\"	, bottomRadius,\n\
        \"TopRadius:=\"		, topRadius\n\
    ], \n\
    [\n\
        \"NAME:Attributes\",\n\
        \"Name:=\"		, name,\n\
        \"Flags:=\"		, \"\",\n\
        \"Color:=\"		, color,\n\
        \"Transparency:=\"	, transparency,\n\
        \"PartCoordinateSystem:=\", \"Global\",\n\
        \"UDMId:=\"		, \"\",\n\
        \"MaterialValue:=\"	, materialValue,\n\
        \"SurfaceMaterialValue:=\", \"\\\"\\\"\",\n\
        \"SolveInside:=\"		, True,\n\
        \"ShellElement:=\"	, False,\n\
        \"ShellElementThickness:=\", \"0mm\",\n\
        \"IsMaterialEditable:=\"	, True,\n\
        \"UseMaterialAppearance:=\", False,\n\
        \"IsLightweight:=\"	, False\n\
    ])\n");
    } else if (index == 4) { //球体
        return QString("def my_CreateSphere(name, xCen = \"0mm\", yCen = \"0mm\", zCen = \"0mm\", radius = \"0.5mm\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateSphere(\n\
    [\n\
        \"NAME:SphereParameters\",\n\
        \"XCenter:=\"		, xCen,\n\
        \"YCenter:=\"		, yCen,\n\
        \"ZCenter:=\"		, zCen,\n\
        \"Radius:=\"		, radius\n\
    ],\n\
    [\n\
        \"NAME:Attributes\",\n\
        \"Name:=\"		, name,\n\
        \"Flags:=\"		, \"\",\n\
        \"Color:=\"		, color,\n\
        \"Transparency:=\"	, transparency,\n\
        \"PartCoordinateSystem:=\", \"Global\",\n\
        \"UDMId:=\"		, \"\",\n\
        \"MaterialValue:=\"	, materialValue,\n\
        \"SurfaceMaterialValue:=\", \"\\\"\\\"\",\n\
        \"SolveInside:=\"		, True,\n\
        \"ShellElement:=\"	, False,\n\
        \"ShellElementThickness:=\", \"0mm\",\n\
        \"IsMaterialEditable:=\"	, True,\n\
        \"UseMaterialAppearance:=\", False,\n\
        \"IsLightweight:=\"	, False\n\
    ])\n");
    } else if (index == 5) { //圆环体
        return QString("def my_CreateTorus(name, xCen = \"0mm\", yCen = \"0mm\", zCen = \"0mm\", majorRadius = \"0.3mm\", minorRadius = \"0.05mm\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateTorus(\n\
    [\n\
        \"NAME:TorusParameters\",\n\
        \"XCenter:=\"		, xCen,\n\
        \"YCenter:=\"		, yCen,\n\
        \"ZCenter:=\"		, zCen,\n\
        \"MajorRadius:=\"		, majorRadius,\n\
        \"MinorRadius:=\"		, minorRadius,\n\
        \"WhichAxis:=\"		, \"Z\"\n\
    ], \n\
    [\n\
        \"NAME:Attributes\",\n\
        \"Name:=\"		, name,\n\
        \"Flags:=\"		, \"\",\n\
        \"Color:=\"		, color,\n\
        \"Transparency:=\"	, transparency,\n\
        \"PartCoordinateSystem:=\", \"Global\",\n\
        \"UDMId:=\"		, \"\",\n\
        \"MaterialValue:=\"	, materialValue,\n\
        \"SurfaceMaterialValue:=\", \"\\\"\\\"\",\n\
        \"SolveInside:=\"		, True,\n\
        \"ShellElement:=\"	, False,\n\
        \"ShellElementThickness:=\", \"0mm\",\n\
        \"IsMaterialEditable:=\"	, True,\n\
        \"UseMaterialAppearance:=\", False,\n\
        \"IsLightweight:=\"	, False\n\
    ])\n");
    } else if (index == 6) { //接合线
        return QString("def my_CreateBondwire(name, wireDiameter = \"0.025mm\", numSides = \"6\", xPadPos = \"3mm\", yPadPos = \"1mm\", zPadPos = \"0mm\", xDir = \"-0.3mm\", yDir = \"0.6mm\", zDir = \"0mm\", distance = \"0.6mm\", h1 = \"0.2mm\", h2 = \"0mm\", beta = \"0\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateBondwire(\n\
    [\n\
        \"NAME:BondwireParameters\",\n\
        \"WireType:=\"		, \"JEDEC_4Points\",\n\
        \"WireDiameter:=\"	, wireDiameter,\n\
        \"NumSides:=\"		, numSides,\n\
        \"XPadPos:=\"		, xPadPos,\n\
        \"YPadPos:=\"		, yPadPos,\n\
        \"ZPadPos:=\"		, zPadPos,\n\
        \"XDir:=\"		, xDir,\n\
        \"YDir:=\"		, yDir,\n\
        \"ZDir:=\"		, zDir,\n\
        \"Distance:=\"		, \"0.670820393249937mm\",\n\
        \"h1:=\"			, h1,\n\
        \"h2:=\"			, h2,\n\
        \"alpha:=\"		, \"80deg\",\n\
        \"beta:=\"		, beta,\n\
        \"WhichAxis:=\"		, \"Z\",\n\
        \"ReverseDirection:=\"	, False\n\
    ],\n\
    [\n\
        \"NAME:Attributes\",\n\
        \"Name:=\"		, name,\n\
        \"Flags:=\"		, \"\",\n\
        \"Color:=\"		, color,\n\
        \"Transparency:=\"	, transparency,\n\
        \"PartCoordinateSystem:=\", \"Global\",\n\
        \"UDMId:=\"		, \"\",\n\
        \"MaterialValue:=\"	, materialValue,\n\
        \"SurfaceMaterialValue:=\", \"\\\"\\\"\",\n\
        \"SolveInside:=\"		, True,\n\
        \"ShellElement:=\"	, False,\n\
        \"ShellElementThickness:=\", \"0mm\",\n\
        \"IsMaterialEditable:=\"	, True,\n\
        \"UseMaterialAppearance:=\", False,\n\
        \"IsLightweight:=\"	, False\n\
    ])\n");
    } else if (index == 7) { //长方形
        return QString("def my_CreateRectangle(name, xStart = \"0mm\", yStart = \"0mm\", zStart = \"0mm\", width = \"0.5mm\", height = \"0.5mm\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateRectangle(\n\
    [\n\
        \"NAME:RectangleParameters\",\n\
        \"IsCovered:=\"		, True,\n\
        \"XStart:=\"		, xStart,\n\
        \"YStart:=\"		, yStart,\n\
        \"ZStart:=\"		, zStart,\n\
        \"Width:=\"		, width,\n\
        \"Height:=\"		, height,\n\
        \"WhichAxis:=\"		, \"Z\"\n\
    ], \n\
    [\n\
        \"NAME:Attributes\",\n\
        \"Name:=\"		, name,\n\
        \"Flags:=\"		, \"\",\n\
        \"Color:=\"		, color,\n\
        \"Transparency:=\"	, transparency,\n\
        \"PartCoordinateSystem:=\", \"Global\",\n\
        \"UDMId:=\"		, \"\",\n\
        \"MaterialValue:=\"	, materialValue,\n\
        \"SurfaceMaterialValue:=\", \"\\\"\\\"\",\n\
        \"SolveInside:=\"		, True,\n\
        \"ShellElement:=\"	, False,\n\
        \"ShellElementThickness:=\", \"0mm\",\n\
        \"IsMaterialEditable:=\"	, True,\n\
        \"UseMaterialAppearance:=\", False,\n\
        \"IsLightweight:=\"	, False\n\
    ])\n");
    } else if (index == 8) { //圆形
        return QString("def my_CreateCircle(name, xCen = \"0mm\", yCen = \"0mm\", zCen = \"0mm\", radius = \"0.5mm\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateCircle(\n\
    [\n\
        \"NAME:CircleParameters\",\n\
        \"IsCovered:=\"		, True,\n\
        \"XCenter:=\"		, xCen,\n\
        \"YCenter:=\"		, yCen,\n\
        \"ZCenter:=\"		, zCen,\n\
        \"Radius:=\"		, radius,\n\
        \"WhichAxis:=\"		, \"Z\",\n\
        \"NumSegments:=\"		, \"0\"\n\
    ], \n\
    [\n\
        \"NAME:Attributes\",\n\
        \"Name:=\"		, name,\n\
        \"Flags:=\"		, \"\",\n\
        \"Color:=\"		, color,\n\
        \"Transparency:=\"	, transparency,\n\
        \"PartCoordinateSystem:=\", \"Global\",\n\
        \"UDMId:=\"		, \"\",\n\
        \"MaterialValue:=\"	, materialValue,\n\
        \"SurfaceMaterialValue:=\", \"\\\"\\\"\",\n\
        \"SolveInside:=\"		, True,\n\
        \"ShellElement:=\"	, False,\n\
        \"ShellElementThickness:=\", \"0mm\",\n\
        \"IsMaterialEditable:=\"	, True,\n\
        \"UseMaterialAppearance:=\", False,\n\
        \"IsLightweight:=\"	, False\n\
    ])\n");
    } else if (index == 9) { //多边形
        return QString("def my_CreateRegularPolygon(name, xCen = \"0mm\", yCen = \"0mm\", zCen = \"0mm\", xStart = \"2mm\", yStart = \"2mm\", zStart = \"0mm\", numSides = \"12\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateRegularPolygon(\n\
    [\n\
        \"NAME:RegularPolygonParameters\",\n\
        \"IsCovered:=\"		, True,\n\
        \"XCenter:=\"		, xCen,\n\
        \"YCenter:=\"		, yCen,\n\
        \"ZCenter:=\"		, zCen,\n\
        \"XStart:=\"		, xStart,\n\
        \"YStart:=\"		, yStart,\n\
        \"ZStart:=\"		, zStart,\n\
        \"NumSides:=\"		, numSides,\n\
        \"WhichAxis:=\"		, \"Z\"\n\
    ],\n\
    [\n\
        \"NAME:Attributes\",\n\
        \"Name:=\"		, name,\n\
        \"Flags:=\"		, \"\",\n\
        \"Color:=\"		, color,\n\
        \"Transparency:=\"	, transparency,\n\
        \"PartCoordinateSystem:=\", \"Global\",\n\
        \"UDMId:=\"		, \"\",\n\
        \"MaterialValue:=\"	, materialValue,\n\
        \"SurfaceMaterialValue:=\", \"\\\"\\\"\",\n\
        \"SolveInside:=\"		, True,\n\
        \"ShellElement:=\"	, False,\n\
        \"ShellElementThickness:=\", \"0mm\",\n\
        \"IsMaterialEditable:=\"	, True,\n\
        \"UseMaterialAppearance:=\", False,\n\
        \"IsLightweight:=\"	, False\n\
    ])\n");
    } else if (index == 10) { //椭圆
        return QString("def my_CreateEllipse(name, xCen = \"0mm\", yCen = \"0mm\", zCen = \"0mm\", majRadius = \"0.3mm\", ratio = \"2.33333333333333\", numSegments = \"0\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateEllipse(\n\
    [\n\
        \"NAME:EllipseParameters\",\n\
        \"IsCovered:=\"		, True,\n\
        \"XCenter:=\"		, xCen,\n\
        \"YCenter:=\"		, yCen,\n\
        \"ZCenter:=\"		, zCen,\n\
        \"MajRadius:=\"		, majRadius,\n\
        \"Ratio:=\"		, ratio,\n\
        \"WhichAxis:=\"		, \"Z\",\n\
        \"NumSegments:=\"		, numSegments\n\
    ],\n\
    [\n\
        \"NAME:Attributes\",\n\
        \"Name:=\"		, name,\n\
        \"Flags:=\"		, \"\",\n\
        \"Color:=\"		, color,\n\
        \"Transparency:=\"	, transparency,\n\
        \"PartCoordinateSystem:=\", \"Global\",\n\
        \"UDMId:=\"		, \"\",\n\
        \"MaterialValue:=\"	, materialValue,\n\
        \"SurfaceMaterialValue:=\", \"\\\"\\\"\",\n\
        \"SolveInside:=\"		, True,\n\
        \"ShellElement:=\"	, False,\n\
        \"ShellElementThickness:=\", \"0mm\",\n\
        \"IsMaterialEditable:=\"	, True,\n\
        \"UseMaterialAppearance:=\", False,\n\
        \"IsLightweight:=\"	, False\n\
    ])\n");
    } else if (index == 11) { //区域
        return QString("def my_CreateRegion(name, posiX = \"0\", nagX = \"0\", posiY = \"0\", nagY = \"0\", posiZ = \"0\", nagZ = \"0\", color = \"(143 175 143)\", materialValue = \"\\\"vacuum\\\"\", transparency = 0):\n\
    oEditor.CreateRegion(\n\
    [\n\
        \"NAME:RegionParameters\",\n\
        \"+XPaddingType:=\"	, \"Percentage Offset\",\n\
        \"+XPadding:=\"		, posiX,\n\
        \"-XPaddingType:=\"	, \"Percentage Offset\",\n\
        \"-XPadding:=\"		, nagX,\n\
        \"+YPaddingType:=\"	, \"Percentage Offset\",\n\
        \"+YPadding:=\"		, posiY,\n\
        \"-YPaddingType:=\"	, \"Percentage Offset\",\n\
        \"-YPadding:=\"		, nagY,\n\
        \"+ZPaddingType:=\"	, \"Percentage Offset\",\n\
        \"+ZPadding:=\"		, posiZ,\n\
        \"-ZPaddingType:=\"	, \"Percentage Offset\",\n\
        \"-ZPadding:=\"		, nagZ\n\
    ], \n\
    [\n\
        \"NAME:Attributes\",\n\
        \"Name:=\"		, name,\n\
        \"Flags:=\"		, \"Wireframe#\",\n\
        \"Color:=\"		, color,\n\
        \"Transparency:=\"	, transparency,\n\
        \"PartCoordinateSystem:=\", \"Global\",\n\
        \"UDMId:=\"		, \"\",\n\
        \"MaterialValue:=\"	, materialValue,\n\
        \"SurfaceMaterialValue:=\", \"\\\"\\\"\",\n\
        \"SolveInside:=\"		, True,\n\
        \"ShellElement:=\"	, False,\n\
        \"ShellElementThickness:=\", \"nan \",\n\
        \"IsMaterialEditable:=\"	, True,\n\
        \"UseMaterialAppearance:=\", False,\n\
        \"IsLightweight:=\"	, False\n\
    ])\n");
    } else if (index == 12) { //点
        return QString("def my_CreatePoint(name, pointX = \"0mm\", pointY = \"0mm\", pointZ = \"0mm\", color = \"(143 175 143)\"):\n\
    oEditor.CreatePoint(\n\
    [\n\
        \"NAME:PointParameters\",\n\
        \"PointX:=\"		, pointX,\n\
        \"PointY:=\"		, pointY,\n\
        \"PointZ:=\"		, pointZ\n\
    ],\n\
    [\n\
        \"NAME:Attributes\",\n\
        \"Name:=\"		, name,\n\
        \"Color:=\"		, color\n\
    ])\n");
    } else if (index == 13) { //截面
        return QString("def my_CreateCutplane(name, planeBaseX = \"-5mm\", planeBaseY = \"-1.8mm\", planeBaseZ = \"0mm\", PlaneNormalX = \"-0.6mm\", PlaneNormalY = \"1.4mm\", PlaneNormalZ = \"0mm\", color = \"(143 175 143)\"):\n\
    oEditor.CreateCutplane(\n\
    [\n\
        \"NAME:PlaneParameters\",\n\
        \"PlaneBaseX:=\"		, planeBaseX,\n\
        \"PlaneBaseY:=\"		, planeBaseY,\n\
        \"PlaneBaseZ:=\"		, planeBaseZ,\n\
        \"PlaneNormalX:=\"	, PlaneNormalX,\n\
        \"PlaneNormalY:=\"	, PlaneNormalY,\n\
        \"PlaneNormalZ:=\"	, PlaneNormalZ\n\
    ],\n\
    [\n\
        \"NAME:Attributes\",\n\
        \"Name:=\"		, name,\n\
        \"Color:=\"		, color\n\
    ])\n");
    } else if (index == 14) { //移动
        return QString("def my_move(selections_list, translateVectorX = \"1mm\", translateVectorY = \"1mm\", translateVectorZ = \"1mm\"):\n\
    selections = \',\'.join(selections_list)\n\
    oEditor.Move(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ],\n\
    [\n\
        \"NAME:TranslateParameters\",\n\
        \"TranslateVectorX:=\"	, translateVectorX,\n\
        \"TranslateVectorY:=\"	, translateVectorY,\n\
        \"TranslateVectorZ:=\"	, translateVectorZ\n\
    ])\n");
    } else if (index == 15) { //旋转
        return QString("def my_rotate(selections_list, rotateAxis = \"X\", rotateAngle = \"90deg\"):\n\
    selections = \',\'.join(selections_list)\n\
    oEditor.Rotate(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ], \n\
    [\n\
        \"NAME:RotateParameters\",\n\
        \"RotateAxis:=\"		, rotateAxis,\n\
        \"RotateAngle:=\"		, rotateAngle\n\
    ])\n");
    } else if (index == 16) { //镜像
        return QString("def my_mirror(selections_list, mirrorBaseX = \"1mm\", mirrorBaseY = \"1mm\", mirrorBaseZ = \"1mm\", mirrorNormalX = \"1mm\", mirrorNormalY = \"0mm\", mirrorNormalZ = \"0mm\"):\n\
    selections = \',\'.join(selections_list)\n\
    oEditor.Mirror(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ], \n\
    [\n\
        \"NAME:MirrorParameters\",\n\
        \"MirrorBaseX:=\"		, mirrorBaseX,\n\
        \"MirrorBaseY:=\"		, mirrorBaseY,\n\
        \"MirrorBaseZ:=\"		, mirrorBaseZ,\n\
        \"MirrorNormalX:=\"	, mirrorNormalX,\n\
        \"MirrorNormalY:=\"	, mirrorNormalY,\n\
        \"MirrorNormalZ:=\"	, mirrorNormalZ\n\
    ])\n");
    } else if (index == 17) { //沿线复制
        return QString("def my_duplicateAlongLine(selections_list, xComponent = \"1mm\", yComponent = \"1mm\", zComponent = \"1mm\", numClones = \"2\"):\n\
    selections = \',\'.join(selections_list)\n\
    oEditor.DuplicateAlongLine(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ],\n\
    [\n\
        \"NAME:DuplicateToAlongLineParameters\",\n\
        \"CreateNewObjects:=\"	, True,\n\
        \"XComponent:=\"		, xComponent,\n\
        \"YComponent:=\"		, yComponent,\n\
        \"ZComponent:=\"		, zComponent,\n\
        \"NumClones:=\"		, numClones\n\
    ],\n\
    [\n\
        \"NAME:Options\",\n\
        \"DuplicateAssignments:=\", False\n\
    ],\n\
    [\n\
        \"CreateGroupsForNewObjects:=\", False\n\
    ])\n");
    } else if (index == 18) { //沿轴复制
        return QString("def my_duplicateAroundAxis(selections_list, whichAxis = \"Z\", angleStr = \"90deg\", numClones = \"2\"):\n\
    selections = \',\'.join(selections_list)\n\
    oEditor.DuplicateAroundAxis(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ],\n\
    [\n\
        \"NAME:DuplicateAroundAxisParameters\",\n\
        \"CreateNewObjects:=\"	, True,\n\
        \"WhichAxis:=\"		, whichAxis,\n\
        \"AngleStr:=\"		, angleStr,\n\
        \"NumClones:=\"		, numClones\n\
    ],\n\
    [\n\
        \"NAME:Options\",\n\
        \"DuplicateAssignments:=\", False\n\
    ],\n\
    [\n\
        \"CreateGroupsForNewObjects:=\", False\n\
    ])\n");
    } else if (index == 19) { //镜像复制
        return QString("def my_duplicateMirror(selections_list, baseX = \"0.6mm\", baseY = \"-0.8mm\", baseZ = \"0mm\", normalX = \"-0.8mm\", normalY = \"-0.5mm\", normalZ = \"0mm\"):\n\
    selections = \',\'.join(selections_list)\n\
    oEditor.DuplicateMirror(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ], \n\
    [\n\
        \"NAME:DuplicateToMirrorParameters\",\n\
        \"DuplicateMirrorBaseX:=\", baseX,\n\
        \"DuplicateMirrorBaseY:=\", baseY,\n\
        \"DuplicateMirrorBaseZ:=\", baseZ,\n\
        \"DuplicateMirrorNormalX:=\", normalX,\n\
        \"DuplicateMirrorNormalY:=\", normalY,\n\
        \"DuplicateMirrorNormalZ:=\", normalZ\n\
    ], \n\
    [\n\
        \"NAME:Options\",\n\
        \"DuplicateAssignments:=\", False\n\
    ], \n\
    [\n\
        \"CreateGroupsForNewObjects:=\", False\n\
    ])\n");
    } else if (index == 20) { //合并
        return QString("def my_unite(selections_list):\n\
    selections = \',\'.join(selections_list)\n\
    oEditor.Unite(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections\n\
    ], \n\
    [\n\
        \"NAME:UniteParameters\",\n\
        \"KeepOriginals:=\"	, False\n\
    ])\n");
    } else if (index == 21) { //减去
        return QString("def my_subtract(blankParst_list, toolParts_list):\n\
    strBlank = \',\'.join(blankParst_list)\n\
    strTool = ','.join(toolParts_list)\n\
    oEditor.Subtract(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Blank Parts:=\"		, strBlank,\n\
        \"Tool Parts:=\"		, strTool\n\
    ], \n\
    [\n\
        \"NAME:SubtractParameters\",\n\
        \"KeepOriginals:=\"	, False\n\
    ])\n");
    } else if (index == 22) { //相交
        return QString("def my_intersect(selections_list):\n\
    selections = \',\'.join(selections_list)\n\
    oEditor.Intersect(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections\n\
    ],\n\
    [\n\
        \"NAME:IntersectParameters\",\n\
        \"KeepOriginals:=\"	, False\n\
    ])\n");
    } else if (index == 23) { //分裂
        return QString("def my_split(selections_list, splitPlane = \"XY\"):\n\
    selections = \',\'.join(selections_list)\n\
    oEditor.Split(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ], \n\
    [\n\
        \"NAME:SplitToParameters\",\n\
        \"SplitPlane:=\"		, splitPlane,\n\
        \"WhichSide:=\"		, \"PositiveOnly\",\n\
        \"ToolType:=\"		, \"PlaneTool\",\n\
        \"ToolEntityID:=\"	, -1,\n\
        \"SplitCrossingObjectsOnly:=\", False,\n\
        \"DeleteInvalidObjects:=\", True\n\
    ])\n");
    } else if (index == 24) { //标记
        return QString("def my_imprint(blankParts_list, toolParts_list):\n\
    strBlank = \',\'.join(blankParts_list)\n\
    strTool = \',\'.join(toolParts_list)\n\
    oEditor.Imprint(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Blank Parts:=\"		, strBlank,\n\
        \"Tool Parts:=\"		, strTool\n\
    ],\n\
    [\n\
        \"NAME:ImprintParameters\",\n\
        \"KeepOriginals:=\"	, False\n\
    ])\n");
    } else if (index == 25) { //沿向量扫
        return QString("def my_sweepAlongVector(profile_list, draftAngle = \"0deg\", draftType = \"Round\", vectorX = \"1mm\", vectorY = \"1mm\", vectorZ = \"1mm\"):\n\
    selections = \',\'.join(profile_list)\n\
    oEditor.SweepAlongVector(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ], \n\
    [\n\
        \"NAME:VectorSweepParameters\",\n\
        \"DraftAngle:=\"		, draftAngle,\n\
        \"DraftType:=\"		, draftType,\n\
        \"CheckFaceFaceIntersection:=\", False,\n\
        \"SweepVectorX:=\"	, vectorX,\n\
        \"SweepVectorY:=\"	, vectory,\n\
        \"SweepVectorZ:=\"	, vectorz\n\
    ])\n");
    } else if (index == 26) { //沿轴扫
        return QString("def my_sweepAroundAxis(profile_list, draftAngle = \"0deg\", draftType = \"Round\", sweepAxis = \"X\", sweepAngle = \"360deg\", numOfSegments = \"0\"):\n\
    selections = \',\'.join(profile_list)\n\
    oEditor.SweepAroundAxis(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ],\n\
    [\n\
        \"NAME:AxisSweepParameters\",\n\
        \"DraftAngle:=\"		, draftAngle,\n\
        \"DraftType:=\"		, draftType,\n\
        \"CheckFaceFaceIntersection:=\", False,\n\
        \"SweepAxis:=\"		, sweepAxis,\n\
        \"SweepAngle:=\"		, sweepAngle,\n\
        \"NumOfSegments:=\"	, numOfSegments\n\
    ])\n");
    } else if (index == 27) { //沿路径扫
        return QString("def my_sweepAlongPath(profile_list, path_list, draftAngle = \"0deg\", draftType = \"Round\", twistAngle = \"90deg\"):\n\
    profile = \',\'.join(profile_list)\n\
    path = \',\'.join(path_list)\n\
    selections = profile + \',\' + path\n\
    oEditor.SweepAlongPath(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ],\n\
    [\n\
        \"NAME:PathSweepParameters\",\n\
        \"DraftAngle:=\"		, draftAngle,\n\
        \"DraftType:=\"		, draftType,\n\
        \"CheckFaceFaceIntersection:=\", False,\n\
        \"TwistAngle:=\"		, twistAngle\n\
    ])\n");
    } else if (index == 28) { //圆角处理
        return QString("def my_fillet(selections, verticesList, radius = \"1mm\", setback = \"0mm\"):\n\
    oEditor.Fillet(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ],\n\
    [\n\
        \"NAME:Parameters\",\n\
        [\n\
            \"NAME:FilletParameters\",\n\
            \"Edges:=\"		, [],\n\
            \"Vertices:=\"		, verticesList,\n\
            \"Radius:=\"		, radius,\n\
            \"Setback:=\"		, setback\n\
        ]\n\
    ])\n");
    } else if (index == 29) { //去直角边
        return QString("def my_chamfer(selections, verticesList, leftDistance = \"1mm\", rightDistance = \"1mm\", chamferType = \"Symmetric\"):\n\
    oEditor.Chamfer(\n\
    [\n\
        \"NAME:Selections\",\n\
        \"Selections:=\"		, selections,\n\
        \"NewPartsModelFlag:=\"	, \"Model\"\n\
    ],\n\
    [\n\
        \"NAME:Parameters\",\n\
        [\n\
            \"NAME:ChamferParameters\",\n\
            \"Edges:=\"		, [],\n\
            \"Vertices:=\"		, verticesList,\n\
            \"LeftDistance:=\"	, leftDistance,\n\
            \"RightDistance:=\"	, rightDistance,\n\
            \"ChamferType:=\"		, chamferType\n\
        ]\n\
    ])\n");
    } else {
        return QString("fuck you!");
    }
}
