//==========================
// 
// �n��[fild.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "fild.h"
#include "manager.h"
#include "texture.h"

//�ÓI�����o������
const int CFild::PRIORITY = 0;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CFild::CFild(int nPriority) :
CObject3D(nPriority),
m_nTexIdx(0),
m_FildType(FILDTYPE::NONE)
{

}

//==========================
//�f�X�g���N�^
//==========================
CFild::~CFild()
{

}

//==========================
//����������
//==========================
HRESULT CFild::Init()
{
	//�����ݒ�
	CObject3D::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CFild::Uninit()
{
	//�I������
	CObject3D::Uninit();
}

//==========================
//�X�V����
//==========================
void CFild::Update()
{
	//�X�V����
	CObject3D::Update();
}

//==========================
//�`�揈��
//==========================
void CFild::Draw()
{
	//�`�揈��
	CObject3D::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CFild* CFild::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CFild* pFild = DBG_NEW CFild;

	//�ʒu�̐ݒ�
	pFild->SetPos(pos);

	//�傫���̐ݒ�
	pFild->SetSize(size);
	
	//�����̐ݒ�
	pFild->SetRot(rot);

	//�F�̐ݒ�
	pFild->SetCol(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
	//pFild->SetCor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//����������
	pFild->Init();

	//�e�N�X�`���ݒ�
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pFild->m_nTexIdx = pTex->Regist("data\\TEXTURE\\blood.png");
	pFild->BindTexture(pTex->GetAdress(pFild->m_nTexIdx));*/

	//�^�C�v�ݒ�
	pFild->SetType(TYPE::FILD);
	pFild->SetFild(FILDTYPE::FILD);

	return pFild;
}

//==========================
//�n�ʂ̎�ނ��擾
//==========================
CFild::FILDTYPE CFild::GetFildType()
{
	return m_FildType;
}

//==========================
//�n�ʂ̎�ނ�ݒ�
//==========================
void CFild::SetFild(FILDTYPE type)
{
	m_FildType = type;
}

//==========================
//�e�N�X�`���ԍ���ݒ�
//==========================
void CFild::SetTexIdx(int Idx)
{
	m_nTexIdx = Idx;
}

//==========================
//�e�N�X�`���ԍ����擾
//==========================
int CFild::GetTexIdx()
{
	return m_nTexIdx;
}