//==========================
// 
// �e[shadow.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "shadow.h"
#include "manager.h"
#include "texture.h"

//�ÓI�����o������
const int CShadow::PRIORITY = 3;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CShadow::CShadow(int nPriority):
CObject3D(nPriority),//���R���X�g���N�^
m_nTexIdx(0)//�e�N�X�`���̔ԍ�
{

}

//==========================
//�f�X�g���N�^
//==========================
CShadow::~CShadow()
{

}

//==========================
//����������
//==========================
HRESULT CShadow::Init()
{
	//�����ݒ�
	CObject3D::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CShadow::Uninit()
{
	//�I������
	CObject3D::Uninit();
}

//==========================
//�X�V����
//==========================
void CShadow::Update()
{
	//�X�V����
	CObject3D::Update();
}

//==========================
//�`�揈��
//==========================
void CShadow::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//���Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`�揈��
	CObject3D::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==========================
//�I�u�W�F�N�g����
//==========================
CShadow* CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CShadow* pShadow = DBG_NEW CShadow;

	//�ʒu�̐ݒ�
	pShadow->SetPos(pos);

	//�傫���̐ݒ�
	pShadow->SetSize(size);

	//�F�̐ݒ�
	pShadow->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	//����������
	pShadow->Init();

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pShadow->m_nTexIdx = pTex->Regist("data\\TEXTURE\\shadow000.jpg");
	pShadow->BindTexture(pTex->GetAdress(pShadow->m_nTexIdx));

	return pShadow;
}

//==========================
//�ړ�����
//==========================
void CShadow::Move(D3DXVECTOR3 pos)
{
	//�ʒu��ύX
	SetPos(D3DXVECTOR3(pos.x, 1.0f, pos.z));
}