//==========================
// 
// ゲーム画面の処理[game.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"game.h"
#include"manager.h"
#include"fild.h"
#include"player.h"
#include"enemy.h"
#include"block.h"
#include"weapon.h"
#include"bigweapon.h"
#include"hitenemy.h"
#include"weaponenemy.h"
#include"building.h"
#include"stagechangepoint.h"
#include"jihanki.h"
#include"deliveryperson.h"
#include"smallweapon.h"
#include"bosshpgauge.h"
#include"objectMesh.h"
#include"sky.h"
#include"bicycle.h"
#include"bat.h"
#include"enemymovepoint.h"
#include"UIbg.h"
#include"opeUI.h"

//==========================
// コンストラクタ
//==========================
CGame::CGame() :
m_Edit(nullptr),//配置ツール情報
m_player(nullptr),//プレイヤーの情報
m_Boss(nullptr),//ボスの情報
m_PlalyerHPGauge(nullptr),//プレイヤーのHPゲージの情報
m_BossHPGauge(nullptr),//ボスのHPゲージの情報
m_playerlife(0)
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
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_INGAME);
	CManager::GetInstance()->GetStageManager()->StageReset();
	CManager::GetInstance()->GetGameManager()->SetGame(CGameManager::GAME::NONE);
	//CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 2000.0f, 2000.0f));
	//CObjectMesh::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f), 3, 3);
	//CBlock::Create(D3DXVECTOR3(0.0f, 0.0f,0.0f), D3DXVECTOR3(3.0f, 1.0f, 3.0f));
	//CBoss::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CHitEnemy::Create(D3DXVECTOR3(-50.0f, 0.0f, 500.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CHitEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 2100.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CHitEnemy::Create(D3DXVECTOR3(50.0f, 0.0f, 500.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CWeaponEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CWeapon::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CStageChangePoint::Create(D3DXVECTOR3(-1900.0f, 0.0f, 1200.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	//CStageChangePoint::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	//CBuilding::Create(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CJihanki::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//CDeliveryPerson::Create(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//CBigWeapon::Create(D3DXVECTOR3(300.0f, 0.0f, 300.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), "data\\MODEL\\bicycle.x");
	//CSmallWeapon::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data\\MODEL\\iron_pipe.x");
	

	//ステージを生成
	m_player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	m_PlalyerHPGauge = CPlayerHPGauge::Create(D3DXVECTOR3(10.0f, 20.0f, 0.0f), 10, 300, m_player->GetLife());
	CManager::GetInstance()->GetStageManager()->Load();

	DisplayUI();

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

	m_player = nullptr;
	m_Boss = nullptr;
	m_PlalyerHPGauge = nullptr;
	m_BossHPGauge = nullptr;
	
	CManager::GetInstance()->GetDebug()->Reset();
	CManager::GetInstance()->GetStageManager()->StageReset();

	CObject::ReleaseAll();

	CManager::GetInstance()->GetSound()->Stop();
}

//==========================
// 更新処理
//==========================
void CGame::Update()
{

	if (m_PlalyerHPGauge != nullptr)
	{
		m_PlalyerHPGauge->SetHP(m_player->GetLife());
	}

	UseEdit();

	//ステージの切り替え
	ChangeStage();

#ifdef _DEBUG
	if (m_Boss != nullptr)
	{
		m_BossHPGauge->SetHP(m_Boss->GetLife());
	}

	if (!CManager::GetInstance()->GetDebug()->GetEdit())
	{//配置ツールを使用していない
		DebugSelect();
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//ゲーム画面に遷移
		CManager::GetInstance()->GetFade()->SetFade(MODE::RESULT);
	}
#endif

	if (CManager::GetInstance()->GetGameManager()->GetGame() != CGameManager::GAME::NONE)
	{
		//ゲーム画面に遷移
		CManager::GetInstance()->GetGameManager()->SetGame(CManager::GetInstance()->GetGameManager()->GetGame());
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
//ステージの切り替え
//==========================
void CGame::ChangeStage()
{
	if (CManager::GetInstance()->GetStageManager()->GetChange()
		&& CManager::GetInstance()->GetStageManager()->ChangeObject())
	{//ステージが切り替わってるとき

		//現在のステージを取得
		int StageNum = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

		//プレイヤーの位置を変更
		if (StageNum == 2)
		{
			m_player->SetPos(D3DXVECTOR3 (-900.0f, 0.0f, 300.0f));
		}
		else
		{
			m_player->SetPos(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		}
		m_player->DeleteWeapon();
		m_player->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));//プレイヤーの向きを変更

		//ステージを生成
		CManager::GetInstance()->GetStageManager()->DeleteAll();//全てのオブジェクトを削除
		CManager::GetInstance()->GetStageManager()->Load();//オブジェクトを読み込む
		CManager::GetInstance()->GetCamera()->Init();

		CManager::GetInstance()->GetStageManager()->ChangeReset();
	}
}

//==========================
//デバッグの種類を選択
//==========================
void CGame::DebugSelect()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F1))
	{//プレイヤーのデバッグ
		CObject::ReleaseAll();

		if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
		{
			CManager::GetInstance()->GetDebug()->Reset();
			CManager::GetInstance()->GetDebug()->StartPlayerTest();//プレイヤーのデバッグをスタート
			CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			//CBoss::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			CBigWeapon::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), "data\\MODEL\\cone.x");
			CSmallWeapon::Create(D3DXVECTOR3(-100.0f,0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data\\MODEL\\iron_pipe.x");
			CSmallWeapon::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "data\\MODEL\\syokaki.x");
			CFild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		else
		{
			CManager::GetInstance()->GetDebug()->FinishPlayerTest();//プレイヤーのデバッグを終了
			Init();
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F2))
	{//ボスのデバッグ
		CObject::ReleaseAll();

		if (!CManager::GetInstance()->GetDebug()->GetBossTest())
		{
			CManager::GetInstance()->GetDebug()->Reset();
			CManager::GetInstance()->GetDebug()->StartBossTest();//ボスのデバッグをスタート
			CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			m_Boss = CBoss::Create(D3DXVECTOR3(0.0f, 0.0f, 400.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			m_BossHPGauge = CBossHPGauge::Create(D3DXVECTOR3(1000.0f, 680.0f, 0.0f), 10, 100, m_Boss->GetLife());
			CBigWeapon::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), "data\\MODEL\\.x");
			CFild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CBuilding::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
		}
		else
		{
			CManager::GetInstance()->GetDebug()->FinishBossTest();//ボスのデバッグを終了
			Init();
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F3))
	{//戦闘のデバッグ
		CObject::ReleaseAll();

		if (!CManager::GetInstance()->GetDebug()->GetBattleTest())
		{
			CManager::GetInstance()->GetDebug()->Reset();
			CManager::GetInstance()->GetDebug()->StartBattleTest();//ボスのデバッグをスタート
			m_player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			m_PlalyerHPGauge = CPlayerHPGauge::Create(D3DXVECTOR3(10.0f, 20.0f, 0.0f), 10, 300, m_player->GetLife());
			CBoss::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			CBicycle::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f,0.0f,0.0f));
			CBat::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CFild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		else
		{
			CManager::GetInstance()->GetDebug()->FinishBattleTest();//ボスのデバッグを終了
			Init();
		}
	}
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
			m_PlalyerHPGauge = nullptr;
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

//==========================
//UI表示
//==========================
void CGame::DisplayUI()
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