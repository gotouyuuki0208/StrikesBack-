//==========================
// 
// �{�X[boss.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "boss.h"
#include "manager.h"
#include "model.h"
#include "weapon.h"
#include "bosshpgauge.h"
#include "bossState.h"
#include "bat.h"
#include "collision.h"

//�ÓI�����o������
const int CBoss::PRIORITY = 1;//�`�揇
const int CBoss::GUARD_PROBABILITY = 60;//�v���C���[���f��̎��K�[�h����m��
const int CBoss::NEAR_ACTION_COUNT = 240;//�v���C���[���߂��Ƃ��ɂ���s���̒���
const int CBoss::HITATTACK_PROBABILITY = 80;//�v���C���[���߂��Ƃ��ɉ���m��
const int CBoss::WEAPONATTACK_PROBABILITY = 70;//���킪�߂��Ƃ��ɕ���U������m��
const int CBoss::ATTACKFINISH_COOLTIME = 300;//�U���I����̃N�[���^�C��
const float CBoss::GUARD_DISTANCE = 5.0f;//��鋗��

//==========================
//�R���X�g���N�^
//==========================
CBoss::CBoss(int nPriority):
CEnemy(nPriority),//���R���X�g���N�^
m_weapon(nullptr),//����̏��
m_HaveWeapon(nullptr),//�����Ă镐��
m_FlameCount(0),//�U���̃t���[�������J�E���g
m_NearCount(0),//�v���C���[���߂Â������̍s���̃J�E���g
m_NearAction(false),//�v���C���[���߂Â������̍s�������Ă��邩����
m_StateMachine(nullptr),//��ԊǗ�
m_NextAttack(true),//���̍U��(false:�f�� true:����)
m_Guard(false),//�K�[�h����
m_weaponbreak(false)//����j�󔻒�
{
	
}

//==========================
//�f�X�g���N�^
//==========================
CBoss::~CBoss()
{

}

