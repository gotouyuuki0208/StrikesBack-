//==========================
// 
// ����G[hitenemy.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "hitenemy.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CHitEnemy::PRIORITY = 1;//�`�揇
const int CHitEnemy::NEAR_ACTION_COUNT = 240;//�v���C���[���߂��Ƃ��ɂ���s���̒���
const int CHitEnemy::ATTACKFINISH_COOLTIME = 300;//�U���I����̃N�[���^�C��
const float CHitEnemy::DUSH_DISTANCE = 10.0f;//���鋗��
const float CHitEnemy::WALK_DISTANCE = 5.0f;//��������
const float CHitEnemy::DUSH_SPEED = 3.5f;//���鑬��
const float CHitEnemy::WALK_SPEED = 2.0f;//��������
//==========================
//�R���X�g���N�^
//==========================
CHitEnemy::CHitEnemy(int nPriority):
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
	SetComboList();//�R���{���X�g�̐ݒ�
}

//==========================
//�f�X�g���N�^
//==========================
CHitEnemy::~CHitEnemy()
{

}

//==========================
//����������
//==========================
HRESULT CHitEnemy::Init()
{
	//�����ݒ�
	CEnemy::Init();

	//����U���ɐݒ�
	SetAttackState(ATTACK_STATE::ATTACK);

	//HP�Q�[�W�𐶐�
	m_HPGauge = CHPGauge3D::Create(D3DXVECTOR3(GetParts(2)->GetMtxWorld()._41, GetParts(2)->GetMtxWorld()._42, GetParts(2)->GetMtxWorld()._43), D3DXVECTOR3(20.0f, 3.0f, 0.0f), GetLife());

	return S_OK;
}

//==========================
//�I������
//==========================
void  CHitEnemy::Uninit()
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
void CHitEnemy::Update()
{
	if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		return;
	}

	if (CManager::GetInstance()->GetTutorial()->GetTutorial())
	{//��������\����
		return;
	}

	//�s���\������
	judgeMovable();

	if (GetMovable())
	{//�s���\�ȂƂ�
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

		//HP�Q�[�W�̐ݒ�
		if (m_HPGauge != nullptr)
		{
			m_HPGauge->SetHP(GetLife());
			m_HPGauge->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 70.0f, GetPos().z));
			m_HPGauge->DrawGauge();
		}
	}
	else
	{//�s���ł��Ȃ��Ƃ�

		Patrol();//�ړ��n�_������

		if (!GetDamage())
		{//�_���[�W��Ԃ���Ȃ���
			Move();//�ړ�����
		}

		//HP�Q�[�W�̐ݒ�
		if (m_HPGauge != nullptr)
		{
			m_HPGauge->EraseGauge();
		}
	}

	//�X�V����
	CEnemy::Update();
	Motion();
}

//==========================
//�`�揈��
//==========================
void CHitEnemy::Draw()
{
	//�`�揈��
	CEnemy::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CHitEnemy* CHitEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CHitEnemy* pHitEnemy = DBG_NEW CHitEnemy;

	//�ʒu�̐ݒ�
	pHitEnemy->SetPos(pos);

	//�����̐ݒ�
	pHitEnemy->SetLife(5);

	//�t�@�C����ǂݍ���
	pHitEnemy->LoadFile("data\\MOTION\\enemy.txt", scale);

	//����������
	pHitEnemy->Init();

	//pHitEnemy->SetDamageCor();

	//���a�̐ݒ�
	pHitEnemy->SetRadius(15.0f);

	//��ނ̐ݒ�
	pHitEnemy->SetType(TYPE::ENEMY);

	//�G�̎�ނ�ݒ�
	pHitEnemy->SetEnemyType(ENEMY_TYPE::HitEnemy);

	//�����蔻�������
	//pHitEnemy->SetVisual();

	return pHitEnemy;
}

//==========================
//�v���C���[�ւ̈ړ�
//==========================
void CHitEnemy::Move()
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
void CHitEnemy::Count()
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
void CHitEnemy::MoveAction()
{
	if ((GetState() != STATE::NEUTRAL)
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

		if (m_NearAction)
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
	else if (!Attackable
		&& ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * WALK_DISTANCE))
	{
		//���[�V������ݒ�
		SetMotion(MOTION_TYPE::NEUTRAL);
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
	//�����̐ݒ�
	ChangeDirection();
}

//==========================
//�U������
//==========================
void CHitEnemy::Attack()
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
		ColisionHitAttack();
	}

	m_FlameCount++;

	bool Colision = ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), 17.0f);
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
		SetAttackState(ATTACK_STATE::ATTACK);
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
void CHitEnemy::ColisionHitAttack()
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
			GetPlayer()->DamegeBlow(GetPos());
		}
	}
}

//==========================
//�����̕ύX
//==========================
float CHitEnemy::ChangeDirection()
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
void CHitEnemy::ResetStak()
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
void CHitEnemy::SetComboList()
{
	m_ComboList[0] = MOTION_TYPE::ATTACK;
	m_ComboList[1] = MOTION_TYPE::ATTACK2;
	m_ComboList[2] = MOTION_TYPE::ATTACK3;

	ResetStak();//�X�^�b�N�̃��Z�b�g
}

//==========================
//�f�[�^�̒ǉ�
//==========================
void CHitEnemy::Push(MOTION_TYPE motion)
{
	if (m_StackIdx < 3)
	{
		m_ComboStack[m_StackIdx++] = motion;
	}
}

//==========================
//�f�[�^�̎��o��
//==========================
CHitEnemy::MOTION_TYPE CHitEnemy::Pop()
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
