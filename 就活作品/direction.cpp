//==========================
// 
// ボス戦演出の管理[direction.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"direction.h"
#include"manager.h"
#include"directionbg.h"
#include"boss.h"

//========================
//コンストラクタ
//========================
CDirection::CDirection():
	m_ExistenceBg(true),
	m_End(false),
	m_boss(nullptr),//ボスの情報
	m_BossMotionEnd(false)
{
	//背景を生成
	m_Bg[0] = CDirectionBg::Create({ SCREEN_WIDTH / 2, -50.0f, 0.0f });
	m_Bg[1] = CDirectionBg::Create({ SCREEN_WIDTH / 2, SCREEN_HEIGHT + 50.0f, 0.0f });
}

//========================
//デストラクタ
//========================
CDirection::~CDirection()
{

}

//========================
//更新処理
//========================
void CDirection::Update()
{
	//背景の更新
	UpdateBg();

	//ボスのモーションが終了したか判定
	BossEndMotion();

	if (m_BossMotionEnd)
	{//ボスのモーションが終了した

		//カメラの情報を取得
		CCamera* pCamera = CManager::GetInstance()->GetCamera();

		//ターゲットの位置へ移動
		pCamera->TarGetMove();

		if (pCamera->FinishDirection())
		{//カメラの移動が終了
			m_End = true;
		}
	}
}

//========================
//背景更新
//========================
void CDirection::UpdateBg()
{
	if (m_ExistenceBg)
	{
		for (int i = 0; i < 2; i++)
		{
			//画面内に入る
			m_Bg[i]->EnterScreen();
		}
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			//画面外に出る
			m_Bg[i]->ExitScreen();
		}
	}

}

//========================
//終了判定を取得
//========================
bool CDirection::GetEnd()
{
	return m_End;
}

//========================
//ボスのモーションが終了したか判定
//========================
void CDirection::BossEndMotion()
{
	if (m_boss->GetMotion() == CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL)
	{//待機モーションを再生している

		//ボスのモーションが終了した
		m_BossMotionEnd = true;

		//背景を消す
		m_ExistenceBg = false;
	}
}

//==========================
//ボスの情報を取得
//==========================
void CDirection::GetBossInfo()
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

	//カメラの位置を変更
	CManager::GetInstance()->GetCamera()->SetPos(m_boss->GetPos());
}