//==========================
//����������
//==========================
HRESULT CBoss::Init()
{
	//�����ݒ�
	CEnemy::Init();

	//HP�Q�[�W�̐���
	CManager::GetInstance()->GetHudManager()->CreateBossHPGauge();

	//��ԊǗ��N���X�̍쐬
	m_StateMachine = DBG_NEW CStateMachine;
	auto NewState = DBG_NEW CBossDirectionState;
	ChangeState(NewState);

	if (GetPlayer() != nullptr)
	{//�v���C���[�Ƀ{�X�̏�����������
		GetPlayer()->GetBoss(this);
	}

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBoss::Uninit()
{
	
	if (!CManager::GetInstance()->GetDebug()->GetEdit())
	{
		//�v���C���[�����{�X�̏����폜
		GetPlayer()->GetBoss(nullptr);

		if (CManager::GetInstance()->GetGameManager()->GetGame() == CGameManager::GAME::NONE)
		{
			CManager::GetInstance()->GetGameManager()->SetGame(CGameManager::GAME::CLEAR);
		}
	}
	
	//�I������
	CEnemy::Uninit();

	if (m_weapon != nullptr)
	{
		m_weapon = nullptr;
	}

	if (m_StateMachine != nullptr)
	{
		delete m_StateMachine;
		m_StateMachine = nullptr;
	}
}

//==========================
//�X�V����
//==========================
void CBoss::Update()
{
	//���[�V�����̍X�V
	MotionUpdate();

	//�X�e�[�g�̍X�V
	m_StateMachine->Update();

	//�X�V����
	CEnemy::Update();

	if (!GetAttackable())
	{//�U���ł��Ȃ��Ƃ�

		//�N�[���^�C�������炷
		SubCoolTime();

		if (GetCoolTime() <= 0)
		{//�N�[���^�C�����Ȃ��Ȃ���

			//���̍U����ݒ�
			ChoiceAttack();

			//�U���\�ɂ���
			ChangeAttackable();
		}
	}

	//HP�Q�[�W�̍X�V
	CManager::GetInstance()->GetHudManager()->ChangeBossHP(GetLife());

	if (GetLife() <= 0)
	{//���C�t���Ȃ�

		//�I������
		Uninit();
	}

}

//==========================
//�`�揈��
//==========================
void CBoss::Draw()
{
	//�`�揈��
	CEnemy::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBoss* CBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CBoss* pBoss = DBG_NEW CBoss;

	//�ʒu�̐ݒ�
	pBoss->SetPos(pos);

	//����������
	pBoss->Init();

	//�����̐ݒ�
	pBoss->SetLife(50);

	//�t�@�C����ǂݍ���
	pBoss->LoadFile("data\\MOTION\\boss.txt", scale);

	//���a�̐ݒ�
	pBoss->SetRadius(15.0f);

	//��ނ̐ݒ�
	pBoss->SetType(TYPE::ENEMY);

	//�G�̎�ނ�ݒ�
	pBoss->SetEnemyType(ENEMY_TYPE::BOSS);

	//�{�X�ɕ������������
	pBoss->InitHaveWeapon();

	return pBoss;
}

//==========================
//���[�V�����̍X�V
//==========================
void CBoss::MotionUpdate()
{
	//�p�[�c�̐��l�̌v�Z
	CalParts();

	if (m_HaveWeapon != nullptr)
	{//����������Ă�
		if (m_HaveWeapon->GetGrab())
		{
			m_HaveWeapon->SetRot(CalMotionRot(15));
			m_HaveWeapon->SetPos(CalMotionPos(15));
		}
	}

	//���[�V�����J�E���^�[��i�߂�
	MotionCountUpdate();

	if (ExceedMaxFlame())
	{//���[�V�����̃J�E���^�[���Đ��t���[���𒴂����Ƃ�

		if (m_HaveWeapon != nullptr)
		{//����������Ă�
			if (m_HaveWeapon->GetGrab())
			{
				KeepFirstPos(m_HaveWeapon->GetPos(), 15);
				KeepFirstRot(m_HaveWeapon->GetRot(), 15);
			}
		}
	}

	//���[�V�����̏����X�V
	UpdateMotionInfo();
}

//==========================
//��Ԃ�ύX
//==========================
void CBoss::ChangeState(CBossStateBase* NewState)
{
	//state�̏��L�҂�ݒ�
	NewState->SetOwner(this);

	//state��ύX
	m_StateMachine->ChangeState(NewState);
}

//==========================
//�U���̎�ނ�I��
//==========================
void CBoss::ChoiceAttack()
{
	//�߂������T��
	FindNearbyWeapons();

	if (m_weapon == nullptr
		&&m_HaveWeapon==nullptr)
	{//���킪���݂��Ă��Ȃ�

		//�U�����@��f��U���ɕύX
		m_NextAttack = false;

		return;
	}
	
	//�����_���Ȑ��l���擾
	int Attack = RandomNum();

	//�v���C���[�ƕ���̂ǂ��炪�߂�������
	bool Near = MeasureDistance();

	if (!Near)
	{//���킪�߂�

		if (Attack <= WEAPONATTACK_PROBABILITY)
		{//����U������

			//�U�����@�𕐊�U���ɕύX
			m_NextAttack = true;
		}
		else
		{
			//����������Ă�����̂Ă�
			ReleseWeapon();

			//�U�����@��f��U���ɕύX
			m_NextAttack = false;
		}
	}
	else
	{//�v���C���[���߂�

		if (Attack <= HITATTACK_PROBABILITY)
		{//�f��U������

			//����������Ă�����̂Ă�
			ReleseWeapon();

			//�U�����@��f��U���ɕύX
			m_NextAttack = false;
		}
		else
		{
			//�U�����@�𕐊�U���ɕύX
			m_NextAttack = true;
		}
	}
}

//==========================
//���̍U�����@���擾
//==========================
bool CBoss::GetNextAttack()
{
	return m_NextAttack;
}

//==========================
//����U���̈ړ�����
//==========================
void CBoss::WeaponMove()
{
	if (!GetWeapon())
	{//���킪���݂��Ă��邩�͂܂�Ă��Ȃ�

		//�����̐ݒ�
		float angle = atan2f(m_weapon->GetPos().x - GetPos().x, m_weapon->GetPos().z - GetPos().z);
		SetRot(D3DXVECTOR3(GetRot().x, angle + D3DX_PI, GetRot().z));

		//�ړ��l��ݒ�
		SetMove(D3DXVECTOR3(sinf(angle) * DUSH_SPEED, 0.0f, cosf(angle) * DUSH_SPEED));

		//����Ƃ̓����蔻��
		ColisionWeapon();
	}
}

//==========================
//����Ƃ̓����蔻��
//==========================
void CBoss::ColisionWeapon()
{

	//�����蔻��
	bool Colision = Collision::Sphere(GetPos(),
		m_weapon->GetPos(),
		GetRadius(),
		m_weapon->GetRadius());

	if (Colision)
	{//�Փ˂��Ă���
		
		//������p�[�c�Ƃ��Đ���
		if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
		{//���蕐��
			
			//����̐e���f����ݒ�
			m_weapon->SetParent(GetParts(5));

			//�ʒu�ƌ�����ݒ�
			m_weapon->SetPos(D3DXVECTOR3(10.0f, -2.0f, -5.0f));
			m_weapon->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			//�����Ă镐��Ƃ��ĕۑ�
			m_HaveWeapon = m_weapon;
			m_weapon = nullptr;
		}
		else
		{
			//����̐e���f����ݒ�
			m_weapon->SetParent(GetParts(8));

			//�ʒu�ƌ�����ݒ�
			m_weapon->SetPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
			m_weapon->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			//�����Ă镐��Ƃ��ĕۑ�
			m_HaveWeapon = m_weapon;
			m_weapon = nullptr;
		}

		m_HaveWeapon->GrabCharacter();//�͂܂ꂽ��Ԃɂ���
	}
}

//==========================
//�߂������T��
//==========================
void CBoss::FindNearbyWeapons()
{
	if (m_HaveWeapon != nullptr)
	{//���łɕ���������Ă���
		return;
	}

	float distance = 0.0f;//����

	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CWeapon::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::WEAPON)
		{//�I�u�W�F�N�g������ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
			continue;
		}

		CWeapon* pWeapon = dynamic_cast<CWeapon*>(pObj);

		if (pWeapon->GetGrab())
		{//���킪�͂܂�Ă���
			pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
			continue;
		}

		float newdistance = (pWeapon->GetPos().x - GetPos().x)* (pWeapon->GetPos().x - GetPos().x) +
			(pWeapon->GetPos().z - GetPos().z)* (pWeapon->GetPos().z - GetPos().z);
		
		if (distance == 0.0f|| newdistance <= distance)
		{
			distance = newdistance;//������ۑ�
			m_weapon = pWeapon;//����̏���ۑ�
		}

		pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
	}
}

