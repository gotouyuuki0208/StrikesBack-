//==========================
// 
// ��[house.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "house.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CHouse::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CHouse::CHouse(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CHouse::~CHouse()
{

}

//==========================
//����������
//==========================
HRESULT CHouse::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CHouse::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CHouse::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CHouse::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CHouse* CHouse::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CHouse* pHouse = DBG_NEW CHouse;

	//�ʒu�̐ݒ�
	pHouse->SetPos(pos);

	//�����̐ݒ�
	pHouse->SetRot(rot);

	//�X�P�[���̐ݒ�
	pHouse->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pHouse->SetModelIdx(pModel->Regist("data\\MODEL\\House_001.x"));
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