//==========================
// 
// ���\��[arrowUI.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "arrowUI.h"
#include "manager.h"
#include "texture.h"
#include"arrowpoint.h"

//�ÓI�����o������
const int CArrowUI::PRIORITY = 3;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CArrowUI::CArrowUI(int nPriority) :
CObject3D(nPriority),
m_nTexIdx(0),
m_Draw(false)
{

}

//==========================
//�f�X�g���N�^
//==========================
CArrowUI::~CArrowUI()
{

}

//==========================
//����������
//==========================
HRESULT CArrowUI::Init()
{
	//�����ݒ�
	CObject3D::Init();

	m_ArrowPoint = CArrowPoint::Create({ 200.0f, 0.0f,0.0f }, { 50.0f,0.0f ,50.0f });;

	return S_OK;
}

//==========================
//�I������
//==========================
void CArrowUI::Uninit()
{
	//�I������
	CObject3D::Uninit();
}

//==========================
//�X�V����
//==========================
void CArrowUI::Update()
{
	//�`�攻��
	JudgeDraw();

	//�����̕ύX
	ChangeDirection();

	//�X�V����
	CObject3D::Update();
}

//==========================
//�`�揈��
//==========================
void CArrowUI::Draw()
{
	if (!m_Draw)
	{
		return;
	}

	//�`�揈��
	CObject3D::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CArrowUI* CArrowUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CArrowUI* pArrowUI = DBG_NEW CArrowUI;

	//�ʒu�̐ݒ�
	pArrowUI->SetPos(pos);

	//�傫���̐ݒ�
	pArrowUI->SetSize(size);

	//�F�̐ݒ�
	pArrowUI->SetCol({ 1.0f,0.0f,0.0f,1.0f });

	//����������
	pArrowUI->Init();

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pArrowUI->m_nTexIdx = pTex->Regist("data\\TEXTURE\\arrow.png");
	pArrowUI->BindTexture(pTex->GetAdress(pArrowUI->m_nTexIdx));

	return pArrowUI;
}

//==========================
//�`�悷�邩����
//==========================
void CArrowUI::JudgeDraw()
{
	m_Draw = false;

	//�s�����̓G�̐����擾
	int Enemynum = CManager::GetInstance()->GetGameManager()->GetActiveEnemy();

	if (Enemynum <= 0)
	{//�G�����Ȃ�

		//�`�悷��
		m_Draw = true;
	}
}

//==========================
//�����̕ύX
//==========================
void CArrowUI::ChangeDirection()
{
	//�x�N�g�����Z�o
	D3DXVECTOR3 pos = m_ArrowPoint->GetPos() - GetPos();

	//�x�N�g���𐳋K��
	D3DXVec3Normalize(&pos, &pos);

	float m_roty = atan2f(pos.x, pos.z);

	SetRot({ 0.0f,m_roty ,0.0f });
}