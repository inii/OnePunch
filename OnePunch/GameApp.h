#pragma once
#include <windows.h>
#include <d3dx9math.h>
#include <d3d9.h>
#include "time.h"
#include "node.h"
#include "SkyBox.h"
#include "TextureCache.h"

class CGameApp
{
	CGameApp();
public:
	~CGameApp();

	static CGameApp& getInstance()
	{
		static CGameApp s;
		return s;
	}

	bool init();
	void update(float dt); //Âß¼­¸üÐÂ
	void render(); //äÖÈ¾
	void release();

	//CNode* getRoot() { return mRoot; }
	CNode* getRoot2d() { return mRoot->getChildByName("Root2d"); }
	CNode* getRoot3d() { return mRoot->getChildByName("Root3d"); }

	void onClicked();

private:
	LPDIRECT3DDEVICE9 m_pDevice;

	CSkyBox* mSkyBox;
	CNode*	 mRoot;
};

