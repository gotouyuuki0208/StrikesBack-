//==========================
// 
// �A�p�[�g[apartment.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "apartment.h"
#include"model.h"
#include"manager.h"

//�ÓI�����o������
const int CApartment::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CApartment::CApartment(int nPriority) :
CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CApartment::~CApartment()
{

}

//==========================
//����������
//==========================
HRESULT CApartment::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CApartment::Uninit()
{
	//�I������
	CBuilding::Uninit();

}

//==========================
//�X�V����
//==========================
void CApartment::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CApartment::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CApartment* CApartment::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CApartment* pApartment = DBG_NEW CApartment;

	//�ʒu�̐ݒ�
	pApartment->SetPos(pos);

	//�����̐ݒ�
	pApartment->SetRot(rot);

	//�X�P�[���̐ݒ�
	pApartment->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pApartment->SetModelIdx(pModel->Regist("data\\MODEL\\apartment.x"));
	pApartment->BindModel(pModel->GetMeshAdress(pApartment->GetModelIdx()),
		pModel->GetBuffMatAdress(pApartment->GetModelIdx()),
		pModel->GetNumMatAdress(pApartment->GetModelIdx()),
		pModel->GetTexIdx(pApartment->GetModelIdx()));

	//����������
	pApartment->Init();

	//�^�C�v��ݒ�
	pApartment->SetType(TYPE::BUILDING);
	pApartment->SetBuildingType(BUILDING_TYPE::APARTMENT);

	return pApartment;
}