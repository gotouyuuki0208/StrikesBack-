//==========================
// 
// �d��[pole.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "pole.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CPole::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CPole::CPole(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CPole::~CPole()
{

}

//==========================
//����������
//==========================
HRESULT CPole::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CPole::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CPole::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CPole::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CPole* CPole::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CPole* pHouse = DBG_NEW CPole;

	//�ʒu�̐ݒ�
	pHouse->SetPos(pos);

	//�����̐ݒ�
	pHouse->SetRot(rot);

	//�X�P�[���̐ݒ�
	pHouse->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pHouse->SetModelIdx(pModel->Regist("data\\MODEL\\pole.x"));
	pHouse->BindModel(pModel->GetMeshAdress(pHouse->GetModelIdx()),
		pModel->GetBuffMatAdress(pHouse->GetModelIdx()),
		pModel->GetNumMatAdress(pHouse->GetModelIdx()),
		pModel->GetTexIdx(pHouse->GetModelIdx()));

	//����������s
	pHouse->Init();

	//�^�C�v��ݒ�
	pHouse->SetType(TYPE::BUILDING);
	pHouse->SetBuildingType(BUILDING_TYPE::POLE);

	return pHouse;
}