//==========================
// 
// ����G[weaponenemy.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "weaponenemy.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CWeaponEnemy::PRIORITY = 1;//�`�揇
const int CWeaponEnemy::NEAR_ACTION_COUNT = 240;//�v���C���[���߂��Ƃ��ɂ���s���̒���
const int CWeaponEnemy::ATTACKFINISH_COOLTIME = 300;//�U���I����̃N�[���^�C��
const float CWeaponEnemy::DUSH_DISTANCE = 10.0f;//���鋗��
const float CWeaponEnemy::WALK_DISTANCE = 5.0f;//��������
const float CWeaponEnemy::DUSH_SPEED = 3.5f;//���鑬��
const float CWeaponEnemy::WALK_SPEED = 2.0f;//��������

//==========================
//�R���X�g���N�^
//==========================
CWeaponEnemy::CWeaponEnemy(int nPriority):
CEnemy(nPriority),//���R���X�g���N�^
m_HPGauge(nullptr),//HP�Q�[�W�̏��
m_NearAction(false),//�v���C���[���߂��ɂ���Ƃ��̍s������
m_NearCount(0),//�v���C���[���߂��ɂ���Ƃ��̍s���J�E���g
Attackable(true),//�U���\����
m_AttackCoolTime(0),//�U���̃N�[���^�C��
m_StackIdx(0),//TOP�̈ʒu
m_Attack(false),//�U������
m_Angle(0.0f),//����
m_FlameCount(0)//�U���̃t���[���J�E���g

{
	SetComboList();//�R���{���X�g�̐���
}

//==========================
//�f�X�g���N�^
//==========================
CWeaponEnemy::~CWeaponEnemy()
{

}

//==========================
//����������
//==========================
HRESULT CWeaponEnemy::Init()
{
	//�����ݒ�
	CEnemy::Init();

	//����U���ɐݒ�
	//SetAttackState(ATTACK_STATE::WEAPONATTACK);

	//HP�Q�[�W�𐶐�
	//m_HPGauge = CHPGauge3D::Create(D3DXVECTOR3(GetParts(2)->GetMtxWorld()._41, GetParts(2)->GetMtxWorld()._42, GetParts(2)->GetMtxWorld()._43), D3DXVECTOR3(20.0f, 3.0f, 0.0f), GetLife());

	return S_OK;
}

//==========================
//�I������
//==========================
void  CWeaponEnemy::Uninit()
{
	//�I������
	CEnemy::Uninit();

	if (m_HPGauge != nullptr)
	{
		m_HPGauge->Uninit();
		m_HPGauge = nullptr;
	}
}

//==========================
//�X�V����
//==========================
void CWeaponEnemy::Update()
{
	if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		return;
	}

	if (CManager::GetInstance()->GetGameManager()->GetPlayGame())
	{//�V�ׂȂ����
		return;
	}

	if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
	{
		Count();//�J�E���g����

		if (!GetDamage())
		{//�_���[�W��Ԃ���Ȃ���

			MoveAction();//�ړ����̍s����ݒ�
			Move();//�ړ�����
			Attack();//�U������
		}
	}

	//�X�V����
	CEnemy::Update();

	//HP�Q�[�W�̐ݒ�
	if (m_HPGauge != nullptr)
	{
		m_HPGauge->SetHP(GetLife());
		m_HPGauge->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 70.0f, GetPos().z));
	}
}

//==========================
//�`�揈��
//==========================
void CWeaponEnemy::Draw()
{
	//�`�揈��
	CEnemy::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CWeaponEnemy* CWeaponEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CModel* pModel = CManager::GetInstance()->GetModel();
	int modelnum = pModel->Regist("data\\MODEL\\bigweapon.x");

	//�C���X�^���X����
	CWeaponEnemy* pWeaponEnemy = DBG_NEW CWeaponEnemy;

	//�ʒu�̐ݒ�
	pWeaponEnemy->SetPos(pos);

	//����������
	pWeaponEnemy->Init();

	//�����̐ݒ�
	pWeaponEnemy->SetLife(10);

	//�t�@�C����ǂݍ���
	pWeaponEnemy->LoadFile("data\\MOTION\\motion_player_15.txt", scale);

	//������p�[�c�Ƃ��Đ���
	pWeaponEnemy->SetParts(D3DXVECTOR3(10.0f, -2.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), pWeaponEnemy->GetParts(5), modelnum, D3DXVECTOR3(1.5f, 1.5f, 1.5f));

	//���a�̐ݒ�
	pWeaponEnemy->SetRadius(15.0f);

	//��ނ̐ݒ�
	pWeaponEnemy->SetType(TYPE::ENEMY);

	//�G�̎�ނ�ݒ�
	pWeaponEnemy->SetEnemyType(ENEMY_TYPE::WeaponEnemy);

	return pWeaponEnemy;
}

