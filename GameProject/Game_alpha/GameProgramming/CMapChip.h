#ifndef CMAPCHIP_H
#define CMAPCHIP_H

class CMapChip : public CRectangle {
public:
	CMapChip(const CVector2 &pos, const CVector2 &scale, CTexture *tex, float uv0, float uv1, float uv2, float uv3)
		: CRectangle(pos, scale, tex)
	{
		mUv[0] = uv0;
		mUv[1] = uv1;
		mUv[2] = uv2;
		mUv[3] = uv3;
		mPriority = -1;
		CTaskManager::Get()->Add(this);
	}
};

#endif
