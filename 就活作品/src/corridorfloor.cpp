//==========================
// 
// �L���̏�[corridorfloor.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"corridorfloor.h"
#include"model.h"
#include"manager.h"

//�ÓI�����o������
const int CCorridorfloor::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CCorridorfloor::CCorridorfloor(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CCorridorfloor::~CCorridorfloor()
{

}

//==========================
//����������
//==========================
HRESULT CCorridorfloor::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CCorridorfloor::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CCorridorfloor::Update()
{
	//�X�V����
	//CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CCorridorfloor::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CCorridorfloor* CCorridorfloor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CCorridorfloor* pConveni = DBG_NEW CCorridorfloor;

	//�ʒu�̐ݒ�
	pConveni->SetPos(pos);

	//�����̐ݒ�
	pConveni->SetRot(rot);

	//�X�P�[���̐ݒ�
	pConveni->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\corridorfild.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//����������
	pConveni->Init();

	//�^�C�v��ݒ�
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::CORRIDORFLOOR);

	return pConveni;
}