//==========================
// 
// �G���G[weakenemy.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "weakenemy.h"
#include "manager.h"
#include "model.h"
#include "enemymovepoint.h"
#include "player.h"
#include "enemystate.h"

//�ÓI�����o������
const int CWeakEnemy::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CWeakEnemy::CWeakEnemy(int nPriority) :
	CEnemy(nPriority),//���R���X�g���N�^
	m_CurPoint(0),//���݂̈ړ��n�_
	m_StateMachine(nullptr),//��ԊǗ�
	m_Color(1.0f)
{
	for (int i = 0; i < POINT; i++)
	{
		m_Point[i] = nullptr;//�ړ��n�_�̏��
	}

	
}

//==========================
//�f�X�g���N�^
//==========================
CWeakEnemy::~CWeakEnemy()
{

}

//==========================
//����������
//==========================
HRESULT CWeakEnemy::Init()
{

	//�����ݒ�
	CEnemy::Init();

	//��ԊǗ��N���X�̍쐬
	m_StateMachine = DBG_NEW CStateMachine;
	auto NewState = DBG_NEW CEnemyMovabeState;
	ChangeState(NewState);

	return S_OK;
}

//==========================
//�I������
//==========================
void  CWeakEnemy::Uninit()
{
	//�I������
	CEnemy::Uninit();

	if (m_StateMachine != nullptr)
	{//��ԊǗ��N���X�̉��

		delete m_StateMachine;
		m_StateMachine = nullptr;
	}
}

//==========================
//�X�V����
//==========================
void CWeakEnemy::Update()
{
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

			//�U���\�ɂ���
			ChangeAttackable();
		}
	}

	if (GetPlayMotion())
	{//���[�V�������Đ�����

		//���[�V�����̍X�V
		Motion();
	}

	//�G���m�̓����蔻��
	ColisionEnemy();

	//�����x0�ō폜
	if (m_Color <= 0.0f)
	{
		Uninit();
	}
}

//==========================
//�`�揈��
//==========================
void CWeakEnemy::Draw()
{
	CEnemy::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CWeakEnemy* CWeakEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CWeakEnemy* pEnemy = DBG_NEW CWeakEnemy;

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
void CWeakEnemy::ChangeState(CEnemyStateBase* NewState)
{
	NewState->SetOwner(this);
	m_StateMachine->ChangeState(NewState);
}

//==========================
//�G���m�̓����蔻��
//==========================
void CWeakEnemy::ColisionEnemy()
{
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CWeakEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CWeakEnemy::PRIORITY);
			continue;
		}

		if (pObj == this)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CWeakEnemy::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//�I�u�W�F�N�g���t�B�[���h�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CWeakEnemy::PRIORITY);
			continue;
		}

		CWeakEnemy* pEnemy = (CWeakEnemy*)pObj;

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

		pObj = CObject::GetObj(pObj, CWeakEnemy::PRIORITY);
	}
}

//==========================
//�ړ��n�_���擾
//==========================
void CWeakEnemy::GetMovePoint()
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
void CWeakEnemy::Patrol()
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
//�U����e����
//==========================
void CWeakEnemy::Hit(D3DXVECTOR3 pos, int damage, MOTION_TYPE HitMotion)
{
	
	if (GetDamageNum() >= 3 || GetHitMotion() == HitMotion)
	{//�_���[�W�񐔂�3��ȏォ�O��Ɠ����U��
		return;
	}

	//��e�񐔂𑝂₷
	AddDamegeNum();

	//�U�����󂯂����[�V������ۑ�
	SetHitMotion(HitMotion);

	//�_���[�W�̐��l���擾
	int DamageNum = damage;

	//���C�t�����炷
	int Life = GetLife();
	SetLife(Life -= DamageNum);

	//�_���[�W���󂯂���Ԃɐݒ�
	SetDamage(true);

	if (GetDamageNum() >= 3)
	{//3���e���Ă���
		DamegeBlow(pos);
	}

}

//==========================
//�p�[�c�̓����x�����炷
//==========================
void CWeakEnemy::SubPartsCol()
{
	//�����x�����炷
	m_Color -= 0.01f;

	//�����x��ݒ�
	SubTransparency(m_Color);
}