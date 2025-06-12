//==========================
// 
// ���ݕ�[drink.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "drink.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CDrink::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CDrink::CDrink(int nPriority) :CItem(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CDrink::~CDrink()
{

}

//==========================
//����������
//==========================
HRESULT CDrink::Init()
{
	//�����ݒ�
	CItem::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CDrink::Uninit()
{
	//�I������
	CItem::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CDrink::Update()
{
	//�X�V����
	CItem::Update();
}

//==========================
//�`�揈��
//==========================
void CDrink::Draw()
{
	//�`�揈��
	CItem::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CDrink* CDrink::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CDrink* pDrink = DBG_NEW CDrink;

	//�ʒu�̐ݒ�
	pDrink->SetPos(pos);

	//�X�P�[���̐ݒ�
	pDrink->SetScale(scale);

	
	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pDrink->SetModelIdx(pModel->Regist("data\\MODEL\\drink.x"));
	pDrink->BindModel(pModel->GetMeshAdress(pDrink->GetModelIdx()),
		pModel->GetBuffMatAdress(pDrink->GetModelIdx()),
		pModel->GetNumMatAdress(pDrink->GetModelIdx()),
		pModel->GetTexIdx(pDrink->GetModelIdx()));

	//����������
	pDrink->Init();

	return pDrink;
}