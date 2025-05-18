//==========================
// 
// HP�Q�[�W[bosshpgauge.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bosshpgauge.h"
#include "texture.h"
#include "manager.h"
#include "bossgaugeframe.h"

//�ÓI�����o������
const int CBossHPGauge::PRIORITY = 4;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBossHPGauge::CBossHPGauge(int nPriority) :
CObject2D(nPriority),//���R���X�g���N�^
m_nTexIdx(0),//�e�N�X�`���̔ԍ�
m_HP(0),//hp�̐��l
m_MaxHP(0),//�ő�HP�̐��l
m_Targetlength(0.0f),//�ړI�̒���
m_length(0.0f),//����
m_Ratio(0.0f)//HP�̊���
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossHPGauge::~CBossHPGauge()
{

}

//==========================
//����������
//==========================
HRESULT CBossHPGauge::Init()
{
	//�����ݒ�
	CObject2D::Init();

	m_length = GetWidth() * 2;//�Q�[�W�̒�����ݒ�

	return S_OK;
}

//==========================
//�I������
//==========================
void CBossHPGauge::Uninit()
{
	//�I������
	CObject2D::Uninit();
}

//==========================
//�X�V����
//==========================
void  CBossHPGauge::Update()
{
	//�Q�[�W�̒�����ݒ�
	SetLength();

	//�F�̕ύX
	SwitchCor();

	//���_���̐ݒ�
	SetVtx();
}

//==========================
//�`�揈��
//==========================
void CBossHPGauge::Draw()
{
	//�`�揈��
	CObject2D::Draw();
}

//==========================
//�I�u�W�F�N�g2D����
//==========================
CBossHPGauge* CBossHPGauge::Create(D3DXVECTOR3 pos, float vertical, float width)
{
	CBossGaugeFrame::Create(pos, vertical + 1.0f, width);

	//�C���X�^���X����
	CBossHPGauge* pBossHPGauge = DBG_NEW CBossHPGauge;

	//�ʒu�̐ݒ�
	pBossHPGauge->SetPos(pos);

	//�傫���̐ݒ�
	pBossHPGauge->SetSize(vertical, width);

	//�F�̐ݒ�
	pBossHPGauge->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//����������
	pBossHPGauge->Init();

	return pBossHPGauge;
}

//==========================
//hp��ݒ�
//==========================
void CBossHPGauge::SetHP(int hp)
{
	m_HP = hp;

	if (m_MaxHP == 0)
	{//�ő�HP���ݒ肳��Ă��Ȃ�

		m_MaxHP = hp;
	}
}

//==========================
//�Q�[�W�̒�����ݒ�
//==========================
void CBossHPGauge::SetLength()
{
	//HP�̊��������߂�
	m_Ratio = static_cast<float>(m_HP) / static_cast<float>(m_MaxHP);

	//�ړI�̒�����ݒ�
	m_Targetlength = ((GetWidth() * 2) * m_Ratio);

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
//�F�̕ύX
//==========================
void CBossHPGauge::SwitchCor()
{
	if (m_Ratio <= 0.2f)
	{
		SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else if (m_Ratio <= 0.5f)
	{
		SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
	}
	else
	{
		SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}
}

//==========================
//���_���̐ݒ�
//==========================
void CBossHPGauge::SetVtx()
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@���擾

	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(GetPos().x - m_length, GetPos().y - GetVertical(), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x, GetPos().y - GetVertical(), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x - m_length, GetPos().y + GetVertical(), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x, GetPos().y + GetVertical(), 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = GetCol();
	pVtx[1].col = GetCol();
	pVtx[2].col = GetCol();
	pVtx[3].col = GetCol();

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}