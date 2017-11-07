#include "GameApp.h"
#include "d3ddevice.h"
#include "camera.h"
#include "Input.h"
#include "terrain.h"
#include "mesh.h"
#include "MagicBox.h"
#include "Map.h"
#include "BillBoard.h"
#include "ParticleSystem.h"
#include "Line.h"
#include "Sprite.h"
#include "Text.h"
#include <string>
#include "MyButton.h"

CGameApp::CGameApp()
{
	mRoot = new CNode;
}

CGameApp::~CGameApp()
{
}

void CGameApp::onClicked()
{
	OutputDebugString("按钮被点击\n");
}

bool CGameApp::init()
{
	if (FAILED(CD3DDevice::getInstance().init()))
		return false;
	CInput::getInstance().init();

	m_pDevice = CD3DDevice::getInstance().getDevice();
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//逆时针裁剪

	m_pDevice->SetRenderState(D3DRS_ZENABLE, true);
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	CTextureCache::getInstance().createTexture("texture\\texture3.bmp");
	CTextureCache::getInstance().createTexture("texture\\milaoshu.png");

	mSkyBox = CSkyBox::create();
	//环境光
	//m_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(128,128,128));

	CNode* node = new CNode();
	mRoot->addChild(node, "Root3d");
	node = new CNode();
	node->setAnchorPos(D3DXVECTOR3(0.5f,0.5f,0));
	mRoot->addChild(node, "Root2d");

	CTerrain* map = CTerrain::create();
	map->setPosition(D3DXVECTOR3(0, 0, 0));
	getRoot3d()->addChild(map, "map");

	//line
	CLine * line = CLine::create();
	getRoot3d()->addChild(line, "line");

	//茶壶
	CMesh* mesh = CMesh::create();
	mesh->setVisible(true);
	mesh->setRotate(D3DXVECTOR3(D3DX_PI/2,0,0));
	mesh->setScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	getRoot3d()->addChild(mesh, "tea");

	////魔方
	//CMagicBox* box = CMagicBox::create();
	//box->setPosition(D3DXVECTOR3(0,3,0));
	//box->setScale(D3DXVECTOR3(0.1f,0.1f,0.1f));
	//getRoot3d()->addChild(box, "bangzi");

	//mesh = CMesh::create();
	//mesh->setRotate(D3DXVECTOR3(D3DX_PI / 2, 0, 0));
	//mesh->setScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	//getRoot3d()->addChild(mesh, "bangzi");

	//CMap* text1 = CMap::create("texture\\texture2.jpg");
	//text1->setPosition(D3DXVECTOR3(0, 5, 0));
	//getRoot3d()->addChild(text1, "text1");

	//CMyEdit

	CMyButton* btn = CMyButton::create(
		"ui\\normal.png",
		"ui\\suspend.png",
		"ui\\clickit.png",
		"ui\\disable.png", 
		std::bind(&CGameApp::onClicked, this));

	btn->setPosition(D3DXVECTOR3(300,300,0.01f));
	btn->setEnable(false);
	getRoot2d()->addChild(btn, "button");

	//std::string s = CMyEdit->getString();

	//CParticleSystem* pParticle = new CParticleSystem();
	//pParticle->setPosition(D3DXVECTOR3(0,20,0));
	//getRoot3d()->addChild(pParticle, "烟花");

	//for (int i = 0; i < 100;i++) {
	//	int r = rand() % 13;
	//	CBillBoard* bill = CBillBoard::create("texture\\tree0.png");
	//	bill->setPosition(D3DXVECTOR3((rand()%100-50)*0.5f,0,(rand()%100-50))*0.5f);

	//	char str[255];
	//	sprintf(str, "bill%d", i);
	//	getRoot3d()->addChild(bill, str);
	//}

	//CSprite* spr = CSprite::create("ui\\normal.png");
	//spr->setPosition(D3DXVECTOR3(300, 300, 0.01f));
	//spr->setScale(D3DXVECTOR3(2, 2, 1.0f));
	//getRoot2d()->addChild(spr, "test");

	//CSprite* spr1 = CSprite::create("texture\\texture.png");
	//spr1->setPosition(D3DXVECTOR3(100, 100, 0.001f));
	//spr1->setAnchorPos(D3DXVECTOR3(0.5f,0.5f,0));
	//spr1->setScale(D3DXVECTOR3(0.5f, 0.5f, 1.0f));
	//getRoot2d()->addChild(spr1, "test.child");

	//CText *t = CText::create("测试！！");
	//t->setColor(D3DCOLOR_ARGB(255,255,0,0));
	//t->setPosition(D3DXVECTOR3(30, -20, -0.01f));
	//spr1->addChild(t, "text");

	return true;
}

void CGameApp::update(float dt)
{
	CInput::getInstance().update();
	getRoot2d()->update(dt);

	CNode* pBox = getRoot3d()->getChildByName("tea");
	if (pBox) {
		D3DXVECTOR3 v = pBox->getPosition();
		v.y += 0.3f;
		CCamera::getInstance().setLookAt(v);
	}

	CCamera::getInstance().update();

	mSkyBox->update(dt);
	getRoot3d()->update(dt);

	//if (CInput::getInstance().keyHold(DIK_W)) {
	//	CNode* p = getRoot2d()->getChildByName("test");
	//	auto pos = p->getPosition();
	//	pos.y -= 1.0f;
	//	p->setPosition(pos);
	//}

	//if (CInput::getInstance().keyHold(DIK_S)) {
	//	CNode* p = getRoot2d()->getChildByName("test");
	//	auto pos = p->getPosition();
	//	pos.y += 1.0f;
	//	p->setPosition(pos);
	//}

	if (CInput::getInstance().keyHold(DIK_SPACE)) {
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else {
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	if (CInput::getInstance().keyDown(DIK_F1)) {
		m_pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	}
	if (CInput::getInstance().keyDown(DIK_F2)) {
		m_pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	}

	if (CInput::getInstance().keyDown(DIK_H)) {
		CNode* p = getRoot2d()->getChildByName("test");
		if(p)
			p->removeFromParent();
	}
}

void CGameApp::render()
{
	//后台颜色缓冲区 清空
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
	//m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	CCamera::getInstance().render();

	mSkyBox->render();
	getRoot3d()->render();

	//m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	m_pDevice->BeginScene();
	auto pSprite = CD3DDevice::getInstance().getSprite();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	getRoot2d()->render();

	pSprite->End();
	m_pDevice->EndScene();

	m_pDevice->Present(NULL, NULL, NULL, NULL);//翻转 后台缓冲区数据拷贝到前台颜色缓冲区 显示出来
}

void CGameApp::release()
{
	mRoot->removeFromParent();
	delete mSkyBox;
	mSkyBox = NULL;
}
