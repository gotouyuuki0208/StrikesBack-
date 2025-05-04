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
//m_AttackState(ATTACK_STATE::USUALLY),//�U�����@
m_EnemyType(ENEMY_TYPE::NONE),//�G�̎��
m_player(nullptr),//�v���C���[�̏��
m_Movable(false),//�s���\������
m_CurPoint(0),//���݂̈ړ��n�_
m_StateMachine(nullptr),//��ԊǗ�
m_Angle(0.0f),//����
Attackable(true),//�U���\����
m_PlayMotion(true)//���[�V�����Đ�����
{
	for (int i = 0; i < POINT;i++)
	{
		m_Point[i] = nullptr;//�ړ��n�_�̏��
	}
	
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

	SetPosOld(GetPos());

	//��ԊǗ��N���X�̍쐬
	m_StateMachine = DBG_NEW CStateMachine;
	auto NewState = DBG_NEW CEnemyMovabeState;
	ChangeState(NewState);

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
	
	for (int i = 0; i < POINT; i++)
	{
		if (m_Point[i] != nullptr)
		{
			m_Point[i] = nullptr;
		}
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
void CEnemy::Update()
{
	//�X�e�[�g�̍X�V
	m_StateMachine->Update();

	//�ړ�����
	Move();

	if (m_PlayMotion)
	{//���[�V�������Đ�����

		//���[�V�����̍X�V
		Motion();
	}
	
	//�X�V����
	CCharacter::Update();

	//�n�ʂƂ̓����蔻��
	CollisionFild();

	//�G���m�̓����蔻��
	ColisionEnemy();

	if (GetDamage())
	{
		//if (m_player->GetInputFrame() >= 54)
		{

			SetDamage(false);
		}
	}

	
	if (GetLife() <= 0)
	{
		CManager::GetInstance()->GetStageManager()->DeleteObj(*this);
		Uninit();
	}

	//if (m_visual != nullptr)
	{
		//m_visual->SetPos(GetPos());
	}
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

	//if (m_visual != nullptr)
	{
		//m_visual->Draw();
	}
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
//��Ԃ�ύX
//==========================
void CEnemy::ChangeState(CEnemyStateBase* NewState)
{
	NewState->SetOwner(this);
	m_StateMachine->ChangeState(NewState);
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

	//�ʒu��ύX
	SetPos(GetPos() + GetMove());

	/*SetDamegeBlow(D3DXVECTOR3(GetDamegeBlow().x + (0 - GetDamegeBlow().x) * 0.25f,
		GetDamegeBlow().y - 1.0f,
		GetDamegeBlow().z + (0 - GetDamegeBlow().z) * 0.25f));

	SetMove(GetDamegeBlow());

	SetPos(GetPos() + GetDamegeBlow());*/
}

//==========================
//�_���[�W���󂯂��Ƃ��̏���
//==========================
void CEnemy::Damage(int damage)
{
	if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
	{
		if (GetState() != STATE::GUARD)
		{//�K�[�h���ĂȂ��Ƃ�

			//���������炷
			SetLife(GetLife() - damage);

			//�_���[�W��ԂɕύX
			SetDamage(true);

			//�_���[�W���[�V�����ɐݒ�
			SetMotion(MOTION_TYPE::DAMAGE);
		}
		else
		{//�K�[�h���Ă�Ƃ�

			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_GUARD);

			if (m_player->GetHaveWeapon())
			{//�v���C���[������������Ă���

				//���������炷
				int Damage = damage / 2;

				if (Damage < 1)
				{//�_���[�W��1��菬�����Ƃ�
					Damage = 1;
				}
				SetLife(GetLife() - Damage);

				//�_���[�W��ԂɕύX
				SetDamage(true);
			}
		}
	}
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
//�G���m�̓����蔻��
//==========================
void CEnemy::ColisionEnemy()
{
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		if (pObj == this)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//�I�u�W�F�N�g���t�B�[���h�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = (CEnemy*)pObj;

		bool Colision = pCollision->Sphere(GetPos(),
			pEnemy->GetPos(),
			GetRadius(),
			pEnemy->GetRadius());

		if (Colision)
		{
			D3DXVECTOR3 Vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����x�N�g��
			D3DXVECTOR3 NormalizeVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���K�������x�N�g��

			//�����x�N�g�����Z�o
			Vector.x = VectorCalculation(pEnemy->GetPos().x, GetPos().x);
			Vector.z = VectorCalculation(pEnemy->GetPos().z, GetPos().z);

			//�x�N�g���𐳋K��
			D3DXVec3Normalize(&NormalizeVec, &Vector);

			//�ʒu��ύX
			pEnemy->SetPos(D3DXVECTOR3(GetPos().x + NormalizeVec.x * (GetRadius() + pEnemy->GetRadius()),
				GetPos().y,
				GetPos().z + NormalizeVec.z * (GetRadius() + pEnemy->GetRadius())));
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
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
	CCollision* pCollision = CManager::GetInstance()->GetCollision();
	bool Colision = pCollision->Sphere(GetPos(), m_player->GetPos(), GetRadius() * 30, m_player->GetRadius());
	
	//�͈͓��ɓ����Ă���
	if (Colision)
	{
		SetMovable();//�s���\�ɂ���
	}
}

//==========================
//�ړ��n�_���擾
//==========================
void CEnemy::GetMovePoint()
{
	if (m_Point[0] != nullptr)
	{
		return;
	}

	int Point = 0;

	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CEnemyMovePoint::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CEnemyMovePoint::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::FILD)
		{//�I�u�W�F�N�g���v���C���[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CEnemyMovePoint::PRIORITY);
			continue;
		}
		
		CFild* pFild = dynamic_cast<CFild*>(pObj);

		if (pFild->GetFildType() != CFild::FILDTYPE::ENEMYMOVEPOINT)
		{//�ړ��n�_�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CEnemyMovePoint::PRIORITY);
			continue;
		}

		CEnemyMovePoint* pPoint = dynamic_cast<CEnemyMovePoint*>(pObj);

		m_Point[Point] = pPoint;
		Point++;

		pObj = CObject::GetObj(pObj, CEnemyMovePoint::PRIORITY);
	}

	CEnemyMovePoint* pPoint = nullptr;
	float distance = 0.0f;

	//��ԋ߂��|�C���g���擾
	for (int i = 0; i < POINT; i++)
	{
		if (m_Point[i] == nullptr)
		{
			break;
		}

		float newdistance = (m_Point[i]->GetPos().x - GetPos().x) * (m_Point[i]->GetPos().x - GetPos().x) +
			(m_Point[i]->GetPos().z - GetPos().z) * (m_Point[i]->GetPos().z - GetPos().z);

		if (distance == 0.0f || newdistance <= distance)
		{
			distance = newdistance;//������ۑ�
			pPoint = m_Point[i];//�ړ��n�_�̏���ۑ�
		}
	}

	for (int i = 0; i < POINT; i++)
	{
		if (m_Point[i] == pPoint)
		{
			break;
		}

		m_CurPoint++;
	}
}

//==========================
//�ړ��n�_������
//==========================
void CEnemy::Patrol()
{
	//�ړ��n�_���擾
	GetMovePoint();

	if (m_Point[m_CurPoint] == nullptr)
	{
		return;
	}

	//�i�ފp�x���v�Z
	float Angle = atan2f(m_Point[m_CurPoint]->GetPos().x - GetPos().x, m_Point[m_CurPoint]->GetPos().z - GetPos().z);

	//������ݒ�
	SetRot(D3DXVECTOR3(GetRot().x, Angle + D3DX_PI, GetRot().z));

	//�ړ��l��ݒ�
	SetMove(D3DXVECTOR3(sinf(Angle) * 2.0f, 0.0f, cosf(Angle) * 2.0f));

	//���[�V������ݒ�
	SetMotion(MOTION_TYPE::MOVE);

	if (GetPos().x <= m_Point[m_CurPoint]->GetPos().x + 10.0f
		&& GetPos().x >= m_Point[m_CurPoint]->GetPos().x - 10.0f
		&& GetPos().z <= m_Point[m_CurPoint]->GetPos().z + 10.0f
		&& GetPos().z >= m_Point[m_CurPoint]->GetPos().z - 10.0f)
	{//�ړ��n�_�ɂ���
		m_CurPoint++;

		if (m_Point[m_CurPoint] == nullptr)
		{//���̈ړ��n�_���Ȃ�
			m_CurPoint = 0;
			SetPos(D3DXVECTOR3(m_Point[m_CurPoint]->GetPos().x, 0.0f, m_Point[m_CurPoint]->GetPos().z));
		}

	}

}

//==========================
//�_�b�V������
//==========================
bool CEnemy::JudgeDush()
{
	//�����蔻��̏����擾
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	if (!pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * DUSH_DISTANCE))
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
	//�����蔻��̏����擾
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	if (pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * DUSH_DISTANCE)
		&& !JudgeStop())
	{//�v���C���[�̔��a��10�{�̋������߂�
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
	//�����蔻��̏����擾
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	if (pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * STOP_DISTANCE))
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
bool CEnemy::JudgeAttacKRange()
{
	//�����蔻��̏����擾
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	if (!pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius()+2.0f, GetPlayer()->GetRadius()+2.0f))
	{//�v���C���[���U���͈͂ɂ��Ȃ�

		return true;
	}

	return false;
}

//==========================
//���[�V�����̍Đ������ύX
//==========================
void CEnemy::ChangePlayMotion()
{
	m_PlayMotion = !m_PlayMotion;
}