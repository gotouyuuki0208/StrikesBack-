//==========================
// 
// �r���{�[�h�`��T���v��[sample_billBoard.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sample_billBoard.h"
#include "texture.h"
#include "manager.h"

//�ÓI�����o������
const int CSampleBillBoard::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CSampleBillBoard::CSampleBillBoard(int nPriority) :CBillBoard(nPriority), m_nTexIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CSampleBillBoard::~CSampleBillBoard()
{

}

//==========================
//����������
//==========================
HRESULT CSampleBillBoard::Init()
{
	//�����ݒ�
	CBillBoard::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CSampleBillBoard::Uninit()
{
	//�I������
	CBillBoard::Uninit();
}

//==========================
//�X�V����
//==========================
void  CSampleBillBoard::Update()
{
	//�X�V����
	CBillBoard::Update();
}

//==========================
//�`�揈��
//==========================
void CSampleBillBoard::Draw()
{
	//�`�揈��
	CBillBoard::Draw();
}

//==========================
//�I�u�W�F�N�g2D����
//==========================
CSampleBillBoard* CSampleBillBoard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CSampleBillBoard* pSampleBillBoard = DBG_NEW CSampleBillBoard;

	//�ʒu�̐ݒ�
	pSampleBillBoard->SetPos(pos);

	//�傫���̐ݒ�
	pSampleBillBoard->SetSize(size);

	//����������
	pSampleBillBoard->Init();

	//�e�N�X�`���̐ݒ�
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pSampleBillBoard->m_nTexIdx = pTex->Regist("data\\TEXTURE\\effect000.jpg");
	pSampleBillBoard->BindTexture(pTex->GetAdress(pSampleBillBoard->m_nTexIdx));*/

	return pSampleBillBoard;
}