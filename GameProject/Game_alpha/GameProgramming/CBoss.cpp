#include "CBoss.h"
#include "CGame2.h"
#include "CScore.h"
#include "CScene.h"
#include "CFade.h"
#include "CTime.h"
#include "CMapSign.h"
#include "CMapScroll.h"

CBoss *CBoss::mpBoss = 0;

void CBoss::Update(){
	if (CMapBossRoomSign::mpBossRoomSign != NULL && CMapBossRoomSign::mpBossRoomSign->mColFlg && mBossBattle){
		if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
			static int IdolInterval = 0;//�ҋ@��Ԃ��玟�̍s���Ɉڂ�܂ł̎���
			//�{�X�ƃv���C���[�Ƃ̃x�N�g�����o��
			mAttack_Search = CPlayerT::mpPlayer->mPosition - mPosition;
			//���Ԋu�ŃW�����v�̗������o��(�Ƃ肠����1�b�Ɉ��)
			if (mBossJcnt < BOSSJUMPTIME)
				mBossJcnt++;
			//��莞�Ԍo�߂���Ɨ������o��
			else{
				mBossJumprad = rand() / 100 % 7;
				mBossJcnt = NULL;
			}
			//�W�����v�̏��������܂�
			//�ҋ@��Ԃ��烉���_���ōs�����Ƃ�(�ړ��A�W�����v�A�U���̂ǂꂩ)
			mBossIBehavior =  rand() / 1000 % 7;
			printf("%d\n", mBossAttackItr);
			//�s���p�^�[������
			switch (mAttackBehavior){

				//�ҋ@���
			case EIDOL:
				if (mPosition.x > CPlayerT::mpPlayer->mPosition.x)
					mDirection = false;
				else
					mDirection = true;

				if (mAttackBehavior != EMANTO){
					//���̍s���܂ł̎��Ԃ����Z����
					if (IdolInterval != BOSSNEXTBEHAVIOR)
						IdolInterval++;
					//�w�肵���b���𒴂���΍s���������_���łƂ�
					else{
						switch (mBossIBehavior){
						case 0: case 1: case 2://0,1,2�͈ړ�
							IdolInterval = NULL;
							mAttackBehavior = EDASH;
							break;
						case 3://3�̓W�����v
							if (mBossLife <= mBossMaxLife * 0.5){
								CEnemy::mpEnemy = new CEnemy(mPosition, EENEMY1);
							}
							IdolInterval = NULL;
							mVelocityY = BOSSGVELOCITY;
							if (!mDirection)
								mVelocityX = -BOSSMOVESPEED * 3;
							else
								mVelocityX = BOSSMOVESPEED * 3;
							mAttackBehavior = EJUMP;
							break;
						case 4://4�̓v���C���[�̌��Ƀe���|�[�g
							//�v���C���[�̌��Ɍ����^�C�~���O�������_���ɂ���
							mBossAttackItr = rand() / 100 % BOSSTELEPOA + 1;
							IdolInterval = NULL;
							//�����ɂȂ铮��ɓ���
							mTelepoEnabled = false;
							//�e���|�[�g����Ɉړ�
							mAttackBehavior = ETELEPO;
							break;
						default:
							IdolInterval = 50;
							break;
						}
					}
				}
				mpBWeapon = 0;
				break;
				//�ҋ@��ԏ����I��


				//�ŏ��̃}���g�̏���
			case EMANTO:
				//�{�X�̃A�j���[�V�������Ō�܂ōs���Ə����J�n
				if (mBossAnimeFream > 4){
					mAttackBehavior = EIDOL;
				}
				mpBWeapon = 0;
				break;//���[�v�I��


				//�{�X�̑��鏈��
			case EDASH:

				if (!mDirection)
					mVelocityX = -BOSSMOVESPEED;
				else
					mVelocityX = BOSSMOVESPEED;

				//�����l���^(1)�̎������{�X���W�����v������
				if (mBossJumprad == 1){
					mVelocityY = BOSSGVELOCITY;
					if (!mDirection)
						mVelocityX = -BOSSMOVESPEED * 3;
					else
						mVelocityX = BOSSMOVESPEED * 3;
					mAttackBehavior = EJUMP;//�{�X�̍s�����W�����v�ɂ���
				}
				else{
					//�v���C���[�Ƃ̋��������͈͓��ɓ���΁A�U�����o��
					if (abs(mAttack_Search.x) < mBossBehavior){
						mAttackBehavior = EBWEAPON;
						mVelocityX = 0;
					}
				}
				break;//���[�v�I��
				//���鏈���I��


				//�{�X�̃W�����v����
			case EJUMP:
				break;
				//�W�����v�����I��

				//�{�X�̍U������
			case EBWEAPON:
				//�{�X�����[���[���o���ĂȂ���
				if (!mpBWeapon){
					//�{�X�̃A�j���[�V�������Ō�܂ōs����
						//�{�X�̃��[���[���Ăяo��
						if (mDirection)
							mpBWeapon = new CWeapon(ECELLNUM::EBWEAPON, mPosition + CVector2(82.0f, 32.0f), mDirection);

						else
							mpBWeapon = new CWeapon(ECELLNUM::EBWEAPON, mPosition + CVector2(-82.0f, 32.0f), mDirection);

						mpBWeapon->mScale = CVector2(20, 20);

						if (mDirection)		//�G���E�������Ă��鎞�ɂ͉E�Ƀ��[���[��i�܂���
							mpBWeapon->mPosition.x += 10;

						else				//�G�����������Ă��鎞�ɂ͍��Ƀ��[���[��i�܂���
							mpBWeapon->mPosition.x -= 10;
				}
				//�G�̃��[���[�����˂��ꂽ���̏������s��
				else {
					//�{�X�̃��[���[�̎�����������
					if (mpBWeapon->mLife < 0){
						if (mpBWeapon->mPosition.x<mPosition.x)
						//���[���[������
						mpBWeapon = NULL;
						if (mpBWeapon == NULL)
						//���[���[�̃A�j���[�V�������ŏ��ɖ߂�
						mBossAnimeFream = 0;
						//�ҋ@��Ԃɂ���
						if (mBossAnimeFream == 0)
						mAttackBehavior = EIDOL;
					}
				}
				break;//���[�v�I��
				//�U�������I��
		case ETELEPO://�u�Ԉړ�
			if (Invincible)
				mAttackBehavior = EIDOL;
			//�v���C���[�̌��ɏo��������
			else if (mTelepoEnabled){
				//������A�j�[���[�V�������ŏ��ɖ߂�
				mBossAnimeFreamT = 4;
				//�A���t�@�l�����l�𒴂��Ă���Ƃ�
				if (mAlpha >= 1.0){
					if (mBossAnimeFream == 4){
						mAttackBehavior = EBWEAPON;
					}
				}
				//�A���t�@�l�����l��������Ă��鎞
				else{
					//������܂ŉ��Z����
					mAlpha += 0.03;
				}
				if (mAlpha <= 0.03){
					//�v���C���[�̌��Ɉړ�������
					if (CPlayerT::mpPlayer->mDirection){
						mPosition.x = CPlayerT::mpPlayer->mPosition.x - BOSSTELEPO;
						mDirection = true;
					}
					else{
						mPosition.x = CPlayerT::mpPlayer->mPosition.x + BOSSTELEPO;
						mDirection = false;
					}
				}
			}
			//�{�X�������铮��ɓ������Ƃ�
			else{
				//�{�X�̏�����A�j���[�V�������Ō�܂ōs�����Ƃ�
				if (mBossAnimeFreamT == 0){
					//�A���t�@�l�����炷
					mAlpha -= 0.03;
					//�A���t�@�l�����l�܂Ō�������
					if (mAlpha <= 0.0f){
						//�J�E���g��0�ɂȂ�܂Ō��Z����
						mBossAttackItr--;
						//�����铮��ɂ͂�������o������A�j���[�V�������ŏ��ɂ��ǂ�
						mBossAnimeFream = 0;
						//�J�E���g��0�ɂȂ�����
						if (mBossAttackItr <=0){
							//�v���C���[�̌��ɏo��������
							mTelepoEnabled = true;
						}
					}
				}
			}
			break;

				//�U�����󂯂���
			case EDAMAGE:
				if (!mDirection)
					mVelocityX = 5;
				else
					mVelocityX = -5;
				//���񐔍U�������ƌ��j�����
				if (mBossLife <= 0)
					mAttackBehavior = EDOWN;

				else if (mBossAnimeFream > 1){
					mAttackBehavior = EIDOL;
				}
				break;//���[�v�I��

			case EDOWN://�v���C���[�ɕ�������
				//�Ō�܂ŃA�j���[�V�������i�񂾎��ɏ����J�n
				if (mBossAnimeFream > 3){
					//���ł܂ł̃J�E���g�_�E���J�n
					if (mBossDeleteTime){
						//0�ɂȂ�܂Ō��Z����
						mBossDeleteTime--;
						//���ł܂œ_�ŁH���J��Ԃ�
						if (mBossDeleteTime % 10 == 0)
							mAlpha = 0.0f;
						else
							mAlpha = 1.0f;
					}
				}
				else {
					static int mBossDownTime = 0;
					if (CSDiamond::mpSDiamond == NULL && !CSDiamond::mGetFlg)
						CSDiamond::mpSDiamond = new CSDiamond(CVector2(mPosition.x, mPosition.y));
					mBossDownTime++;
					if (mBossDownTime >= BOSS_DOWN_TIME && CSDiamond::mGetFlg){
						CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ERESULT);
						CGame2::mTimeMin = CTime::ElapsedTimeMin();
						CGame2::mTimeSec = CTime::ElapsedTimeSec();
						CScore::GetScore();
						return;
					}
				}
				break;
				//�_���[�W�����I��
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

			if (mVelocityX > 0.0f)
				mVelocityX -= 0.25f;

			if (mVelocityX < 0.0f)
				mVelocityX += 0.25f;


			mPosition.x += mVelocityX;
			mBossLifeProportion = static_cast <float> (mBossLife) / static_cast <float> (mBossMaxLife);

			//���N���X�̍X�V����
			CRectangle::Update();
		}
	}
	else if (CMapBossRoomSign::mpBossRoomSign != NULL && !CMapBossRoomSign::mpBossRoomSign->mColFlg){
		mBossBattle = false;
		mPosition = mBossDefaultPos;
		mAttackBehavior = EIDOL;
		mVelocityX = mVelocityY = 0.0f;
	}
	if (mPosition.y < -100){
		mPosition.y = mBossDefaultPos.y;
		mPosition.x = CMapScroll::mpScroll->mPosition.x;
	}
}

