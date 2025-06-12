//==========================
// 
// ゲーム全体管理[GameManager.h]
// Author Yuki Goto
//
//==========================
#include"GameManager.h"
#include"manager.h"
#include"direction.h"
#include"hitenemy.h"
#include"enemy.h"

//==========================
//コンストラクタ
//==========================
CGameManager::CGameManager():
m_GameClear(GAME::NONE),
m_player(nullptr),
m_Direction(false),
m_count(0),
m_PlayGame(false),
m_GameStartTutorial(false),
m_direction(nullptr),
m_CameraLookOn(false),
m_NowWave(0),
m_ActiveEnemy(0),
m_EnemyBeing(false)
{

}

//==========================
//デストラクタ
//==========================
CGameManager::~CGameManager()
{

}

//==========================
//初期化処理
//==========================
void CGameManager::Init()
{
	//BGMの再生
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_INGAME);

	//ステージ情報を初期化
	CManager::GetInstance()->GetStageManager()->StageReset();

	//ステージを生成
	CManager::GetInstance()->GetStageManager()->Load();
	
	//クリア情報を初期化
	SetGame(GAME::NONE);

	//プレイヤーの情報を取得
	GetPlayerInfo();

	//ウェーブ2で行動
	//Enemy = CHitEnemy::Create({ 0.0f,0.0f ,700.0f }, { 1.5f,1.5f ,1.5f }, 2);

	//ウェーブ1で行動
	//CHitEnemy::Create({ 0.0f,0.0f ,500.0f }, { 1.5f,1.5f ,1.5f }, 1);

	//演出のインスタンス生成
	m_direction = DBG_NEW CDirection;
}

//==========================
//終了処理
//==========================
void CGameManager::Uninit()
{
	if (m_player != nullptr)
	{//プレイヤーの情報を消す
		m_player = nullptr;
	}

	if (m_direction != nullptr)
	{//演出の情報を消す
		delete m_direction;
		m_direction = nullptr;
	}

	m_count = 0;
	m_PlayGame = false;
	m_GameStartTutorial = false;
	m_NowWave = 1;

	//ステージ情報を削除
	CManager::GetInstance()->GetStageManager()->StageReset();

	//オブジェクトを消す
	CObject::ReleaseAll();

	//BGMを停止
	CManager::GetInstance()->GetSound()->Stop();

	//HUD管理クラスの情報を初期化
	CManager::GetInstance()->GetHudManager()->Reset();

	//チュートリアル管理クラスの情報を初期化
	CManager::GetInstance()->GetTutorial()->Reset();
}

//==========================
//更新処理
//==========================
void CGameManager::Update()
{
	//ウェーブの更新
	//WaveUpdate();

	//チュートリアルの設定
	SetTutorial();

	//カメラの設定
	SetCamera();

	//ステージを変更
	CManager::GetInstance()->GetStageManager()->ChangeStage();
}

//==========================
//チュートリアルの設定
//==========================
void CGameManager::SetTutorial()
{
	//ゲーム開始時のチュートリアルを表示
	StartTutorial();

	//チュートリアル表示を消す
	EndTutorial();
}

//==========================
//カメラの設定
//==========================
void CGameManager::SetCamera()
{
	//カメラの情報を取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	CInputJoypad* pPad = CManager::GetInstance()->GetJoypad();

	if (pPad->GetTrigger(CInputJoypad::JOYKEY::JOYKEY_RIGHT_THUMB))
	{//カメラを切り替え
		m_CameraLookOn = !m_CameraLookOn;
	}

	if (!m_Direction)
	{//演出中じゃない

		if (!m_CameraLookOn)
		{//ロックオンしない

			//カメラ追従
			pCamera->Move({ m_player->GetPos().x, m_player->GetPos().y, m_player->GetPos().z });
		}
		else
		{//ロックオンする

			//敵をロックオン
			CmeraLookOn();
		}
	}
	else
	{//演出中

		//ボス戦の開始演出
		StartBossBattle();
	}
}

//==========================
//ゲームのクリア情報を設定
//==========================
void CGameManager::SetGame(GAME game)
{
	m_GameClear = game;
}

//==========================
//ゲームのクリア情報を取得
//==========================
CGameManager::GAME CGameManager::GetGame()
{
	return m_GameClear;
}

