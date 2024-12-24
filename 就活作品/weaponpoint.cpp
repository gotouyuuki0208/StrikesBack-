//==========================
// 
// ����̈ʒu�\��[weaponpoint.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "weaponpoint.h"
#include "texture.h"
#include "manager.h"

//�ÓI�����o������
const int CWeaponPoint::PRIORITY = 3;//�`�揇
const float CWeaponPoint::MOVE = 0.1f;//�ړ���
const float CWeaponPoint::DISTANCE = 5.0f;//�ړ����鋗��

//==========================
//�R���X�g���N�^
//==========================
CWeaponPoint::CWeaponPoint(int nPriority) :
CBillBoard(nPriority),//���R���X�g���N�^
m_nTexIdx(0),//�e�N�X�`���̔ԍ�
m_MoveDirection(true),//�ړ������؂�ւ�����
m_FirstPos(0.0f)//�ŏ��̈ʒu
{

}

//==========================
//�f�X�g���N�^
//==========================
CWeaponPoint::~CWeaponPoint()
{

}

//==========================
//����������
//==========================
HRESULT CWeaponPoint::Init()
{
	//�����ݒ�
	CBillBoard::Init();

	//�ŏ��̈ʒu��ۑ�
	m_FirstPos = GetPos().y;
	
	return S_OK;
}

//==========================
//�I������
//==========================
void CWeaponPoint::Uninit()
{
	//�I������
	CBillBoard::Uninit();
}

//==========================
//�X�V����
//==========================
void  CWeaponPoint::Update()
{
	//�ړ�����
	Move();

	//�X�V����
	CBillBoard::Update();
}

//==========================
//�`�揈��
//==========================
void CWeaponPoint::Draw()
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
CWeaponPoint* CWeaponPoint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CWeaponPoint* pWeaponPoint = DBG_NEW CWeaponPoint;

	//�ʒu�̐ݒ�
	pWeaponPoint->SetPos(pos);

	//�傫���̐ݒ�
	pWeaponPoint->SetSize(size);

	//�F�̐ݒ�
	pWeaponPoint->SetCor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));//�ɐݒ�

	//����������
	pWeaponPoint->Init();

	//�e�N�X�`���̐ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pWeaponPoint->m_nTexIdx = pTex->Regist("data\\TEXTURE\\point.png");
	pWeaponPoint->BindTexture(pTex->GetAdress(pWeaponPoint->m_nTexIdx));

	return pWeaponPoint;
}

//==========================
//�ړ�����
//==========================
void CWeaponPoint::Move()
{
	if (m_MoveDirection)
	{
		//�オ��
		SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + MOVE, GetPos().z));
	}
	else
	{
		//������
		SetPos(D3DXVECTOR3(GetPos().x, GetPos().y - MOVE, GetPos().z));
	}

	if (GetPos().y >= (m_FirstPos + DISTANCE))
	{//�ŏ��̈ʒu������̋��������Ȃ����Ƃ�

		GetPos().y = m_FirstPos + DISTANCE;
		m_MoveDirection = false;//������
	}
	else if (GetPos().y <= m_FirstPos)
	{//�ŏ��̈ʒu������̋����Ⴍ�Ȃ����Ƃ�

		GetPos().y = m_FirstPos;
		m_MoveDirection = true;//�オ��
	}
}