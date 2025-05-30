//==========================
// 
// �{�X��J�n���̍��w�i����[directionbg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"directionbg.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int CDirectionBg::PRIORITY = 4;//�`��D��x
//========================
//�R���X�g���N�^
//========================
CDirectionBg::CDirectionBg(int nPriority) :
	CObject2D(nPriority),
	m_CountFlame(0),
	m_FirstPos({0.0f,0.0f,0.0f}),
	m_Delete(false)
{

}

//========================
//�f�X�g���N�^
//========================
CDirectionBg::~CDirectionBg()
{

}

//========================
//�����ݒ�
//========================
HRESULT CDirectionBg::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void CDirectionBg::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void CDirectionBg::Update()
{
	CObject2D::Update();

	if (m_Delete)
	{//��ʊO�ɂł�

		//�I������
		Uninit();
	}
}

//========================
//�`�揈��
//========================
void CDirectionBg::Draw()
{
	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
CDirectionBg* CDirectionBg::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CDirectionBg* pTutorialBg = DBG_NEW CDirectionBg;

	//�ʒu�̐ݒ�
	pTutorialBg->SetPos(pos);
	
	//�ŏ��̈ʒu��ۑ�
	pTutorialBg->m_FirstPos = pos;

	//�T�C�Y�ݒ�
	pTutorialBg->SetSize(50.0f, SCREEN_WIDTH / 2);

	//�F��ݒ�
	pTutorialBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//�����ݒ�
	pTutorialBg->Init();

	return pTutorialBg;
}

//========================
//��ʂɓ���
//========================
void CDirectionBg::EnterScreen()
{
	if (m_CountFlame > 5)
	{//5�t���[���ړ�����
		return;
	}

	//�t���[�������J�E���g
	m_CountFlame++;

	if (m_FirstPos.y < 0.0f)
	{//��ɂ���|���S��

		//�ʒu��ύX
		SetPos({ GetPos().x, GetPos().y + 10.0f ,GetPos().z });
	}
	else
	{//���ɂ���|���S��

		//�ʒu��ύX
		SetPos({ GetPos().x, GetPos().y - 10.0f ,GetPos().z });
	}
}

//========================
//��ʂ���o��
//========================
void CDirectionBg::ExitScreen()
{
	if (m_FirstPos.y < 0.0f)
	{//��ɂ���|���S��

		//�ʒu��ύX
		SetPos({ GetPos().x, GetPos().y - 10.0f ,GetPos().z });

		if (GetPos().y <= m_FirstPos.y)
		{//��ʊO
			m_Delete = true;
		}
	}
	else
	{//���ɂ���|���S��

		//�ʒu��ύX
		SetPos({ GetPos().x, GetPos().y + 10.0f ,GetPos().z });

		if (GetPos().y >= m_FirstPos.y)
		{//��ʊO
			m_Delete = true;
		}
	}
}