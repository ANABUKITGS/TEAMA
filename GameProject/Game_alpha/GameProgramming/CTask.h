#ifndef CTASK_H
#define CTASK_H

//�}�b�v �z�� ���g
enum ECELLNUM{
	/*------ �}�b�v �`�� �Ȃ� ------*/
	ENONE = 1,			//�� | 0�͎g�p�֎~
	EGROUND,			//�����
	EUNDER,				//�����甲���鑫��
	EBELTL,				//�x���g�R���x�A��
	EBELTR,				//�x���g�R���x�A�E
	EJEWELRY,			//���
	EJEWELRY2,			//��΂̌���
	ECHIKUWA,			//������u���b�N
	ESWITCH_GROUND1,	//�X�C�b�`�� �؂�ւ�鑫�� 1
	ESWITCH_GROUND2,	//�X�C�b�`�� �؂�ւ�鑫�� 2
	ESWITCH,			//�X�C�b�`�� �؂�ւ�鑫��� �X�C�b�`

	/*------ �L�����N�^�[ �Ȃ� ------*/
	ECHECKPOINT,		//�`�F�b�N�|�C���g
	EPLAYER,			//�v���C���[
	EENEMY1,			//�G1
	EENEMY2,			//�G2
	EENEMY3,			//�G3
	EBOSS,				//�{�X

	/*------ ����M�~�b�N ------*/
	EBOX,				//�ؔ�
	ESTEEL,				//�S��
	ESIZE,				//ECELLNUM �T�C�Y

	EBELT,
};


class CTask{
protected:
	ECELLNUM mTag;
	//�����o�ϐ�
	CTask*mpPrev;	//�O�|�C���^(�����̑O�̃^�X�N�|�C���^)
	CTask*mpNext;	//���|�C���^(�����̌�̃^�X�N�|�C���^)
	bool mEnabled;	//�L���t���O(true:�L���Afalse:����)
	int mPriority;	//�^�X�N�̗D��x �傫���l���D��x�������A���X�g�̐擪�ɕ���

	//�����o���\�b�h
	CTask()	//�R���X�g���N�^
		:mpPrev(0), mpNext(0), mEnabled(true), mPriority(0)
	{}

	CTask(bool enabled, int priority)	//�����L�R���X�g���N�^
		:mpPrev(0), mpNext(0), mEnabled(enabled), mPriority(priority)
	{}

	virtual ~CTask(){	//���z�֐��̃f�X�g���N�^
	}
	virtual void Update(){}	//1�t���[���Ŏ��s���鏈�����`
	virtual void Render(){}	//1�t���[���ŕ`�悷�鏈�����`
	virtual bool Collision(CTask*m, CTask*y){ return false; }	//�Փˏ������`����

	friend class CTaskManager;	//�^�X�N�}�l�[�W���[�Ŏg��
public:

	bool GetEnabled() { return mEnabled; }

};

#endif