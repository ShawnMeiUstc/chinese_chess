/*
 * 选择对话框，
 * 选择游戏模式
 */

#ifndef CHOICE_H
#define CHOICE_H

#include <QDialog>
#include <QPushButton>

class Choice : public QDialog
{
    Q_OBJECT
public:
    explicit Choice(QWidget *parent = 0);

    QPushButton* _buttons[2];
    int _selected;

    ~Choice();

public slots:
    void slotClicked();
};

#endif // CHOICE_H
