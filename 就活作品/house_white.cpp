//==========================
// 
// ������[house_white.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "house_white.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CHouseWhite::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CHouseWhite::CHouseWhite(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CHouseWhite::~CHouseWhite()
{

}

//==========================
//����������
//==========================
HRESULT CHouseWhite::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CHouseWhite::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CHouseWhite::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CHouseWhite::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CHouseWhite* CHouseWhite::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CHouseWhite* pHouse = DBG_NEW CHouseWhite;

	//�ʒu�̐ݒ�
	pHouse->SetPos(pos);

	//�����̐ݒ�
	pHouse->SetRot(rot);

	//�X�P�[���̐ݒ�
	pHouse->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pHouse->SetModelIdx(pModel->Regist("data\\MODEL\\House_002.x"));
	pHouse->BindModel(pModel->GetMeshAdress(pHouse->GetModelIdx()),
		pModel->GetBuffMatAdress(pHouse->GetModelIdx()),
		pModel->GetNumMatAdress(pHouse->GetModelIdx()),
		pModel->GetTexIdx(pHouse->GetModelIdx()));

	//����������
	pHouse->Init();

	//�^�C�v��ݒ�
	pHouse->SetType(TYPE::BUILDING);
	pHouse->SetBuildingType(BUILDING_TYPE::HOUSEWHITE);

	return pHouse;
}