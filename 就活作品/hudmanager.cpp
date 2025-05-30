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
#include"UIbg.h"
#include"opeUI.h"

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

//==========================
//UI表示
//==========================
void CHudManager::DisplayUI()
{
	for (int i = 0; i < 5; i++)
	{
		CUIBg::Create(D3DXVECTOR3(1100.0f, 30.0f + (i * 40.0f), 0.0f));
	}
	COpeUI::Create(D3DXVECTOR3(1150.0f, 30.0f, 0.0f), D3DXVECTOR3(100.0f, 20.0f, 0.0f), "data\\TEXTURE\\dush.png");
	COpeUI::Create(D3DXVECTOR3(1130.0f, 70.0f, 0.0f), D3DXVECTOR3(70.0f, 20.0f, 0.0f), "data\\TEXTURE\\camera.png");
	COpeUI::Create(D3DXVECTOR3(1140.0f, 110.0f, 0.0f), D3DXVECTOR3(60.0f, 20.0f, 0.0f), "data\\TEXTURE\\attack.png");
	COpeUI::Create(D3DXVECTOR3(1100.0f, 150.0f, 0.0f), D3DXVECTOR3(100.0f, 20.0f, 0.0f), "data\\TEXTURE\\grab.png");
	COpeUI::Create(D3DXVECTOR3(1130.0f, 190.0f, 0.0f), D3DXVECTOR3(70.0f, 20.0f, 0.0f), "data\\TEXTURE\\guard.png");
}