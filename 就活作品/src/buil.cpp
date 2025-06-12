//==========================
// 
// �r��[buil.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"buil.h"
#include"model.h"
#include"manager.h"

//�ÓI�����o������
const int CBuil::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBuil::CBuil(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBuil::~CBuil()
{

}

//==========================
//����������
//==========================
HRESULT CBuil::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBuil::Uninit()
{
	//�I������
	CBuilding::Uninit();

}

//==========================
//�X�V����
//==========================
void CBuil::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CBuil::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBuil* CBuil::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CBuil* pBuil = DBG_NEW CBuil;

	//�ʒu�̐ݒ�
	pBuil->SetPos(pos);

	//�����̐ݒ�
	pBuil->SetRot(rot);

	//�X�P�[���̐ݒ�
	pBuil->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBuil->SetModelIdx(pModel->Regist("data\\MODEL\\buil.x"));
	pBuil->BindModel(pModel->GetMeshAdress(pBuil->GetModelIdx()),
		pModel->GetBuffMatAdress(pBuil->GetModelIdx()),
		pModel->GetNumMatAdress(pBuil->GetModelIdx()),
		pModel->GetTexIdx(pBuil->GetModelIdx()));

	//����������
	pBuil->Init();

	//�^�C�v��ݒ�
	pBuil->SetType(TYPE::BUILDING);
	pBuil->SetBuildingType(BUILDING_TYPE::BUILDING);

	return pBuil;
}