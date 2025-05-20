//==========================
// 
// HUD管理[hudmanager.h]
// Author Yuki Goto
//
//==========================
#include"hudmanager.h"
#include"manager.h"
#include"playerhpgauge.h"
#include"bosshpgauge.h"

//==========================
//コンストラクタ
//==========================
CHudManager::CHudManager():
	m_pPlayerHPGauge(nullptr),//プレイヤーのHPゲージ
	m_pBossHPGauge(nullptr)//ボスのHPゲージ
{

}

//==========================
//デストラクタ
//==========================
CHudManager::~CHudManager()
{

}

//==========================
//プレイヤーHPが変更された
//==========================
void CHudManager::ChangePlayerHP(int hp)
{
	if (m_pPlayerHPGauge == nullptr)
	{
		return;
	}

	//HPゲージにHPの数値を渡す
	m_pPlayerHPGauge->SetHP(hp);
}

//==========================
//ボスのHPが変更された
//==========================
void CHudManager::ChangeBossHP(int hp)
{
	if (m_pBossHPGauge == nullptr)
	{
		return;
	}

	//HPゲージにHPの数値を渡す
	m_pBossHPGauge->SetHP(hp);
}

//==========================
//プレイヤーのゲージを生成
//==========================
void CHudManager::CreatePlayerHPGauge()
{
	if (m_pPlayerHPGauge != nullptr)
	{
		return;
	}

	//プレイヤーのHPゲージを生成
	m_pPlayerHPGauge = CPlayerHPGauge::Create({ 10.0f, 20.0f, 0.0f },//位置
		10,//縦幅
		300);//横幅

}

//==========================
//ボスのゲージを生成
//==========================
void CHudManager::CreateBossHPGauge()
{
	if (m_pBossHPGauge != nullptr)
	{
		return;
	}

	//ボスのHPゲージを生成
	m_pBossHPGauge = CBossHPGauge::Create({ 1200.0f, 680.0f, 0.0f },//位置
		10,//縦幅
		300);//横幅
}

//==========================
//リセット
//==========================
void CHudManager::Reset()
{
	if (m_pBossHPGauge != nullptr)
	{
		m_pBossHPGauge = nullptr;
	}

	if (m_pPlayerHPGauge != nullptr)
	{
		m_pPlayerHPGauge = nullptr;
	}
}