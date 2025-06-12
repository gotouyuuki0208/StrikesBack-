//==========================
// 
// [darkbg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"darkbg.h"
#include"manager.h"

//�ÓI�����o�ϐ�������
const int CDarkBg::PRIORITY = 5;
//==========================
// �R���X�g���N�^
//==========================
CDarkBg::CDarkBg(int priority) :CObject2D(priority)
{
	m_cor = 0.0f;
	m_fade = FADE::FADE_NONE;
}

//==========================
// �f�X�g���N�^
//==========================
CDarkBg::~CDarkBg()
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CDarkBg::Init()
{
	SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	SetSize(360.0f, 640.0f);
	CObject2D::Init();

	return S_OK;
}

//==========================
// �I������
//==========================
void CDarkBg::Uninit()
{

}

//==========================
// �X�V����
//==========================
void CDarkBg::Update()
{
	if (m_fade != FADE::FADE_NONE)
	{
		if (m_fade == FADE::FADE_IN)
		{//�t�F�[�h�C�����
			m_cor -= 0.05f;

			if (m_cor <= 0.0f)
			{
				m_cor = 0.0f;
				m_fade = FADE::FADE_NONE;
			}
		}
		else if (m_fade == FADE::FADE_OUT)
		{//�t�F�[�h�A�E�g���
			m_cor += 0.05f;

			if (m_cor >= 1.0f)
			{
				m_cor = 1.0f;
				m_fade = FADE::FADE_IN;
			}
		}
	}

	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_cor));//�F�̐ݒ�
	CObject2D::Update();//�X�V����

}

//==========================
// �`�揈��
//==========================
void CDarkBg::Draw()
{
	CObject2D::Draw();
}

//==========================
//�t�F�[�h�̐ݒ菈��
//==========================
void CDarkBg::SetFade()
{
	m_fade = FADE::FADE_OUT;
}

//==========================
//�t�F�[�h�̏�Ԏ擾
//==========================
CDarkBg::FADE CDarkBg::GetFade()
{
	return m_fade;
}

//==========================
//����
//==========================
CDarkBg* CDarkBg::Create()
{
	CDarkBg* pDarkBg = DBG_NEW CDarkBg;

	pDarkBg->Init();

	pDarkBg->SetType(TYPE::FADE);
	return pDarkBg;
}

//==========================
//�����x�̎擾
//==========================
float CDarkBg::GetCol()
{
	return m_cor;
}