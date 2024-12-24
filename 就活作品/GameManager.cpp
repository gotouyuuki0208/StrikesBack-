//==========================
// 
// ゲーム全体管理[GameManager.h]
// Author Yuki Goto
//
//==========================
#include"GameManager.h"
#include"manager.h"

//==========================
//コンストラクタ
//==========================
CGameManager::CGameManager():GameClear(GAME::NONE)
{

}

//==========================
//デストラクタ
//==========================
CGameManager::~CGameManager()
{

}

//==========================
//ゲーム管理
//==========================
void CGameManager::SetGame(GAME game)
{
	GameClear = game;
}

CGameManager::GAME CGameManager::GetGame()
{
	return GameClear;
}