#include "CBoss.h"
#include "CGame2.h"
#include "CScene.h"

/*
�{�X�̈ړ�����
*/
float CBoss::BossFowrd(float speed){
	float r = speed;
	if (mPosition.x > CPlayerT::mpPlayer->mPosition.x){
		mDirection = false;
		mPosition.x -= r;
	}
	else{
		mDirection = true;
		mPosition.x += r;
	}
	return r;
}

/*
�{�X�̃W�����v����
*/
void CBoss::BossJump(){
	static bool Jump = true;
	//�����l���^�̎��̓W�����v����
	if (Jump){
		//BossFowrd(BOSSMOVESPEED);
		mVelocityY = BOSSGVELOCITY;	//�d�͉��Z�̒l��ݒ�
	}
}

void CBoss::Update(){
	if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
		static const short int Back = 5;
		printf("%d\n", mBossDamageCnt);
		//�{�X�ƃv���C���[�Ƃ̃x�N�g�����o��
		mAttack_Search = CPlayerT::mpPlayer->mPosition - mPosition;
		//���Ԋu�ŃW�����v�̗������o��(�Ƃ肠����1�b�Ɉ��)
		if (mBossJcnt < BOSSJUMPTIME)
			mBossJcnt++;
		//��莞�Ԍo�߂���Ɨ������o��
		else{
			mBossJumprad = rand() / 100 % 7;
			//printf("%d\n", mBossJumprad);
			mBossJcnt = NULL;
		}

		//�s���p�^�[������
		switch (mAttackBehavior){

		case EIDOL://�ҋ@���
			break;

		case EMANTO://�ŏ��̃}���g�̏���
			//�{�X�̃A�j���[�V�������Ō�܂ōs���Ə����J�n
			if (mBossAnimeFream > 4)
				mAttackBehavior = EDASH;
			break;//���[�v�I��

		case EDASH:				//�{�X�̑��鏈��
			BossFowrd(BOSSMOVESPEED);//�{�X�̈ړ����x���w��

			//�����l���^(1)�̎������{�X���W�����v������
			if (mBossJumprad == 1){
				mAttackBehavior = EJUMP;//�{�X�̍s�����W�����v�ɂ���
				mBossJumprad = NULL;//�{�X�̗����l����x0�ɂ��ĘA���W�����v��h��
			}

			//�v���C���[�Ƃ̋��������͈͓��ɓ���΁A�U�����o��
			/*if (abs(mAttack_Search.x) < mBossBehavior)
				mAttackBehavior = EBWEAPON;*/
			break;//���[�v�I��

		case EJUMP:	//�{�X�̃W�����v����
			BossJump();//�{�X���W�����v������
			if (!mBossJumprad)
				mAttackBehavior = EDASH;
			break;

		case EBWEAPON:		//�{�X�̍U������
			if (!mpBWeapon){
				if (mBossAttackItr < 0){
					mBossAttackItr = ATTACK_INTERVAL;
					//�{�X�̃��[���[���Ăяo��
					mpBWeapon = new CWeapon(EEWEAPON, mPosition, mDirection);

					if (mDirection)		//�G���E�������Ă��鎞�ɂ͉E�Ƀ��[���[��i�܂���
						mpBWeapon->mPosition.x += 10;

					else				//�G�����������Ă��鎞�ɂ͍��Ƀ��[���[��i�܂���
						mpBWeapon->mPosition.x -= 10;
				}
			}
			//�G�̃��[���[�����˂��ꂽ���̏������s��
			else {
				if (mpBWeapon->mLife < 0){
					mpBWeapon = 0;
					mAttackBehavior = EDASH;
				}
			}
			break;//���[�v�I��

		case EDAMAGE://�U�����󂯂���
			if (CPlayerT::mpPlayer->mPosition.x<mPosition.x)
				mPosition.x += Back;
			else
				mPosition.x-=Back;
			if (mBossAnimeFream > 1)
				mAttackBehavior = EDASH;
			//���ȏ�̃_���[�W���󂯂�Ə��ł̃A�j���[�V�����ֈڍs
			if (mBossDamageCnt == 3)
				mAttackBehavior = EDOWN;
			break;//���[�v�I��

		case EDOWN://�v���C���[�ɕ�������
			//�Ō�܂ŃA�j���[�V�������i�񂾎��ɏ����J�n
			if (mBossAnimeFream > 4){
				//���ł܂ł̃J�E���g�_�E���J�n
				if (mBossDeleteTime){
					//0�ɂȂ�܂Ō��Z����
					mBossDeleteTime--;
					//���ł܂œ_�ŁH���J��Ԃ�
					if (BOSS_DELCNT%mBossDeleteTime == 0)
						mAlpha = 0.0f;
					else
						mAlpha = 1.0f;
				}
				//0�ɂȂ�������ł�����
				else
					mEnabled = false;
			}
			break;

		default:	//�ʏ�ł͋����̉��߂Ŕ��肷��
			//�v���C���[�����͈͓��ɓ���΃}���g�̃A�j���[�V�������s��
			if (STARTBEHAVIOR > abs(mAttack_Search.x))
				mAttackBehavior = EMANTO;
			////�v���C���[�Ƃ̋��������̋����O�ł���΃v���C���[�ɋ߂Â�
			//if (abs(mAttack_Search.x) > mBossBehavior)
			//	mAttackBehavior = EDASH;
			break;
		}
		//�_���[�W���󂯂����ɍs������
			if (Invincible){
				mBossInvincibleTime--;
				//���G���Ԃ�ǉ�
				if (mBossInvincibleTime % 10 == 0)
					mAlpha = 0.0f;
				else
					mAlpha = 1.0f;
				if (!mBossInvincibleTime){
					mBossInvincibleTime = BOSSINVINCIBLE;
					mAlpha = 1.0f;
					Invincible = false;
				}
			}
		//�d�͏���
		Gravity();
	}
	//���N���X�̍X�V����
	CRectangle::Update();
}

