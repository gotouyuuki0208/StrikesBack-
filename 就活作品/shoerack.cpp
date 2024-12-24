//==========================
// 
// ���ʔ�[shoerack.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"shoerack.h"
#include"model.h"
#include"manager.h"

//�ÓI�����o������
const int CShoerack::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CShoerack::CShoerack(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CShoerack::~CShoerack()
{

}

//==========================
//����������
//==========================
HRESULT CShoerack::Init()
{
	//�����ݒ�
	CBuilding::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CShoerack::Uninit()
{
	//�I������
	CBuilding::Uninit();
}

//==========================
//�X�V����
//==========================
void CShoerack::Update()
{
	//�X�V����
	CBuilding::Update();
}

//==========================
//�`�揈��
//==========================
void CShoerack::Draw()
{
	//�`�揈��
	CBuilding::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CShoerack* CShoerack::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CShoerack* pConveni = DBG_NEW CShoerack;

	//�ʒu�̐ݒ�
	pConveni->SetPos(pos);

	//�����̐ݒ�
	pConveni->SetRot(rot);

	//�X�P�[���̐ݒ�
	pConveni->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\shoerack.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//����������
	pConveni->Init();

	//�^�C�v��ݒ�
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::SHOERACK);

	return pConveni;
}