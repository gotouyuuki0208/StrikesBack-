//==========================
// 
// 操作説明管理[TutorialManager.cpp]
// Author Yuki Goto
//
//==========================

#include"TutorialManager.h"

//==========================
//コンストラクタ
//==========================
CTutorial::CTutorial() :
m_Tutorial(false),//説明表示判定
m_Action(false),//行動説明
m_Weapon(false),//武器説明
m_Recovery(false)//回復説明
{

}


//==========================
//デストラクタ
//==========================
CTutorial::~CTutorial()
{

}

//==========================
//説明を表示しているかを取得
//==========================
bool CTutorial::GetTutorial()
{
	return m_Tutorial;
}

//==========================
//説明を開始
//==========================
void CTutorial::StartTutorial()
{
	m_Tutorial = true;
}

//==========================
//説明を終了
//==========================
void CTutorial::FinishTutorial()
{
	m_Tutorial = false;
}

//==========================
//行動説明を表示した状態に変更
//==========================
void CTutorial::SetAction()
{
	m_Action = true;
}

//==========================
//武器説明を表示した状態に変更
//==========================
void CTutorial::SetWeapon()
{
	m_Weapon = true;
}

//==========================
//回復説明を表示した状態に変更
//==========================
void CTutorial::SetRecovery()
{
	m_Recovery = true;
}

//==========================
//行動説明を表示した状態に取得
//==========================
bool CTutorial::GetAction()
{
	return m_Action;
}

//==========================
//武器説明を表示した状態に取得
//==========================
bool CTutorial::GetWeapon()
{
	return m_Weapon;
}

//==========================
//回復説明を表示した状態に取得
//==========================
bool CTutorial::GetRecovery()
{
	return m_Recovery;
}