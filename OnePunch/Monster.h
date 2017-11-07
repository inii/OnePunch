#pragma once
#include "Node.h"
//#include<stdlib.h>
#include<time.h>

class CMonster : public CNode
{
	
	//怪物级别：普通，精英，boss
	enum GRADE
	{
		Normal, Elite,boss
	};
		string mName;
	int mLv;
	int mGrade;
	int mHP;
	int mDefense;//防御力
	int mAttack;//攻击力
	D3DXVECTOR3 mBornPos;//刷新地点
	CMonster();
public:
	static CMonster* create()
	{
		CMonster *cm = new CMonster();
		return cm;
		
	}
	void BornPos(float x, float y, float z);
	void attack();
	~CMonster();


};

