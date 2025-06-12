//==========================
// 
// �o�X�P�b�g�S�[��[basketgoal.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "basketgoal.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CBasketgoal::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBasketgoal::CBasketgoal(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBasketgoal::~CBasketgoal()
{

}

//==========================
//����������
//==========================
HRESULT CBasketgoal::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBasketgoal::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CBasketgoal::Update()
{
	//�X�V����
	//CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CBasketgoal::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBasketgoal* CBasketgoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CBasketgoal* pBasketgoal = DBG_NEW CBasketgoal;

	//�ʒu�̐ݒ�
	pBasketgoal->SetPos(pos);

	//�����̐ݒ�
	pBasketgoal->SetRot(rot);

	//�X�P�[���̐ݒ�
	pBasketgoal->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBasketgoal->SetModelIdx(pModel->Regist("data\\MODEL\\basketgoal.x"));
	pBasketgoal->BindModel(pModel->GetMeshAdress(pBasketgoal->GetModelIdx()),
		pModel->GetBuffMatAdress(pBasketgoal->GetModelIdx()),
		pModel->GetNumMatAdress(pBasketgoal->GetModelIdx()),
		pModel->GetTexIdx(pBasketgoal->GetModelIdx()));

	//����������
	pBasketgoal->Init();

	//�^�C�v��ݒ�
	pBasketgoal->SetType(TYPE::BUILDING);
	pBasketgoal->SetBuildingType(BUILDING_TYPE::BASKETGOAL);

	return pBasketgoal;
}