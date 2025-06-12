//==========================
// 
// デバッグ[debug.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "debug.h"

//==========================
// コンストラクタ
//==========================
CDebug::CDebug():
m_TestPlayer(false),
m_TestBoss(false),
m_TestBattle(false),
m_UseEdit(false)
{

}

//==========================
// デストラクタ
//==========================
CDebug::~CDebug()
{

}

//==========================
//デバッグ情報をリセット
//==========================
void CDebug::Reset()
{
	FinishPlayerTest();
	FinishBossTest();
	FinishEdit();
}

//==========================
//プレイヤーのテスト
//==========================
bool CDebug::GetPlayerTest()
{
	return m_TestPlayer;
}

//==========================
//プレイヤーのテスト開始
//==========================
void CDebug::StartPlayerTest()
{
	m_TestPlayer = true;
}

//==========================
//プレイヤーのテスト終了
//==========================
void CDebug::FinishPlayerTest()
{
	m_TestPlayer = false;
}

//==========================
//ボスのテスト
//==========================
bool CDebug::GetBossTest()
{
	return m_TestBoss;
}

//==========================
//ボスのテスト開始
//==========================
void CDebug::StartBossTest()
{
	m_TestBoss = true;
}

//==========================
//ボスのテスト終了
//==========================
void CDebug::FinishBossTest()
{
	m_TestBoss = false;
}

//==========================
//バトルのテスト
//==========================
bool CDebug::GetBattleTest()
{
	return m_TestBattle;
}
//==========================
//バトルのテスト開始
//==========================
void CDebug::StartBattleTest()
{
	m_TestBattle = true;
}

//==========================
//バトルのテスト終了
//==========================
void CDebug::FinishBattleTest()
{
	m_TestBattle = false;
}

//==========================
//バトルのテスト
//==========================
bool CDebug::GetEdit()
{
	return m_UseEdit;
}
//==========================
//バトルのテスト開始
//==========================
void CDebug::StartEdit()
{
	m_UseEdit = true;
}

//==========================
//バトルのテスト終了
//==========================
void CDebug::FinishEdit()
{
	m_UseEdit = false;
}