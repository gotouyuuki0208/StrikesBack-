//==========================
// 
// �^�C�g�����S[TitleLogo.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"TitleLogo.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int CTitleLogo::PRIORITY = 4;//�`��D��x
int  CTitleLogo::m_nTexIdx = 0;//�e�N�X�`��ID
//========================
//�R���X�g���N�^
//========================
CTitleLogo::CTitleLogo(int nPriority) :CObject2D(nPriority)
{

}

//========================
//�f�X�g���N�^
//========================
CTitleLogo::~CTitleLogo()
{

}

//========================
//�����ݒ�
//========================
HRESULT CTitleLogo::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void CTitleLogo::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void CTitleLogo::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void CTitleLogo::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
CTitleLogo* CTitleLogo::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CTitleLogo* pTitleLogo = DBG_NEW CTitleLogo;

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pTitleLogo->m_nTexIdx = pTex->Regist("data\\TEXTURE\\logo.png");
	pTitleLogo->BindTexture(pTex->GetAdress(pTitleLogo->m_nTexIdx));

	//�ʒu�̐ݒ�
	pTitleLogo->SetPos(pos);

	//�T�C�Y�ݒ�
	pTitleLogo->SetSize(150.0f,250.0f);

	//�F��ݒ�
	pTitleLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�����ݒ�
	pTitleLogo->Init();

	return pTitleLogo;
}