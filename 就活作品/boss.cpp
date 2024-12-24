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

//�ÓI�����o������
const int CBoss::PRIORITY = 1;//�`�揇
const int CBoss::GUARD_PROBABILITY = 60;//�v���C���[���f��̎��K�[�h����m��
const int CBoss::NEAR_ACTION_COUNT = 240;//�v���C���[���߂��Ƃ��ɂ���s���̒���
const int CBoss::HITATTACK_PROBABILITY = 80;//�v���C���[���߂��Ƃ��ɉ���m��
const int CBoss::WEAPONATTACK_PROBABILITY = 70;//���킪�߂��Ƃ��ɕ���U������m��
const int CBoss::ATTACKFINISH_COOLTIME = 300;//�U���I����̃N�[���^�C��
const float CBoss::DUSH_DISTANCE = 10.0f;//���鋗��
const float CBoss::WALK_DISTANCE = 5.0f;//��������
const float CBoss::GUARD_DISTANCE = 3.0f;//��鋗��
const float CBoss::DUSH_SPEED = 3.5f;//���鑬��
const float CBoss::WALK_SPEED = 2.0f;//��������
//==========================
//�R���X�g���N�^
//==========================
CBoss::CBoss(int nPriority):
CEnemy(nPriority),//���R���X�g���N�^
m_weapon(nullptr),//����̏��
m_Attack(false),//�U������
m_AttackCoolTime(0),//�U���̃N�[���^�C��
m_FlameCount(0),//�U���̃t���[�������J�E���g
m_AttackNum(0),//�U����
Attackable(true),//�U���\������
m_ComboStack{},//�U���R���{�̃X�^�b�N
m_StackIdx(0),//�X�^�b�N��TOP�̈ʒu
m_Angle(0.0f),//����
m_NearCount(0),//�v���C���[���߂Â������̍s���̃J�E���g
m_NearAction(false),//�v���C���[���߂Â������̍s�������Ă��邩����
m_BossHPGauge(nullptr)
{
	SetComboList();//�R���{���X�g�̐���
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

	//�U�����@��ݒ�
	SetAttackState(ATTACK_STATE::ATTACK);

	if (GetPlayer() != nullptr)
	{
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

	if (m_BossHPGauge != nullptr)
	{
		m_BossHPGauge = nullptr;
	}

	if (m_weapon != nullptr)
	{
		m_weapon = nullptr;
	}

}

//==========================
//�X�V����
//==========================
void CBoss::Update()
{
	if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		return;
	}

	if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
	{
		Count();//�J�E���g����

		if (!GetDamage())
		{//�_���[�W��Ԃ���Ȃ���

			
			if(GetAttackState() == ATTACK_STATE::WEAPONATTACK)
			{
				WeaponMove();//����U�����̍s����ݒ�
			}
			else
			{
				MoveAction();//�ړ����̍s����ݒ�
			}
			Move();//�ړ�����
			Attack();//�U������
		}
			Guard();//�K�[�h����
	}
	
	if (CManager::GetInstance()->GetDebug()->GetPlayerTest())
	{
		ChangeDirection();
	}

	//�X�V����
	CEnemy::Update();

	if (m_BossHPGauge != nullptr)
	{
		m_BossHPGauge->SetHP(GetLife());
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

	//HP�Q�[�W�̐���
	pBoss->m_BossHPGauge = CBossHPGauge::Create(D3DXVECTOR3(1200.0f, 680.0f, 0.0f), 10, 200, pBoss->GetLife());

	//�t�@�C����ǂݍ���
	pBoss->LoadFile("data\\MOTION\\boss.txt", scale);

	//���a�̐ݒ�
	pBoss->SetRadius(15.0f);

	//��ނ̐ݒ�
	pBoss->SetType(TYPE::ENEMY);

	//�G�̎�ނ�ݒ�
	pBoss->SetEnemyType(ENEMY_TYPE::BOSS);

	return pBoss;
}

//==========================
//�U���̎�ނ�I��
//==========================
void CBoss::ChoiceAttack()
{
	//�߂������T��
	FindNearbyWeapons();

	if (m_weapon == nullptr)
	{//���킪���݂��Ă��Ȃ�

		//�U�����@��ݒ�
		SetAttackState(ATTACK_STATE::ATTACK);

		return;
	}
	
	//�����_���Ȑ��l���擾
	int Attack = RandomNum();

	//�v���C���[�ƕ���̂ǂ��炪�߂�������
	bool Near = MeasureDistance();

	if (!Near)
	{//���킪�߂�

		if (Attack <= WEAPONATTACK_PROBABILITY
			||GetPartsExistence(15))
		{
			//�U�����@��ݒ�
			SetAttackState(ATTACK_STATE::WEAPONATTACK);
		}
		else
		{
			//�U�����@��ݒ�
			SetAttackState(ATTACK_STATE::ATTACK);
			ReleseWeapon();
		}
	}
	else
	{//�v���C���[���߂�

		if (Attack <= HITATTACK_PROBABILITY
			&& !GetPartsExistence(15))
		{
			//�U�����@��ݒ�
			SetAttackState(ATTACK_STATE::ATTACK);
			ReleseWeapon();
		}
		else
		{
			//�U�����@��ݒ�
			SetAttackState(ATTACK_STATE::WEAPONATTACK);
		}
	}
}

//==========================
//�ړ�����
//==========================
void CBoss::Move()
{
	if (GetState() != STATE::USUALLY)
	{//�U����Ԃ̎��I��
		return;
	}

	//�O��̈ʒu��ۑ�
	SetPosOld(GetPos());

	SetMove(D3DXVECTOR3(GetMove().x += (0 - GetMove().x) * 0.25f,
		GetMove().y,
		GetMove().z += (0 - GetMove().z) * 0.25f));

	//�ʒu��ύX
	SetPos(GetPos() + GetMove());

	//���[�V������ݒ�
	SetOldMotion(GetMotion());
}

//==========================
//�ړ����̍s��
//==========================
void CBoss::MoveAction()
{
	if ((GetState() != STATE::USUALLY)
		|| m_AttackCoolTime > (ATTACKFINISH_COOLTIME - 60))
	{//�ʏ��ԈȊO�̎��܂��͍U���I�����Ă���1�b�����Ă��Ȃ����I��
		return;
	}
	
	if (!ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * DUSH_DISTANCE))
	{//�v���C���[�̔��a��10�{�̋�����艓��

		//�ړ��l��ݒ�
		SetMove(D3DXVECTOR3(sinf(m_Angle) * DUSH_SPEED, 0.0f, cosf(m_Angle) * DUSH_SPEED));

		//���[�V������ݒ�
		SetMotion(MOTION_TYPE::DUSH);

		if(m_NearAction)
		{
			m_NearAction = false;
			m_NearCount = 0;
		}
	}
	else if (!ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * WALK_DISTANCE))
	{//�v���C���[�̔��a��5�{�̋�����艓��

		//�ړ��l��ݒ�
		SetMove(D3DXVECTOR3(sinf(m_Angle) * WALK_SPEED, 0.0f, cosf(m_Angle) * WALK_SPEED));

		//���[�V������ݒ�
		SetMotion(MOTION_TYPE::MOVE);
		if (m_NearAction)
		{
			m_NearAction = false;
			m_NearCount = 0;
		}
	}
	else if (Attackable
		&& !ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() + 2.0f))
	{//�U���\���v���C���[��艓��

		//�ړ��l��ݒ�
		SetMove(D3DXVECTOR3(sinf(m_Angle) * WALK_SPEED, 0.0f, cosf(m_Angle) * WALK_SPEED));

		//���[�V������ݒ�
		SetMotion(MOTION_TYPE::MOVE);
	}
	else if (Attackable
		&& ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() + 2.0f))
	{
		SetState(STATE::ATTACK);
	}
	else
	{
		if (ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * GUARD_DISTANCE))
		{//�v���C���[�̔��a��3�{�̋����ɂ���
			if (!m_NearAction)
			{
				PlayerNearAction();
			}
		}
		else
		{
			//�ړ��l��ݒ�
			SetMove(D3DXVECTOR3(sinf(m_Angle) * 1.0f, 0.0f, cosf(m_Angle) * 1.0f));

			//���[�V������ݒ�
			SetMotion(MOTION_TYPE::MOVE);
		}
	}

	//�����̐ݒ�
	ChangeDirection();
}

