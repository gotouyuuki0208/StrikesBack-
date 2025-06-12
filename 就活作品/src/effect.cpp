//==========================
// 
// �G�t�F�N�g����[effect.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"effect.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int CEffect::PRIORITY = 3;//�`��D��x
int CEffect::m_nTexIdx = 0;//�e�N�X�`��ID

//==========================
// �R���X�g���N�^
//==========================
CEffect::CEffect(int Priority):
CBillBoard(Priority),//���R���X�g���N�^
m_nLife(30),//����
cor(1.0f),//�F
m_Vertical(0.0f),//�c�̒���
m_Width(0.0f)//���̒���
{

}

//==========================
// �f�X�g���N�^
//==========================
CEffect::~CEffect(void)
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CEffect::Init(void)
{
	//����������
	CBillBoard::Init();

	return S_OK;
}

//==========================
// �I������
//==========================
void CEffect::Uninit(void)
{
	//�I������
	CBillBoard::Uninit();
}

//==========================
// �X�V����
//==========================
void CEffect::Update(void)
{
	m_nLife--;//���������炷

	//����������
	m_Vertical -= 0.2f;
	m_Width -= 0.2f;
	SetSize(D3DXVECTOR3(m_Width, m_Vertical, 0.0f));

	cor -= 0.01f;//�����x�����炷
	
	SetCol(D3DXCOLOR(GetCol().r, GetCol().g, GetCol().b, cor));//�F�̐ݒ�

	if (m_nLife <= 0 || m_Vertical <= 0)
	{
		Uninit();
		return;
	}

	//�X�V����
	CBillBoard::Update();
}

//==========================
// �`�揈��
//==========================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`�揈��
	CBillBoard::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//========================
//�I�u�W�F�N�g2D����
//========================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR cor, float Vertical, float Width)
{
	CEffect* pEffect = DBG_NEW CEffect;

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	m_nTexIdx = pTex->Regist("data\\TEXTURE\\effect000.jpg");
	pEffect->BindTexture(pTex->GetAdress(m_nTexIdx));

	//�ʒu�̐ݒ�
	pEffect->SetPos(pos);

	//�F�̐ݒ�
	pEffect->SetCol(cor);

	//�T�C�Y�̐ݒ�
	pEffect->m_Width = Width;
	pEffect->m_Vertical = Vertical;
	pEffect->SetSize(D3DXVECTOR3(Width, Vertical, 0.0f));

	//����������
	pEffect->Init();

	return pEffect;
}