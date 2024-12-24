//==========================
// 
// ��[wall.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"wall.h"
#include"model.h"
#include"manager.h"

//�ÓI�����o������
const int CWall::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CWall::CWall(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CWall::~CWall()
{

}

//==========================
//����������
//==========================
HRESULT CWall::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CWall::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CWall::Update()
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
}

//==========================
//�`�揈��
//==========================
void CWall::Draw()
{
	if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		//�`�揈��
		CBuilding::Draw();
	}
}

//==========================
//�I�u�W�F�N�g����
//==========================
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CWall* pConveni = DBG_NEW CWall;

	//�ʒu�̐ݒ�
	pConveni->SetPos(pos);

	//�����̐ݒ�
	pConveni->SetRot(rot);

	//�X�P�[���̐ݒ�
	pConveni->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\wall.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//����������
	pConveni->Init();

	//�^�C�v��ݒ�
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::WALL);

	return pConveni;
}