#include "Monster.h"



CMonster::CMonster()
{
	srand(time(0));

}


CMonster::~CMonster()
{
}

void CMonster::BornPos(float x, float y, float z)
{

	x += rand() % 50;
	y += rand() % 50;
	mBornPos.x = x;
	mBornPos.y = y;
	mBornPos.z = z;
}
void CMonster::attack()
{

}