//==========================
// 
// �`���[�g���A���|�b�v�A�b�v�\��[TutorialPopup.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "TutorialPopup.h"
#include "texture.h"
#include "manager.h"

//�ÓI�����o������
const int CTutorialPopup::PRIORITY = 3;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CTutorialPopup::CTutorialPopup(int nPriority) :
	CObject2D(nPriority),//���R���X�g���N�^
	m_nTexIdx(0),//�e�N�X�`���̔ԍ�
	m_transparency(0.0f),//�����x
	m_input(false)//���͔���
{

}

//==========================
//�f�X�g���N�^
//==========================
CTutorialPopup::~CTutorialPopup()
{

}

//==========================
//����������
//==========================
HRESULT CTutorialPopup::Init()
{
	//�����ݒ�
	CObject2D::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CTutorialPopup::Uninit()
{
	//�I������
	CObject2D::Uninit();
}

//==========================
//�X�V����
//==========================
void  CTutorialPopup::Update()
{
	if (!m_input)
	{//�L�[���͂���Ă��Ȃ�

		//�s�����ɂ���
		MakeOpaque();
	}
	else
	{//�L�[���͂���Ă���

		//�����ɂ���
		MakeTransparent();
	}
	

	//�X�V����
	CObject2D::Update();

	if (m_transparency <= 0.0f)
	{//�����ɂȂ���

		Uninit();
	}
}

//==========================
//�`�揈��
//==========================
void CTutorialPopup::Draw()
{
	//�`�揈��
	CObject2D::Draw();
}

//==========================
//�I�u�W�F�N�g2D����
//==========================
CTutorialPopup* CTutorialPopup::Create()
{
	//�C���X�^���X����
	CTutorialPopup* pSampleObject2D = DBG_NEW CTutorialPopup;

	//�ʒu�̐ݒ�
	pSampleObject2D->SetPos({ 640.0f, 340.0f, 0.0f });

	//�傫���̐ݒ�
	pSampleObject2D->SetSize(250.0f, 350.0f);

	//����������
	pSampleObject2D->Init();

	//�F�̐ݒ�
	pSampleObject2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	//�e�N�X�`���̐ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pSampleObject2D->m_nTexIdx = pTex->Regist("data\\TEXTURE\\33_Symmetry.png");
	pSampleObject2D->BindTexture(pTex->GetAdress(pSampleObject2D->m_nTexIdx));

	//�e�N�X�`���̑傫���ݒ�
	pSampleObject2D->SetTexSize(1.0f, 1.0f, 0.0f);

	return pSampleObject2D;
}

//==========================
//�s�����ɂ���
//==========================
void CTutorialPopup::MakeOpaque()
{
	//�F���擾
	D3DXCOLOR col = GetCol();
	
	if (col.a >= 1.0f)
	{//�s�����ɂȂ��Ă�
		return;
	}

	//�����x���グ��
	m_transparency = col.a + 0.1f;

	//�F�̐ݒ�
	SetCol(D3DXCOLOR(col.r, col.g, col.b, m_transparency));
}

//==========================
//�����ɂ���
//==========================
void CTutorialPopup::MakeTransparent()
{
	D3DXCOLOR col = GetCol();

	if (col.a <= 0.0f)
	{//�����ɂȂ��Ă�
		return;
	}

	//�����x��������
	m_transparency = col.a - 0.1f;

	//�F�̐ݒ�
	SetCol(D3DXCOLOR(col.r, col.g, col.b, m_transparency));
}

//==========================
//�L�[����
//==========================
void CTutorialPopup::KeyInput()
{
	if (m_input)
	{//���łɃ{�^����������Ă���
		return;
	}

	m_input = true;
}