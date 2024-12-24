//==========================
// 
// [KnockDown.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"knockdown.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int CKnockDown::PRIORITY = 4;//�`��D��x
int  CKnockDown::m_nTexIdx = 0;//�e�N�X�`��ID

//========================
//�R���X�g���N�^
//========================
CKnockDown::CKnockDown(int nPriority) :CObject2D(nPriority)
{

}

//========================
//�f�X�g���N�^
//========================
CKnockDown::~CKnockDown()
{

}

//========================
//�����ݒ�
//========================
HRESULT CKnockDown::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void CKnockDown::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void CKnockDown::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void CKnockDown::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
CKnockDown* CKnockDown::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CKnockDown* pKnockDown = DBG_NEW CKnockDown;

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pKnockDown->m_nTexIdx = pTex->Regist("data\\TEXTURE\\NumberOfPeopleDefeated.png");
	pKnockDown->BindTexture(pTex->GetAdress(pKnockDown->m_nTexIdx));

	//�ʒu�̐ݒ�
	pKnockDown->SetPos(pos);

	//�T�C�Y�ݒ�
	pKnockDown->SetSize(50.0f, 200.0f);

	//�F��ݒ�
	pKnockDown->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�����ݒ�
	pKnockDown->Init();

	return pKnockDown;
}