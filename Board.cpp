#include "Board.h"
#include <QPainter>
#include <QMouseEvent>



Board::Board(QWidget *parent, bool side) : QFrame(parent)
{
	this->_r = 20;
	setMinimumSize(_r * 19 + 1, _r * 21 + 1);
	initStone(side);
}
//初始化
void Board::initStone(bool side)
{
	_redBottom = side;
	for (int i = 0; i != 32; ++i)
	{
		_stone[i].init(i, _redBottom);
	}
	_selectId = -1;
	_bRedTurn = true;
	update();
}
//绘制
void Board::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	drawplate(painter);
	//四个炮处的棋盘处理
	drawpattern(painter, 2, 3);
	drawpattern(painter, 8, 3);
	drawpattern(painter, 2, 8);
	drawpattern(painter, 8, 8);

	//画32颗棋子
	for (int i = 0; i != 32; ++i)
	{
		drawstone(painter, i);
	}
}

QPoint Board::center(int row, int col)
{
	QPoint ret;
	ret.rx() = (col + 1) * _r * 2;
	ret.ry() = (row + 1) * _r * 2;
	return ret;
}
QPoint Board::center(int id)
{
	return center(_stone[id]._row, _stone[id]._col);

}

void Board::drawplate(QPainter &painter)
{
	//画10条横线
	for (int i = 1; i != 11; ++i)
	{
		painter.drawLine(QPoint(2 * _r, i * 2 * _r), QPoint(9 * 2 * _r, i * 2 * _r));
	}

	//画9条竖线，只有第一条、第九条贯穿
	for (int i = 1; i != 10; ++i)
	{
		if (i == 1 || i == 9)
			painter.drawLine(QPoint(i * 2 * _r, 2 * _r), QPoint(i * 2 * _r, 10 * 2 * _r));
		else
		{
			painter.drawLine(QPoint(i * 2 * _r, 2 * _r), QPoint(i * 2 * _r, 5 * 2 * _r));
			painter.drawLine(QPoint(i * 2 * _r, 6 * 2 * _r), QPoint(i * 2 * _r, 10 * 2 * _r));

		}
	}


	//画九宫格
	painter.drawLine(QPoint(4 * 2 * _r, 2 * _r), QPoint(6 * 2 * _r, 3 * 2 * _r));
	painter.drawLine(QPoint(6 * 2 * _r, 2 * _r), QPoint(4 * 2 * _r, 3 * 2 * _r));
	painter.drawLine(QPoint(4 * 2 * _r, 8 * 2 * _r), QPoint(6 * 2 * _r, 10 * 2 * _r));
	painter.drawLine(QPoint(6 * 2 * _r, 8 * 2 * _r), QPoint(4 * 2 * _r, 10 * 2 * _r));

	//画楚河、汉界
	painter.setPen(Qt::black);
	painter.setFont(QFont("隶书", _r, 700));
	QRect rect1 = QRect(4 * _r, 10 * _r, _r * 2, _r * 2);
	QRect rect2 = QRect(6 * _r, 10 * _r, _r * 2, _r * 2);
	QRect rect3 = QRect(12 * _r, 10 * _r, _r * 2, _r * 2);
	QRect rect4 = QRect(14 * _r, 10 * _r, _r * 2, _r * 2);
	painter.drawText(rect1, "楚", QTextOption(Qt::AlignCenter));
	painter.drawText(rect2, "河", QTextOption(Qt::AlignCenter));
	painter.drawText(rect3, "汉", QTextOption(Qt::AlignCenter));
	painter.drawText(rect4, "界", QTextOption(Qt::AlignCenter));
}

void Board::drawpattern(QPainter& painter, int row, int col)
{
	const int offset = 0.1 * 2 * _r;
	painter.drawLine(QPoint(row * 2 * _r - offset, col * 2 * _r - offset), QPoint(row * 2 * _r - 5 * offset, col * 2 * _r - offset));
	painter.drawLine(QPoint(row * 2 * _r - offset, col * 2 * _r - offset), QPoint(row * 2 * _r - offset, col * 2 * _r - 5 * offset));
	painter.drawLine(QPoint(row * 2 * _r - offset, col * 2 * _r + offset), QPoint(row * 2 * _r - 5 * offset, col * 2 * _r + offset));
	painter.drawLine(QPoint(row * 2 * _r - offset, col * 2 * _r + offset), QPoint(row * 2 * _r - offset, col * 2 * _r + 5 * offset));
	painter.drawLine(QPoint(row * 2 * _r + offset, col * 2 * _r - offset), QPoint(row * 2 * _r + 5 * offset, col * 2 * _r - offset));
	painter.drawLine(QPoint(row * 2 * _r + offset, col * 2 * _r - offset), QPoint(row * 2 * _r + offset, col * 2 * _r - 5 * offset));
	painter.drawLine(QPoint(row * 2 * _r + offset, col * 2 * _r + offset), QPoint(row * 2 * _r + 5 * offset, col * 2 * _r + offset));
	painter.drawLine(QPoint(row * 2 * _r + offset, col * 2 * _r + offset), QPoint(row * 2 * _r + offset, col * 2 * _r + 5 * offset));
}

