//==========================
// 
// ��[garden.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "garden.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CGarden::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CGarden::CGarden(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CGarden::~CGarden()
{

}

//==========================
//����������
//==========================
HRESULT CGarden::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CGarden::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CGarden::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CGarden::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CGarden* CGarden::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CGarden* pGarden = DBG_NEW CGarden;

	//�ʒu�̐ݒ�
	pGarden->SetPos(pos);

	//�����̐ݒ�
	pGarden->SetRot(rot);

	//�X�P�[���̐ݒ�
	pGarden->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGarden->SetModelIdx(pModel->Regist("data\\MODEL\\Garden.x"));
	pGarden->BindModel(pModel->GetMeshAdress(pGarden->GetModelIdx()),
		pModel->GetBuffMatAdress(pGarden->GetModelIdx()),
		pModel->GetNumMatAdress(pGarden->GetModelIdx()),
		pModel->GetTexIdx(pGarden->GetModelIdx()));

	//����������
	pGarden->Init();

	//�^�C�v��ݒ�
	pGarden->SetType(TYPE::BUILDING);
	pGarden->SetBuildingType(BUILDING_TYPE::GARDEN);

	return pGarden;
}