//==========================
// 
// �x���`�v���X[benchpress.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "benchpress.h"
#include "manager.h"
#include "model.h"


//�ÓI�����o������
const int CBenchPress::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBenchPress::CBenchPress(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBenchPress::~CBenchPress()
{

}

//==========================
//����������
//==========================
HRESULT CBenchPress::Init()
{
	//�T�C�Y�ݒ�
	//SetSize();

	//�����ݒ�
	CObjectX::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBenchPress::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CBenchPress::Update()
{
	//�X�V����
	CObjectX::Update();
}

//==========================
//�`�揈��
//==========================
void CBenchPress::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBenchPress* CBenchPress::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CBenchPress* pBenchPress = DBG_NEW CBenchPress;

	//�ʒu�̐ݒ�
	pBenchPress->SetPos(pos);

	//�X�P�[���̐ݒ�
	pBenchPress->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBenchPress->m_nModelIdx = pModel->Regist("data\\MODEL\\benchpress.x");
	pBenchPress->BindModel(pModel->GetMeshAdress(pBenchPress->m_nModelIdx),
		pModel->GetBuffMatAdress(pBenchPress->m_nModelIdx),
		pModel->GetNumMatAdress(pBenchPress->m_nModelIdx),
		pModel->GetTexIdx(pBenchPress->m_nModelIdx));

	//����������
	pBenchPress->Init();

	return pBenchPress;
}