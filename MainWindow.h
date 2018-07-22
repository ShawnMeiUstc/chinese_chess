/*
 * 根据用户选择，
 * 生成不同模式游戏
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "Board.h"
#include "Panel.h"


class MainWindow : public QWidget
{
	Q_OBJECT
public:
	explicit MainWindow(int gameType, QWidget *parent = 0);

	int _gameType;

	~MainWindow();

signals:

	public slots :
};

#endif // MAINWINDOW_H
