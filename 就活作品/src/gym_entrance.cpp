//==========================
// 
// �̈�ٓ���[gym_entrance.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "gym_entrance.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CGymentrance::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CGymentrance::CGymentrance(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CGymentrance::~CGymentrance()
{

}

//==========================
//����������
//==========================
HRESULT CGymentrance::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CGymentrance::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CGymentrance::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CGymentrance::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CGymentrance* CGymentrance::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CGymentrance* pGymentrance = DBG_NEW CGymentrance;

	//�ʒu�̐ݒ�
	pGymentrance->SetPos(pos);

	//�����̐ݒ�
	pGymentrance->SetRot(rot);

	//�X�P�[���̐ݒ�
	pGymentrance->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGymentrance->SetModelIdx(pModel->Regist("data\\MODEL\\gym_entrance.x"));
	pGymentrance->BindModel(pModel->GetMeshAdress(pGymentrance->GetModelIdx()),
		pModel->GetBuffMatAdress(pGymentrance->GetModelIdx()),
		pModel->GetNumMatAdress(pGymentrance->GetModelIdx()),
		pModel->GetTexIdx(pGymentrance->GetModelIdx()));

	//����������
	pGymentrance->Init();

	//�^�C�v��ݒ�
	pGymentrance->SetType(TYPE::BUILDING);
	pGymentrance->SetBuildingType(BUILDING_TYPE::GYMENTRANCE);

	return pGymentrance;
}