//==========================
// 
// �w�i����[opeUI.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"opeUI.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int COpeUI::PRIORITY = 4;//�`��D��x
//========================
//�R���X�g���N�^
//========================
COpeUI::COpeUI(int nPriority) :
CObject2D(nPriority),
m_nTexIdx(0)
{

}

//========================
//�f�X�g���N�^
//========================
COpeUI::~COpeUI()
{

}

//========================
//�����ݒ�
//========================
HRESULT COpeUI::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void COpeUI::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void COpeUI::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void COpeUI::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
COpeUI* COpeUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char texname[256])
{
	//�C���X�^���X����
	COpeUI* pOpeUI = DBG_NEW COpeUI;

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pOpeUI->m_nTexIdx = pTex->Regist(texname);
	pOpeUI->BindTexture(pTex->GetAdress(pOpeUI->m_nTexIdx));

	//�ʒu�̐ݒ�
	pOpeUI->SetPos(pos);

	//�T�C�Y�ݒ�
	pOpeUI->SetSize(size.y, size.x);

	//�F��ݒ�
	pOpeUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�����ݒ�
	pOpeUI->Init();

	return pOpeUI;
}