#include "Text.h"
#include "D3DDevice.h"

CText::CText(const string& s)
	:mHeight(30)
	, mWidth(22)
{
	mString = s;

	m_vAnchorPos.z = 0.0f;

	LPDIRECT3DDEVICE9 pDev = CD3DDevice::getInstance().getDevice();
	if (FAILED(D3DXCreateFont(pDev, mHeight, mWidth, 400, 3, 0, GB2312_CHARSET, 0, 0, 0, "宋体", &mFont)))
	{
		MessageBox(NULL, "创建d3d字体对象失败", "警告", MB_OK);
		return;
	}
}

CText::~CText()
{
	if (mFont)
	{
		mFont->Release();
		mFont = NULL;
	}

}

void CText::update(float dt)
{
	CNode::update(dt);
}

void CText::render()
{
	//先渲染自己
	auto pSprite = CD3DDevice::getInstance().getSprite();
	pSprite->SetTransform(&m_mMatrix);

	int x = 0, y = 0;
	RECT rect = { x, y, x + mString.size()*mWidth, y + mHeight };
	mFont->DrawText(pSprite, mString.c_str(), -1, &rect, DT_TOP | DT_CENTER, m_color);

	CNode::render();
}
