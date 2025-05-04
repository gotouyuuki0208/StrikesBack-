//==========================
// 
// �L���̓V��[corridorceiling.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"corridorceiling.h"
#include"model.h"
#include"manager.h"

//�ÓI�����o������
const int CCorridorceiling::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CCorridorceiling::CCorridorceiling(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CCorridorceiling::~CCorridorceiling()
{

}

//==========================
//����������
//==========================
HRESULT CCorridorceiling::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CCorridorceiling::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CCorridorceiling::Update()
{
	//�X�V����
	//CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CCorridorceiling::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CCorridorceiling* CCorridorceiling::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CCorridorceiling* pConveni = DBG_NEW CCorridorceiling;

	//�ʒu�̐ݒ�
	pConveni->SetPos(pos);

	//�����̐ݒ�
	pConveni->SetRot(rot);

	//�X�P�[���̐ݒ�
	pConveni->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\corridorceiling.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//����������
	pConveni->Init();

	//�^�C�v��ݒ�
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::CORRIDORCEILING);

	return pConveni;
}