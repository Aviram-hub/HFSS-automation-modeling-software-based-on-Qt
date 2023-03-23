#ifndef ACTION_LABEL_H
#define ACTION_LABEL_H

#include <QWidget>

namespace Ui {
class Action_Label;
}

class Action_Label : public QWidget
{
    Q_OBJECT

public:
    explicit Action_Label(QWidget *parent = 0, QString text = "", int index = 0);
    ~Action_Label();

    QString text_;
private:
    Ui::Action_Label *ui;
};

#endif // ACTION_LABEL_H
