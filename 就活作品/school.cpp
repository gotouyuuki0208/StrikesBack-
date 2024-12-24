//==========================
// 
// �w�Z[school.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "school.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CSchool::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CSchool::CSchool(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CSchool::~CSchool()
{

}

//==========================
//����������
//==========================
HRESULT CSchool::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CSchool::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CSchool::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CSchool::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CSchool* CSchool::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CSchool* pConveni = DBG_NEW CSchool;

	//�ʒu�̐ݒ�
	pConveni->SetPos(pos);

	//�����̐ݒ�
	pConveni->SetRot(rot);

	//�X�P�[���̐ݒ�
	pConveni->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\school.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//����������
	pConveni->Init();

	//�^�C�v��ݒ�
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::SCHOOL);

	return pConveni;
}