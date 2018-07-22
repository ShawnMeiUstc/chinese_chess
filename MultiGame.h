/*
 * 人人对战，
 * 棋盘布局随机
 */

#ifndef MULTIGAME_H
#define MULTIGAME_H

#include "Board.h"
#include <QtGlobal>
#include <QTime>

class MultiGame : public Board
{
	Q_OBJECT
public:
	explicit MultiGame(QWidget* parent = 0);
public:
	static bool _side()
	{
		return qrand() % 2; //随机数决定棋子红黑摆放位置
	}
	~MultiGame();
};

#endif // MULTIGAME_H
