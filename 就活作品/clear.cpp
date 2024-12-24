//==========================
// 
// �^�C�g�����S[Clear.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"clear.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int CClear::PRIORITY = 4;//�`��D��x
int  CClear::m_nTexIdx = 0;//�e�N�X�`��ID
//========================
//�R���X�g���N�^
//========================
CClear::CClear(int nPriority) :CObject2D(nPriority)
{

}

//========================
//�f�X�g���N�^
//========================
CClear::~CClear()
{

}

//========================
//�����ݒ�
//========================
HRESULT CClear::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void CClear::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void CClear::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void CClear::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
CClear* CClear::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CClear* pClear = DBG_NEW CClear;

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pClear->m_nTexIdx = pTex->Regist("data\\TEXTURE\\GameClear.png");
	pClear->BindTexture(pTex->GetAdress(pClear->m_nTexIdx));

	//�ʒu�̐ݒ�
	pClear->SetPos(pos);

	//�T�C�Y�ݒ�
	pClear->SetSize(100.0f, 350.0f);

	//�F��ݒ�
	pClear->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�����ݒ�
	pClear->Init();

	return pClear;
}