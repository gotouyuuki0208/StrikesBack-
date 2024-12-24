//==========================
// 
// ��[fence.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "fence.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CFence::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CFence::CFence(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CFence::~CFence()
{

}

//==========================
//����������
//==========================
HRESULT CFence::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CFence::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CFence::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CFence::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CFence* CFence::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CFence* pFence = DBG_NEW CFence;

	//�ʒu�̐ݒ�
	pFence->SetPos(pos);

	//�����̐ݒ�
	pFence->SetRot(rot);

	//�X�P�[���̐ݒ�
	pFence->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pFence->SetModelIdx(pModel->Regist("data\\MODEL\\Fence.x"));
	pFence->BindModel(pModel->GetMeshAdress(pFence->GetModelIdx()),
		pModel->GetBuffMatAdress(pFence->GetModelIdx()),
		pModel->GetNumMatAdress(pFence->GetModelIdx()),
		pModel->GetTexIdx(pFence->GetModelIdx()));

	//����������
	pFence->Init();

	//�^�C�v��ݒ�
	pFence->SetType(TYPE::BUILDING);
	pFence->SetBuildingType(BUILDING_TYPE::FENCE);

	return pFence;
}