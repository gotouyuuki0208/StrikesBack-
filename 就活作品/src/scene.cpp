//==========================
// 
// �V�[���Ǘ�[scene.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"scene.h"
#include"title.h"
#include"game.h"
#include"result.h"

//==========================
// �R���X�g���N�^
//==========================
CScene::CScene()
{
	m_mode = MODE::TITLE;
}

//==========================
// �f�X�g���N�^
//==========================
CScene::~CScene()
{
	
}

//==========================
// �����ݒ�
//==========================
HRESULT CScene::Init()
{
	return S_OK;

}

//==========================
// �I������
//==========================
void CScene::Uninit()
{

}

//==========================
// �X�V����
//==========================
void CScene::Update()
{

}

//==========================
// �`�揈��
//==========================
void CScene::Draw()
{

}

//==========================
// ��������
//==========================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr;

	switch (mode)
	{
	case MODE::TITLE:
		pScene = DBG_NEW CTitle;
		break;

	case MODE::GAME:
		pScene = DBG_NEW CGame;
		break;

	case MODE::RESULT:
		pScene = DBG_NEW CResult;
		break;

	default:
		break;
	}

	pScene->m_mode = mode;

	return pScene;
}

//==========================
//���݂̃V�[�����擾
//==========================
CScene::MODE CScene::GetScene()
{
	return m_mode;
}