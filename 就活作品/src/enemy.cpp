//==========================
// 
// �G�l�~�[[enemy.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "enemy.h"
#include "manager.h"
#include "model.h"
#include "enemymovepoint.h"
#include "player.h"
#include "enemystate.h"
#include"collision.h"

//�ÓI�����o������
const int CEnemy::PRIORITY = 1;//�`�揇
const float CEnemy::DUSH_DISTANCE = 10.0f;//���鋗��
const float CEnemy::DUSH_SPEED = 3.5f;//���鑬��
const float CEnemy::STOP_DISTANCE = 5.0f;//��~���鋗��
const float CEnemy::WALK_SPEED = 2.0f;//��������

//==========================
//�R���X�g���N�^
//==========================
CEnemy::CEnemy(int nPriority) :
CCharacter(nPriority),//���R���X�g���N�^
m_EnemyType(ENEMY_TYPE::NONE),//�G�̎��
m_player(nullptr),//�v���C���[�̏��
m_Movable(false),//�s���\������
m_Angle(0.0f),//����
Attackable(true),//�U���\����
m_PlayMotion(true),//���[�V�����Đ�����
m_DamageNum(0),//�_���[�W�񐔂��J�E���g
m_Attack(false),//�U������
m_AttackCoolTime(0),
m_ActionWave(0)
{
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Mtx);
}

//==========================
//�f�X�g���N�^
//==========================
CEnemy::~CEnemy()
{

}

//==========================
//����������
//==========================
HRESULT CEnemy::Init()
{

	//�����ݒ�
	CCharacter::Init();

	//�v���C���[�̏����擾
	GetPlayerInfo();

	//���݂̈ʒu��ۑ�
	SetPosOld(GetPos());

	return S_OK;
}

//==========================
//�I������
//==========================
void  CEnemy::Uninit()
{
	//�I������
	CCharacter::Uninit();

	if (m_player != nullptr)
	{
		m_player = nullptr;
	}	
}

//==========================
//�X�V����
//==========================
void CEnemy::Update()
{
	//�X�V����
	CCharacter::Update();

	//�n�ʂƂ̓����蔻��
	CollisionFild();
}

//==========================
//�`�揈��
//==========================
void CEnemy::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&GetMtxWorld());

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	
	if (GetState() == STATE::GRAB)
	{
		D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &m_Mtx);
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//���f���p�[�c�̕`��
	PartsDraw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CEnemy* pEnemy = DBG_NEW CEnemy;

	//�ʒu�̐ݒ�
	pEnemy->SetPos(pos);

	//����������
	pEnemy->Init();

	//�t�@�C����ǂݍ���
	pEnemy->LoadFile("data\\MOTION\\motion_enemy_hit.txt", scale);

	//�^�C�v�ݒ�
	pEnemy->SetType(TYPE::ENEMY);

	return pEnemy;
}

//==========================
//�ړ�����
//==========================
void CEnemy::Move()
{
	//�O��̈ʒu��ۑ�
	SetPosOld(GetPos());

	//�ړ��l�̐ݒ�
	SetMove(D3DXVECTOR3(GetMove().x += (0 - GetMove().x) * 0.25f,
		GetMove().y,
		GetMove().z += (0 - GetMove().z) * 0.25f));

	//������т̈ړ�����
	SetDamegeBlow(D3DXVECTOR3(GetDamegeBlow().x + (0 - GetDamegeBlow().x) * 0.25f,
		GetDamegeBlow().y,
		GetDamegeBlow().z + (0 - GetDamegeBlow().z) * 0.25f));

	SetMove(D3DXVECTOR3(GetMove().x + GetDamegeBlow().x,
		GetMove().y + GetDamegeBlow().y,
		GetMove().z + GetDamegeBlow().z));

	//�ʒu��ύX
	SetPos(GetPos() + GetMove());
}

//==========================
//�͂܂�鏈��
//==========================
void CEnemy::BeGrabbed(D3DXMATRIX mtx)
{
	SetState(STATE::GRAB);//�͂܂�Ă��ԂɕύX

	m_Mtx = mtx;//�}�g���b�N�X�̕ۑ�

	SetPos(D3DXVECTOR3(15.0f, 0.0f, 50.0f));
	SetRot(D3DXVECTOR3(0.0f, 1.57f, -1.57f));
}

