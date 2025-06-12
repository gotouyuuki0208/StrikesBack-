//==========================
// 
// �`���[�g���A���̔w�i����[tutorialbg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"tutorialbg.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int CTutorialBg::PRIORITY = 3;//�`��D��x
//========================
//�R���X�g���N�^
//========================
CTutorialBg::CTutorialBg(int nPriority):CObject2D(nPriority)
{
	
}

//========================
//�f�X�g���N�^
//========================
CTutorialBg::~CTutorialBg()
{

}

//========================
//�����ݒ�
//========================
HRESULT CTutorialBg::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void CTutorialBg::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void CTutorialBg::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void CTutorialBg::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
CTutorialBg* CTutorialBg::Create()
{
	//�C���X�^���X����
	CTutorialBg* pTutorialBg = DBG_NEW CTutorialBg;

	//�ʒu�̐ݒ�
	pTutorialBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//�T�C�Y�ݒ�
	pTutorialBg->SetSize(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);

	//�F��ݒ�
	pTutorialBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));

	//�����ݒ�
	pTutorialBg->Init();

	return pTutorialBg;
}