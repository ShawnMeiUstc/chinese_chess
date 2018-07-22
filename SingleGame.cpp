#include "SingleGame.h"
#include <QTimer>


SingleGame::SingleGame(QWidget *parent) :Board(parent, true)
{
	_level = 4;
}


void SingleGame::back()
{
	if (_bRedTurn)
	{
		backOne();
		backOne();
	}
}

void SingleGame::click(int id, int row, int col)
{
	if (_bRedTurn)
	{
		Board::click(id, row, col);
		if (!_bRedTurn)
		{
			QTimer::singleShot(100, this, SLOT(computerMove()));
		}
	}
}


Step* SingleGame::getBestMove()
{
	Step* ret = NULL;
	QVector<Step*> steps;
	getAllPossibleMove(steps);
	int maxInAllMinScore = -100000;

	while (steps.count())
	{
		Step* step = steps.last();
		steps.removeLast();

		fakeMove(step);
		int minScore = getMinScore(this->_level - 1, maxInAllMinScore);
		unfakeMove(step);

		if (minScore > maxInAllMinScore)
		{
			if (ret) delete ret;
			ret = step;
			maxInAllMinScore = minScore;
		}
		else
		{
			delete step;
		}
	}
	return ret;
}

int SingleGame::score()
{
	// enum TYPE {JIANG, SHUAI, B_SHI,R_SHI, B_XIANG,R_XIANG, JU, MA, PAO, BING, ZU};
	static int s[] = { 15000,15000,241,241,251,251,1001,601,801,151,151 };
	int scoreBlack = 0;
	int scoreRed = 0;
	for (int i = 0; i != 16; ++i)
	{
		if (_stone[i]._dead) continue;
		scoreBlack += s[_stone[i]._type];
	}
	for (int i = 16; i != 32; ++i)
	{
		if (_stone[i]._dead) continue;
		scoreRed += s[_stone[i]._type];
	}
	return scoreBlack - scoreRed;
}

int SingleGame::getMinScore(int level, int curMin)
{
	if (level == 0)
		return score(); //递归基

	QVector<Step*> steps;
	getAllPossibleMove(steps);
	int minInAllMaxScore = 300000;

	while (steps.count())
	{
		Step* step = steps.last();
		steps.removeLast();

		fakeMove(step);
		int maxScore = getMaxScore(level - 1, minInAllMaxScore);
		unfakeMove(step);
		delete step;

		if (maxScore <= curMin)     //剪枝优化
		{
			while (steps.count())
			{
				Step* step = steps.last();
				steps.removeLast();
				delete step;
			}
			return maxScore;
		}

		if (maxScore < minInAllMaxScore)
		{
			minInAllMaxScore = maxScore;
		}


	}
	return minInAllMaxScore;
}

int SingleGame::getMaxScore(int level, int curMax)
{
	if (level == 0)
		return score(); //递归基

	QVector<Step*> steps;
	getAllPossibleMove(steps);
	int maxInAllMinScore = -100000;

	while (steps.count())
	{
		Step* step = steps.last();
		steps.removeLast();

		fakeMove(step);
		int minScore = getMinScore(level - 1, maxInAllMinScore);
		unfakeMove(step);
		delete step;

		if (minScore >= curMax)   //剪枝优化
		{
			while (steps.count())
			{
				Step* step = steps.last();
				steps.removeLast();
				delete step;
			}
			return minScore;
		}
		if (minScore > maxInAllMinScore)
		{
			maxInAllMinScore = minScore;
		}


	}
	return maxInAllMinScore;
}


void SingleGame::fakeMove(Step *step)
{
	killStone(step->_killid);
	moveStone(step->_moveid, step->_rowTo, step->_colTo);
}

void SingleGame::unfakeMove(Step *step)
{
	reliveStone(step->_killid);
	moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}

void SingleGame::getAllPossibleMove(QVector<Step *> &steps)
{
	int min, max;
	if (this->_bRedTurn)
	{
		min = 16, max = 32;
	}
	else
	{
		min = 0, max = 16;
	}

	for (int i = min; i < max; i++)
	{
		if (this->_stone[i]._dead) continue;
		for (int row = 0; row <= 9; ++row)
		{
			for (int col = 0; col <= 8; ++col)
			{
				int killid = this->getStoneId(row, col);
				if (sameColor(i, killid)) continue;

				if (canMove(i, killid, row, col))
				{
					saveStep(i, killid, row, col, steps);
				}
			}
		}
	}
}


SingleGame::~SingleGame()
{

}


void SingleGame::computerMove()
{
	Step* step = getBestMove();
	moveStone(step->_moveid, step->_killid, step->_rowTo, step->_colTo);
	delete step;
	update();
}
