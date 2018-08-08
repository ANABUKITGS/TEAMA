#ifndef CMAPSIGN_H
#define CMAPSIGN_H

#include "CMapChip.h"
#include "CMap.h"
#define SIGN_UV 0, 64, 64 * 6, 64 * 5

class CMapSign : public CMapChip {
public:
	bool mTextbox;
	int sign_num;
	CTexture mTexSignhoge;
	CMapSign(const CVector2& pos, const CVector2& scale)
		//CMapChip�ŏ�����
		: CMapChip(pos, scale, NULL, SIGN_UV, ECELLNUM::ESIGN)
	{
		mTexSignhoge.Load(".\\Data\\Images\\Map\\MapSign.tga");
		mTextbox = false;
		static int sign_num_temp = 0;
		sign_num_temp++;
		sign_num = sign_num_temp;
		mTag = ECELLNUM::ESIGN;
	}
	void Update();
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	void Render();
};
#endif