//==========================
//����U���̈ړ�����
//==========================
void CBoss::WeaponMove()
{
	if ((GetState() != STATE::USUALLY)
		|| m_AttackCoolTime > (ATTACKFINISH_COOLTIME - 60))
	{//�ʏ��ԈȊO�̎��܂��͍U���I�����Ă���1�b�����Ă��Ȃ����I��
		return;
	}

	if (!GetPartsExistence(15)
		&& m_weapon!=nullptr)
	{
		//�����̐ݒ�
		float angle = atan2f(m_weapon->GetPos().x - GetPos().x, m_weapon->GetPos().z - GetPos().z);
		SetRot(D3DXVECTOR3(GetRot().x, angle + D3DX_PI, GetRot().z));

		//�ړ��l��ݒ�
		SetMove(D3DXVECTOR3(sinf(angle) * DUSH_SPEED, 0.0f, cosf(angle) * DUSH_SPEED));

		//���[�V������ݒ�
		SetMotion(MOTION_TYPE::DUSH);
		SetOldMotion(GetMotion());

		//����Ƃ̓����蔻��
		ColisionWeapon();
	}
	else
	{
		MoveAction();//�ړ����̍s����ݒ�
	}
}

//==========================
//�����̕ύX
//==========================
float CBoss::ChangeDirection()
{
	if (GetMotion() != MOTION_TYPE::GUARD)
	{
		//�i�ފp�x���v�Z
		m_Angle = atan2f(GetPlayer()->GetPos().x - GetPos().x, GetPlayer()->GetPos().z - GetPos().z);

		//������ݒ�
		SetRot(D3DXVECTOR3(GetRot().x, m_Angle + D3DX_PI, GetRot().z));
	}

	return m_Angle;
}

