//==========================
// 
// �̈�ِ���[gym_front.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "gym_front.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CGymfront::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CGymfront::CGymfront(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CGymfront::~CGymfront()
{

}

//==========================
//����������
//==========================
HRESULT CGymfront::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CGymfront::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CGymfront::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CGymfront::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CGymfront* CGymfront::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CGymfront* pGymfront = DBG_NEW CGymfront;

	//�ʒu�̐ݒ�
	pGymfront->SetPos(pos);

	//�����̐ݒ�
	pGymfront->SetRot(rot);

	//�X�P�[���̐ݒ�
	pGymfront->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGymfront->SetModelIdx(pModel->Regist("data\\MODEL\\gym_front.x"));
	pGymfront->BindModel(pModel->GetMeshAdress(pGymfront->GetModelIdx()),
		pModel->GetBuffMatAdress(pGymfront->GetModelIdx()),
		pModel->GetNumMatAdress(pGymfront->GetModelIdx()),
		pModel->GetTexIdx(pGymfront->GetModelIdx()));

	//����������
	pGymfront->Init();

	//�^�C�v��ݒ�
	pGymfront->SetType(TYPE::BUILDING);
	pGymfront->SetBuildingType(BUILDING_TYPE::GYMFRONT);

	return pGymfront;
}