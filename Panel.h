/*
 * 添加悔棋按钮
 */

#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QPushButton>

class Panel : public QWidget
{
	Q_OBJECT
public:
	explicit Panel(QWidget *parent = 0);

	QPushButton* _back;

	~Panel();

signals:
	void sigBack();

	public slots:
};

#endif // PANEL_H
