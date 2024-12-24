//==========================
// 
// �̈�ٕ�[gym_wall.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "gym_wall.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CGymwall::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CGymwall::CGymwall(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CGymwall::~CGymwall()
{

}

//==========================
//����������
//==========================
HRESULT CGymwall::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CGymwall::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CGymwall::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CGymwall::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CGymwall* CGymwall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CGymwall* pGymwall = DBG_NEW CGymwall;

	//�ʒu�̐ݒ�
	pGymwall->SetPos(pos);

	//�����̐ݒ�
	pGymwall->SetRot(rot);

	//�X�P�[���̐ݒ�
	pGymwall->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGymwall->SetModelIdx(pModel->Regist("data\\MODEL\\gym_wall.x"));
	pGymwall->BindModel(pModel->GetMeshAdress(pGymwall->GetModelIdx()),
		pModel->GetBuffMatAdress(pGymwall->GetModelIdx()),
		pModel->GetNumMatAdress(pGymwall->GetModelIdx()),
		pModel->GetTexIdx(pGymwall->GetModelIdx()));

	//����������
	pGymwall->Init();

	//�^�C�v��ݒ�
	pGymwall->SetType(TYPE::BUILDING);
	pGymwall->SetBuildingType(BUILDING_TYPE::GYMWALL);

	return pGymwall;
}