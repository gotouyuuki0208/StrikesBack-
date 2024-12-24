//==========================
// 
// �����̃h�A[room_door.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"room_door.h"
#include"model.h"
#include"manager.h"

//�ÓI�����o������
const int CRoomDoor::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CRoomDoor::CRoomDoor(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CRoomDoor::~CRoomDoor()
{

}

//==========================
//����������
//==========================
HRESULT CRoomDoor::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CRoomDoor::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CRoomDoor::Update()
{
	//�X�V����
	//CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CRoomDoor::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CRoomDoor* CRoomDoor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CRoomDoor* pConveni = DBG_NEW CRoomDoor;

	//�ʒu�̐ݒ�
	pConveni->SetPos(pos);

	//�����̐ݒ�
	pConveni->SetRot(rot);

	//�X�P�[���̐ݒ�
	pConveni->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\door.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//����������
	pConveni->Init();

	//�^�C�v��ݒ�
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::ROOMDOOR);

	return pConveni;
}