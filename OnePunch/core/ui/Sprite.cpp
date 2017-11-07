#include "Sprite.h"
#include "GameApp.h"
#include "D3DDevice.h"

CSprite::CSprite(const string& path)
{
	mTexture = CTextureCache::getInstance().createTexture(path);
	m_vAnchorPos.z = 0.0f;
}

CSprite::~CSprite()
{
}

void CSprite::update(float dt)
{
	CNode::update(dt);
}

void CSprite::render()
{
	//ÏÈäÖÈ¾×Ô¼º
	auto pSprite = CD3DDevice::getInstance().getSprite();
	pSprite->SetTransform(&m_mMatrix);

	int w = mTexture->getWidth();
	int h = mTexture->getHeight();

	D3DXVECTOR3 v = m_vAnchorPos;
	v.x = w*v.x;
	v.y = h*v.y;

	pSprite->Draw(mTexture->getD3dTex(), NULL, &v, NULL, m_color);

	CNode::render();
}
