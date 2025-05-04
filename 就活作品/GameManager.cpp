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
CGameManager::CGameManager():
GameClear(GAME::NONE),
m_player(nullptr),//プレイヤーの情報
m_Direction(false),//演出の判定
m_boss(nullptr),
m_count(0),
m_StageChamge(false)
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
	SetGame(GAME::NONE);//クリア情報を初期化
	GetPlayerInfo();//プレイヤーの情報を取得
}

//==========================
//終了処理
//==========================
void CGameManager::Uninit()
{
	if (m_player != nullptr)
	{
		m_player = nullptr;
	}
}

//==========================
//ゲームのクリア情報を設定
//==========================
void CGameManager::SetGame(GAME game)
{
	GameClear = game;
}

//==========================
//ゲームのクリア情報を取得
//==========================
CGameManager::GAME CGameManager::GetGame()
{
	return GameClear;
}

//==========================
//カメラが追従する対象を設定
//==========================
void CGameManager::SetCamera()
{
	if (!m_Direction)
	{
		
		//カメラ追従
		CManager::GetInstance()->GetCamera()->Move(m_player->GetPos());
	}
	else
	{
		if (!CManager::GetInstance()->GetStageManager()->GetChange())
		{
			m_count++;
			if (m_count > 60)
			{
				StartBossBattle();
			}
			else
			{
				CManager::GetInstance()->GetCamera()->Move(m_boss->GetPos());
			}
		}
	}
}

//==========================

//==========================
void CGameManager::a()
{
	//プレイヤーのHPゲージの更新
	CManager::GetInstance()->GetStageManager()->HPGaugeUpdate();

	//カメラ追従する対象を設定
	SetCamera();
	
	//ステージの切り替え
	CManager::GetInstance()->GetStageManager()->ChangeStage();
}

//==========================
//演出の設定
//==========================
void CGameManager::SetDirection()
{
	m_Direction = !m_Direction;
}

//==========================
//演出中か取得
//==========================
bool CGameManager::GetDirection()
{
	return m_Direction;
}

//==========================
//切り替わり判定を取得
//==========================
bool CGameManager::GetChange()
{
	return m_StageChamge;
}

//==========================
//切り替わり判定をリセット
//==========================
void CGameManager::SetChange()
{
	m_StageChamge = !m_StageChamge;
}

//==========================
//ボス戦開始時の演出
//==========================
void CGameManager::StartBossBattle()
{
	if (m_boss == nullptr)
	{
		return;
	}

	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	D3DXVECTOR3 pos = m_player->GetPos();

	pCamera->SetTargetPos(m_player->GetPos());
	pCamera->TarGetMove();

	if (pCamera->GetPosV().z <= m_player->GetPos().z + (pCamera->Z_DISTANCE+1.0f))
	{
		SetDirection();
		D3DXVECTOR3 pos = m_player->GetPos();
		int a = 0;
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
//ボスの情報を取得
//==========================
void CGameManager::GetBossInfo()
{
	
	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CBoss::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//オブジェクトがエネミーではない
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		if (pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE::BOSS)
		{//オブジェクトがボスではない
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		CBoss* pBoss = (CBoss*)pObj;

		//ボスの情報を取得
		m_boss = pBoss;

		break;
	}
}