//==========================
//�͂܂�Ă��Ȃ���ԂɕύX
//==========================
void CEnemy::ReleaseGrab(D3DXVECTOR3 rot)
{
	SetState(STATE::NEUTRAL);//�ʏ��ԂɕύX

	SetPos(D3DXVECTOR3(GetMtxWorld()._41, GetMtxWorld()._42, GetMtxWorld()._43));
	SetRot(rot);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Mtx);

}

//==========================
//�G�̎�ނ�ݒ�
//==========================
void CEnemy::SetEnemyType(ENEMY_TYPE EnemyType)
{
	m_EnemyType = EnemyType;
}

//==========================
//�G�̎�ނ��擾
//==========================
CEnemy::ENEMY_TYPE CEnemy::GetEnemyType()
{
	return m_EnemyType;
}

//==========================
//�v���C���[�̏����擾
//==========================
CPlayer* CEnemy::GetPlayer()
{
	return m_player;
}

//==========================
//�n�ʂƂ̓����蔻��
//==========================
void CEnemy::CollisionFild()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CFild::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CFild::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::FILD)
		{//�I�u�W�F�N�g���t�B�[���h�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CFild::PRIORITY);
			continue;
		}

		//�I�u�W�F�N�g��Fild�N���X�ɃL���X�g
		CFild* pFild = (CFild*)pObj;

		if (GetPos().x < pFild->GetPos().x + pFild->GetSize().x
			&& GetPos().x > pFild->GetPos().x - pFild->GetSize().x
			&& GetPos().z < pFild->GetPos().z + pFild->GetSize().z
			&& GetPos().z > pFild->GetPos().z - pFild->GetSize().z)
		{//�Փ˂��Ă���
			SetMove(D3DXVECTOR3(GetMove().x, 0.0f, GetMove().z));
			SetPos(D3DXVECTOR3(GetPos().x, pFild->GetPos().y, GetPos().z));
			break;
		}

		pObj = CObject::GetObj(pObj, CFild::PRIORITY);
	}
}

//==========================
//�v���C���[�̏����擾
//==========================
void CEnemy::GetPlayerInfo()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CPlayer::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::PLAYER)
		{//�I�u�W�F�N�g���v���C���[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		CPlayer* pPlayer = (CPlayer*)pObj;

		//�v���C���[�̏����擾
		m_player = pPlayer;

		break;
	}
}

//==========================
//�ړ��\���擾
//==========================
bool CEnemy::GetMovable()
{
	return m_Movable;
}

//==========================
//�s���\�ɂ���
//==========================
void CEnemy::SetMovable()
{
	m_Movable = true;
}

//==========================
//�s���o���邩����
//==========================
void CEnemy::JudgeMovable()
{
	if (m_player == nullptr
		|| m_Movable)
	{//�v���C���[�̏��������ĂȂ������łɍs���\�ȂƂ�
		return;
	}

	//���̓����蔻��
	bool Colision = Collision::Sphere(GetPos(), m_player->GetPos(), GetRadius() * 30, m_player->GetRadius());
	
	//�͈͓��ɓ����Ă���
	if (Colision)
	{
		SetMovable();//�s���\�ɂ���
	}
}

//==========================
//�U�����̈ړ�
//==========================
void CEnemy::AttackMove()
{
	//�����̕ύX
	ChangeDirection();

	//�ړ��l��ݒ�
	SetMove(D3DXVECTOR3(sinf(m_Angle) * WALK_SPEED, 0.0f, cosf(m_Angle) * WALK_SPEED));
}

//==========================
//�_�b�V������
//==========================
bool CEnemy::JudgeDush()
{
	
	if (!Collision::Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * DUSH_DISTANCE))
	{//�v���C���[�̔��a��10�{�̋�����艓��
		return true;
	}

	return false;
}

//==========================
//�_�b�V���ړ�����
//==========================
void CEnemy::Dush()
{
	//�����̕ύX
	ChangeDirection();

	//�ړ��l��ݒ�
	SetMove(D3DXVECTOR3(sinf(m_Angle) * DUSH_SPEED, 0.0f, cosf(m_Angle) * DUSH_SPEED));
}

//==========================
//��������
//==========================
bool CEnemy::JudgeWalk()
{
	if (Collision::Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * DUSH_DISTANCE)
		&& !JudgeStop())
	{//�v���C���[�̔��a��10�{�̋������߂�����~���鋗����艓��
		return true;
	}

	return false;
}

