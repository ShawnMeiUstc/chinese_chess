/*
 * 棋子类，
 * 包括棋子的属性
 * 和生成方式
 */

#ifndef STONE_H
#define STONE_H

#include <QPainter>
#include <QRect>


class Stone
{
public:
	Stone();

	enum TYPE {
		JIANG, SHUAI, B_SHI, R_SHI, B_XIANG,
		R_XIANG, JU, MA, PAO, BING, ZU
	};

	int _row;    //棋子行列
	int _col;
	int _id;     //棋子id
	bool _dead;  // 是否被杀？
	bool _red;   // 红黑
	TYPE _type;  // 棋子字符

	QString getText();      //获取字符
	void init(int id, bool redBottom);//初始化
	~Stone();
};

#endif // STONE_H
