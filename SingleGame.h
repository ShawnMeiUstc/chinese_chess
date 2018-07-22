/*
 * 人机对战，
 * 棋盘布局固定，
 * 红方在下
 */

#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "Board.h"


class SingleGame : public Board
{

public:
	explicit SingleGame(QWidget* parent = 0);
	int _level; //预估步数
	void back(); //预估之后回退，每次回退两步
	void click(int id, int row, int col);//重写父类的click()

	//最小值-最大值算法：下一步中，电脑可能走的方向有n个，走一个方向，人就有若干种应对方法
	//人所有的应对方法中必然是走让电脑局面分最小的那一种
	//所以n个分支就有n个最小局面分
	//电脑到底走哪一步，就要取决于这n个局面分中的最大者
	//这就是最小值中取最大值的算法

	//剪枝优化就是记录下之前已遍历分支中当前取得的最大值
	//当某一分支中出现了局面分低于当前这个最大值
	//就不再考虑这个分支中其他情况而是直接剪除它

	Step* getBestMove(); //找全局分最高的走棋步
	void getAllPossibleMove(QVector<Step*>& steps); //遍历所有可能步数
	//递归函数
	int getMinScore(int level, int curMin); //对黑方（电脑）
	int getMaxScore(int level, int curMax); //对红方（人）
	int score(); //局面分，黑房总分减去红方总分

	void fakeMove(Step* step);   // 循环内部移动一步以计算局面分
	void unfakeMove(Step* step); // 撤销fakemove

	~SingleGame();

	public slots:
	void computerMove();


};

#endif // SINGLEGAME_H