//==========================
//�����ړ�����
//==========================
void CEnemy::Walk()
{
	//�����̕ύX
	ChangeDirection();

	//�ړ��l��ݒ�
	SetMove(D3DXVECTOR3(sinf(m_Angle) * WALK_SPEED, 0.0f, cosf(m_Angle) * WALK_SPEED));
}

//==========================
//��~����
//==========================
bool CEnemy::JudgeStop()
{
	if (Collision::Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * STOP_DISTANCE))
	{//�������߂�
		return true;
	}

	return false;
}

//==========================
//�����̕ύX
//==========================
float CEnemy::ChangeDirection()
{
	//�i�ފp�x���v�Z
	m_Angle = atan2f(GetPlayer()->GetPos().x - GetPos().x, GetPlayer()->GetPos().z - GetPos().z);

	//������ݒ�
	SetRot(D3DXVECTOR3(GetRot().x, m_Angle + D3DX_PI, GetRot().z));

	return m_Angle;
}

//==========================
//�U���\������
//==========================
bool CEnemy::GetAttackable()
{
	return Attackable;
}

//==========================
//�U���\�����ύX
//==========================
void CEnemy::ChangeAttackable()
{
	Attackable = !Attackable;
}

//==========================
//�U���͈͂Ƀv���C���[�����邩����
//==========================
bool CEnemy::JudgeAttackRange()
{
	if (!Collision::Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius()+2.0f, GetPlayer()->GetRadius()+2.0f))
	{//�v���C���[���U���͈͂ɂ��Ȃ�

		return true;
	}

	return false;
}

//==========================
//���[�V�����̍Đ������ύX
//==========================
void CEnemy::ChangePlayMotion(bool play)
{
	m_PlayMotion = play;
}

//==========================
//���[�V�����̍Đ�������擾
//==========================
bool CEnemy::GetPlayMotion()
{
	return m_PlayMotion;
}

//==========================
//��e�񐔏�����
//==========================
void CEnemy::ResetDamageNum()
{
	m_DamageNum = 0;
}

//==========================
//��e�񐔎擾
//==========================
int CEnemy::GetDamageNum()
{
	return m_DamageNum;
}

//==========================
//�_���[�W�񐔂𑝂₷
//==========================
void CEnemy::AddDamegeNum()
{
	m_DamageNum++;
}

//==========================
//�v���C���[�ւ̉���U���̓����蔻��
//==========================
void CEnemy::HitPlayer(int PartsNum)
{
	//����
	bool Colision = Collision::Sphere(D3DXVECTOR3(GetPartsMtx(PartsNum)._41, GetPartsMtx(PartsNum)._42, GetPartsMtx(PartsNum)._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		GetRadius(),
		GetPlayer()->GetRadius());

	//�U�����������Ă���
	if (Colision && !m_Attack)
	{
		//�T�E���h���Đ�
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

		//�v���C���[�̃_���[�W����
		GetPlayer()->hit(GetPos(), 1);
		m_Attack = true;
	}
}

//==========================
//�U����������Z�b�g
//==========================
void CEnemy::ResetAttack()
{
	m_Attack = false;
}

//==========================
//�U���̃N�[���^�C����ݒ�
//==========================
void CEnemy::SetCoolTime(int time)
{
	m_AttackCoolTime = time;
}

//==========================
//�U���̃N�[���^�C�����擾
//==========================
int CEnemy::GetCoolTime()
{
	return m_AttackCoolTime;
}

//==========================
//�N�[���^�C�������炷
//==========================
void CEnemy::SubCoolTime()
{
	m_AttackCoolTime--;
}

//==========================
//�U�����󂯂����[�V������ۑ�
//==========================
void CEnemy::SetHitMotion(MOTION_TYPE motion)
{
	m_HitMotion = motion;
}

//==========================
//�U�����󂯂����[�V�������擾
//==========================
CMotionModel::MOTION_TYPE CEnemy::GetHitMotion()
{
	return m_HitMotion;
}

//==========================
//�U��������擾
//==========================
bool CEnemy::GetAttack()
{
	return m_Attack;
}

//==========================
//�U�������ݒ�
//==========================
void CEnemy::SetAttack()
{
	m_Attack = true;
}

//==========================
//�s������E�F�[�u��ݒ�
//==========================
void CEnemy::SetActionWave(int wave)
{
	m_ActionWave = wave;
}

//==========================
//�s������E�F�[�u���擾
//==========================
int CEnemy::GetActionWave()
{
	return m_ActionWave;
}