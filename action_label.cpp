#include "action_label.h"
#include "ui_action_label.h"

Action_Label::Action_Label(QWidget *parent, QString text, int index) :
    QWidget(parent),
    ui(new Ui::Action_Label)
{
    ui->setupUi(this);
    if (index == 0) {
        text_ = "长方体: ";
    } else if (index == 1) {
        text_ = "圆柱体: ";
    } else if (index == 2) {
        text_ = "棱柱体: ";
    } else if (index == 3) {
        text_ = "圆锥体: ";
    } else if (index == 4) {
        text_ = "球体: ";
    } else if (index == 5) {
        text_ = "圆环体: ";
    } else if (index == 6) {
        text_ = "接合线: ";
    } else if (index == 7) {
        text_ = "长方形: ";
    } else if (index == 8) {
        text_ = "圆形: ";
    } else if (index == 9) {
        text_ = "多边形: ";
    } else if (index == 10) {
        text_ = "椭圆: ";
    } else if (index == 11) {
        text_ = "区域: ";
    } else if (index == 12) {
        text_ = "点: ";
    } else if (index == 13) {
        text_ = "截面: ";
    } else if (index == 14) {
        text_ = "移动: ";
    } else if (index == 15) {
        text_ = "旋转: ";
    } else if (index == 16) {
        text_ = "镜像: ";
    } else if (index == 17) {
        text_ = "沿线复制: ";
    } else if (index == 18) {
        text_ = "沿轴复制: ";
    } else if (index == 19) {
        text_ = "镜像复制: ";
    } else if (index == 20) {
        text_ = "合并: ";
    } else if (index == 21) {
        text_ = "减去: ";
    } else if (index == 22) {
        text_ = "相交: ";
    } else if (index == 23) {
        text_ = "分裂: ";
    } else if (index == 24) {
        text_ = "标记: ";
    } else if (index == 25) {
        text_ = "沿向量扫: ";
    } else if (index == 26) {
        text_ = "沿轴扫: ";
    } else if (index == 27) {
        text_ = "沿路径扫: ";
    } else if (index == 28) {
        text_ = "圆角处理: ";
    } else if (index == 29) {
        text_ = "去直角边: ";
    }
    this->text_ += text;
    ui->toolButton->setText(text_);
}

Action_Label::~Action_Label()
{
    delete ui;
}