//==========================
//�����𑪂�
//==========================
bool CBoss::MeasureDistance()
{
	if (m_weapon == nullptr)
	{//���킪�Ȃ�
		return true;
	}

	//��ԋ߂�����Ƃ̋����𑪒�
	float WeaponDistance = (m_weapon->GetPos().x - GetPos().x) * (m_weapon->GetPos().x - GetPos().x) +
		(m_weapon->GetPos().z - GetPos().z) * (m_weapon->GetPos().z - GetPos().z);

	//�v���C���[�Ƃ̋����𑪒�
	float PlayerDistance = (GetPlayer()->GetPos().x - GetPos().x) * (GetPlayer()->GetPos().x - GetPos().x) +
		(GetPlayer()->GetPos().z - GetPos().z) * (GetPlayer()->GetPos().z - GetPos().z);

	if (WeaponDistance <= PlayerDistance)
	{//���킪�v���C���[���߂�
		return false;
	}

	return true;

}

//==========================
//�����_���Ȑ��l���擾
//==========================
int CBoss::RandomNum()
{
	//0����100�͈̔͂Ń����_���Ȑ��l���擾
	random_device rd;
	uniform_int_distribution<int> dist(1, 100);
	int random_number = dist(rd);

	return random_number;
}

//==========================
//����𗣂�
//==========================
void CBoss::ReleseWeapon()
{
	if (m_HaveWeapon != nullptr)
	{
		if (m_HaveWeapon->GetGrab())
		{//����������Ă�Ƃ�

			//�v���C���[��������̈ʒu���擾
			D3DXVECTOR3 pos = D3DXVECTOR3(m_HaveWeapon->GetMtxWorld()._41, 0.0f, m_HaveWeapon->GetMtxWorld()._43);
			m_HaveWeapon->SetParent(nullptr);
			m_HaveWeapon->ReleseCharacter(pos);//��������
			m_HaveWeapon->CorrectInfo();
			m_HaveWeapon = nullptr;//����̏����폜

			auto NewState = DBG_NEW CBossNeutralState;
			ChangeState(NewState);
		}
	}
}

//==========================
//�͂ޕ����ς���
//==========================
void CBoss::GrabChangeWeapon(CWeapon* weapon)
{
	if (m_weapon == nullptr
		|| m_weapon != weapon)
	{//�͂ޕ��킪�Ȃ����͂܂ꂽ���킪�͂ޕ���ƈႤ����̂Ƃ�
		return;
	}

	//�ʂ̕����T��
	m_weapon = nullptr;
	FindNearbyWeapons();
}

//==========================
//������������Ă��邩����
//==========================
bool CBoss::GetWeapon()
{
	if (m_HaveWeapon != nullptr)
	{
		return true;
	}

	return false;
}

