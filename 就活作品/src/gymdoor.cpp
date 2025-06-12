//==========================
// 
// �̈�ٕ�[gym_Door.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "gymdoor.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CGymDoor::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CGymDoor::CGymDoor(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CGymDoor::~CGymDoor()
{

}

//==========================
//����������
//==========================
HRESULT CGymDoor::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CGymDoor::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CGymDoor::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CGymDoor::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CGymDoor* CGymDoor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CGymDoor* pGymDoor = DBG_NEW CGymDoor;

	//�ʒu�̐ݒ�
	pGymDoor->SetPos(pos);

	//�����̐ݒ�
	pGymDoor->SetRot(rot);

	//�X�P�[���̐ݒ�
	pGymDoor->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGymDoor->SetModelIdx(pModel->Regist("data\\MODEL\\gymdoor.x"));
	pGymDoor->BindModel(pModel->GetMeshAdress(pGymDoor->GetModelIdx()),
		pModel->GetBuffMatAdress(pGymDoor->GetModelIdx()),
		pModel->GetNumMatAdress(pGymDoor->GetModelIdx()),
		pModel->GetTexIdx(pGymDoor->GetModelIdx()));

	//����������
	pGymDoor->Init();

	//�^�C�v��ݒ�
	pGymDoor->SetType(TYPE::BUILDING);
	pGymDoor->SetBuildingType(BUILDING_TYPE::GYMDOOR);

	return pGymDoor;
}