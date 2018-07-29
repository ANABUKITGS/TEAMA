#include "CTaskManager.h"
#include "CRectangle.h"

CTaskManager *CTaskManager::mpInstance = 0;

CTaskManager*CTaskManager::Get(){
	if (!mpInstance)
		mpInstance = new CTaskManager();
	return mpInstance;
}

void CTaskManager::Add(CTask*task){
	if (mpHead){	//2���ڈȍ~
		CTask*c = mpHead;	//�J�����g���쐬���Đ擪�ɐݒ�
		if (task->mPriority >= c->mPriority){
			task->mpPrev = 0;	//�O�^�X�N�͌��Ȃ�
			task->mpNext = c;	//���^�X�N�̓J�����g(�J�����g�͌��݌��Ă���ꏊ���w��)
			c->mpPrev = task;	//�J�����g�̑O�̓^�X�N(�O�������)
			return;
		}

		c->mpNext = c;
		
		while (c){
			if (task->mPriority >= c->mPriority){
				c->mpNext->mpPrev = task;	//�J�����g�̎��̑O���^�X�N�ɂ���
				task->mpPrev = c->mpPrev;	//�^�X�N�̑O���J�����g�̑O�ɂ���
				task->mpNext = c;	//�^�X�N�̎����J�����g��
				c->mpPrev = task;	//�J�����g�̑O���^�X�N�ɂ���
				return;
			}
		}
		c->mpNext = c;

		mpTail->mpNext = task;
		task->mpPrev = mpTail;
		mpTail = task;
		task->mpNext = 0;

	}
	else{
		mpHead = task;
		task->mpNext = 0;
		task->mpPrev = 0;
		mpTail = task;
	}
}

void CTaskManager::Update(){
	CRectangle*p = (CRectangle*)mpHead;	//�q�N���X�̃J�����g�ɃL���X�g�ϊ������擪�^�X�N����
	while (p){	//�J�����gp
		p->Update();	//���݃J�����g�̍X�V�������s��
		p=(CRectangle*)p->mpNext;	//�L���X�g�ϊ����s�����^�X�N�̎����J�����g�ɑ��
	}
}

void CTaskManager::Render(){
	CRectangle*p = (CRectangle*)mpHead;	//�q�N���X�̃J�����g�ɃL���X�g�ϊ������擪�^�X�N����
	while (p){	//�J�����gp
		p->Render();	//���݃J�����g�̕`�揈�����s��
		p = (CRectangle*)mpHead->mpNext;	//�L���X�g�ϊ����s�����^�X�N�̎����J�����g�ɑ��
	}
}

void CTaskManager::Remove(){

}

CTask* CTaskManager::Remove(CTask*task){
	CTask*p = task->mpNext;
	//�擪�������ꍇ
	if (task == mpHead){
		mpHead = task->mpNext;
		mpHead->mpPrev = 0;
	}
	//�Ōゾ�����ꍇ
	if (task == mpTail){
		mpTail = task->mpPrev;
		mpTail->mpNext = 0;
	}
	//�r���������ꍇ
	if (task->mpPrev != 0){
		task->mpPrev->mpNext = task->mpNext;
	}
	if (task->mpNext != 0){
		task->mpNext->mpPrev = task->mpPrev;
	}
	delete task;

	return p;
}

void CTaskManager::Destroy(){
	//�J�����gc��擪�ɂ���
	CTask *c = mpHead;
	//�J�����g��0�ɂȂ�����I��
	while (c){
		//�J�����g�����ɂ���
		c = c->mpNext;
		//�擪���폜
		delete mpHead;
		//�擪�ɃJ�����g��������
		mpHead = c;
	}
	//�Ō��0�ɂ���
	mpTail = 0;
	//�������g���폜
	if (mpInstance)
		delete mpInstance;
	mpInstance = 0;
}