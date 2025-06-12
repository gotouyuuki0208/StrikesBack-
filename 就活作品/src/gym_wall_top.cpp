//==========================
// 
// �̈�ٕǏ㕔[gym_wall_top.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "gym_wall_top.h"
#include "model.h"
#include "manager.h"

//�ÓI�����o������
const int CGymwalltop::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CGymwalltop::CGymwalltop(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CGymwalltop::~CGymwalltop()
{

}

//==========================
//����������
//==========================
HRESULT CGymwalltop::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CGymwalltop::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CGymwalltop::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CGymwalltop::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CGymwalltop* CGymwalltop::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CGymwalltop* pGymwalltop = DBG_NEW CGymwalltop;

	//�ʒu�̐ݒ�
	pGymwalltop->SetPos(pos);

	//�����̐ݒ�
	pGymwalltop->SetRot(rot);

	//�X�P�[���̐ݒ�
	pGymwalltop->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGymwalltop->SetModelIdx(pModel->Regist("data\\MODEL\\gym_wall_top.x"));
	pGymwalltop->BindModel(pModel->GetMeshAdress(pGymwalltop->GetModelIdx()),
		pModel->GetBuffMatAdress(pGymwalltop->GetModelIdx()),
		pModel->GetNumMatAdress(pGymwalltop->GetModelIdx()),
		pModel->GetTexIdx(pGymwalltop->GetModelIdx()));

	//����������
	pGymwalltop->Init();

	//�^�C�v��ݒ�
	pGymwalltop->SetType(TYPE::BUILDING);
	pGymwalltop->SetBuildingType(BUILDING_TYPE::GYMWALLTOP);

	return pGymwalltop;
}