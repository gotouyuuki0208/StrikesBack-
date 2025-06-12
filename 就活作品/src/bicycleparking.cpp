//==========================
// 
// ���֏�[bicycleparking.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bicycleparking.h"
#include"model.h"
#include"manager.h"

//�ÓI�����o������
const int CBParking::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBParking::CBParking(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBParking::~CBParking()
{

}

//==========================
//����������
//==========================
HRESULT CBParking::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBParking::Uninit()
{
	//�I������
	CBuilding::Uninit();

}

//==========================
//�X�V����
//==========================
void CBParking::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CBParking::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBParking* CBParking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CBParking* pApartment = DBG_NEW CBParking;

	//�ʒu�̐ݒ�
	pApartment->SetPos(pos);

	//�����̐ݒ�
	pApartment->SetRot(rot);

	//�X�P�[���̐ݒ�
	pApartment->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pApartment->SetModelIdx(pModel->Regist("data\\MODEL\\bicycleparking.x"));
	pApartment->BindModel(pModel->GetMeshAdress(pApartment->GetModelIdx()),
		pModel->GetBuffMatAdress(pApartment->GetModelIdx()),
		pModel->GetNumMatAdress(pApartment->GetModelIdx()),
		pModel->GetTexIdx(pApartment->GetModelIdx()));

	//����������
	pApartment->Init();

	//�^�C�v��ݒ�
	pApartment->SetType(TYPE::BUILDING);
	pApartment->SetBuildingType(BUILDING_TYPE::BPARKING);

	return pApartment;
}