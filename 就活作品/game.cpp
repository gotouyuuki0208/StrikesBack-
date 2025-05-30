//==========================
// 
// �Q�[����ʂ̏���[game.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"game.h"
#include"manager.h"
#include"stagechangepoint.h"
#include"objectMesh.h"
#include"hitenemy.h"
#include"TutorialPopup.h"
#include"directionbg.h"

//==========================
// �R���X�g���N�^
//==========================
CGame::CGame() :
m_Edit(nullptr)//�z�u�c�[�����
{
	m_Edit = DBG_NEW CEdit;
}

//==========================
// �f�X�g���N�^
//==========================
CGame::~CGame()
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CGame::Init()
{
	//�Q�[���̏����ݒ�
	CManager::GetInstance()->GetGameManager()->Init();

	return S_OK;
}

//==========================
// �I������
//==========================
void CGame::Uninit()
{
	if (m_Edit != nullptr)
	{
		m_Edit->Uninit();
		delete m_Edit;
		m_Edit = nullptr;
	}
	
	//�Q�[���̏I������
	CManager::GetInstance()->GetGameManager()->Uninit();
}

//==========================
// �X�V����
//==========================
void CGame::Update()
{
	//�Q�[���̍X�V����
	CManager::GetInstance()->GetGameManager()->Update();

#ifdef _DEBUG//�f�o�b�O��

	//�z�u�G�f�B�^�̎g�p
	UseEdit();

	//�G���^�[�L�[�Ń��U���g��
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//���U���g��ʂɑJ��
		CManager::GetInstance()->GetFade()->SetFade(MODE::RESULT);
	}
#endif

	if (CManager::GetInstance()->GetGameManager()->GetGame() != CGameManager::GAME::NONE)
	{//�Q�[�����I������

		//���U���g��ʂɑJ��
		CManager::GetInstance()->GetFade()->SetFade(MODE::RESULT);
	}
}

//==========================
// �`�揈��
//==========================
void CGame::Draw()
{

}

//==========================
//�z�u�c�[���̎g�p
//==========================
void CGame::UseEdit()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F4))
	{
		if (!CManager::GetInstance()->GetDebug()->GetEdit())
		{
			CManager::GetInstance()->GetDebug()->StartEdit();
			CObject::ReleaseAll();
			m_Edit->Uninit();

			//���݂̃X�e�[�W���擾
			int StageNum = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());
			//�X�e�[�W�𐶐�
			m_Edit->Load(StageNum);

			m_Edit->Init();
		}
		else
		{
			CManager::GetInstance()->GetDebug()->FinishEdit();
			CObject::ReleaseAll();
			m_Edit->Uninit();
			Init();
			
		}
		CManager::GetInstance()->GetKeyboard()->Update();

	}
	
	if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		m_Edit->Update();
	}
}