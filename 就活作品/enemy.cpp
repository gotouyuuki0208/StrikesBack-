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

//�ÓI�����o������
const int CEnemy::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CEnemy::CEnemy(int nPriority) :
CMotionModel(nPriority),//���R���X�g���N�^
m_AttackState(ATTACK_STATE::USUALLY),//�U�����@
m_state(STATE::USUALLY),//���݂̏��S
m_nLife(0),//����
m_Damage(false),//�_���[�W����
m_EnemyType(ENEMY_TYPE::NONE),//�G�̎��
m_visual(nullptr),//�����蔻��̉���
m_player(nullptr),//�v���C���[�̏��
m_Movable(false),//�s���\������
m_DamageMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),//������т̈ړ��l
m_CurPoint(0)//���݂̈ړ��n�_
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
	CMotionModel::Init();

	//�v���C���[�̏����擾
	GetPlayerInfo();

	//�ړ��n�_���擾
	GetMovePoint();

	SetPosOld(GetPos());

	return S_OK;
}

//==========================
//�I������
//==========================
void  CEnemy::Uninit()
{
	//�I������
	CMotionModel::Uninit();

	if (m_visual != nullptr)
	{
		m_visual->Uninit();
		m_visual = nullptr;
	}

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
}

//==========================
//�X�V����
//==========================
void CEnemy::Update()
{
	//�ړ�����
	Move();

	//���[�V�����̍X�V
	Motion();

	//�X�V����
	CMotionModel::Update();

	//�n�ʂƂ̓����蔻��
	CollisionFild();

	//�G���m�̓����蔻��
	ColisionEnemy();

	if (m_Damage)
	{
		if (m_player->GetInputFrame() >= 54)
		{
			m_Damage=false;
		}
	}

	if (m_nLife <= 0)
	{
		Uninit();
	}

	if (m_visual != nullptr)
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

	if (m_state == STATE::GRAB)
	{
		D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &m_Mtx);
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//���f���p�[�c�̕`��
	PartsDraw();

	if (m_visual != nullptr)
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
//�ړ�����
//==========================
void CEnemy::Move()
{
	/*if (m_state == STATE::GRAB)
	{
		return;
	}*/

	SetMove(D3DXVECTOR3(m_DamageMove.x += (0 - m_DamageMove.x) * 0.25f,
		m_DamageMove.y-1.0f,
		m_DamageMove.z += (0 - m_DamageMove.z) * 0.25f));

	SetPos(GetPos() + m_DamageMove);
}

//==========================
//�_���[�W���󂯂��Ƃ��̏���
//==========================
void CEnemy::Damage(int damage)
{
	if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
	{
		if (GetState() != STATE::GUARD)
		{
			//���������炷
			m_nLife -= damage;

			//�_���[�W��ԂɕύX
			SetDamage();

			SetMotion(MOTION_TYPE::DAMAGE);
		}
		else
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_GUARD);

			if (m_player->GetHaveWeapon())
			{//�v���C���[������������Ă���
				//���������炷
				int Damage = damage / 2;

				if (Damage < 1)
				{//�_���[�W��1��菬�����Ƃ�
					Damage = 1;
				}
				m_nLife -= Damage;

				//�_���[�W��ԂɕύX
				SetDamage();
			}
		}
	}
}

//==========================
//��e���̐�����я���
//==========================
void CEnemy::DamegeBlow(D3DXVECTOR3 pos)
{
	if (GetState() != STATE::GUARD)
	{
		SetMotion(MOTION_TYPE::DAMAGEBLOW);
	}
	float angle = atan2f(GetPos().x - pos.x, GetPos().z - pos.z);
	m_DamageMove = (D3DXVECTOR3(sinf(angle) * 15.0f, GetMove().y, cosf(angle) * 15.0f));
	//SetPos(GetPos() + GetMove());

}

//==========================
//�͂܂�鏈��
//==========================
void CEnemy::BeGrabbed(D3DXMATRIX mtx)
{
	m_state = STATE::GRAB;//�͂܂�Ă��ԂɕύX

	m_Mtx = mtx;//�}�g���b�N�X�̕ۑ�

	SetPos(D3DXVECTOR3(15.0f, 0.0f, 50.0f));
	SetRot(D3DXVECTOR3(0.0f, 1.57f, -1.57f));
}

//==========================
//�͂܂�Ă��Ȃ���ԂɕύX
//==========================
void CEnemy::ReleaseGrab(D3DXVECTOR3 rot)
{
	m_state = STATE::USUALLY;//�ʏ��ԂɕύX

	SetPos(D3DXVECTOR3(GetMtxWorld()._41, GetMtxWorld()._42, GetMtxWorld()._43));
	SetRot(rot);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Mtx);

}


//==========================
//��Ԃ̐ݒ�
//==========================
void CEnemy::SetAttackState(ATTACK_STATE state)
{
	m_AttackState = state;
}

//==========================
//��Ԃ̎擾
//==========================
CEnemy::ATTACK_STATE CEnemy::GetAttackState()
{
	return m_AttackState;
}

//==========================
//��Ԃ̐ݒ�
//==========================
void CEnemy::SetState(STATE state)
{
	m_state = state;
}

//==========================
//��Ԃ̎擾
//==========================
CEnemy::STATE CEnemy::GetState()
{
	return m_state;
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
//��e���̓����蔻��̉���
//==========================
void CEnemy::DamageVisual(int PartsNum, float Radius)
{
	GetParts(PartsNum)->CreateVisual(D3DXVECTOR3(GetParts(PartsNum)->GetMtxWorld()._41, GetParts(PartsNum)->GetMtxWorld()._42, GetParts(PartsNum)->GetMtxWorld()._43), Radius);
}

//==========================
//�����̐ݒ�
//==========================
void CEnemy::SetLife(int life)
{
	m_nLife = life;
}

//==========================
//�����̎擾
//==========================
int CEnemy::GetLife()
{
	return m_nLife;
}

//==========================
//�_���[�W����̎擾
//==========================
bool CEnemy::GetDamage()
{
	return m_Damage;
}

//==========================
//�_���[�W����̕ύX
//==========================
void CEnemy::SetDamage()
{
	m_Damage = true;
}

//==========================
//�����蔻��̉�������
//==========================
void CEnemy::SetVisual()
{
	if (m_visual == nullptr)
	{
		//m_visual = CCollisionVisual::Create(GetPos(), GetRadius());
	}
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

		bool Colision = ColisionSphere(GetPos(),
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
void CEnemy::judgeMovable()
{
	if (m_player == nullptr
		|| m_Movable)
	{//�v���C���[�̏��������ĂȂ������łɍs���\�ȂƂ�
		return;
	}

	bool Colision = ColisionSphere(GetPos(), m_player->GetPos(), GetRadius() * 30, m_player->GetRadius());
	
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