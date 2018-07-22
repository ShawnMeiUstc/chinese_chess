/*
 * 棋盘类：包括棋盘、棋子的布局，
 * 走棋、吃棋的规则
 */

#ifndef BOARD_H
#define BOARD_H

#include <QFrame>
#include <QVector>
#include "Stone.h"
#include "Step.h"


class Board : public QFrame
{
	Q_OBJECT

public:
	explicit Board(QWidget *parent = 0, bool side = true);

	//游戏数据
	Stone _stone[32];//32颗棋子
	int _r;          //棋子的半径
	int _selectId;   //选中的棋子
	bool _bRedTurn;  //控制轮到谁走
	bool _redBottom; //控制初始化化时布局，默认红棋在下
	QVector<Step*> _steps; //储存走棋步数


	void initStone(bool);//初始化棋子属性

	//绘制：
	void paintEvent(QPaintEvent*); //重写paintEvent()函数，完成绘制工作
	//画棋盘辅助函数
	//棋子中心行列坐标转换为实际坐标
	QPoint center(int row, int col);
	QPoint center(int id);

	//绘制函数
	void drawplate(QPainter&);         //画棋盘轮廓
	void drawpattern(QPainter&, int, int); //绘制4个炮处图案
	void drawstone(QPainter&, int);    //画棋子


	//走棋规则辅助函数

	bool getRowCol(QPoint pt, int& row, int& col); //获取棋子行列信息（判断该处是否有棋子）
	bool sameColor(int id1, int id2); //棋子是否同色
	int getStoneId(int row, int col); //获取棋子id
	void killStone(int id);  //杀死棋子
	void reliveStone(int id); //复活棋子
	void moveStone(int moveid, int row, int col); //移动棋子


	bool canSelect(int id); //判断能不能选中棋子
	void moveStone(int moveid, int killid, int row, int col); //吃棋移动
	void trySelectStone(int id); //尝试选中棋子
	void tryMoveStone(int killid, int row, int col); //尝试吃棋移动
	virtual void click(int id, int row, int col); //吃掉点击处棋子
	void click(QPoint pt); //获取点击处棋子id
	int relation_d(int moveid, int row, int col);  //走棋规则核心参数
	int getChessAcountAtLine(int row, int col, int row1, int col1); //计算走棋路径上棋子数量

	void saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps);//保存走棋步数
	void back(Step* step); //撤销上一步棋的改变
	void backOne();//调整保存步数的向量，更新棋盘
	virtual void back();//调用backOne()


	//走棋规则
	bool canMoveJIANG(int moveid, int killid, int row, int col);
	bool canMoveSHI(int moveid, int killid, int row, int col);
	bool canMoveXIANG(int moveid, int killid, int row, int col);
	bool canMoveJU(int moveid, int killid, int row, int col);
	bool canMoveMA(int moveid, int killid, int row, int col);
	bool canMovePAO(int moveid, int killid, int row, int col);
	bool canMoveBING(int moveid, int killid, int row, int col);
	bool canMove(int moveid, int killid, int row, int col);

	void mouseReleaseEvent(QMouseEvent*); //重写mouseReleaseEvent()函数，完成走棋工作

	~Board();

signals:

	public slots :
		void slotBack();
	virtual void computerMove();
};

#endif // BOARD_H
