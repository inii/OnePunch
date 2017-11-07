#include "MyButton.h"
#include "Input.h"
#include "MainWnd.h"
#include "D3DDevice.h"

using namespace std;
CMyButton::CMyButton()
{
	mState = state_normal;
	m_vAnchorPos.z = 0.0f;
	mEnable = true;
}

CMyButton::~CMyButton()
{
}

void CMyButton::init(const string& normal,
	const string& suspend,
	const string& clickin,
	const string& disable,
	const std::function<void()>& func)
{
	mNormal = CTextureCache::getInstance().createTexture(normal);
	mSuspend = CTextureCache::getInstance().createTexture(suspend);
	mClickin = CTextureCache::getInstance().createTexture(clickin);
	mDisable = CTextureCache::getInstance().createTexture(disable);

	mClickCallback = func;
	updateCollide();
}

void CMyButton::updateCollide()
{
	int w = mNormal->getWidth();
	int h = mNormal->getHeight();

	mCollide.left = m_vPos.x - (m_vAnchorPos.x*w);
	mCollide.right = m_vPos.x + ((1-m_vAnchorPos.x)*w);

	mCollide.top = m_vPos.y - (m_vAnchorPos.y*h);
	mCollide.bottom = m_vPos.y + ((1 - m_vAnchorPos.y)*h);
}

void CMyButton::update(float dt)
{
	CNode::update(dt);

	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CMainWnd::getInstance().getMainWnd();
	ScreenToClient(wnd, &pt);

	mState = state_normal;
	if (!mEnable)
	{
		mState = state_disable;
		return;
	}

	if (CCollide::isCollide(D3DXVECTOR2(pt.x, pt.y), mCollide)) {
		mState = state_suspend;

		CInput& input = CInput::getInstance();
		if (input.mouseHold(0)) {
			mState = state_clickin;
		}

		if (input.mouseUp(0)) {
			mClickCallback();
		}
	}
}

void CMyButton::render()
{
	auto pSprite = CD3DDevice::getInstance().getSprite();
	pSprite->SetTransform(&m_mMatrix);

	int w = mNormal->getWidth();
	int h = mNormal->getHeight();
	D3DXVECTOR3 v = m_vAnchorPos;
	v.x = w*v.x;
	v.y = h*v.y;

	switch (mState)
	{
	case CMyButton::state_normal:
		pSprite->Draw(mNormal->getD3dTex(), NULL, &v, NULL, m_color);
		break;
	case CMyButton::state_suspend:
		pSprite->Draw(mSuspend->getD3dTex(), NULL, &v, NULL, m_color);
		break;
	case CMyButton::state_clickin:
		pSprite->Draw(mClickin->getD3dTex(), NULL, &v, NULL, m_color);
		break;
	case CMyButton::state_disable:
		pSprite->Draw(mDisable->getD3dTex(), NULL, &v, NULL, m_color);
		break;
	default:
		break;
	}

	CNode::render();
}