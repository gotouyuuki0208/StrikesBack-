//==========================
// 
// [TitleStart.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"titlestart.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int CTitleStart::PRIORITY = 4;//�`��D��x
int  CTitleStart::m_nTexIdx = 0;//�e�N�X�`��ID
//========================
//�R���X�g���N�^
//========================
CTitleStart::CTitleStart(int nPriority) :CObject2D(nPriority)
{

}

//========================
//�f�X�g���N�^
//========================
CTitleStart::~CTitleStart()
{

}

//========================
//�����ݒ�
//========================
HRESULT CTitleStart::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void CTitleStart::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void CTitleStart::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void CTitleStart::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
CTitleStart* CTitleStart::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CTitleStart* pTitleStart = DBG_NEW CTitleStart;

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pTitleStart->m_nTexIdx = pTex->Regist("data\\TEXTURE\\gamestart.png");
	pTitleStart->BindTexture(pTex->GetAdress(pTitleStart->m_nTexIdx));

	//�ʒu�̐ݒ�
	pTitleStart->SetPos(pos);

	//�T�C�Y�ݒ�
	pTitleStart->SetSize(50.0f, 200.0f);

	//�F��ݒ�
	pTitleStart->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�����ݒ�
	pTitleStart->Init();

	return pTitleStart;
}