//==========================
// 
// �K�[�h�G�t�F�N�g[guardeffect.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "guardeffect.h"
#include "manager.h"
#include "texture.h"

//�ÓI�����o������
const int CGuardEffect::PRIORITY = 3;//�`�揇
const float CGuardEffect::SUB_COL = 0.03f;//�F�̌��炷���l
//==========================
//�R���X�g���N�^
//==========================
CGuardEffect::CGuardEffect(int nPriority) :
	CObject3D(nPriority),//���R���X�g���N�^
	m_nTexIdx(0)//�e�N�X�`���̔ԍ�
{

}

//==========================
//�f�X�g���N�^
//==========================
CGuardEffect::~CGuardEffect()
{

}

//==========================
//����������
//==========================
HRESULT CGuardEffect::Init()
{
	//�����ݒ�
	CObject3D::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CGuardEffect::Uninit()
{
	//�I������
	CObject3D::Uninit();
}

//==========================
//�X�V����
//==========================
void CGuardEffect::Update()
{
	//�X�V����
	CObject3D::Update();
	
	//�F�̕ύX
	ChangeCol();
}

//==========================
//�`�揈��
//==========================
void CGuardEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//�J�����O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�`�揈��
	CObject3D::Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//==========================
//�I�u�W�F�N�g����
//==========================
CGuardEffect* CGuardEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CGuardEffect* pGuardEffect = DBG_NEW CGuardEffect;

	//�ʒu�̐ݒ�
	pGuardEffect->SetPos(pos);

	//�����̐ݒ�
	pGuardEffect->SetRot(rot);

	//�傫���̐ݒ�
	pGuardEffect->SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));

	//�F�̐ݒ�
	pGuardEffect->SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.3f));

	//����������
	pGuardEffect->Init();

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pGuardEffect->m_nTexIdx = pTex->Regist("data\\TEXTURE\\GuardEffect.png");
	pGuardEffect->BindTexture(pTex->GetAdress(pGuardEffect->m_nTexIdx));

	return pGuardEffect;
}

//==========================
//�F�̕ύX
//==========================
void CGuardEffect::ChangeCol()
{
	SetCol(D3DXCOLOR(GetCol().r, GetCol().g, GetCol().b, GetCol().a - SUB_COL));
}