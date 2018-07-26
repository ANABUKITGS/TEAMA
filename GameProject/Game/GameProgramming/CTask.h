#ifndef CTASK_H
#define CTASK_H

class CTask{
protected:
	//�����o�ϐ�
	CTask*mpPrev;	//�O�|�C���^(�����̑O�̃^�X�N�|�C���^)
	CTask*mpNext;	//���|�C���^(�����̌�̃^�X�N�|�C���^)
	bool mEnabled;	//�L���t���O(true:�L���Afalse:����)
	int mPriority;	//�^�X�N�̗D��x �傫���l���D��x�������A���X�g�̐擪�ɕ���

	//�����o���\�b�h
	CTask()	//�R���X�g���N�^
		:mpPrev(0), mpNext(0), mEnabled(true)
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

};

#endif