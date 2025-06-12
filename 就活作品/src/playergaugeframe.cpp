//==========================
// 
// �v���C���[��HP�Q�[�W�̘g[playergaugeframe.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "playergaugeframe.h"
#include "texture.h"
#include "manager.h"

//�ÓI�����o������
const int CPlayerHPGaugeFrame::PRIORITY = 4;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CPlayerHPGaugeFrame::CPlayerHPGaugeFrame(int nPriority) :
CObject2D(nPriority),//���R���X�g���N�^
m_nTexIdx(0)//�e�N�X�`���̔ԍ�
{

}

//==========================
//�f�X�g���N�^
//==========================
CPlayerHPGaugeFrame::~CPlayerHPGaugeFrame()
{

}

//==========================
//����������
//==========================
HRESULT CPlayerHPGaugeFrame::Init()
{
	//�����ݒ�
	CObject2D::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CPlayerHPGaugeFrame::Uninit()
{
	//�I������
	CObject2D::Uninit();
}

//==========================
//�X�V����
//==========================
void  CPlayerHPGaugeFrame::Update()
{
	//���_���̐ݒ�
	SetVtx();
}

//==========================
//�`�揈��
//==========================
void CPlayerHPGaugeFrame::Draw()
{
	//�`�揈��
	CObject2D::Draw();
}

//==========================
//�I�u�W�F�N�g2D����
//==========================
CPlayerHPGaugeFrame* CPlayerHPGaugeFrame::Create(D3DXVECTOR3 pos, float vertical, float width)
{
	//�C���X�^���X����
	CPlayerHPGaugeFrame* pPlayerHPGauge = DBG_NEW CPlayerHPGaugeFrame;

	//�ʒu�̐ݒ�
	pPlayerHPGauge->SetPos(pos);

	//�傫���̐ݒ�
	pPlayerHPGauge->SetSize(vertical, width);

	//�F�̐ݒ�
	pPlayerHPGauge->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//����������
	pPlayerHPGauge->Init();

	return pPlayerHPGauge;
}

//==========================
//���_���̐ݒ�
//==========================
void CPlayerHPGaugeFrame::SetVtx()
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//���_�o�b�t�@���擾

	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(GetPos().x - 1.0f, GetPos().y - GetVertical(), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + (GetWidth() * 2) + 1.0f, GetPos().y - GetVertical(), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x - 1.0f, GetPos().y + GetVertical(), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + (GetWidth() * 2) + 1.0f, GetPos().y + GetVertical(), 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = GetCol();
	pVtx[1].col = GetCol();
	pVtx[2].col = GetCol();
	pVtx[3].col = GetCol();

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}