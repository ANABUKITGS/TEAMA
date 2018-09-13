#include "CBoss.h"
#include "CGame2.h"
#include "CScore.h"
#include "CScene.h"
#include "CFade.h"
#include "CTime.h"
#include "CMapSign.h"
#include "CMapScroll.h"
#include "CBossGimmick.h"
#include "CMapSign.h"

CBoss *CBoss::mpBoss = 0;

//���������������ă����_���Ȓl���o��
int CBoss::GetRand(int random){
	srand((unsigned)time(NULL) - clock());
	return rand() % random;
}

//-----------------------------------------------------BossBehP�����J�n---------------------------------------------------------------------
/*
BossBehP
�{�X���ҋ@��Ԃ��烉���_���ŋN�����s��
�ҋ@��Ԃ���V���ɍs�����N��������A�ύX����ꍇ�͂�����
*/
void CBoss::BossBehP(BehP BP){
	//�{�X�ƃv���C���[�Ƃ̃x�N�g�����o��
	mAttack_Search = CPlayerT::mpPlayer->mPosition - mPosition;
	switch (BP){
	case EDASH_0: case EDASH_1: case EDASH_2://0,1,2�͈ړ�
		IdolInterval = NULL;
		mAttackBehavior = EDASH;
		break;
	case BehP::EJUMP_3://3�̓W�����v
		if (mBossLife <= mBossMaxLife * 0.5){
			CEnemy::mpEnemy = new CEnemy(mPosition, EENEMY1);
		}
		IdolInterval = NULL;
		mAttackBehavior = EJUMP;
		break;
	case BehP::ETELEPO_4://4�̓v���C���[�̌��Ƀe���|�[�g
		mBossAnimeFreamT = 4;
		//���G���Ԃ�off�̎�
		if (!Invincible){
			//�v���C���[�̌��Ɍ����^�C�~���O�������_���ɂ���
			mBossAttackItr = GetRand(BOSSTELEPOA + 1);
			//�����ɂȂ铮��ɓ���
			mTelepoEnabled = false;
			//�e���|�[�g����Ɉړ�
			mAttackBehavior = ETELEPO;
		}
		//���G���Ԃ�on�̎�
		else{
			mBossAnimeFream = 0;
			//�v���C���[�Ƃ̋��������͈͓��܂ŏk�܂��
			if (abs(mAttack_Search.x) < mBossBehavior)
				mAttackBehavior = EATTACK;
			else
				mAttackBehavior = EJUMP;
		}
		IdolInterval = NULL;
		break;
	default:
		IdolInterval = 50;
		break;
	}
}
//-----------------------------------------------------BossBehP�����I��---------------------------------------------------------------------



