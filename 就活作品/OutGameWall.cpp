//==========================
// 
// �^�C�g���ƃ��U���g��ʂ̕�[OutGameWall.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "OutGameWall.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int COutGameWall::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
COutGameWall::COutGameWall(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
COutGameWall::~COutGameWall()
{

}

//==========================
//����������
//==========================
HRESULT COutGameWall::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  COutGameWall::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void COutGameWall::Update()
{
	//�X�V����
	//CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void COutGameWall::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
COutGameWall* COutGameWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	COutGameWall* pOutGameWall = DBG_NEW COutGameWall;

	//�ʒu�̐ݒ�
	pOutGameWall->SetPos(pos);

	//�����̐ݒ�
	pOutGameWall->SetRot(rot);

	//�X�P�[���̐ݒ�
	pOutGameWall->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pOutGameWall->SetModelIdx(pModel->Regist("data\\MODEL\\outgamewall.x"));
	pOutGameWall->BindModel(pModel->GetMeshAdress(pOutGameWall->GetModelIdx()),
		pModel->GetBuffMatAdress(pOutGameWall->GetModelIdx()),
		pModel->GetNumMatAdress(pOutGameWall->GetModelIdx()),
		pModel->GetTexIdx(pOutGameWall->GetModelIdx()));

	//����������
	pOutGameWall->Init();

	//�^�C�v��ݒ�
	pOutGameWall->SetType(TYPE::BUILDING);

	return pOutGameWall;
}