#include "MainWindow.h"
#include <QHBoxLayout>
#include "SingleGame.h"
#include "MultiGame.h"


MainWindow::MainWindow(int gameType, QWidget *parent) : QWidget(parent)
{
    _gameType = gameType;

    if(_gameType == 0)
    {
        SingleGame* game = new SingleGame;
        Panel* panel = new Panel;
        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
    }
    else if(_gameType == 1)
    {
        MultiGame* game = new MultiGame;
        Panel* panel = new Panel;
        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
    }
}

MainWindow::~MainWindow()
{

}

