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

//==========================
//�R���X�g���N�^
//==========================
CHitEnemy::CHitEnemy(int nPriority):
CEnemy(nPriority),//���R���X�g���N�^
m_HPGauge(nullptr),//HP�Q�[�W�̏��
m_NearAction(false),//�v���C���[���߂��ɂ���Ƃ��̍s������
m_NearCount(0),//�v���C���[���߂��ɂ���Ƃ��̍s���J�E���g
m_AttackCoolTime(0),//�U���̃N�[���^�C��
m_Attack(false),//�U������
m_FlameCount(0)//�U���̃t���[���J�E���g
{

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
	//SetAttackState(ATTACK_STATE::ATTACK);

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

	//�X�V����
	CEnemy::Update();
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

	//if (!Attackable)
	//{//�U���ł��Ȃ��Ƃ�

	//	m_AttackCoolTime--;

	//	if (m_AttackCoolTime <= 0)
	//	{
	//		Attackable = true;
	//		m_AttackCoolTime = 0;
	//	}
	//}
}

//==========================
//�U������
//==========================
void CHitEnemy::Attack()
{
	//if (GetState() != STATE::ATTACK || !Attackable)
	//{//�U����ԈȊO�̎��܂��͍U���s��Ԃ̎��I��
	//	return;
	//}

	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	if (GetOldMotion() == GetMotion())
	{//�O��̃��[�V�����ƍ��̃��[�V����������

		//���̃��[�V������ۑ�
		SetOldMotion(GetMotion());
	}

	if (m_FlameCount >= 10)
	{
		ColisionHitAttack();
	}

	m_FlameCount++;

	bool Colision = pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), 17.0f);
	if (m_FlameCount >= 26 && Colision )
	{//�t���[������24�ȏォ�v���C���[���߂����R���{�ł���

		m_FlameCount = 0;//�J�E���g���Ă��t���[���������Z�b�g
		m_Attack = false;//�U�����Ă��Ȃ���Ԃ̖߂�
		ChangeDirection();//������ς���
	}
	else if (m_FlameCount >= 24 && !Colision)
	{//�v���C���[�������܂��̓R���{�ł��Ȃ�

		SetOldMotion(GetMotion());//���̃��[�V������ۑ�
		SetState(STATE::NEUTRAL);//�ʏ��ԂɕύX
		//SetAttackState(ATTACK_STATE::ATTACK);
		if (GetPartsExistence(15))
		{
			SetMotion(MOTION_TYPE::WEAPONNEUTRAL);//���펝���ҋ@��ԂɕύX
		}

		m_FlameCount = 0;//�t���[���������Z�b�g
		m_Attack = false;//�U����������Z�b�g
		//Attackable = false;//�U���s���
		m_AttackCoolTime = ATTACKFINISH_COOLTIME;
	}
}

//==========================
//�U���̓����蔻��
//==========================
void CHitEnemy::ColisionHitAttack()
{
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	bool Colision = pCollision->Sphere(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		GetRadius(),
		GetPlayer()->GetRadius());

	if (Colision && !m_Attack)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

		GetPlayer()->hit(GetPos(),1);
		m_Attack = true;
	}
}

