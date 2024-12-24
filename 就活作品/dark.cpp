//==========================
// 
// �w�i����[bg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"dark.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int CDark::PRIORITY = 4;//�`��D��x
//========================
//�R���X�g���N�^
//========================
CDark::CDark(int nPriority) :CObject2D(nPriority)
{

}

//========================
//�f�X�g���N�^
//========================
CDark::~CDark()
{

}

//========================
//�����ݒ�
//========================
HRESULT CDark::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void CDark::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void CDark::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void CDark::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
CDark* CDark::Create()
{
	//�C���X�^���X����
	CDark* pDark = DBG_NEW CDark;

	//�e�N�X�`���ݒ�
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pDark->m_nTexIdx = pTex->Regist(texname);
	pDark->BindTexture(pTex->GetAdress(pDark->m_nTexIdx));*/

	//�ʒu�̐ݒ�
	pDark->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//�T�C�Y�ݒ�
	pDark->SetSize(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);

	//�F��ݒ�
	pDark->SetCor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));

	//�����ݒ�
	pDark->Init();

	return pDark;
}