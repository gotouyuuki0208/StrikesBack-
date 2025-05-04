//==========================
// 
// ����[building.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "building.h"
#include "manager.h"
#include "model.h"
#include "player.h"
#include "enemy.h"

//�ÓI�����o������
const int CBuilding::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBuilding::CBuilding(int nPriority):
CObjectX(nPriority),
m_nModelIdx(0),
m_Building_Type(BUILDING_TYPE::NONE)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBuilding::~CBuilding()
{

}

//==========================
//����������
//==========================
HRESULT CBuilding::Init()
{
	//�T�C�Y�ݒ�
	SetSize();

	//�����ݒ�
	CObjectX::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBuilding::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CBuilding::Update()
{
	//�X�V����
	CObjectX::Update();

	int rot = static_cast<int>(GetRot().y);

	if (rot == 1 || rot == -1)
	{
		//�v���C���[�Ƃ̓����蔻��
		ColisionPlayerWide();
	}
	else
	{
		//�v���C���[�Ƃ̓����蔻��
		ColisionPlayer();
	}
	
	if (!CManager::GetInstance()->GetDebug()->GetEdit())
	{
		if (rot == 1 || rot == -1)
		{
			//�G�Ƃ̓����蔻��
			ColisionEnemyWide();
		}
		else
		{
			//�v���C���[�Ƃ̓����蔻��
			ColisionEnemy();
		}
	}
}

//==========================
//�`�揈��
//==========================
void CBuilding::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBuilding* CBuilding::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CBuilding* pBuilding = DBG_NEW CBuilding;

	//�ʒu�̐ݒ�
	pBuilding->SetPos(pos);

	//�X�P�[���̐ݒ�
	pBuilding->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBuilding->m_nModelIdx = pModel->Regist("data\\MODEL\\test_building001.x");
	pBuilding->BindModel(pModel->GetMeshAdress(pBuilding->m_nModelIdx),
		pModel->GetBuffMatAdress(pBuilding->m_nModelIdx),
		pModel->GetNumMatAdress(pBuilding->m_nModelIdx),
		pModel->GetTexIdx(pBuilding->m_nModelIdx));

	//����������
	pBuilding->Init();

	//�^�C�v��ݒ�
	pBuilding->SetType(TYPE::BUILDING);
	pBuilding->SetBuildingType(BUILDING_TYPE::BUILDING);

	return pBuilding;
}

//==========================
//�����̎�ނ��擾
//==========================
CBuilding::BUILDING_TYPE CBuilding::GetBuildingType()
{
	return m_Building_Type;
}

//==========================
//�����̎�ނ�ݒ�
//==========================
void CBuilding::SetBuildingType(BUILDING_TYPE type)
{
	m_Building_Type = type;
}

//==========================
//���f���̔ԍ����擾
//==========================
int CBuilding::GetModelIdx()
{
	return m_nModelIdx;
}

//==========================
//���f���̔ԍ���ݒ�
//==========================
void CBuilding::SetModelIdx(int Idx)
{
	m_nModelIdx = Idx;
}

//==========================
//�v���C���[�Ƃ̓����蔻��
//==========================
void CBuilding::ColisionPlayer()
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

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		if (pPlayer->GetPosOld().z + 10.0f <= GetPos().z + GetVtxMin().z
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x)
		{//��O
			pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, pPlayer->GetMove().y, 0.0f));
			pPlayer->SetPos(D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y, GetPos().z + GetVtxMin().z - 10.0f));
		}
		else if (pPlayer->GetPosOld().z - 10.0f >= GetPos().z + GetVtxMax().z
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x)
		{//��
			pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, pPlayer->GetMove().y, 0.0f));
			pPlayer->SetPos(D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y, GetPos().z + GetVtxMax().z + 10.0f));
		}
		else if (pPlayer->GetPosOld().x - 10.0f >= GetPos().x + GetVtxMax().x
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z)
		{//�E
			pPlayer->SetMove(D3DXVECTOR3(0.0f, pPlayer->GetMove().y, pPlayer->GetMove().z));
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x+ GetVtxMax().x+10.0f, pPlayer->GetPos().y, pPlayer->GetPos().z));
		}
		else if (pPlayer->GetPosOld().x + 10.0f <= GetPos().x + GetVtxMin().x
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z)
		{//��
			pPlayer->SetMove(D3DXVECTOR3(0.0f, pPlayer->GetMove().y, pPlayer->GetMove().z));
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMin().x - 10.0f, pPlayer->GetPos().y, pPlayer->GetPos().z));
		}
		break;
	}
}