//-----------------------------------------------------Boss_A_BehP�����J�n------------------------------------------------------------------
/*
Boss_A_BehP
mAttackBehavior�ϐ�����s���ɂȂ���֐�
BossBehP�֐�����q����V���ȍs���̒ǉ���ύX�͂�����
*/
void CBoss::Boss_A_BehP(){
	//�{�X�ƃv���C���[�Ƃ̃x�N�g�����o��
	mAttack_Search = CPlayerT::mpPlayer->mPosition - mPosition;

	//�ҋ@��Ԃ��烉���_���ōs�����Ƃ�(�ړ��A�W�����v�A�U���̂ǂꂩ)
#if _DEBUG
	//�f�o�b�O�̎��Ɋe�s�����m�F���������͂�����
	mBossIBehavior = EJUMP_3;
#else
	//�����[�X�p
	mBossIBehavior = GetRand(BehP::ESIZE_7);

#endif

	//�s���p�^�[������
	switch (mAttackBehavior){
		//�ҋ@���
	case EIDOL:
		//�v���C���[�̈ʒu�������Ȃ�A��������
		if (mPosition.x > CPlayerT::mpPlayer->mPosition.x)
			mDirection = false;
		//�v���C���[�̈ʒu���E���Ȃ�A�E������
		else
			mDirection = true;

		if (mAttackBehavior != EMANTO){
			//���̍s���܂ł̎��Ԃ����Z����
			if (IdolInterval != BOSSNEXTBEHAVIOR)
				IdolInterval++;
			//�w�肵���b���𒴂���΍s���������_���łƂ�
			else{
				//�����^����񋓌^�փL���X�g�ϊ�
				//sraric_cast<Behp>(mBossIBehavior)�ł��\
				BossBehP((BehP)(mBossIBehavior));
			}
		}
		mpBWeapon = 0;

		if (CBossGimmick::mpBossGimmick != NULL && CBossGimmick::mpBossGimmick->mGimmickFlg){
			//�{�X�����ɂ���Ƃ�
			if (mPosition.x<CMapScroll::mpScroll->mPosition.x){
				//�v���C���[�����ɂ���Ƃ�
				if (CPlayerT::mpPlayer->mPosition.x < CMapScroll::mpScroll->mPosition.x){
					//�{�X���E�Ɍ�������
					mDirection = true;
				}
				//�v���C���[���E�ɂ���Ƃ�
				else{
					//�{�X�����Ɍ�������
					//mDirection = false;
					break;
				}
			}
			//�{�X���E�ɂ���Ƃ�
			else{
				//�v���C���[���E�ɂ���Ƃ�
				if (CPlayerT::mpPlayer->mPosition.x > CMapScroll::mpScroll->mPosition.x){
					//�{�X�����ɂނ�����
					mDirection = false;
				}
				//�v���C���[�����ɂ���Ƃ�
				else{
					//�{�X���E�Ɍ�������
					//mDirection = true;
					break;
				}
			}
			mAttackBehavior = EJUMP;
		}
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
			mVelocityX = -BOSSMOVESPEED-mBossSpeedUp;
		else
			mVelocityX = BOSSMOVESPEED+mBossSpeedUp;

		//�����l���^(1)�̎������{�X���W�����v������
		if (mBossJumprad == 1)
			mAttackBehavior = EJUMP;//�{�X�̍s�����W�����v�ɂ���
		else{
			//�v���C���[�Ƃ̋��������͈͓��ɓ���΁A�U�����o��
			if (abs(mAttack_Search.x) < mBossBehavior){
				mBossAnimeFream = 0;
				mAttackBehavior = EATTACK;
				mVelocityX = 0;
			}
		}
		break;//���[�v�I��
		//���鏈���I��


		//�{�X�̃W�����v����
	case EJUMP:
		if (mBossAnimeFream == 4){
			mBossAnimeFream = 0;
			mJumpTmEnabled = true;
			mAttackBehavior = EIDOL;
		}
		else{
			if (mJumpTmEnabled){
				mVelocityY = BOSSGVELOCITY;
				if (!mDirection)
					mVelocityX = (-BOSSMOVESPEED * 3 )- mBossSpeedUp;
				else
					mVelocityX = (BOSSMOVESPEED * 3 )+ mBossSpeedUp;
				CSE::mSoundBossJump.Play();
				mJumpTmEnabled = false;
			}
		}
		break;
		//�W�����v�����I��

		//�{�X�̍U������
	case EATTACK:
		//�{�X�����[���[���o���ĂȂ���
		if (!mpBWeapon){
			//�{�X�̃A�j���[�V�������Ō�܂ōs����
			//�{�X�̃��[���[���Ăяo��
			if (mBossAnimeFream > 3){
				CSE::mSoundBossYoyo.Play();
				if (mDirection){
					mpBWeapon = new CWeapon(this, ECELLNUM::EBWEAPON, mPosition + CVector2(82.0f, 32.0f), mDirection);
				}

				else{
					mpBWeapon = new CWeapon(this, ECELLNUM::EBWEAPON, mPosition + CVector2(-82.0f, 32.0f), mDirection);
				}
				mpBWeapon->mScale = CVector2(20, 20);

				if (mDirection)		//�G���E�������Ă��鎞�ɂ͉E�Ƀ��[���[��i�܂���
					mpBWeapon->mPosition.x += 10;

				else				//�G�����������Ă��鎞�ɂ͍��Ƀ��[���[��i�܂���
					mpBWeapon->mPosition.x -= 10;
			}
		}
		break;//���[�v�I��
		//�U�������I��
	case ETELEPO://�u�Ԉړ�
		if (Invincible)
			mAttackBehavior = EIDOL;
		else if (mAlpha >= 1.0f){
			if (!mTelepoEnabled)
				//��������ʉ����Đ�
				CSE::mSoundBossTelepoIn.Play();
		}
		else{
			if (mTelepoEnabled&&mBossAnimeFreamT==0)
			//�����������ʉ����Đ�
			CSE::mSoundBossTelepoOut.Play();
		}
		//�v���C���[�̌��ɏo��������
		if (mTelepoEnabled){
			//�{�X�̕Ǌђʃo�O�h�~�p����
			if (mPosition.y < -100){
				mPosition.y = mBossDefaultPos.y;
				if (CPlayerT::mpPlayer->mDirection == false){
					mDirection = true;
					mPosition.x = CPlayerT::mpPlayer->mPosition.x - BOSSTELEPO;
				}
				else{
					mDirection = false;
					mPosition.x = CPlayerT::mpPlayer->mPosition.x + BOSSTELEPO;
				}
			}
			if (mPosition.x <= CMapScroll::mpScroll->mPosition.x - 640.0){
				mPosition.y = mBossDefaultPos.y;
				if (CPlayerT::mpPlayer->mDirection){
					mDirection = false;
					mPosition.x = CPlayerT::mpPlayer->mPosition.x + BOSSTELEPO;
				}
			}
			//�����I��
			if (mAlpha <= 0.03){
				//�v���C���[�̌��Ɉړ�������
				if (CPlayerT::mpPlayer->mDirection){
					mPosition = CVector2(CPlayerT::mpPlayer->mPosition.x - BOSSTELEPO, CPlayerT::mpPlayer->mPosition.y);
					mDirection = true;
				}
				else{
					mPosition = CVector2(CPlayerT::mpPlayer->mPosition.x + BOSSTELEPO, CPlayerT::mpPlayer->mPosition.y);
					mDirection = false;
				}
			}
			//�A���t�@�l�����l�𒴂��Ă���Ƃ�
			if (mAlpha >= 1.0){
				if (mBossAnimeFream > 4){
					//������A�j�[���[�V�������ŏ��ɖ߂�
					mBossAnimeFreamT = 4;
					mBossAnimeFream = 0;
					mAttackBehavior = EATTACK;
				}
			}
			//�A���t�@�l�����l��������Ă��鎞
			else{
				//������܂ŉ��Z����
				mAlpha += 0.03;
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
					//�J�E���g��0�ɂȂ�����
					if (mBossAttackItr <= 0){
						mBossAnimeFreamT = 4;
						//�����铮��ɂ͂�������o������A�j���[�V�������ŏ��ɂ��ǂ�
						mBossAnimeFream = 0;
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

		else if (mBossLife > 0) {
			if (mBossAnimeFream > 1){
				mAttackBehavior = EIDOL;
			}
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
				CGame2::mTime = CTime::GetTime();
				CScore::GetScore();
				return;
			}
		}
		return;
		break;
		//�_���[�W�����I��

		//�K�[�h����
	case EGUARD:
		//�����U�����̃o�O�C���ׁ̈A�A���t�@�l�����MAX�ɂ���
		mAlpha = 1.0f;
		//�����ŃK�[�h�������ɉ�����������w��
		if (!mDirection)
			mVelocityX = 4;
		else
			mVelocityX = -4;
		//�v���C���[�����˂������[���[���v���C���[�ɖ߂�����A
		//�G�̏�Ԃ�ҋ@��ԂɈڍs
		if (CPlayerT::mpPlayer->mpWeapon == 0){
			mBossAnimeFream = 0;
			mAttackBehavior = EIDOL;
		}

		if (CBossGimmick::mpBossGimmick != NULL && CBossGimmick::mpBossGimmick->mGimmickFlg){
			//�{�X�����ɂ���Ƃ�
			if (mPosition.x<CMapScroll::mpScroll->mPosition.x){
				//�v���C���[�����ɂ���Ƃ�
				if (CPlayerT::mpPlayer->mPosition.x < CMapScroll::mpScroll->mPosition.x){
					//�{�X���E�Ɍ�������
					mDirection = true;
				}
				//�v���C���[���E�ɂ���Ƃ�
				else{
					//�{�X�����Ɍ�������
					mDirection = false;
					break;
				}
			}
			//�{�X���E�ɂ���Ƃ�
			else{
				//�v���C���[���E�ɂ���Ƃ�
				if (CPlayerT::mpPlayer->mPosition.x > CMapScroll::mpScroll->mPosition.x){
					//�{�X�����ɂނ�����
					mDirection = false;
				}
				//�v���C���[�����ɂ���Ƃ�
				else{
					//�{�X���E�Ɍ�������
					mDirection = true;
					break;
				}
			}
			mAttackBehavior = EJUMP;
		}
		break;
		//�K�[�h�����I��

	case EAVOIDANCE:

		break;
	}
}
//-----------------------------------------------------Boss_A_BehP�����I��------------------------------------------------------------------

//-----------------------------------------------------Update�����J�n-----------------------------------------------------------------------
/*
�X�V�������s��
�s���ȊO�ōׂ��ȕύX��ǉ��͂�����
*/
void CBoss::Update(){
	if (CMapBossRoomSign::mpBossRoomSign != NULL && CMapBossRoomSign::mpBossRoomSign->mColFlg && mBossBattle){
		if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
			printf("%d\n", mBossSpeedUp);
			//���Ԋu�ŃW�����v�̗������o��(�Ƃ肠����1�b�Ɉ��)
			if (mBossJcnt < BOSSJUMPTIME)
				mBossJcnt++;
			//��莞�Ԍo�߂���Ɨ������o��
			else{
				mBossJumprad = GetRand(7);
				mBossJcnt = NULL;
			}
			//�W�����v�̏��������܂�

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
			//�_���[�W���󂯂����ɍs�����������܂�

			//�{�X�̊����@��
			if (mVelocityX > 0.0f)
				mVelocityX -= 0.25f;

			if (mVelocityX < 0.0f)
				mVelocityX += 0.25f;


			mPosition.x += mVelocityX;
			//�{�X�̊����@�������܂�

			//�{�X�̌���HP�̊������o������
			mBossLifeProportion = static_cast <float> (mBossLife) / static_cast <float> (mBossMaxLife);

			//HP��50%�ȉ��A20%���傫�����̓X�s�[�h��2�グ��
			if (mBossLifeProportion<=0.5&&mBossLifeProportion>0.2)
				mBossSpeedUp = 2;
			//HP��20%�ȉ��ɂȂ�ƃX�s�[�h��3�グ��
			else if (mBossLifeProportion<=0.2)
				mBossSpeedUp = 3;

			if (mBossLife <= 0)
				mAttackBehavior = EDOWN;

			//���s������
			Boss_A_BehP();

			//�d�͏���
			Gravity();

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
}
//-----------------------------------------------------Update�����I��-----------------------------------------------------------------------



//-----------------------------------------------------Collision�����J�n--------------------------------------------------------------------
/*
�����蔻�菈�����s��
�����蔻���ύX�A�ǉ��͂�����
*/
bool CBoss::Collision(CRectangle*p){
	if (p->GetEnabled()){
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			switch (p->mTag){
			case ECELLNUM::EUNDER:
				if ((mPosition.y > p->mPosition.y)&&mVelocityY<=0.0){
					mVelocityY = 0.0f;
					mPosition.y = mPosition.y + aj.y;
				}
				break;
			case ECELLNUM::EPWEAPON://�v���C���[�̃��[���[�ƏՓ˂�����
				//�{�X�����G��ԁA�W�����v���A�_�E�����A�����U���̂����ꂩ�̏�Ԃ̎��͔��肵�Ȃ�
				if (Invincible || mAttackBehavior == EJUMP || mAttackBehavior == EDOWN || mAttackBehavior == ETELEPO)
					return false;
				//�A���t�@�l��MAX�l�������������͍U���̓q�b�g���Ȃ�
				else if (mAlpha < 1.0)
					return false;
				//�{�X�ƌ����������Ă��鎞�Ƀ��[���[�ōU������ƃK�[�h������
				else if (CPlayerT::mpPlayer->mDirection != mDirection){
					if (mpBWeapon)
						mpBWeapon->mPosition = CVector2(mPosition.x, mPosition.y);
					mAttackBehavior = EGUARD;
					return false;
				}
				//���G���Ԃ̃t���O��OFF�̎��Ƀ_���[�W�����Z����
				else  if(!Invincible){
					if (mpBWeapon)
						mpBWeapon->mPosition = CVector2(mPosition.x, mPosition.y);
					mVelocityY = 0.0f;
					mBossLife--;
					//���G���Ԃ̃t���O��ON�ɂ���
					Invincible = true;
					//�U�����󂯂����̃A�j���[�V����������
					//���񐔈ȏ�̍U�����󂯂ĂȂ����ɃA�j���[�V���������
					if (mAttackBehavior != EDOWN){
						mAttackBehavior = EDAMAGE;
					}
				}
				if (CPlayerT::mpPlayer->mpWeapon->mPosition.x > mPosition.x)
					mDirection = true;
				else
					mDirection = false;
				break;

			case ECELLNUM::EBOX:
			case ECELLNUM::ESTEEL:
				//�������̃I�u�W�F�N�g�ƐڐG�����ꍇ
				if (p->mBreak){

					if (mAttackBehavior == EJUMP || Invincible || mAttackBehavior == EDOWN || mAlpha < 1.0)
						break;

					//���G���Ԃ̃t���O��OFF�̎��Ƀ_���[�W�����Z����
					else if (!Invincible){
						mVelocityY = 0.0f;
						mBossLife -= static_cast <float> (mBossMaxLife)* 0.2;
						//���G���Ԃ̃t���O��ON�ɂ���
						Invincible = true;
						//�U�����󂯂����̃A�j���[�V����������
						//���񐔈ȏ�̍U�����󂯂ĂȂ����ɃA�j���[�V���������
						if (mAttackBehavior != EDOWN&&mAttackBehavior != ETELEPO){
							if (mpBWeapon)
								mpBWeapon->mPosition = CVector2(mPosition.x, mPosition.y);
							mAttackBehavior = EDAMAGE;
						}
					}
				}
				break;

			case ECELLNUM::EBWEAPON:
				if (mAttackBehavior==EATTACK)
				mAttackBehavior = EIDOL;
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
//-----------------------------------------------------Collision�����I��--------------------------------------------------------------------



//-----------------------------------------------------Render�����J�n-----------------------------------------------------------------------
/*
�A�j���[�V�����̑�����V���ɒǉ��A�ύX�͂�����
*/
void CBoss::Render(){
	switch (mAttackBehavior){

	case EIDOL://�ҋ@���
		// �A�j���[�V�����̖��� - 1���w�肵�A���̖����𒴂�����
		if (mBossAnimeFream > 2)
		//�A�j���[�V�����̍ŏ��ɖ߂�
		mBossAnimeFream = 0;
		//�A�j���[�V�����̑������w��(���l:�����A�j���[�V����,���l:�x���A�j���[�V����)
		Boss_Ani_Count_Frame = 10 - mBossSpeedUp;
		if (!mDirection)//������
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2304, 2048, mAlpha);
		else			//�E����
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2304, 2048, mAlpha);
		break;

	case EMANTO://�}���g�A�j���[�V����
		//�e�N�X�`���̖���-1�����l���傫���Ȃ��
		if (mBossAnimeFream > 4)
			//���[�v�̐擪�ɖ߂�
			mBossAnimeFream = 0;
		//���̃R�}�ɍs���^�C�~���O
		Boss_Ani_Count_Frame = 5;

		if (!mDirection)	//������
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
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

			Boss_Ani_Count_Frame = 10;

			if (!mDirection)	//������
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1536, 1280, mAlpha);
			else				//�E����
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1536, 1280, mAlpha);
		}
		//�W�����v������
		else if (mVelocityY < -0.1f){
			mBossAnimeFream = 0;

			if (!mDirection)	//������
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1792, 1536, mAlpha);
			else				//�E����
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1792, 1536, mAlpha);
		}
		//���n�n�_
		else if (mVelocityY==0.0){
			//�A�j���[�V�����̖���-1���w�肵�A���̖����𒴂�����
			if (mBossAnimeFream > 4)
				mBossAnimeFream = 4;//���[�v�J�n�ʒu(1���ڂ̃A�j���[�V����)�ɖ߂�

			//�A�j���[�V�����̑������w��(���l:�����A�j���[�V����,���l:�x���A�j���[�V����)
			Boss_Ani_Count_Frame = 5;

			if (!mDirection)//������
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 1792, 1536, mAlpha);

			else			//�E����
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream+1) * 256, 1792, 1536, mAlpha);
		}
		break;

	case EATTACK://�U��
		if (mpBWeapon != NULL)
			mBossAnimeFream = 3;
		else{
			if (mBossAnimeFream > 2)
				mBossAnimeFream = 3;
		}
		Boss_Ani_Count_Frame = 5-mBossSpeedUp;

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
			Boss_Ani_Count_Frame = 6 - mBossSpeedUp;

			if (!mDirection)	//������
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFreamT + 1) * 256, mBossAnimeFreamT * 256, 512, 256, mAlpha);
			else				//�E����
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFreamT * 256, (mBossAnimeFreamT + 1) * 256, 512, 256, mAlpha);
		}
		else if (mTelepoEnabled){
			if (mAlpha <=1.0f){
				mBossAnimeFreamT = 0;

				if (!mDirection)	//������
					mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFreamT + 1) * 256, mBossAnimeFreamT * 256, 512, 256, mAlpha);
				else				//�E����
					mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFreamT * 256, (mBossAnimeFreamT + 1) * 256, 512, 256, mAlpha);
			}
			else{
				//�e�N�X�`���̖���-1�����l���傫���Ȃ��
				if (mBossAnimeFream > 4)
					//���[�v�̐擪�ɖ߂�
					mBossAnimeFream = 0;
				//���̃R�}�ɍs���^�C�~���O
				Boss_Ani_Count_Frame = 5 - mBossSpeedUp;

				if (!mDirection)	//������
					mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
				else				//�E����
					mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 512, 256, mAlpha);
			}
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

	case EGUARD://�K�[�h������
		//�w��e�N�X�`���̖����𒴂�����
		if (mBossAnimeFream > 0)
			//�Ō�̉摜�ŌŒ肷��
			mBossAnimeFream = 0;
		if (!mDirection)	//������
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
		else				//�E����
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 512, 256, mAlpha);
		break;
	}
	//���̃R�}�ɍs���ׂɉ��Z����
	Boss_Ani_Count++;
	//��R�}�̃t���[���������傫���Ȃ��
	if (Boss_Ani_Count > Boss_Ani_Count_Frame){
		//���̃R�}�ɍs��
		mBossAnimeFream++;
		if (mAttackBehavior == ETELEPO)
			mBossAnimeFreamT--;
		//�J�E���g�����Z�b�g����
		Boss_Ani_Count = 0;
	}
}
//-----------------------------------------------------Render�����I��-----------------------------------------------------------------------