//==========================
//�U������
//==========================
void CBoss::Attack()
{
	if (GetState() != STATE::ATTACK || !Attackable)
	{//�U����ԈȊO�̎��܂��͍U���s��Ԃ̎��I��
		return;
	}

	if (GetOldMotion() == GetMotion())
	{//�O��̃��[�V�����ƍ��̃��[�V����������

		//���̃��[�V������ۑ�
		SetOldMotion(GetMotion());

		//�U�����[�V�����ɕύX
		SetMotion(Pop());
	}

	if (m_FlameCount >= 10)
	{
		if (GetPartsExistence(15))
		{
			ColisionWeaponAttack();
		}
		else
		{
			ColisionHitAttack();
		}
	}

	m_FlameCount++;

	bool Colision = ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), 17.0f);
	if (m_FlameCount >= 26 && Colision&& m_StackIdx > 0)
	{//�t���[������24�ȏォ�v���C���[���߂����R���{�ł���

			SetMotion(Pop());//���[�V�������Đ�
			m_FlameCount = 0;//�J�E���g���Ă��t���[���������Z�b�g
			m_Attack = false;//�U�����Ă��Ȃ���Ԃ̖߂�
			ChangeDirection();//������ς���
	}
	else if (m_FlameCount >= 24 &&(!Colision||m_StackIdx <= 0))
	{//�v���C���[�������܂��̓R���{�ł��Ȃ�
		
		SetOldMotion(GetMotion());//���̃��[�V������ۑ�
		SetState(STATE::USUALLY);//�ʏ��ԂɕύX
		SetAttackState(ATTACK_STATE::ATTACK);
		if (GetPartsExistence(15))
		{
			if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
			{
				SetMotion(MOTION_TYPE::WEAPONNEUTRAL);//���펝���ҋ@��ԂɕύX
			}
			else
			{
				SetMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//���펝���ҋ@��ԂɕύX
			}
		}

		ResetStak();//�R���{�̃X�^�b�N�����Z�b�g
		m_FlameCount = 0;//�t���[���������Z�b�g
		m_Attack = false;//�U����������Z�b�g
		Attackable = false;//�U���s���
		m_AttackCoolTime = ATTACKFINISH_COOLTIME;
	}
}

//==========================
//�U���̓����蔻��
//==========================
void CBoss::ColisionHitAttack()
{
	bool Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		GetRadius(),
		GetPlayer()->GetRadius());
	
	if (Colision && !m_Attack)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);
		GetPlayer()->Damage(1);
		m_Attack = true;

		if (m_StackIdx <= 0)
		{
			GetPlayer()->DamageBlow(GetPos());
		}
	}
}

//==========================
//����U���̓����蔻��
//==========================
void CBoss::ColisionWeaponAttack()
{
	bool Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(15)._41, GetPartsMtx(15)._42, GetPartsMtx(15)._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		30.0f,
		30.0f);

	if (Colision && !m_Attack)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_WEAOPNATTACK);
		GetPlayer()->Damage(1);
		m_Attack = true;

		if (m_StackIdx <= 0)
		{
			GetPlayer()->DamageBlow(GetPos());
		}

		if (m_weapon == nullptr)
		{
			return;
		}

		m_weapon->SubDurability();

		if (m_weapon->GetDurability() <= 0)
		{
			//����p�[�c���폜
			DeleteParts(15);
			SetMotion(MOTION_TYPE::NEUTRAL);//�ҋ@���[�V����
			SetComboList();

			//������폜
			m_weapon->Uninit();
			m_weapon = nullptr;
		}
	}
}

//==========================
//�U���\������
//==========================
bool CBoss::JudgeAttackable()
{
	if (m_AttackCoolTime < 240)
	{
		m_AttackCoolTime++;
		return false;
	}

	m_AttackCoolTime = 0;
	return true;
}