void Board::drawstone(QPainter& painter, int id)
{
	if (_stone[id]._dead)                  //死掉的棋子不显示
		return;


	painter.setPen(Qt::black);
	painter.setFont(QFont("隶书", _r, 700));

	painter.setBrush(QBrush(Qt::lightGray));
	if (id == _selectId)                     //选中棋子变色（黄色）
		painter.setBrush(QBrush(Qt::yellow));

	QPoint c = center(id);
	QRect rect = QRect(c.x() - _r, c.y() - _r, _r * 2, _r * 2);

	painter.drawEllipse(center(id), _r, _r);

	if (_stone[id]._red)                     //红色棋子换红笔
		painter.setPen(Qt::red);

	painter.drawText(rect, _stone[id].getText(), QTextOption(Qt::AlignCenter));

}

//走棋
bool Board::getRowCol(QPoint pt, int& row, int& col)
{
	for (row = 0; row <= 9; ++row)
		for (col = 0; col <= 8; ++col)
		{
			QPoint c = center(row, col);
			if ((pt.x() + _r) / c.x() == 1 && (pt.y() + _r) / c.y() == 1
				&& (pt.x() + _r) % c.x() < 2 * _r && (pt.y() + _r) % c.y() < 2 * _r)
				return true;
		}
	return false;
}

bool Board::sameColor(int id1, int id2)
{
	if (id1 == -1 || id2 == -1)
		return false;
	return _stone[id1]._red == _stone[id2]._red;
}

int Board::getStoneId(int row, int col)
{
	for (int i = 0; i != 32; ++i)
	{
		if (_stone[i]._row == row && _stone[i]._col == col && !_stone[i]._dead)
			return i;
	}
	return -1;
}

void Board::killStone(int id)
{
	if (id == -1)
		return;
	_stone[id]._dead = true;
}

void Board::reliveStone(int id)
{
	if (id == -1)
		return;
	_stone[id]._dead = false;
}

void Board::moveStone(int moveid, int row, int col)
{
	_stone[moveid]._row = row;
	_stone[moveid]._col = col;
	_bRedTurn = !_bRedTurn;
}


bool Board::canSelect(int id)
{
	if (id == -1)
		return false;
	else
		return _bRedTurn == _stone[id]._red;
}

void Board::moveStone(int moveid, int killid, int row, int col)
{
	saveStep(moveid, killid, row, col, _steps);
	killStone(killid);
	moveStone(moveid, row, col);
}

void Board::trySelectStone(int id)
{
	if (id == -1) return;
	if (!canSelect(id)) return;
	_selectId = id;
	update();
}

void Board::tryMoveStone(int killid, int row, int col)
{
	if (killid != -1 && sameColor(killid, _selectId))//同色重选
	{
		trySelectStone(killid);
		return;
	}

	bool ret = canMove(_selectId, killid, row, col);
	if (ret)
	{
		moveStone(_selectId, killid, row, col);
		_selectId = -1;
		update();
	}
}

void Board::click(int id, int row, int col)
{
	if (this->_selectId == -1)
	{
		trySelectStone(id);
	}
	else
	{
		tryMoveStone(id, row, col);
	}
}

void Board::click(QPoint pt)
{
	int row = 0, col = 0;
	bool bClicked = getRowCol(pt, row, col);
	if (!bClicked) return;

	int id = getStoneId(row, col);
	click(id, row, col);
}

int Board::relation_d(int moveid, int row, int col)
{
	int dr = _stone[moveid]._row - row;
	int dc = _stone[moveid]._col - col;
	int d = qAbs<int>(dr) * 10 + qAbs<int>(dc);
	return d;
}

int Board::getChessAcountAtLine(int row, int col, int row1, int col1)
{
	int ret = 0;
	if (row != row1 && col != col1)
		return -1;
	if (row == row1 && col == col1)
		return -1;
	if (row == row1)
	{
		int min = (col < col1) ? col : col1;
		int max = (col < col1) ? col1 : col;
		for (int i = min + 1; i < max; ++i)
		{
			if (getStoneId(row, i) != -1)
				++ret;
		}
	}
	else
	{
		int min = (row < row1) ? row : row1;
		int max = (row < row1) ? row1 : row;
		for (int i = min + 1; i < max; ++i)
		{
			if (getStoneId(i, col) != -1)
				++ret;
		}
	}
	return ret;
}

void Board::saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps)
{
	int row1 = _stone[moveid]._row;
	int col1 = _stone[moveid]._col;
	Step* step = new Step;
	step->_colFrom = col1;
	step->_colTo = col;
	step->_rowFrom = row1;
	step->_rowTo = row;
	step->_moveid = moveid;
	step->_killid = killid;

	steps.append(step);
}

void Board::back(Step *step)
{
	reliveStone(step->_killid);
	moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}

void Board::backOne()
{
	if (this->_steps.size() == 0) return;

	Step* step = this->_steps.last();
	_steps.removeLast();
	back(step);

	update();
	delete step;
}

