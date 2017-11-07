#pragma once
#include <d3d9.h>
#include <string>
#include "Node.h"
#include "TextureCache.h"

using namespace std;
class CSprite : public CNode
{
	CSprite(const string& path);
public:
	~CSprite();

	static CSprite* create(const string& path) {
		CSprite* p = new CSprite(path);
		return p;
	}

	virtual void update(float dt);
	virtual void render();

	CTexture* getTexture() { return mTexture; }

private:

	CTexture* mTexture;//Œ∆¿Ì÷∏’Î
};