bool CBoss::Collision(CRectangle*p){
	//return false;
	if (p->GetEnabled()){
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			switch (p->mTag){
			case EUNDER:
				if ((mPosition.y > p->mPosition.y) && mVelocityY < 0){
					mVelocityY = 0.0f;
					mPosition = mPosition + aj;
				}
				break;
			case EPWEAPON://�v���C���[�̃��[���[�ƏՓ˂�����
				//���G���Ԃ̃t���O��ON�ɂ���
				Invincible = true;
				mVelocityY = 0.0f;
				//�_���[�W�����Z����
				mBossDamageCnt++;
				//�U�����󂯂����̃A�j���[�V����������
				mAttackBehavior = EDAMAGE;
				break;
			case ESWITCH_GROUND1:
			case ESWITCH_GROUND2:
			case ENONE:
			case ECHIKUWA:
			case EBELTL:
			case EBELTR:
			case ESIGN:
			case EEWEAPON:
			case ESEARCH:
			case ESWITCH:
			case EPLAYER:
				break;

			default:
				CVector2 ad;
				if (aj.x > 0) {
					//�E��
					if (!(p->mColFlg & EDT_RIGHT)) {
						mPosition.x = mPosition.x + aj.x;
					}
				}
				else if (aj.x < 0) {
					//����
					if (!(p->mColFlg & EDT_LEFT)) {
						mPosition.x = mPosition.x + aj.x;
					}
				}
				if (CRectangle::Collision(p, &aj, &ad)) {
					if (ad.y < 0) {
						//����
						if (!(p->mColFlg & EDT_BOTTOM)) {
							mPosition.y = mPosition.y + ad.y;
							mVelocityY = 0.0f;
						}
					}
					else if (ad.y > 0) {
						//���
						if (!(p->mColFlg & EDT_TOP)) {
							mPosition.y = mPosition.y + ad.y;
							mVelocityY = 0.0f;
						}
					}
				}
				break;
			}
			return true;
		}
	}
	return false;
}

