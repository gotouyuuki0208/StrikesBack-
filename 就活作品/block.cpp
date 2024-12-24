//==========================
// 
// �u���b�N[block.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "block.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CBlock::PRIORITY = 2;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBlock::CBlock(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBlock::~CBlock()
{

}

//==========================
//����������
//==========================
HRESULT CBlock::Init()
{
	//�T�C�Y�ݒ�
	SetSize();

	//�����ݒ�
	CObjectX::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBlock::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CBlock::Update()
{
	//�X�V����
	CObjectX::Update();
}

//==========================
//�`�揈��
//==========================
void CBlock::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CBlock* pBlock = DBG_NEW CBlock;

	//�ʒu�̐ݒ�
	pBlock->SetPos(pos);

	//�X�P�[���̐ݒ�
	pBlock->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBlock->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pBlock->BindModel(pModel->GetMeshAdress(pBlock->m_nModelIdx),
		pModel->GetBuffMatAdress(pBlock->m_nModelIdx),
		pModel->GetNumMatAdress(pBlock->m_nModelIdx),
		pModel->GetTexIdx(pBlock->m_nModelIdx));

	//����������
	pBlock->Init();

	pBlock->SetType(TYPE::BLOCK);
	return pBlock;
}