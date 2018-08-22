#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H

#include "CTask.h"

class CTaskManager{
	//�����o�ϐ�
	CTask*mpHead;	//�^�X�N���X�g�̐擪�^�X�N�ւ̃|�C���^
	CTask*mpTail;	//�^�X�N���X�g�̍ŏI�^�X�N�ւ̃|�C���^
	static CTaskManager*mpInstance;	//�^�X�N�}�l�[�W���ւ̃|�C���^(�V���O���g��)
public:

	//�����o���\�b�h
	CTaskManager()	//�R���X�g���N�^
		:mpHead(0), mpTail(0)
	{}
	static CTaskManager*Get();	//�^�X�N�}�l�[�W���𐶐����đ������
	void Add(CTask*task);		//task���^�X�N�}�l�[�W���ɒǉ����� task��mPriority���傫���l���A�擪�ɋ߂�����
	void Update();				//�^�X�N���X�g�̐擪���珇�ɁA�^�X�N�̍X�V�������Ăяo��
	void Collision();			//�^�X�N���X�g�̐擪���珇�ɁA�^�X�N�̏Փˏ������Ăяo��
	void Render();				//�^�X�N���X�g�̐擪���珇�ɁA�^�X�N�̕`�揈�����Ăяo��
	void Remove();				//�^�X�N���X�g����A�����Ȃ�^�X�N���폜��delete����
	CTask* Remove(CTask*task);	//task�ɊY������^�X�N���A�^�X�N���X�g����폜���Adelete����
	void Destroy();				//�^�X�N���X�g�̃^�X�N��S��delete���A�^�X�N�}�l�[�W����delete����
};

#endif