//==========================
// 
// �w�i����[bg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"bg.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int CBg::PRIORITY = 4;//�`��D��x
int  CBg::m_nTexIdx = 0;//�e�N�X�`��ID
//========================
//�R���X�g���N�^
//========================
CBg::CBg(int nPriority):CObject2D(nPriority)
{
	
}

//========================
//�f�X�g���N�^
//========================
CBg::~CBg()
{

}

//========================
//�����ݒ�
//========================
HRESULT CBg::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void CBg::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void CBg::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void CBg::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
CBg* CBg::Create(const char texname[256])
{
	//�C���X�^���X����
	CBg* pBg = DBG_NEW CBg;

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pBg->m_nTexIdx = pTex->Regist(texname);
	pBg->BindTexture(pTex->GetAdress(pBg->m_nTexIdx));

	//�ʒu�̐ݒ�
	pBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//�T�C�Y�ݒ�
	pBg->SetSize(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);

	//�F��ݒ�
	pBg->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�����ݒ�
	pBg->Init();

	return pBg;
}