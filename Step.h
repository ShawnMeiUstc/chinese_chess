/*
 * 走棋步类，
 * 主要记录相关id和行列信息
 */

#ifndef STEP_H
#define STEP_H

#include <QObject>

class Step : public QObject
{
	Q_OBJECT
public:
	explicit Step(QObject *parent = 0);
	~Step();

	int _moveid;
	int _killid;
	int _rowFrom;
	int _colFrom;
	int _rowTo;
	int _colTo;

signals:

	public slots :
};

#endif // STEP_H

