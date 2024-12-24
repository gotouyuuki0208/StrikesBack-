//==========================
// 
// �^�C�g�����S[Over.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"GameOver.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int COver::PRIORITY = 4;//�`��D��x
int  COver::m_nTexIdx = 0;//�e�N�X�`��ID
//========================
//�R���X�g���N�^
//========================
COver::COver(int nPriority) :CObject2D(nPriority)
{

}

//========================
//�f�X�g���N�^
//========================
COver::~COver()
{

}

//========================
//�����ݒ�
//========================
HRESULT COver::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void COver::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void COver::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void COver::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
COver* COver::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	COver* pOver = DBG_NEW COver;

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pOver->m_nTexIdx = pTex->Regist("data\\TEXTURE\\GameOver.png");
	pOver->BindTexture(pTex->GetAdress(pOver->m_nTexIdx));

	//�ʒu�̐ݒ�
	pOver->SetPos(pos);

	//�T�C�Y�ݒ�
	pOver->SetSize(100.0f, 350.0f);

	//�F��ݒ�
	pOver->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�����ݒ�
	pOver->Init();

	return pOver;
}