void Board::back()
{
	backOne();
}



bool Board::canMoveJIANG(int moveid, int, int row, int col)
{
	//目标移动范围在九宫格内
	//移动方向只能是竖直或水平方向
	//移动距离一格
	//特例：将、帅相对，中间无子，可直接飞杀

	if (getChessAcountAtLine(_stone[4]._row, _stone[4]._col, _stone[27]._row, _stone[27]._col) == 0)
	{
		if (moveid == 4 && _stone[27]._row == row &&  _stone[27]._col == col)
			return true;
		if (moveid == 27 && _stone[4]._row == row &&  _stone[4]._col == col)
			return true;
	}
	else
	{
		if (moveid < 16)
		{
			if (row > 2) return false;
		}
		else
		{
			if (row < 7) return false;
		}
		if (col < 3) return false;
		if (col > 5) return false;

		int d = relation_d(moveid, row, col);
		if (d == 1 || d == 10)
			return true;
	}
	return false;
}

bool Board::canMoveSHI(int moveid, int, int row, int col)
{

	//与将类似，走斜线改变d值
	if (moveid < 16)
	{
		if (row > 2) return false;
	}
	else
	{
		if (row < 7) return false;
	}
	if (col < 3) return false;
	if (col > 5) return false;

	int d = relation_d(moveid, row, col);
	if (d == 11)
		return true;


	return false;
}

bool Board::canMoveXIANG(int moveid, int, int row, int col)
{
	if (moveid > 15)  //不能飞过河
	{
		if (row <= 4) return false;
	}
	else
	{
		if (row >= 5) return false;
	}

	if (_stone[moveid]._col % 2) //不能走奇数列
		return false;

	int d = relation_d(moveid, row, col);
	if (d != 22) return false;

	int rEye = (row + _stone[moveid]._row) / 2;
	int cEye = (col + _stone[moveid]._col) / 2;
	if (getStoneId(rEye, cEye) != -1)
		return false;
	return true;
}

bool Board::canMoveJU(int moveid, int, int row, int col)
{
	if (getChessAcountAtLine(_stone[moveid]._row, _stone[moveid]._col, row, col) == 0)
		return true;
	return false;
}

bool Board::canMoveMA(int moveid, int, int row, int col)
{
	int d = relation_d(moveid, row, col);
	//纵向马腿
	int zongLeg_r = (_stone[moveid]._row + row) / 2;
	int zongLeg_c = _stone[moveid]._col;
	//横向马腿
	int hengLeg_r = _stone[moveid]._row;
	int hengLeg_c = (_stone[moveid]._col + col) / 2;

	if (d != 21 && d != 12)
	{
		return false;
	}
	else if (d == 12 && getStoneId(hengLeg_r, hengLeg_c) != -1)
	{
		return false;
	}
	else if (d == 21 && getStoneId(zongLeg_r, zongLeg_c) != -1)
	{
		return false;
	}
	return true;


}

bool Board::canMovePAO(int moveid, int killid, int row, int col)
{
	int ret = getChessAcountAtLine(_stone[moveid]._row, _stone[moveid]._col, row, col);
	if (killid != -1)
	{
		if (ret == 1)
			return true;
	}
	else
	{
		if (ret == 0)
			return true;
	}
	return false;
}

bool Board::canMoveBING(int moveid, int, int row, int col)
{
	int d = relation_d(moveid, row, col);
	if (d != 1 && d != 10)
		return false;

	if (moveid > 15)
	{
		if (_stone[moveid]._row < row)
			return false;
		if (_stone[moveid]._row >= 5 && _stone[moveid]._row == row)
			return false;
	}
	else
	{
		if (_stone[moveid]._row > row)
			return false;
		if (_stone[moveid]._row <= 4 && _stone[moveid]._row == row)
			return false;
	}


	return true;
}

bool Board::canMove(int moveid, int killid, int row, int col)
{
	if (sameColor(moveid, killid)) return false;//同色不能吃
	switch (_stone[moveid]._type)
	{
	case Stone::JIANG:
	case Stone::SHUAI:
		return canMoveJIANG(moveid, killid, row, col);

	case Stone::B_SHI:
	case Stone::R_SHI:
		return canMoveSHI(moveid, killid, row, col);

	case Stone::B_XIANG:
	case Stone::R_XIANG:
		return canMoveXIANG(moveid, killid, row, col);

	case Stone::JU:
		return canMoveJU(moveid, killid, row, col);

	case Stone::MA:
		return canMoveMA(moveid, killid, row, col);

	case Stone::PAO:
		return canMovePAO(moveid, killid, row, col);

	case Stone::BING:
	case Stone::ZU:
		return canMoveBING(moveid, killid, row, col);

	}


	return false;
}

void Board::mouseReleaseEvent(QMouseEvent* ev)
{
	if (ev->button() != Qt::LeftButton) //不是左键点击，直接返回
	{
		return;
	}

	click(ev->pos());
}


Board::~Board()
{

}

//槽函数
void Board::slotBack()
{
	back();
}

void Board::computerMove()
{

}
