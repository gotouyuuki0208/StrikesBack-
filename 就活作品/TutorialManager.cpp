//==========================
// 
// 操作説明管理[TutorialManager.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"manager.h"
#include"TutorialManager.h"
#include"TutorialPopup.h"
#include"tutorialbg.h"

//==========================
//コンストラクタ
//==========================
CTutorialManager::CTutorialManager():
m_Action(false),//行動説明
m_Weapon(false),//武器説明
m_Recovery(false),//回復説明
m_pTutorialPopup(nullptr),//ポップアップ表示するチュートリアルの情報
m_pTutorialBg(nullptr)//背景の情報
{

}

//==========================
//デストラクタ
//==========================
CTutorialManager::~CTutorialManager()
{

}

//==========================
//行動の説明を表示
//==========================
void CTutorialManager::ActionTutorialDisplay()
{
	if (m_Action)
	{//すでに行動説明をしている

		return;
	}

	//背景の生成
	m_pTutorialBg = CTutorialBg::Create();

	//ポップアップ表示を生成
	m_pTutorialPopup = CTutorialPopup::Create();

	//行動説明をした状態に変更
	m_Action = true;

	//プレイヤーを操作できないように変更
	CManager::GetInstance()->GetGameManager()->ChangePlayGame(false);
}

//==========================
//武器の説明を表示
//==========================
void CTutorialManager::WeaponTutorialDisplay()
{
	if (m_Weapon)
	{//すでに武器説明をしている

		return;
	}

	//背景の生成
	m_pTutorialBg = CTutorialBg::Create();

	//ポップアップ表示を生成
	m_pTutorialPopup = CTutorialPopup::Create();

	//武器説明をした状態に変更
	m_Weapon = true;

	//プレイヤーを操作できないように変更
	CManager::GetInstance()->GetGameManager()->ChangePlayGame(false);
}

//==========================
//回復の説明を表示
//==========================
void CTutorialManager::RecoveryTutorialDisplay()
{
	if (m_Recovery)
	{//すでに回復説明をしている

		return;
	}

	//背景の生成
	m_pTutorialBg = CTutorialBg::Create();

	//ポップアップ表示を生成
	m_pTutorialPopup = CTutorialPopup::Create();

	//回復説明をした状態に変更
	m_Recovery = true;

	//プレイヤーを操作できないように変更
	CManager::GetInstance()->GetGameManager()->ChangePlayGame(false);
}

//==========================
//説明を消す
//==========================
void CTutorialManager::TutorialDelete()
{

	if (m_pTutorialPopup != nullptr)
	{//ポップアップ表示がされていない

		//キー入力されたことを通知
		m_pTutorialPopup->KeyInput();
		m_pTutorialPopup = nullptr;

		//背景削除
		m_pTutorialBg->Uninit();
		m_pTutorialPopup = nullptr;

		//プレイヤーを操作できるようにに変更
		CManager::GetInstance()->GetGameManager()->ChangePlayGame(true);
	}
}
