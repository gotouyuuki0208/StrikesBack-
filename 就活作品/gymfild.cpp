//==========================
// 
// ����[curb.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "gymfild.h"
#include "manager.h"
#include "texture.h"

//�ÓI�����o������
const int CGymFild::PRIORITY = 0;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CGymFild::CGymFild(int nPriority) :
	CFild(nPriority)
{

}

//==========================
//�f�X�g���N�^
//==========================
CGymFild::~CGymFild()
{

}

//==========================
//����������
//==========================
HRESULT CGymFild::Init()
{
	//�����ݒ�
	CFild::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CGymFild::Uninit()
{
	//�I������
	CFild::Uninit();
}

//==========================
//�X�V����
//==========================
void CGymFild::Update()
{
	//�X�V����
	CFild::Update();
}

//==========================
//�`�揈��
//==========================
void CGymFild::Draw()
{
	//�`�揈��
	CFild::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CGymFild* CGymFild::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CGymFild* pFild = DBG_NEW CGymFild;

	//�ʒu�̐ݒ�
	pFild->SetPos(D3DXVECTOR3(pos.x, 0.0f, pos.z));

	//�傫���̐ݒ�
	pFild->SetSize(size);

	//�傫���̐ݒ�
	pFild->SetRot(rot);

	//�F�̐ݒ�
	pFild->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//����������
	pFild->Init();

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pFild->SetTexIdx(pTex->Regist("data\\TEXTURE\\gymfild.png"));
	pFild->BindTexture(pTex->GetAdress(pFild->GetTexIdx()));

	//�^�C�v�ݒ�
	pFild->SetType(TYPE::FILD);
	pFild->SetFild(FILDTYPE::GYMFILD);

	return pFild;
}