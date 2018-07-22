#include "Stone.h"
Stone::Stone()
{

}

QString Stone::getText()
{
	{
		switch (this->_type)
		{
		case JIANG:
			return "將";
		case SHUAI:
			return "帥";
		case R_SHI:
			return "士";
		case R_XIANG:
			return "相";
		case B_SHI:
			return "仕";
		case B_XIANG:
			return "象";
		case JU:
			return "車";
		case MA:
			return "馬";
		case PAO:
			return "炮";
		case BING:
			return "兵";
		case ZU:
			return "卒";
		}
		return "error!";
	}
}

void Stone::init(int id, bool redBottom)
{

	struct position
	{
		int row, col;
		Stone::TYPE type;
	};

	position posRedBottom[32] =
	{

		{0,0,Stone::JU},     //id = 0
		{0,1,Stone::MA},
		{0,2,Stone::B_XIANG},
		{0,3,Stone::B_SHI},
		{0,4,Stone::JIANG},//id =4
		{0,5,Stone::B_SHI},
		{0,6,Stone::B_XIANG},
		{0,7,Stone::MA},
		{0,8,Stone::JU},
		{2,1,Stone::PAO},
		{2,7,Stone::PAO},
		{3,0,Stone::ZU},
		{3,2,Stone::ZU},
		{3,4,Stone::ZU},
		{3,6,Stone::ZU},
		{3,8,Stone::ZU},    //id = 15


		{6,0,Stone::BING},  //id = 16
		{6,2,Stone::BING},
		{6,4,Stone::BING},
		{6,6,Stone::BING},
		{6,8,Stone::BING},
		{7,1,Stone::PAO},
		{7,7,Stone::PAO},
		{9,0,Stone::JU},
		{9,1,Stone::MA},
		{9,2,Stone::R_XIANG},
		{9,3,Stone::R_SHI},
		{9,4,Stone::SHUAI}, // id = 27
		{9,5,Stone::R_SHI},
		{9,6,Stone::R_XIANG},
		{9,7,Stone::MA},
		{9,8,Stone::JU}      //id = 31
	};
	position posBlackBottom[32] =
	{

		{0,0,Stone::JU},     //id = 0
		{0,1,Stone::MA},
		{0,2,Stone::R_XIANG},
		{0,3,Stone::R_SHI},
		{0,4,Stone::SHUAI}, // id = 4
		{0,5,Stone::R_SHI},
		{0,6,Stone::R_XIANG},
		{0,7,Stone::MA},
		{0,8,Stone::JU},
		{2,1,Stone::PAO},
		{2,7,Stone::PAO},
		{3,0,Stone::BING},
		{3,2,Stone::BING},
		{3,4,Stone::BING},
		{3,6,Stone::BING},
		{3,8,Stone::BING},    //id = 15


		{6,0,Stone::ZU},  //id = 16
		{6,2,Stone::ZU},
		{6,4,Stone::ZU},
		{6,6,Stone::ZU},
		{6,8,Stone::ZU},
		{7,1,Stone::PAO},
		{7,7,Stone::PAO},
		{9,0,Stone::JU},
		{9,1,Stone::MA},
		{9,2,Stone::B_XIANG},
		{9,3,Stone::B_SHI},
		{9,4,Stone::JIANG}, // id = 27
		{9,5,Stone::B_SHI},
		{9,6,Stone::B_XIANG},
		{9,7,Stone::MA},
		{9,8,Stone::JU}      //id = 31
	};

	// 初始化
	if (redBottom)
	{
		_id = id;
		_dead = false;
		_red = (id >= 16);
		_row = posRedBottom[id].row;
		_col = posRedBottom[id].col;
		_type = posRedBottom[id].type;
	}
	else
	{

		_id = id;
		_dead = false;
		_red = (id <= 15);
		_row = posBlackBottom[id].row;
		_col = posBlackBottom[id].col;
		_type = posBlackBottom[id].type;
	}
}

Stone::~Stone()
{

}

