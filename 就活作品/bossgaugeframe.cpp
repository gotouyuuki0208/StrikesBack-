//==========================
// 
// �{�X��HP�Q�[�W�̘g[bossgaugeframe.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bossgaugeframe.h"
#include "texture.h"
#include "manager.h"

//�ÓI�����o������
const int CBossGaugeFrame::PRIORITY = 4;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBossGaugeFrame::CBossGaugeFrame(int nPriority) :
CObject2D(nPriority),//���R���X�g���N�^
m_nTexIdx(0)//�e�N�X�`���̔ԍ�
{

}

//==========================
//�f�X�g���N�^
//==========================
CBossGaugeFrame::~CBossGaugeFrame()
{

}

//==========================
//����������
//==========================
HRESULT CBossGaugeFrame::Init()
{
	//�����ݒ�
	CObject2D::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CBossGaugeFrame::Uninit()
{
	//�I������
	CObject2D::Uninit();
}

//==========================
//�X�V����
//==========================
void  CBossGaugeFrame::Update()
{
	//���_���̐ݒ�
	SetVtx();
}

//==========================
//�`�揈��
//==========================
void CBossGaugeFrame::Draw()
{
	//�`�揈��
	CObject2D::Draw();
}

//==========================
//�I�u�W�F�N�g2D����
//==========================
CBossGaugeFrame* CBossGaugeFrame::Create(D3DXVECTOR3 pos, float vertical, float width)
{
	//�C���X�^���X����
	CBossGaugeFrame* pBossHPGauge = DBG_NEW CBossGaugeFrame;

	//�ʒu�̐ݒ�
	pBossHPGauge->SetPos(pos);

	//�傫���̐ݒ�
	pBossHPGauge->SetSize(vertical, width);

	//�F�̐ݒ�
	pBossHPGauge->SetCor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//����������
	pBossHPGauge->Init();

	return pBossHPGauge;
}

//==========================
//���_���̐ݒ�
//==========================
void CBossGaugeFrame::SetVtx()
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@���擾

	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(GetPos().x - (GetWidth() * 2) - 1.0f, GetPos().y - GetVertical(), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + 1.0f, GetPos().y - GetVertical(), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x - (GetWidth() * 2) - 1.0f, GetPos().y + GetVertical(), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + 1.0f, GetPos().y + GetVertical(), 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = GetCor();
	pVtx[1].col = GetCor();
	pVtx[2].col = GetCor();
	pVtx[3].col = GetCor();

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}