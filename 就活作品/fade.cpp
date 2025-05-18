//==========================
// 
// �t�F�[�h����[fade.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "fade.h"
#include"manager.h"

//�ÓI�����o�ϐ�������
const int CFade::PRIORITY = 5;
//==========================
// �R���X�g���N�^
//==========================
CFade::CFade(int priority):
CObject2D(priority),			//���R���X�g���N�^
m_Transparency(0.0f),					//�F
m_fade(FADE::FADE_NONE),		//�t�F�[�h�̏��
g_modenext(CScene::MODE::TITLE),//���̃V�[��
m_InGame(false)					//�Q�[����������
{
	
}

//==========================
// �f�X�g���N�^
//==========================
CFade::~CFade()
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CFade::Init()
{
	//�ʒu�̐ݒ�
	SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	
	//�傫���̐ݒ�
	SetSize(360.0f, 640.0f);
	
	//�����ݒ�
	CObject2D::Init();

	return S_OK;
}

//==========================
// �I������
//==========================
void CFade::Uninit()
{

}

//==========================
// �X�V����
//==========================
void CFade::Update()
{
	if (m_fade != FADE::FADE_NONE)
	{
		if (m_fade == FADE::FADE_IN)
		{//�t�F�[�h�C�����
			m_Transparency -= 0.05f;

			if (m_Transparency <= 0.0f)
			{
				m_Transparency = 0.0f;
				m_fade = FADE::FADE_NONE;
			}
		}
		else if (m_fade == FADE::FADE_OUT)
		{//�t�F�[�h�A�E�g���
			m_Transparency += 0.05f;

			if (m_Transparency >= 1.0f)
			{
				m_Transparency = 1.0f;
				m_fade = FADE::FADE_IN;

				if (!m_InGame)
				{
					CManager::GetInstance()->SetMode(g_modenext);
				}

				m_InGame = false;
			}
		}
	}

	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_Transparency));//�F�̐ݒ�
	CObject2D::Update();//�X�V����

}

//==========================
// �`�揈��
//==========================
void CFade::Draw()
{
	CObject2D::Draw();
}

//==========================
//�t�F�[�h�̐ݒ菈��
//==========================
void CFade::SetFade(CScene::MODE modenext)
{
	g_modenext = modenext;
	m_fade = FADE::FADE_OUT;
}

//==========================
//�t�F�[�h�̏�Ԏ擾
//==========================
CFade::FADE CFade::GetFade()
{
	return m_fade;
}

//==========================
//����
//==========================
CFade* CFade::Create()
{
	CFade* pFade = DBG_NEW CFade;

	pFade->Init();

	pFade->SetType(TYPE::FADE);

	return pFade;
}

//==========================
//�Q�[�����ł̃t�F�[�h
//==========================
void CFade::InGameFade()
{
	m_fade = FADE::FADE_OUT;
	m_InGame = true;
}

//==========================
//�����x�̎擾
//==========================
float CFade::GetTransparency()
{
	return m_Transparency;
}