//==========================
//����Ƃ̓����蔻��
//==========================
void CBoss::ColisionWeapon()
{
	bool Colision = ColisionSphere(GetPos(),
		m_weapon->GetPos(),
		GetRadius(),
		m_weapon->GetRadius());

	if (Colision)
	{
		//������p�[�c�Ƃ��Đ���
		
		if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
		{
			SetParts(D3DXVECTOR3(10.0f, -2.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetParts(5), m_weapon->GetModelIdx(), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			m_weapon->GrabCharacter();
			SetMotion(MOTION_TYPE::WEAPONNEUTRAL);//�ҋ@���[�V����(���펝��)
		}
		else
		{
			SetParts(D3DXVECTOR3(-10.0f, .0f, .0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetParts(8), m_weapon->GetModelIdx(), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			m_weapon->GrabCharacter();
			SetMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//�ҋ@���[�V����(���펝��)
		}

		SetComboList();
	}
}

//==========================
//�߂������T��
//==========================
void CBoss::FindNearbyWeapons()
{
	if (m_weapon != nullptr)
	{
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
//�R���{���X�g�̐���
//==========================
void CBoss::SetComboList()
{
	
	if (!GetPartsExistence(15))
	{
		m_ComboList[0] = MOTION_TYPE::ATTACK;
		m_ComboList[1] = MOTION_TYPE::ATTACK2;
		m_ComboList[2] = MOTION_TYPE::ATTACK3;
	}
	else
	{
		if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
		{
			m_ComboList[0] = MOTION_TYPE::WEAPONATTACK;
			m_ComboList[1] = MOTION_TYPE::WEAPONATTACK2;
			m_ComboList[2] = MOTION_TYPE::WEAPONATTACK3;
		}
		else
		{
			m_ComboList[0] = MOTION_TYPE::SMALLWEAPONATTACK;
			m_ComboList[1] = MOTION_TYPE::SMALLWEAPONATTACK2;
			m_ComboList[2] = MOTION_TYPE::SMALLWEAPONATTACK3;
		}
	}

	ResetStak();//�X�^�b�N�̃��Z�b�g
}

//==========================
//�X�^�b�N�̏���߂�
//==========================
void CBoss::ResetStak()
{
	m_StackIdx = 0;
	for (int i = 2; i >= 0; i--)
	{
		Push(m_ComboList[i]);
	}
}

//==========================
//�f�[�^�̒ǉ�
//==========================
void CBoss::Push(MOTION_TYPE motion)
{
	if (m_StackIdx < 3)
	{
		m_ComboStack[m_StackIdx++] = motion;
	}
}

//==========================
//�f�[�^�̎��o��
//==========================
CMotionModel::MOTION_TYPE CBoss::Pop()
{
	if (m_StackIdx <= 0)
	{
		if (GetPartsExistence(15))
		{
			if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
			{
			return MOTION_TYPE::WEAPONNEUTRAL;
			}
			else
			{
				return MOTION_TYPE::SMALLWEAPONNEUTRAL;
			}
		}
		else
		{
			return MOTION_TYPE::NEUTRAL;
		}
	}

	return m_ComboStack[--m_StackIdx];

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
//�K�[�h����
//==========================
void CBoss::Guard()
{
	if (GetState() != STATE::GUARD)
	{
		return;
	}
	
	if (m_weapon != nullptr
		&& m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
	{
		return;
	}

	if (GetPartsExistence(15)) 
	{
		SetMotion(MOTION_TYPE::SMALLWEAPONGUARD);
	}
	else
	{
		SetMotion(MOTION_TYPE::GUARD);

	}

	if (!ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * GUARD_DISTANCE))
	{
		m_NearAction = false;
		m_NearCount = 0;
		SetState(STATE::USUALLY);
	}
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

	m_NearAction = true;

	int Action = RandomNum();
	if (Action <= GUARD_PROBABILITY)
	{
		Guard();
		SetState(STATE::GUARD);
	}
	else
	{
		SetMotion(MOTION_TYPE::NEUTRAL);
	}
}

//==========================
//�J�E���g����
//==========================
void CBoss::Count()
{
	if (m_NearAction)
	{//�v���C���[���߂Â����Ƃ��̍s�������Ă���
		m_NearCount++;
		if (m_NearCount >= NEAR_ACTION_COUNT
			&& GetPlayer()->GetState() != CPlayer::STATE::ATTACK)
		{
			m_NearAction = false;
			m_NearCount = 0;
			SetState(STATE::USUALLY);
		}
	}

	if (!Attackable)
	{//�U���ł��Ȃ��Ƃ�

		m_AttackCoolTime--;

		if (m_AttackCoolTime <= 0)
		{
			Attackable = true;
			m_AttackCoolTime = 0;
			ChoiceAttack();//���̍U�������߂�
		}
	}	
}

//==========================
//����𗣂�
//==========================
void CBoss::ReleseWeapon()
{
	if (GetPartsExistence(15))
	{//����������Ă�Ƃ�

		//����p�[�c���폜
		DeleteParts(15);

		m_weapon->ReleseCharacter(D3DXVECTOR3(GetParts(14)->GetMtxWorld()._41,0.0f, GetParts(14)->GetMtxWorld()._43));
		m_weapon = nullptr;

		SetComboList();
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