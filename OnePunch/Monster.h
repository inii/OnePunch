#pragma once
#include "Node.h"
//#include<stdlib.h>
#include<time.h>

class CMonster : public CNode
{
	
	//���Ｖ����ͨ����Ӣ��boss
	enum GRADE
	{
		Normal, Elite,boss
	};
		string mName;
	int mLv;
	int mGrade;
	int mHP;
	int mDefense;//������
	int mAttack;//������
	D3DXVECTOR3 mBornPos;//ˢ�µص�
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

