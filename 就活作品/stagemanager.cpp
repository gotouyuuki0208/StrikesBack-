//==========================
// 
// ステージ管理[stagemanager.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"stagemanager.h"
#include"manager.h"

//==========================
//コンストラクタ
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
//デストラクタ
//==========================
CStageManager::~CStageManager()
{
	
}

//==========================
//終了処理
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
//ステージを設定
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
//ステージを取得
//==========================
CStageManager::STAGE CStageManager::GetStage()
{
	return m_Stage;
}

//==========================
//切り替わり判定を取得
//==========================
bool CStageManager::GetChange()
{
	return m_Change;
}

//==========================
//切り替わり判定をリセット
//==========================
void CStageManager::ChangeReset()
{
	m_Change = false;
}

//==========================
//オブジェクト変更タイミング
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