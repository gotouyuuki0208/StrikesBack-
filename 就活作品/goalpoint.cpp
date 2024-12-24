//==========================
// 
// �X�e�[�W�J�ڈʒu�̈ʒu�\��[Goalpoint.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "Goalpoint.h"
#include "texture.h"
#include "manager.h"

//�ÓI�����o������
const int CGoalPoint::PRIORITY = 3;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CGoalPoint::CGoalPoint(int nPriority) :CBillBoard(nPriority), m_nTexIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CGoalPoint::~CGoalPoint()
{

}

//==========================
//����������
//==========================
HRESULT CGoalPoint::Init()
{
	//�����ݒ�
	CBillBoard::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CGoalPoint::Uninit()
{
	//�I������
	CBillBoard::Uninit();
}

//==========================
//�X�V����
//==========================
void  CGoalPoint::Update()
{
	//�X�V����
	CBillBoard::Update();
}

//==========================
//�`�揈��
//==========================
void CGoalPoint::Draw()
{
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
CGoalPoint* CGoalPoint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CGoalPoint* pGoalPoint = DBG_NEW CGoalPoint;

	//�ʒu�̐ݒ�
	pGoalPoint->SetPos(pos);

	//�傫���̐ݒ�
	pGoalPoint->SetSize(size);

	//�F�̐ݒ�
	pGoalPoint->SetCor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));//�΂ɐݒ�

	//����������
	pGoalPoint->Init();

	//�e�N�X�`���̐ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pGoalPoint->m_nTexIdx = pTex->Regist("data\\TEXTURE\\point.png");
	pGoalPoint->BindTexture(pTex->GetAdress(pGoalPoint->m_nTexIdx));

	return pGoalPoint;
}