//==========================
//ゲーム開始時の操作説明表示
//==========================
void CGameManager::StartTutorial()
{
	if (m_GameStartTutorial)
	{//すでに説明した
		return;
	}

	//色の透明度を取得
	float Transparency = CManager::GetInstance()->GetFade()->GetTransparency();

	if (Transparency > 0.0f)
	{//シーン切り替えのフェードが終わってない

		return;
	}

	//フレーム数を数える
	m_count++;

	if (m_count <= 30)
	{//1秒経過していない
		return;
	}

	//フラグを変更
	m_GameStartTutorial = true;

	//チュートリアル表示
	CManager::GetInstance()->GetTutorial()->ActionTutorialDisplay();
}

//==========================
//操作説明表示の終了
//==========================
void CGameManager::EndTutorial()
{
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_B))
	{//ボタンが押された

		//チュートリアル表示を消す
		CManager::GetInstance()->GetTutorial()->TutorialDelete();
	}
}

//==========================
//遊べる状態か取得
//==========================
bool CGameManager::GetPlayGame()
{
	return m_PlayGame;
}

//==========================
//キャラクター操作の判定を変更
//==========================
void CGameManager::ChangePlayGame(bool play)
{
	m_PlayGame = play;
}

//==========================
//演出中に変更
//==========================
void CGameManager::SetDirection()
{
	//演出中に変更
	m_Direction = true;

	//ボスの情報を取得する
	m_direction->GetBossInfo();
}
//==========================
//演出中か取得
//==========================
bool CGameManager::GetDirection()
{
	return m_Direction;
}

//==========================
//ボス戦開始時の演出
//==========================
void CGameManager::StartBossBattle()
{
	//カメラの情報を取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//プレイヤーの位置
	D3DXVECTOR3 pos = m_player->GetPos();

	//カメラが最終的に移動する位置を設定
	pCamera->SetTargetPos(m_player->GetPos(),3000);

	//操作不可に変更
	m_PlayGame = false;

	//演出の更新
	m_direction->Update();

	if (m_direction->GetEnd())
	{//終了した

		//演出中じゃない設定に変更
		m_Direction = false;

		//操作可能に変更
		m_PlayGame = true;
	}
}

//==========================
//プレイヤーの情報を取得
//==========================
void CGameManager::GetPlayerInfo()
{
	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CPlayer::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::PLAYER)
		{//オブジェクトがプレイヤーではない
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		CPlayer* pPlayer = (CPlayer*)pObj;

		//プレイヤーの情報を取得
		m_player = pPlayer;

		break;
	}
}

//==========================
//カメラのロックオン
//==========================
void CGameManager::CmeraLookOn()
{
	if (Enemy == nullptr)
	{
		return;
	}

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//カメラ追従
	pCamera->LockOn({ m_player->GetPos().x, m_player->GetPos().y, m_player->GetPos().z }
	, { Enemy->GetPos().x, Enemy->GetPos().y, Enemy->GetPos().z });

}

//==========================
//現在のウェーブを取得
//==========================
int CGameManager::GetWave()
{
	return m_NowWave;
}

//==========================
//ウェーブを増やす
//==========================
void CGameManager::AddWave()
{
	m_NowWave++;
}

//==========================
//行動してる敵の数を増やす
//==========================
void CGameManager::AddActiveEnemy()
{
	m_ActiveEnemy++;
}

//==========================
//行動してる敵の数を減らす
//==========================
void CGameManager::SubActiveEnemy()
{
	m_ActiveEnemy--;
}

//==========================
//行動中の敵の数を取得
//==========================
int CGameManager::GetActiveEnemy()
{
	return m_ActiveEnemy;
}

//==========================
//ウェーブの更新
//==========================
void CGameManager::WaveUpdate()
{
	//ステージマネージャーの情報
	CStageManager* pStageManager = CManager::GetInstance()->GetStageManager();

	//敵がいるか判定
	JudgeEnemyBeing();

	if (!m_PlayGame|| !m_EnemyBeing|| pStageManager->GetChange())
	{//行動できないか敵がいないかステージ切り替わり中

		return;
	}

	if (m_ActiveEnemy <= 0)
	{//行動してる敵がいない

		m_NowWave++;
	}
}

//==========================
//敵が存在してるか判定
//==========================
void CGameManager::JudgeEnemyBeing()
{
	m_EnemyBeing = false;

	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//オブジェクトが敵ではない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		m_EnemyBeing = true;

		break;
	}
}