//==========================
//�v���C���[�ւ̈ړ�
//==========================
void CWeaponEnemy::Move()
{
	if (GetState() != STATE::NEUTRAL)
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
//�J�E���g����
//==========================
void CWeaponEnemy::Count()
{
	if (m_NearAction)
	{//�v���C���[���߂Â����Ƃ��̍s�������Ă���
		m_NearCount++;
		if (m_NearCount >= NEAR_ACTION_COUNT
			&& GetPlayer()->GetState() != CPlayer::STATE::ATTACK)
		{
			m_NearAction = false;
			m_NearCount = 0;
			SetState(STATE::NEUTRAL);
		}
	}

	if (!Attackable)
	{//�U���ł��Ȃ��Ƃ�

		m_AttackCoolTime--;

		if (m_AttackCoolTime <= 0)
		{
			Attackable = true;
			m_AttackCoolTime = 0;
		}
	}
}

//==========================
//�ړ����̍s��
//==========================
void CWeaponEnemy::MoveAction()
{
	if ((GetState() != STATE::NEUTRAL)
		|| m_AttackCoolTime > (ATTACKFINISH_COOLTIME - 60))
	{//�ʏ��ԈȊO�̎��܂��͍U���I�����Ă���1�b�����Ă��Ȃ����I��
		return;
	}

	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	if (!pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * DUSH_DISTANCE))
	{//�v���C���[�̔��a��10�{�̋�����艓��

		//�ړ��l��ݒ�
		SetMove(D3DXVECTOR3(sinf(m_Angle) * DUSH_SPEED, 0.0f, cosf(m_Angle) * DUSH_SPEED));

		//���[�V������ݒ�
		SetMotion(MOTION_TYPE::DUSH);

		if (m_NearAction)
		{
			m_NearAction = false;
			m_NearCount = 0;
		}
	}
	else if (!pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * WALK_DISTANCE))
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
		&& !pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() + 2.0f))
	{//�U���\���v���C���[��艓��

		//�ړ��l��ݒ�
		SetMove(D3DXVECTOR3(sinf(m_Angle) * WALK_SPEED, 0.0f, cosf(m_Angle) * WALK_SPEED));

		//���[�V������ݒ�
		SetMotion(MOTION_TYPE::MOVE);
	}
	else if (Attackable
		&& pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() + 2.0f))
	{
		SetState(STATE::ATTACK);
	}

	//�����̐ݒ�
	ChangeDirection();
}

//==========================
//�U������
//==========================
void CWeaponEnemy::Attack()
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
		ColisionWeaponAttack();
	}

	m_FlameCount++;

	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	bool Colision = pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), 17.0f);
	if (m_FlameCount >= 26 && Colision && m_StackIdx > 0)
	{//�t���[������24�ȏォ�v���C���[���߂����R���{�ł���

		SetMotion(Pop());//���[�V�������Đ�
		m_FlameCount = 0;//�J�E���g���Ă��t���[���������Z�b�g
		m_Attack = false;//�U�����Ă��Ȃ���Ԃ̖߂�
		ChangeDirection();//������ς���
	}
	else if (m_FlameCount >= 24 && (!Colision || m_StackIdx <= 0))
	{//�v���C���[�������܂��̓R���{�ł��Ȃ�

		SetOldMotion(GetMotion());//���̃��[�V������ۑ�
		SetState(STATE::NEUTRAL);//�ʏ��ԂɕύX
		//SetAttackState(ATTACK_STATE::ATTACK);
		if (GetPartsExistence(15))
		{
			SetMotion(MOTION_TYPE::WEAPONNEUTRAL);//���펝���ҋ@��ԂɕύX
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
void CWeaponEnemy::ColisionWeaponAttack()
{
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	bool Colision = pCollision->Sphere(D3DXVECTOR3(GetPartsMtx(15)._41, GetPartsMtx(15)._42, GetPartsMtx(15)._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		30.0f,
		30.0f);

	if (Colision && !m_Attack)
	{
		//GetPlayer()->Damage();
		m_Attack = true;

		if (m_StackIdx <= 0)
		{
			GetPlayer()->DamegeBlow(GetPos());
		}
	}
}

//==========================
//�����̕ύX
//==========================
float CWeaponEnemy::ChangeDirection()
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
//�X�^�b�N�̏���߂�
//==========================
void CWeaponEnemy::ResetStak()
{
	m_StackIdx = 0;
	for (int i = 2; i >= 0; i--)
	{
		Push(m_ComboList[i]);
	}
}

//==========================
//�R���{���X�g�̐���
//==========================
void CWeaponEnemy::SetComboList()
{
	m_ComboList[0] = MOTION_TYPE::WEAPONATTACK;
	m_ComboList[1] = MOTION_TYPE::WEAPONATTACK2;
	m_ComboList[2] = MOTION_TYPE::WEAPONATTACK3;

	ResetStak();//�X�^�b�N�̃��Z�b�g
}

//==========================
//�f�[�^�̒ǉ�
//==========================
void CWeaponEnemy::Push(MOTION_TYPE motion)
{
	if (m_StackIdx < 3)
	{
		m_ComboStack[m_StackIdx++] = motion;
	}
}

//==========================
//�f�[�^�̎��o��
//==========================
CWeaponEnemy::MOTION_TYPE CWeaponEnemy::Pop()
{
	if (m_StackIdx <= 0)
	{
		if (GetPartsExistence(15))
		{
			return MOTION_TYPE::WEAPONNEUTRAL;
		}
		else
		{
			return MOTION_TYPE::NEUTRAL;
		}
	}

	return m_ComboStack[--m_StackIdx];

}
