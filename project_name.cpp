#include "project_name.h"
#include "ui_project_name.h"

project_name::project_name(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::project_name)
{
    ui->setupUi(this);
}

project_name::~project_name()
{
    delete ui;
}
