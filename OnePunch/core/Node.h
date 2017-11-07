#pragma once
#include <string>
#include <map>
#include <d3dx9math.h>

using namespace std;
//�ڵ�
class CNode
{
	friend class CGameApp;
public:
	CNode();
	virtual ~CNode();

	bool addChild(CNode* pChild, const string& name);

	//�Ӹ��ڵ�ɾ��
	void removeFromParent();
	//ɾ���ӽڵ�
	bool removeChildByName(const string& name);
	//ɾ���Լ�
	void removeSelf();

	//����ê��
	void setAnchorPos(const D3DXVECTOR3& v) { m_vAnchorPos = v; }
	//��ȡê��
	D3DXVECTOR3 getAnchorPos() { return m_vAnchorPos; }

	D3DXCOLOR getColor() { return m_color; }
	void setColor(D3DXCOLOR c) { m_color = c; }

	//����λ��
	virtual void setPosition(const D3DXVECTOR3& v){m_vPos = v;}
	//��������
	void setScale(const D3DXVECTOR3& v) {m_vScale = v;}
	//������ת
	void setRotate(const D3DXVECTOR3& v){m_vRotate = v;}
	//��ȡλ��
	D3DXVECTOR3 getPosition() { return m_vPos; }
	//��ȡ����
	D3DXVECTOR3 getScale() { return m_vScale; }
	//��ȡ��ת
	D3DXVECTOR3 getRotate() { return m_vRotate; }
	//�õ����ڵ�
	CNode* getParent() { return mParent; }
	//�õ��ӽڵ�
	CNode* getChildByName(const string& name);
	//�õ���ǰ����
	D3DXMATRIX getMatrix() { return m_mMatrix; }
	
	void setVisible(bool b) { isVisible = b; }

	void setName(const string& name) { this->name = name; }

protected:
	virtual void update(float dt);
	virtual void render();

	bool isVisible; //�Ƿ���ʾ

	D3DXMATRIX m_mMatrix; //�任����

	D3DXVECTOR3 m_vPos;   //λ��
	D3DXVECTOR3 m_vScale; //����
	D3DXVECTOR3 m_vRotate;//��ת

	D3DCOLOR	m_color;//��ɫ
	D3DXVECTOR3 m_vAnchorPos;//ê��

	CNode* mParent;  // ���ڵ�
	map<string, CNode*> mChildren;//�ӽڵ�

	string name; //����
};

