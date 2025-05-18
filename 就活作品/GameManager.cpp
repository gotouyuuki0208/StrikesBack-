//==========================
// 
// ゲーム全体管理[GameManager.h]
// Author Yuki Goto
//
//==========================
#include"GameManager.h"
#include"manager.h"
#include"direction.h"

//==========================
//コンストラクタ
//==========================
CGameManager::CGameManager():
m_GameClear(GAME::NONE),
m_player(nullptr),//プレイヤーの情報
m_Direction(false),//演出の判定
m_count(0),//フレーム数カウント用
m_PlayGame(false),//ゲームを遊べるか判定(false:遊べない true:遊べる)
m_GameStartTutorial(false),//ゲームの開始時の操作説明を表示したか判定
m_direction(nullptr)//演出の情報
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

	//ステージ情報を削除
	CManager::GetInstance()->GetStageManager()->StageReset();

	//オブジェクトを消す
	CObject::ReleaseAll();

	//BGMを停止
	CManager::GetInstance()->GetSound()->Stop();
}

//==========================
//更新処理
//==========================
void CGameManager::Update()
{
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
	CManager::GetInstance()->GetGameManager()->StartTutorial();

	//チュートリアル表示を消す
	CManager::GetInstance()->GetGameManager()->EndTutorial();
}

//==========================
//カメラの設定
//==========================
void CGameManager::SetCamera()
{
	if (!m_Direction)
	{
		//カメラ追従
		CManager::GetInstance()->GetCamera()->Move({ m_player->GetPos().x, m_player->GetPos().y, m_player->GetPos().z });
	}
	else
	{
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