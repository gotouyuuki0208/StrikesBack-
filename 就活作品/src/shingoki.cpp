//==========================
// 
// �M���@[shingoki.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "shingoki.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CShingoki::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CShingoki::CShingoki(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CShingoki::~CShingoki()
{

}

//==========================
//����������
//==========================
HRESULT CShingoki::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CShingoki::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CShingoki::Update()
{
	//�X�V����
	//CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CShingoki::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CShingoki* CShingoki::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CShingoki* pHouse = DBG_NEW CShingoki;

	//�ʒu�̐ݒ�
	pHouse->SetPos(pos);

	//�����̐ݒ�
	pHouse->SetRot(rot);

	//�X�P�[���̐ݒ�
	pHouse->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pHouse->SetModelIdx(pModel->Regist("data\\MODEL\\shingoki.x"));
	pHouse->BindModel(pModel->GetMeshAdress(pHouse->GetModelIdx()),
		pModel->GetBuffMatAdress(pHouse->GetModelIdx()),
		pModel->GetNumMatAdress(pHouse->GetModelIdx()),
		pModel->GetTexIdx(pHouse->GetModelIdx()));

	//����������
	pHouse->Init();

	//�^�C�v��ݒ�
	pHouse->SetType(TYPE::BUILDING);
	pHouse->SetBuildingType(BUILDING_TYPE::HOUSE);

	return pHouse;
}