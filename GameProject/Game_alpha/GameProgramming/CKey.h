#ifndef CKEY_H
#define CKEY_H
/*
 �L�[���̓N���X
*/
class CKey {
	//�L�[��������Ă��邩�̃t���O
	static bool flg[256];

	static unsigned int oncetimekey[256];
public:
	//k�L�[��������Ă����true��Ԃ�
	static bool Push(char k);
	//k�L�[�������ꂽ���Ɉ�x����true��Ԃ�
	static bool Once(char k);

	static bool OncePush(char k);
};

#endif
