//==========================
// 
// �X�e�[�W�Ǘ�[stagemanager.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"stagemanager.h"
#include"manager.h"

//==========================
//�R���X�g���N�^
//==========================
CStageManager::CStageManager():
m_Stage(STAGE::STAGE_FIRST),
m_Change(false),
m_DarkBg(nullptr),
m_Rast(0)
{
	m_Rast = static_cast<int>(STAGE::STAGE_BOSS);
	m_DarkBg = CDarkBg::Create();
}

//==========================
//�f�X�g���N�^
//==========================
CStageManager::~CStageManager()
{
	
}

//==========================
//�I������
//==========================
void CStageManager::Uninit()
{
	if (m_DarkBg != nullptr)
	{
		m_DarkBg->CObject2D::Uninit();
		delete m_DarkBg;
		m_DarkBg = nullptr;
	}
}

//==========================
//�X�e�[�W��ݒ�
//==========================
void CStageManager::SetStage()
{
	int stage = static_cast<int>(m_Stage);

	if (stage >= m_Rast)
	{
		stage = -1;
	}

	m_Stage = static_cast<STAGE>(stage + 1);
	m_Change = true;
	m_DarkBg->SetFade();
}

//==========================
//�X�e�[�W���擾
//==========================
CStageManager::STAGE CStageManager::GetStage()
{
	return m_Stage;
}

//==========================
//�؂�ւ�蔻����擾
//==========================
bool CStageManager::GetChange()
{
	return m_Change;
}

//==========================
//�؂�ւ�蔻������Z�b�g
//==========================
void CStageManager::ChangeReset()
{
	m_Change = false;
}

//==========================
//�I�u�W�F�N�g�ύX�^�C�~���O
//==========================
bool CStageManager::ChangeObject()
{
	if (m_DarkBg->GetCor() >= 1.0f)
	{
		return true;
	}

	return false;
}

void CStageManager::StageReset()
{
	m_Stage = STAGE::STAGE_FIRST;
}