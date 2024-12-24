//==========================
// 
// ����[curb.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "curb.h"
#include "manager.h"
#include "texture.h"

//�ÓI�����o������
const int CCurb::PRIORITY = 0;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CCurb::CCurb(int nPriority):
CFild(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CCurb::~CCurb()
{

}

//==========================
//����������
//==========================
HRESULT CCurb::Init()
{
	//�����ݒ�
	CFild::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CCurb::Uninit()
{
	//�I������
	CFild::Uninit();
}

//==========================
//�X�V����
//==========================
void CCurb::Update()
{
	//�X�V����
	CFild::Update();
}

//==========================
//�`�揈��
//==========================
void CCurb::Draw()
{
	//�`�揈��
	CFild::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CCurb* CCurb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CCurb* pFild = DBG_NEW CCurb;

	//�ʒu�̐ݒ�
	pFild->SetPos(D3DXVECTOR3(pos.x, 0.5f, pos.z));

	//�傫���̐ݒ�
	pFild->SetSize(size);

	//�傫���̐ݒ�
	pFild->SetRot(rot);

	//�F�̐ݒ�
	pFild->SetCor(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));

	//����������
	pFild->Init();

	//�e�N�X�`���ݒ�
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pFild->m_nTexIdx = pTex->Regist("data\\TEXTURE\\blood.png");
	pFild->BindTexture(pTex->GetAdress(pFild->m_nTexIdx));*/

	//�^�C�v�ݒ�
	pFild->SetType(TYPE::FILD);
	pFild->SetFild(FILDTYPE::CURB);

	return pFild;
}