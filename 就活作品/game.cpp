//==========================
// 
// ゲーム画面の処理[game.cpp]
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
// コンストラクタ
//==========================
CGame::CGame() :
m_Edit(nullptr)//配置ツール情報
{
	m_Edit = DBG_NEW CEdit;
}

//==========================
// デストラクタ
//==========================
CGame::~CGame()
{

}

//==========================
// 初期設定
//==========================
HRESULT CGame::Init()
{
	//ゲームの初期設定
	CManager::GetInstance()->GetGameManager()->Init();

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CGame::Uninit()
{
	if (m_Edit != nullptr)
	{
		m_Edit->Uninit();
		delete m_Edit;
		m_Edit = nullptr;
	}
	
	//ゲームの終了処理
	CManager::GetInstance()->GetGameManager()->Uninit();
}

//==========================
// 更新処理
//==========================
void CGame::Update()
{
	//ゲームの更新処理
	CManager::GetInstance()->GetGameManager()->Update();

#ifdef _DEBUG//デバッグ時

	//配置エディタの使用
	UseEdit();

	//エンターキーでリザルトへ
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//リザルト画面に遷移
		CManager::GetInstance()->GetFade()->SetFade(MODE::RESULT);
	}
#endif

	if (CManager::GetInstance()->GetGameManager()->GetGame() != CGameManager::GAME::NONE)
	{//ゲームが終了した

		//リザルト画面に遷移
		CManager::GetInstance()->GetFade()->SetFade(MODE::RESULT);
	}
}

//==========================
// 描画処理
//==========================
void CGame::Draw()
{

}

//==========================
//配置ツールの使用
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

			//現在のステージを取得
			int StageNum = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());
			//ステージを生成
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