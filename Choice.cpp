#include "Choice.h"
#include <QGridLayout>

Choice::Choice(QWidget *parent) : QDialog(parent)
{
	QGridLayout* lay = new QGridLayout(this);
	lay->addWidget(_buttons[0] = new QPushButton("人机对战"), 0, 0, 1, 1);
	lay->addWidget(_buttons[1] = new QPushButton("人人对战"), 1, 0, 1, 1);
	lay->setHorizontalSpacing(10);
	lay->setVerticalSpacing(10);
	lay->setContentsMargins(10, 10, 10, 10);

	for (int i = 0; i < 2; ++i)
	{
		connect(_buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
	}
}


Choice::~Choice()
{

}

void Choice::slotClicked()
{
	QObject* s = sender();
	for (int i = 0; i < 2; ++i)
	{
		if (_buttons[i] == s)
		{
			this->_selected = i;
			break;
		}
	}
	accept();
}
