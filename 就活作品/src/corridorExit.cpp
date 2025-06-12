//==========================
// 
// �L���̏o��[corridorExit.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "corridorExit.h"
#include"model.h"
#include"manager.h"

//�ÓI�����o������
const int CCorridorExit::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CCorridorExit::CCorridorExit(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CCorridorExit::~CCorridorExit()
{

}

//==========================
//����������
//==========================
HRESULT CCorridorExit::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CCorridorExit::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CCorridorExit::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CCorridorExit::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CCorridorExit* CCorridorExit::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CCorridorExit* pCorridorExit = DBG_NEW CCorridorExit;

	//�ʒu�̐ݒ�
	pCorridorExit->SetPos(pos);

	//�����̐ݒ�
	pCorridorExit->SetRot(rot);

	//�X�P�[���̐ݒ�
	pCorridorExit->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pCorridorExit->SetModelIdx(pModel->Regist("data\\MODEL\\corridorExit.x"));
	pCorridorExit->BindModel(pModel->GetMeshAdress(pCorridorExit->GetModelIdx()),
		pModel->GetBuffMatAdress(pCorridorExit->GetModelIdx()),
		pModel->GetNumMatAdress(pCorridorExit->GetModelIdx()),
		pModel->GetTexIdx(pCorridorExit->GetModelIdx()));

	//����������
	pCorridorExit->Init();

	//�^�C�v��ݒ�
	pCorridorExit->SetType(TYPE::BUILDING);
	pCorridorExit->SetBuildingType(BUILDING_TYPE::CEXIT);

	return pCorridorExit;
}