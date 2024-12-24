//==========================
// 
// �p�[�e�B�N������[particle.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"particle.h"
#include"manager.h"
#include"texture.h"

//�ÓI�����o�ϐ�
const int CParticle::PRIORITY = 3;//�`�揇
//==========================
// �R���X�g���N�^
//==========================
CParticle::CParticle(int priority):CBillBoard(priority),m_nLife(30), m_cor(1.0f), m_nTexIdx(0)
{
	m_posmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Width = 10.0f;//��
	m_Vertical = 10.0f;//�c
	m_speed = 0.0f;//���x
}

//==========================
// �f�X�g���N�^
//==========================
CParticle::~CParticle(void)
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CParticle::Init(void)
{
	m_posmove.x = sinf((float)(rand() % 629 - 314) / 100.0f) * (float)(rand() % 100 + 1) / m_speed;
	m_posmove.y = sinf((float)(rand() % 629 - 314) / 100.0f) * (float)(rand() % 100 + 1) / m_speed;
	m_posmove.y = cosf((float)(rand() % 629) / 100.0f + 5.0f) * (float)(rand() % 100 + 1) / m_speed;

	CBillBoard::Init();

	return S_OK;
}

//==========================
// �I������
//==========================
void CParticle::Uninit(void)
{
	CBillBoard::Uninit();
}

//==========================
// �X�V����
//==========================
void CParticle::Update(void)
{
	m_nLife--;
	
	//�ʒu�ݒ�
	SetPos(D3DXVECTOR3(GetPos().x + m_posmove.x, (GetPos().y + m_posmove.y) - 5.0f, GetPos().z + m_posmove.z));

	m_cor -= 0.01f;

	SetCor(D3DXCOLOR(GetCor().r, GetCor().g, GetCor().b, m_cor));//�F�̐ݒ�

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	CBillBoard::Update();
}

//==========================
// �`�揈��
//==========================
void CParticle::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillBoard::Draw();//�`�揈��

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
}

//========================
//�I�u�W�F�N�g2D����
//========================
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXCOLOR cor, int life, float Width, float Vertical,float speed)
{
	CParticle* pParticle = DBG_NEW CParticle;

	//�ʒu�̐ݒ�
	pParticle->SetPos(pos);

	//�F�̐ݒ�
	pParticle->SetCor(cor);

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pParticle->m_nTexIdx = pTex->Regist("data\\TEXTURE\\effect000.jpg");
	pParticle->BindTexture(pTex->GetAdress(pParticle->m_nTexIdx));

	//�T�C�Y�̐ݒ�
	pParticle->SetSize(D3DXVECTOR3(Width, Vertical, 0.0f));

	//�ړ����x�̐ݒ�
	pParticle->m_speed = speed;
	
	//����������
	pParticle->Init();

	//�����̐ݒ�
	pParticle->m_nLife = life;

	return pParticle;
}