void CBoss::Render(){
	switch (mAttackBehavior){

	case EIDOL://�ҋ@���
		break;

	case EMANTO://�}���g�A�j���[�V����
		//�e�N�X�`���̖���-1�����l���傫���Ȃ��
		if (mBossAnimeFream > 4)
			//���[�v�̐擪�ɖ߂�
			mBossAnimeFream = 0;
		//���̃R�}�ɍs���^�C�~���O
		Boss_Ani_Count_Frame = 5;

		if (!mDirection)	//������
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
		else				//�E����
			mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2,
			mPosition.y + CELLSIZE*2, mBossAnimeFream * 256, (mBossAnimeFream+1) * 256, 512, 256, mAlpha);
		break;

	case EDASH://���蓮��
		if (mBossAnimeFream > 4)
			mBossAnimeFream = 0;

		Boss_Ani_Count_Frame = 5;

		if (!mDirection)//������
			mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2,
			mPosition.y + CELLSIZE*2, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 256, 0, mAlpha);

		else//�E����
			mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2,mPosition.y - CELLSIZE*2, 
			mPosition.y + CELLSIZE*2, mBossAnimeFream * 256, (mBossAnimeFream+1) * 256, 256, 0, mAlpha);
		break;

	case EJUMP://�W�����v����
		//�W�����v�㏸���̎��̏���
		if (mVelocityY > 0.0f){
			if (mBossAnimeFream > 1)
				mBossAnimeFream = 0;

			Boss_Ani_Count_Frame= 10;

			if (!mDirection)	//������
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2,mPosition.y - CELLSIZE*2, 
				mPosition.y + CELLSIZE*2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1536, 1280, mAlpha);
			else				//�E����
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2,
				mPosition.y + CELLSIZE*2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1536, 1280, mAlpha);
		}
		//�W�����v������
		else if (mVelocityY < 0.0f){
			if (mBossAnimeFream > 1)
				mBossAnimeFream = 0;

			Boss_Ani_Count_Frame = 10;

			if (!mDirection)	//������
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2, 
				mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1792, 1536, mAlpha);
			else				//�E����
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2,
				mPosition.y + CELLSIZE * 2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1792, 1536, mAlpha);
		}
		//�W�����v�ō��n�_
		else if (mVelocityY >= BOSSGVELOCITY){
			//�A�j���[�V�����̖���-1���w�肵�A���̖����𒴂�����
			if (mBossAnimeFream > 4)
				mBossAnimeFream = 0;//���[�v�J�n�ʒu(1���ڂ̃A�j���[�V����)�ɖ߂�

			//�A�j���[�V�����̑������w��(���l:�����A�j���[�V����,���l:�x���A�j���[�V����)
			Boss_Ani_Count_Frame = 4;

			if (!mDirection)//������
				mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
				mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 768, 512, mAlpha);

			else			//�E����
				mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
				mPosition.y + CELLSIZE * 2, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 768, 512, mAlpha);
		}
		//���n�n�_
		else if (mVelocityY == 0.0f){
			//�A�j���[�V�����̖���-1���w�肵�A���̖����𒴂�����
			if (mBossAnimeFream > 3)
				mBossAnimeFream = 0;//���[�v�J�n�ʒu(1���ڂ̃A�j���[�V����)�ɖ߂�

			//�A�j���[�V�����̑������w��(���l:�����A�j���[�V����,���l:�x���A�j���[�V����)
			Boss_Ani_Count_Frame = 10;

			if (!mDirection)//������
				mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
				mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2506, 2250, mAlpha);

			else			//�E����
				mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
				mPosition.y + CELLSIZE * 2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2506, 2250, mAlpha);
		}
		break;

	case EBWEAPON://�U��
		if (mBossAnimeFream > 5)
			mBossAnimeFream = 0;

		Boss_Ani_Count = 20;

		//������
		if (!mDirection)
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2250, 1994, mAlpha);
		//�E����
		else
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2250, 1994, mAlpha);
		break;

	case EDAMAGE://�U�����󂯂���
		if (mBossAnimeFream > 1)
			mBossAnimeFream = 0;

		Boss_Ani_Count = 14;

		if (!mDirection)	//������
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1280, 1024, mAlpha);
		else				//�E����
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1280, 1024, mAlpha);

		break;

	case EDOWN://�_�E���������i�v���C���[�ɕ��������j
		//�w��e�N�X�`���̖����𒴂�����
		if (mBossAnimeFream > 4)
			//�Ō�̉摜�ŌŒ肷��
			mBossAnimeFream = 4;

		//�A�j���[�V�����̑������w��
		Boss_Ani_Count = 10;

		//������
		if (!mDirection)
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1024, 768, mAlpha);
		//�E����
		else
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1024, 768, mAlpha);
		break;
	}
	//���̃R�}�ɍs���ׂɉ��Z����
	Boss_Ani_Count++;
	//��R�}�̃t���[���������傫���Ȃ��
	if (Boss_Ani_Count > Boss_Ani_Count_Frame){
		//���̃R�}�ɍs��
		mBossAnimeFream++;
		//�J�E���g�����Z�b�g����
		Boss_Ani_Count = 0;
	}
}