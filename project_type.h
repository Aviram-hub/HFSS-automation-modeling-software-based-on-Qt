#ifndef PROJECT_TYPE_H
#define PROJECT_TYPE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class project_type;
}

class project_type : public QDialog
{
    Q_OBJECT

public:
    explicit project_type(QWidget *parent = 0, MainWindow* mainWindow = 0);
    ~project_type();

    MainWindow* mainWindow_;
protected:
    void closeEvent(QCloseEvent *event) override;

    bool should_call = true;
signals:
    void play_projectName();
private:
    Ui::project_type *ui;
};

#endif // PROJECT_TYPE_H
