//==========================
// 
// �r���{�[�h��HP�Q�[�W[hpgauge3D.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "hpgauge3D.h"
#include "texture.h"
#include "manager.h"

//�ÓI�����o������
const int CHPGauge3D::PRIORITY = 3;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CHPGauge3D::CHPGauge3D(int nPriority) :
CBillBoard(nPriority),//���R���X�g���N�^
m_nTexIdx(0),//�e�N�X�`���̔ԍ�
m_HP(0),//HP�̐��l
m_MaxHP(0),//�ő�HP�̐��l
m_Targetlength(0.0f),//�ړI�̒���
m_length(0.0f),//����
m_Ratio(0.0f),//HP�̊���
m_Draw(true)//�`�攻��
{	

}

//==========================
//�f�X�g���N�^
//==========================
CHPGauge3D::~CHPGauge3D()
{

}

//==========================
//����������
//==========================
HRESULT CHPGauge3D::Init()
{
	//�����ݒ�
	CBillBoard::Init();
	
	m_length = GetSize().x * 2;//�Q�[�W�̒�����ݒ�

	return S_OK;
}

//==========================
//�I������
//==========================
void CHPGauge3D::Uninit()
{
	//�I������
	CBillBoard::Uninit();
}

//==========================
//�X�V����
//==========================
void  CHPGauge3D::Update()
{
	SetLength();//�Q�[�W�Ȓ�����ݒ�

	SwitchCor();//�F�̕ύX

	SetVtx();//���_���̐ݒ�
}

//==========================
//�`�揈��
//==========================
void CHPGauge3D::Draw()
{
	if (!m_Draw)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�`�揈��
	CBillBoard::Draw();

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================
//�I�u�W�F�N�g2D����
//==========================
CHPGauge3D* CHPGauge3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int hp)
{
	//�C���X�^���X����
	CHPGauge3D* pHPGauge3D = DBG_NEW CHPGauge3D;

	//�ʒu�̐ݒ�
	pHPGauge3D->SetPos(pos);

	//�傫���̐ݒ�
	pHPGauge3D->SetSize(size);

	//����������
	pHPGauge3D->Init();

	//HP�̐ݒ�
	pHPGauge3D->SetHP(hp);//HP��ݒ�
	pHPGauge3D->m_MaxHP = hp;//�ő�HP��ݒ�

	return pHPGauge3D;
}

//==========================
//hp��ݒ�
//==========================
void CHPGauge3D::SetHP(int hp)
{
	m_HP = hp;
}

//==========================
//���_���̐ݒ�
//==========================
void CHPGauge3D::SetVtx()
{
	if (GetVtxBuff() == nullptr)
	{
		return;
	}
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@���擾


	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-GetSize().x,+GetSize().y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_length - GetSize().x, +GetSize().y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-GetSize().x, -GetSize().y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_length - GetSize().x, -GetSize().y, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = GetCor();
	pVtx[1].col = GetCor();
	pVtx[2].col = GetCor();
	pVtx[3].col = GetCor();

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//==========================
//�F�̕ύX
//==========================
void CHPGauge3D::SwitchCor()
{
	if (m_Ratio <= 0.2f)
	{
		SetCor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else if (m_Ratio <= 0.5f)
	{
		SetCor(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
	}
	else
	{
		SetCor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}
}

//==========================
//�Q�[�W�̒�����ݒ�
//==========================
void CHPGauge3D::SetLength()
{
	//HP�̊��������߂�
	m_Ratio = static_cast<float>(m_HP) / static_cast<float>(m_MaxHP);

	//�ړI�̒�����ݒ�
	m_Targetlength = ((GetSize().x * 2) * m_Ratio);

	if (m_Targetlength <= m_length)
	{//���݂̒������ړI�̒�����蒷���Ƃ�

		m_length -= 1.0f;//�Z������

		if (m_Targetlength >= m_length)
		{//�ړI�̒������Z���Ȃ����Ƃ�

			m_length = m_Targetlength;//���������ɂ���
		}
	}
}

//==========================
//�\�����Ȃ�
//==========================
void CHPGauge3D::EraseGauge()
{
	m_Draw = false;
}

//==========================
//�\������
//==========================
void CHPGauge3D::DrawGauge()
{
	m_Draw = true;
}