bool CBoss::Collision(CRectangle*p){
	if (p->GetEnabled()){
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			switch (p->mTag){
			case ECELLNUM::EUNDER:
				if ((mPosition.y > p->mPosition.y) && mVelocityY <= 0.0f){
					mVelocityY = 0.0f;
					mPosition.y = mPosition.y + aj.y;
				}
				break;
			case ECELLNUM::EPWEAPON://�v���C���[�̃��[���[�ƏՓ˂�����
				if (CPlayerT::mpPlayer->mpWeapon->mPosition.x > mPosition.x)
					mDirection = true;
				else
					mDirection = false;
				mVelocityY = 0.0f;
				if (Invincible)
					return false;
				//���G���Ԃ̃t���O��OFF�̎��Ƀ_���[�W�����Z����
				else{
					mBossLife--;
					//���G���Ԃ̃t���O��ON�ɂ���
					Invincible = true;
					//�U�����󂯂����̃A�j���[�V����������
					//���񐔈ȏ�̍U�����󂯂ĂȂ����ɃA�j���[�V���������
					if (mAttackBehavior != EDOWN)
						mAttackBehavior = EDAMAGE;
				}
				break;

			case ECELLNUM::EBOX:
			case ECELLNUM::ESTEEL:
				if (mAttackBehavior == EDAMAGE)
					return false;
				//�������̃I�u�W�F�N�g�ƐڐG�����ꍇ
				if (p->mBreak){
					mAttackBehavior = EDAMAGE;

					mVelocityY = 0.0f;
					if (Invincible)
						return false;
					//���G���Ԃ̃t���O��OFF�̎��Ƀ_���[�W�����Z����
					else{
						mBossLife -= static_cast <float> (mBossMaxLife)* 0.2;
						//���G���Ԃ̃t���O��ON�ɂ���
						Invincible = true;
						//�U�����󂯂����̃A�j���[�V����������
						//���񐔈ȏ�̍U�����󂯂ĂȂ����ɃA�j���[�V���������
						if (mAttackBehavior != EDOWN)
							mAttackBehavior = EDAMAGE;
					}
				}
				break;

			case ECELLNUM::ESWITCH_GROUND1:
			case ECELLNUM::ESWITCH_GROUND2:
			case ECELLNUM::ENONE:
			case ECELLNUM::ECHIKUWA:
			case ECELLNUM::EBELTL:
			case ECELLNUM::EBELTR:
			case ECELLNUM::ESIGN:
			case ECELLNUM::EEWEAPON:
			case ECELLNUM::ESEARCH:
			case ECELLNUM::ESWITCH:
			case ECELLNUM::EPLAYER:
			case ECELLNUM::EENEMY1:
			case ECELLNUM::EENEMY2:
			case ECELLNUM::EENEMY3:
			case ECELLNUM::EICE:
			case ECELLNUM::EBOSSROOM:
			case ECELLNUM::EJEWELRY:
			case ECELLNUM::EJEWELRY2:
			case ECELLNUM::ESDIAMOND:
				break;

			default:
				CVector2 ad;
				if (aj.x > 0) {
					//�E��
					if (!(p->mColFlg & EDT_RIGHT)) {
						mPosition.x = mPosition.x + aj.x;
						//mAttackBehavior = EIDOL;
						if (mIce)
							mVelocityX = 0.0f;
					}
				}
				else if (aj.x < 0) {
					//����
					if (!(p->mColFlg & EDT_LEFT)) {
						mPosition.x = mPosition.x + aj.x;
						//mAttackBehavior = EIDOL;
						if (mIce)
							mVelocityX = 0.0f;
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
							if (mAttackBehavior==EJUMP)
							mAttackBehavior = EIDOL;
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
		// �A�j���[�V�����̖��� - 1���w�肵�A���̖����𒴂�����
		//if (mBossAnimeFream > 2)
			//�A�j���[�V�����̍ŏ��ɖ߂�
			//mBossAnimeFream = 0;
		//�A�j���[�V�����̑������w��(���l:�����A�j���[�V����,���l:�x���A�j���[�V����)
		//Boss_Ani_Count_Frame = 20;

		//if (!mDirection)//������
		//	mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2304, 2048, mAlpha);
		//else			//�E����
		//	mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2304, 2048, mAlpha);

		if (mBossAnimeFream > 4)
			mBossAnimeFream = 0;
		Boss_Ani_Count_Frame = 9;
		if (!mDirection)	//������
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
		else				//�E����
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 512, 256, mAlpha);

		break;

	case EMANTO://�}���g�A�j���[�V����
		//�e�N�X�`���̖���-1�����l���傫���Ȃ��
		if (mBossAnimeFream > 4)
			//���[�v�̐擪�ɖ߂�
			mBossAnimeFream = 0;
		//���̃R�}�ɍs���^�C�~���O
		Boss_Ani_Count_Frame = 5;

		if (!mDirection)	//������
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
		else				//�E����
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 512, 256, mAlpha);
		break;

	case EDASH://���蓮��
		if (mBossAnimeFream > 4)
			mBossAnimeFream = 0;

		Boss_Ani_Count_Frame = 5;

		if (!mDirection)//������
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 256, 0, mAlpha);

		else//�E����
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 256, 0, mAlpha);
		break;

	case EJUMP://�W�����v����
		//�W�����v�㏸���̎��̏���
		if (mVelocityY > 0.0f){
			if (mBossAnimeFream > 1)
				mBossAnimeFream = 0;

			Boss_Ani_Count_Frame= 10;

			if (!mDirection)	//������
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1536, 1280, mAlpha);
			else				//�E����
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1536, 1280, mAlpha);
		}
		//�W�����v������
		else if (mVelocityY < 0.0f){
			if (mBossAnimeFream > 1)
				mBossAnimeFream = 0;

			Boss_Ani_Count_Frame = 10;

			if (!mDirection)	//������
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1792, 1536, mAlpha);
			else				//�E����
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1792, 1536, mAlpha);
		}
		////�W�����v�ō��n�_
		//else if (mVelocityY >= BOSSGVELOCITY){
		//	//�A�j���[�V�����̖���-1���w�肵�A���̖����𒴂�����
		//	if (mBossAnimeFream > 4)
		//		mBossAnimeFream = 0;//���[�v�J�n�ʒu(1���ڂ̃A�j���[�V����)�ɖ߂�

		//	//�A�j���[�V�����̑������w��(���l:�����A�j���[�V����,���l:�x���A�j���[�V����)
		//	Boss_Ani_Count_Frame = 4;

		//	if (!mDirection)//������
		//		mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 768, 512, mAlpha);

		//	else			//�E����
		//		mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 768, 512, mAlpha);
		//}
		//���n�n�_
		else if (mVelocityY == 0.0f){
			//�A�j���[�V�����̖���-1���w�肵�A���̖����𒴂�����
			if (mBossAnimeFream > 3)
				mBossAnimeFream = 0;//���[�v�J�n�ʒu(1���ڂ̃A�j���[�V����)�ɖ߂�

			//�A�j���[�V�����̑������w��(���l:�����A�j���[�V����,���l:�x���A�j���[�V����)
			Boss_Ani_Count_Frame = 10;

			if (!mDirection)//������
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2506, 2250, mAlpha);

			else			//�E����
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2506, 2250, mAlpha);
		}
		break;

	case EBWEAPON://�U��
		if (mpBWeapon != NULL){
			if (!mDirection)
				//���[���[�̕R
				mpBWeapon->mTexYoyo.DrawImage(BSTRING_UV_L, 1.0f);

			else
				//���[���[�̕R
				mpBWeapon->mTexYoyo.DrawImage(BSTRING_UV_R, 1.0f);
		}
		if (mBossAnimeFream > 3)
			mBossAnimeFream = 3;

			Boss_Ani_Count = 8;

			//������
			if (!mDirection)
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2048, 1792, mAlpha);
			//�E����
			else
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2048, 1792, mAlpha);
		break;
		
			case ETELEPO://�u�Ԉړ�
		if (!mTelepoEnabled){
			//�e�N�X�`���̖���-1�����l���傫���Ȃ��
			if (mBossAnimeFreamT < 1)
				//���[�v�̐擪�ɖ߂�
				mBossAnimeFreamT = 0;
			//���̃R�}�ɍs���^�C�~���O
			Boss_Ani_Count_Frame = 6;

			if (!mDirection)	//������
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFreamT + 1) * 256, mBossAnimeFreamT * 256, 512, 256, mAlpha);
			else				//�E����
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFreamT * 256, (mBossAnimeFreamT + 1) * 256, 512, 256, mAlpha);
		}
		else if(mTelepoEnabled){
			//�e�N�X�`���̖���-1�����l���傫���Ȃ��
			if (mBossAnimeFream > 4)
				//���[�v�̐擪�ɖ߂�
				mBossAnimeFream = 4;
			//���̃R�}�ɍs���^�C�~���O
			Boss_Ani_Count_Frame = 6;

			if (!mDirection)	//������
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
			else				//�E����
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 512, 256, mAlpha);
		}
		break;


	case EDAMAGE://�U�����󂯂���
		if (mBossAnimeFream > 1){
			mBossAnimeFream = 0;
		}
		Boss_Ani_Count_Frame = 12;

		if (!mDirection)	//������
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1024, 768, mAlpha);
		else				//�E����
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1024, 768, mAlpha);
		break;


	case EDOWN://�_�E���������i�v���C���[�ɕ��������j
		//�w��e�N�X�`���̖����𒴂�����
		if (mBossAnimeFream > 3)
			//�Ō�̉摜�ŌŒ肷��
			mBossAnimeFream = 3;

		//�A�j���[�V�����̑������w��
		Boss_Ani_Count_Frame = 6;

		if (mBossAnimeFream == 3)
			mTexture.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE*2,
			mPosition.y + CELLSIZE, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1280, 1024, mAlpha);

		else{
			//������
			if (!mDirection)
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1280, 1024, mAlpha);
			//�E����
			else
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1280, 1024, mAlpha);
		}
		break;
	}
	//���̃R�}�ɍs���ׂɉ��Z����
	Boss_Ani_Count++;
	//��R�}�̃t���[���������傫���Ȃ��
	if (Boss_Ani_Count > Boss_Ani_Count_Frame){
		if (mAttackBehavior == ETELEPO)
			mBossAnimeFreamT--;
		//���̃R�}�ɍs��
		mBossAnimeFream++;
		//�J�E���g�����Z�b�g����
		Boss_Ani_Count = 0;
	}
}