//==========================
//����̃^�C�v���擾
//==========================
bool CBoss::GetWeaponType()
{
	if (m_HaveWeapon->GetWeaponType() == CWeapon::WEAPONTYPE::SMALL)
	{//���킪�Ў蕐��
		return false;
	}
	else if (m_HaveWeapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
	{//���蕐��
		return true;
	}
}

//==========================
//�U����e����
//==========================
bool CBoss::hit(D3DXVECTOR3 pos, int damage,MOTION_TYPE hitmotion)
{
	
	if (GetDamageNum() >= 3 || GetHitMotion() == hitmotion)
	{//3��U�����󂯂Ă�

		return false;
	}

	//��e�񐔂𑝂₷
	AddDamegeNum();

	//���[�V������ۑ�
	SetHitMotion(hitmotion);

	//�_���[�W�̐��l���擾
	int DamageNum = damage;

	//���݂̏�Ԃ��擾
	auto State = m_StateMachine->GetState();

	if (typeid(*State) == typeid(CGuardState))
	{//�K�[�h��Ԃ̎�

		//�_���[�W�����炷
		DamageNum /= 2;
	}
	else if (typeid(*State) == typeid(CSmallWeaponGuardState))
	{//����K�[�h��Ԃ̎�

		//�_���[�W�����炷
		DamageNum /= 2;

		//����̑ϋv�����炷
		WeaponDamage();
	}

	//���C�t�����炷
	int Life = GetLife();
	SetLife(Life -= DamageNum);

	if (typeid(*State) != typeid(CGuardState))
	{//�K�[�h��Ԃł͂Ȃ�
		Damage();

		if (GetDamageNum() >= 3)
		{//3���e���Ă���
			DamegeBlow(pos);
		}
	}

	return true;
}

//==========================
//����̑ϋv�l�����炷
//==========================
void CBoss::WeaponDamage()
{
	//����̑ϋv�l�����炷
	m_HaveWeapon->SubDurability();

	if (m_HaveWeapon->GetDurability() <= 0)
	{//�ϋv�l���Ȃ��Ȃ����Ƃ�
		DeleteParts(15);

		//������폜����
		CManager::GetInstance()->GetStageManager()->DeleteObj(*m_HaveWeapon);
		m_HaveWeapon->Uninit();
		m_HaveWeapon = nullptr;

		m_weaponbreak = true;
	}
}

//==========================
//�K�[�h�̏������Z�b�g
//==========================
void CBoss::GuardReset()
{
	//�߂��̂Ƃ��̍s�������Ă��Ȃ�
	m_NearAction = false;

	//�K�[�h���Ȃ���ԂɕύX
	m_Guard = false;
}

//==========================
//�v���C���[���߂��Ƃ��̍s��
//==========================
void CBoss::PlayerNearAction()
{
	if (m_NearAction)
	{
		return;
	}

	//�v���C���[���߂��Ƃ��̍s�������Ă�����
	m_NearAction = true;

	//�����_���Ȑ������擾
	int Action = RandomNum();

	if (Action <= GUARD_PROBABILITY)
	{//�������K�[�h����m���̐�����菬����

		//�K�[�h����
		m_Guard = true;
	}
	else
	{
		//�K�[�h���Ȃ�
		m_Guard = false;
	}
}

//==========================
//�K�[�h���邩�擾
//==========================
bool CBoss::GetGuard()
{
	return m_Guard;
}

//==========================
//�K�[�h���鋗���ɂ��邩����
//==========================
bool CBoss::JudgeGuard()
{
	if (Collision::Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius()* GUARD_DISTANCE))
	{//�v���C���[���K�[�h���鋗���ɂ���

		return true;
	}

	return false;
}

//==========================
//�ŏ��ɕ������������
//==========================
void CBoss::InitHaveWeapon()
{
	//�o�b�g����������
	m_HaveWeapon = CBat::Create({ 0.0f,0.0f,0.0f }, { 1.5f,1.5f,1.5f }, { 0.0f,0.0f,0.0f });

	//����̐e���f����ݒ�
	m_HaveWeapon->SetParent(GetParts(8));

	//�ʒu�ƌ�����ݒ�
	m_HaveWeapon->SetPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
	m_HaveWeapon->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�͂܂ꂽ��Ԃɂ���
	m_HaveWeapon->GrabCharacter();

}

//==========================
//�_���[�W����
//==========================
void CBoss::Damage()
{
	SetDamage(true);

	if (GetLife() <= 0)
	{
		if (CManager::GetInstance()->GetGameManager()->GetGame() == CGameManager::GAME::NONE)
		{
			CManager::GetInstance()->GetGameManager()->SetGame(CGameManager::GAME::CLEAR);
		}
	}
}

//==========================
//����U���̓����蔻��
//==========================
void CBoss::ColisionWeaponAttack()
{
	if (m_HaveWeapon == nullptr)
	{
		return;
	}

	bool Colision = Collision::Sphere(D3DXVECTOR3(m_HaveWeapon->GetMtxWorld()._41, m_HaveWeapon->GetMtxWorld()._42, m_HaveWeapon->GetMtxWorld()._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		30.0f,
		30.0f);

	
	if (Colision && !GetAttack())
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_WEAOPNATTACK);
		SetAttack();

		GetPlayer()->hit(GetPos(),2);
		
		WeaponDamage();
	}
}

//==========================
//���킪��ꂽ���擾
//==========================
bool CBoss::GetWeaponBreak()
{
	return m_weaponbreak;
}

//==========================
//����j�󔻒�����Z�b�g
//==========================
void CBoss::BreakReset()
{
	m_weaponbreak = false;
}