//==========================
//���f�����������̎��̓����蔻��
//==========================
void CBuilding::ColisionPlayerWide()
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

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		if (pPlayer->GetPosOld().z + 10.0f <= GetPos().z + GetVtxMin().x
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z)
		{//��O
			pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, pPlayer->GetMove().y, 0.0f));
			pPlayer->SetPos(D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y, GetPos().z + GetVtxMin().x - 10.0f));
		}
		else if (pPlayer->GetPosOld().z - 10.0f >= GetPos().z + GetVtxMax().x
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z)
		{//��
			pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, pPlayer->GetMove().y, 0.0f));
			pPlayer->SetPos(D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y, GetPos().z + GetVtxMax().x + 10.0f));
		}
		else if (pPlayer->GetPosOld().x - 10.0f >= GetPos().x + GetVtxMax().z
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x)
		{//�E
			pPlayer->SetMove(D3DXVECTOR3(0.0f, pPlayer->GetMove().y, pPlayer->GetMove().z));
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMax().z + 10.0f, pPlayer->GetPos().y, pPlayer->GetPos().z));
		}
		else if (pPlayer->GetPosOld().x + 10.0f <= GetPos().x + GetVtxMin().z
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x)
		{//��
			pPlayer->SetMove(D3DXVECTOR3(0.0f, pPlayer->GetMove().y, pPlayer->GetMove().z));
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMin().z - 10.0f, pPlayer->GetPos().y, pPlayer->GetPos().z));
		}
		break;
	}
}

//==========================
//�G�Ƃ̓����蔻��
//==========================
void  CBuilding::ColisionEnemy()
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

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//�I�u�W�F�N�g���v���C���[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		
		if (pEnemy->GetPosOld().z + 10.0f <= GetPos().z + GetVtxMin().z
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x)
		{//��O
			pEnemy->SetMove(D3DXVECTOR3(pEnemy->GetMove().x, pEnemy->GetMove().y, 0.0f));
			pEnemy->SetPos(D3DXVECTOR3(pEnemy->GetPos().x, pEnemy->GetPos().y, GetPos().z + GetVtxMin().z - 10.0f));
		}
		if (pEnemy->GetPosOld().z - 10.0f >= GetPos().z + GetVtxMax().z
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x)
		{//��
			pEnemy->SetMove(D3DXVECTOR3(pEnemy->GetMove().x, pEnemy->GetMove().y, 0.0f));
			pEnemy->SetPos(D3DXVECTOR3(pEnemy->GetPos().x, pEnemy->GetPos().y, GetPos().z + GetVtxMax().z + 10.0f));
		}
		else if (pEnemy->GetPosOld().x - 10.0f >= GetPos().x + GetVtxMax().x
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z)
		{//�E
			pEnemy->SetMove(D3DXVECTOR3(0.0f, pEnemy->GetMove().y, pEnemy->GetMove().z));
			pEnemy->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMax().x + 10.0f, pEnemy->GetPos().y, pEnemy->GetPos().z));
		}
		else if (pEnemy->GetPosOld().x + 10.0f <= GetPos().x + GetVtxMin().x
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z)
		{//��
			pEnemy->SetMove(D3DXVECTOR3(0.0f, pEnemy->GetMove().y, pEnemy->GetMove().z));
			pEnemy->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMin().x - 10.0f, pEnemy->GetPos().y, pEnemy->GetPos().z));
		}
		
		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);

	}
}

//==========================
//���f�����������̎��̓G�Ƃ̓����蔻��
//==========================
void CBuilding::ColisionEnemyWide()
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

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//�I�u�W�F�N�g���v���C���[�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		if (pEnemy->GetPosOld().z + 10.0f <= GetPos().z + GetVtxMin().x
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z)
		{//��O
			pEnemy->SetMove(D3DXVECTOR3(pEnemy->GetMove().x, pEnemy->GetMove().y, 0.0f));
			pEnemy->SetPos(D3DXVECTOR3(pEnemy->GetPos().x, pEnemy->GetPos().y, GetPos().z + GetVtxMin().x - 10.0f));
		}
		else if (pEnemy->GetPosOld().z - 10.0f >= GetPos().z + GetVtxMax().x
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z)
		{//��
			pEnemy->SetMove(D3DXVECTOR3(pEnemy->GetMove().x, pEnemy->GetMove().y, 0.0f));
			pEnemy->SetPos(D3DXVECTOR3(pEnemy->GetPos().x, pEnemy->GetPos().y, GetPos().z + GetVtxMax().x + 10.0f));
		}
		else if (pEnemy->GetPosOld().x - 10.0f >= GetPos().x + GetVtxMax().z
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x)
		{//�E
			pEnemy->SetMove(D3DXVECTOR3(0.0f, pEnemy->GetMove().y, pEnemy->GetMove().z));
			pEnemy->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMax().z + 10.0f, pEnemy->GetPos().y, pEnemy->GetPos().z));
		}
		else if (pEnemy->GetPosOld().x + 10.0f <= GetPos().x + GetVtxMin().z
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x)
		{//��
			pEnemy->SetMove(D3DXVECTOR3(0.0f, pEnemy->GetMove().y, pEnemy->GetMove().z));
			pEnemy->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMin().z - 10.0f, pEnemy->GetPos().y, pEnemy->GetPos().z));
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}
}