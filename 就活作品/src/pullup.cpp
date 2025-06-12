//==========================
// 
// �����@[pullup.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "pullup.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CPullUp::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CPullUp::CPullUp(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CPullUp::~CPullUp()
{

}

//==========================
//����������
//==========================
HRESULT CPullUp::Init()
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
void  CPullUp::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CPullUp::Update()
{
	//�X�V����
	CObjectX::Update();
}

//==========================
//�`�揈��
//==========================
void CPullUp::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CPullUp* CPullUp::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CPullUp* pPullUp = DBG_NEW CPullUp;

	//�ʒu�̐ݒ�
	pPullUp->SetPos(pos);

	//�X�P�[���̐ݒ�
	pPullUp->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pPullUp->m_nModelIdx = pModel->Regist("data\\MODEL\\pullup.x");
	pPullUp->BindModel(pModel->GetMeshAdress(pPullUp->m_nModelIdx),
		pModel->GetBuffMatAdress(pPullUp->m_nModelIdx),
		pModel->GetNumMatAdress(pPullUp->m_nModelIdx),
		pModel->GetTexIdx(pPullUp->m_nModelIdx));

	//����������
	pPullUp->Init();

	return pPullUp;
}