//==========================
// 
// �������UI�̔w�i[UIbg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"UIbg.h"


//�ÓI�����o�̏�����
const int CUIBg::PRIORITY = 4;//�`��D��x

//========================
//�R���X�g���N�^
//========================
CUIBg::CUIBg(int nPriority) :CObject2D(nPriority)
{

}

//========================
//�f�X�g���N�^
//========================
CUIBg::~CUIBg()
{

}

//========================
//�����ݒ�
//========================
HRESULT CUIBg::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void CUIBg::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void CUIBg::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void CUIBg::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
CUIBg* CUIBg::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CUIBg* pUIBg = DBG_NEW CUIBg;

	//�ʒu�̐ݒ�
	pUIBg->SetPos(pos);

	//�T�C�Y�ݒ�
	pUIBg->SetSize(20.0f,150.0f);

	//�F��ݒ�
	pUIBg->SetCor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

	//�����ݒ�
	pUIBg->Init();

	return pUIBg;
}