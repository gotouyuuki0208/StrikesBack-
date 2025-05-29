//==========================
// 
// 敵の状態管理[enemystate.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "enemystate.h"
#include"enemyattackstate.h"
#include "weakenemy.h"

//静的メンバ初期化
const int CEnemyDamageState::DAMEGE_FLAME = 54;//ダメージ状態を終了するまでのフレーム数
const int CEnemyDamageBrrowState::BRROW_FLAME = 50;//ダメージ状態を終了するまでのフレーム数
//==============================================================================
//敵の状態クラス
//==============================================================================

//==========================
//コンストラクタ
//==========================
CEnemyStateBase::CEnemyStateBase() :
	m_pEnemy(nullptr)//敵の情報
{

}

//==========================
//デストラクタ
//==========================
CEnemyStateBase::~CEnemyStateBase()
{

}

//==========================
//ステートの所持者を設定
//==========================
void CEnemyStateBase::SetOwner(CWeakEnemy* enemy)
{
	m_pEnemy = enemy;
}

//==========================
//ステートの所有者を取得
//==========================
CWeakEnemy* CEnemyStateBase::GetOwner()
{
	return m_pEnemy;
}

//========================================================================================================
//待機状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CEnemyNeutralState::CEnemyNeutralState()
{

}

//==========================
//デストラクタ
//==========================
CEnemyNeutralState::~CEnemyNeutralState()
{

}

//==========================
//開始
//==========================
void CEnemyNeutralState::Start()
{
	//モーションを設定
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);
}

//==========================
//更新
//==========================
void CEnemyNeutralState::Update()
{

	//モーションを設定
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);

	if (m_pEnemy->GetDamage())
	{//ダメージを受けた

		m_pEnemy->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CEnemyDamageState;
		m_pEnemy->ChangeState(NewState);
		return;
	}

	if (m_pEnemy->JudgeWalk()//歩いて近づく範囲にいる
		||m_pEnemy->GetAttackable()//攻撃可能か
		|| m_pEnemy->GetPatrol())//移動地点を巡回
	{

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyMoveState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
	else if (m_pEnemy->JudgeDush()
		&&!m_pEnemy->GetPatrol())
	{//走って近づく範囲にいる

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyDushState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CEnemyNeutralState::Uninit()
{
	CEnemyStateBase::Uninit();
}

//========================================================================================================
//移動状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CEnemyMoveState::CEnemyMoveState()
{

}

//==========================
//デストラクタ
//==========================
CEnemyMoveState::~CEnemyMoveState()
{

}

//==========================
//開始
//==========================
void CEnemyMoveState::Start()
{
	//モーションを設定
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::MOVE);
}

//==========================
//更新
//==========================
void CEnemyMoveState::Update()
{
	//モーションを設定
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::MOVE);

	//移動処理
	if (!m_pEnemy->GetPatrol())
	{//移動地点を巡回しない

		//プレイヤーに向かう
		m_pEnemy->Walk();
	}
	else
	{
		//移動地点を巡回
		m_pEnemy->Patrol();

		if (m_pEnemy->JudgeWalk())
		{//プレイヤーが近づく範囲にいる

			//巡回を終了
			m_pEnemy->SetEndPatrol();
		}
	}
	m_pEnemy->Move();

	if (m_pEnemy->GetDamage())
	{//ダメージを受けた

		m_pEnemy->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CEnemyDamageState;
		m_pEnemy->ChangeState(NewState);
		return;
	}

	if (m_pEnemy->JudgeDush()
		&& !m_pEnemy->GetPatrol())
	{//走って近づく状態

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyDushState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
	else if (m_pEnemy->GetAttackable()
		&& !m_pEnemy->JudgeAttackRange())
	{//攻撃可能かつ攻撃範囲にいる

		//攻撃状態に変更
		auto NewState = DBG_NEW CEnemyAttackState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
	else if (m_pEnemy->JudgeStop()
		&& !m_pEnemy->GetAttackable())
	{//停止する範囲にいるかつ攻撃できない

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CEnemyMoveState::Uninit()
{
	CEnemyStateBase::Uninit();
}

//========================================================================================================
//ダメージ状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CEnemyDamageState::CEnemyDamageState():
	m_DmageCount(0)//ダメージを受けてからのフレーム数
{

}

//==========================
//デストラクタ
//==========================
CEnemyDamageState::~CEnemyDamageState()
{

}

//==========================
//開始
//==========================
void CEnemyDamageState::Start()
{
	//モーションを設定
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::DAMAGE);
}

//==========================
//更新
//==========================
void CEnemyDamageState::Update()
{
	//モーションを設定
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::DAMAGE);

	//ダメージを受けてからのフレーム数を数える
	m_DmageCount++;

	if (m_DmageCount >= DAMEGE_FLAME)
	{
		m_DmageCount = 0;
		m_pEnemy->ResetDamageNum();//被弾回数を初期化
		m_pEnemy->SetDamage(false);

		//移動状態に変更
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);

		return;
	}

	if (m_pEnemy->GetDamageNum() >= 3
		|| m_pEnemy->GetLife() <= 0)
	{//連続で3回被弾した

		m_pEnemy->SetDamage(false);

		//吹き飛び状態に変更
		auto NewState = DBG_NEW CEnemyDamageBrrowState;
		m_pEnemy->ChangeState(NewState);
		return;
	}

	if (m_pEnemy->GetDamage())
	{//ダメージを受けた

		m_pEnemy->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CEnemyDamageState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CEnemyDamageState::Uninit()
{
	CEnemyStateBase::Uninit();
}

//========================================================================================================
//ダッシュ状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CEnemyDushState::CEnemyDushState()
{

}

//==========================
//デストラクタ
//==========================
CEnemyDushState::~CEnemyDushState()
{

}

//==========================
//開始
//==========================
void CEnemyDushState::Start()
{
	//モーションを設定
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::DUSH);
}

//==========================
//更新
//==========================
void CEnemyDushState::Update()
{
	//モーションを設定
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::DUSH);

	//移動処理
	m_pEnemy->Dush();
	m_pEnemy->Move();

	if (m_pEnemy->GetDamage())
	{//ダメージを受けた

		m_pEnemy->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CEnemyDamageState;
		m_pEnemy->ChangeState(NewState);
		return;
	}

	if (m_pEnemy->JudgeWalk())
	{//歩いて近づく状態

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyMoveState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
	else if (m_pEnemy->JudgeStop())
	{//停止する範囲にいるかつ攻撃できない

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CEnemyDushState::Uninit()
{
	CEnemyStateBase::Uninit();
}

//========================================================================================================
//吹き飛び状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CEnemyDamageBrrowState::CEnemyDamageBrrowState() :
	m_DmageCount(0)//ダメージを受けてからのフレーム数
{

}

//==========================
//デストラクタ
//==========================
CEnemyDamageBrrowState::~CEnemyDamageBrrowState()
{

}

//==========================
//開始
//==========================
void CEnemyDamageBrrowState::Start()
{
	//モーションを設定
	m_pEnemy->SetMotion(CMotionModel::MOTION_TYPE::DAMAGEBLOW);
}

//==========================
//更新
//==========================
void CEnemyDamageBrrowState::Update()
{
	//移動処理
	m_pEnemy->Move();

	m_DmageCount++;

	if (m_pEnemy->GetLife() <= 0)
	{//ライフが0

		if (m_DmageCount >= 30)
		{
			m_pEnemy->ChangePlayMotion(false);//モーションを停止
			m_pEnemy->SubPartsCol();//色を薄くする
		}
	}
	else if (m_DmageCount >= BRROW_FLAME)
	{
		m_DmageCount = 0;
		m_pEnemy->ResetDamageNum();//被弾回数を初期化

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CEnemyDamageBrrowState::Uninit()
{
	CEnemyStateBase::Uninit();
}

//========================================================================================================
//攻撃状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CEnemyAttackState::CEnemyAttackState():
m_FlameCount(0),//攻撃のフレーム数
m_Combo(true),//コンボ判定
m_EnemyAttackStateMachine(nullptr)//攻撃の状態管理
{

}

//==========================
//デストラクタ
//==========================
CEnemyAttackState::~CEnemyAttackState()
{

}

//==========================
//開始
//==========================
void CEnemyAttackState::Start()
{
	m_EnemyAttackStateMachine = DBG_NEW CEnemyAttackStateMachine;

	
	if (m_pEnemy->GetEnemyType()==CEnemy::ENEMY_TYPE::HitEnemy)
	{//素手の敵

		auto NewState = DBG_NEW CFirstEnemyAttackState;
		ChangeAttack(NewState);
	}
	else
	{//片手武器
		auto NewState = DBG_NEW CFirstSmallWeaponEnemyAttack;
		ChangeAttack(NewState);
	}
}

//==========================
//更新
//==========================
void CEnemyAttackState::Update()
{
	if (m_pEnemy->GetDamage())
	{//ダメージを受けた

		//攻撃出来ない状態に変更
		m_pEnemy->ChangeAttackable();

		//攻撃のクールタイムを設定
		m_pEnemy->SetCoolTime(300);

		m_pEnemy->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CEnemyDamageState;
		m_pEnemy->ChangeState(NewState);
		return;
	}

	m_FlameCount++;
	m_EnemyAttackStateMachine->Update();	

	if (m_Combo)
	{//攻撃中は終了
		return;
	}

	if (m_pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::HitEnemy)
	{//素手の敵

		//攻撃出来ない状態に変更
		m_pEnemy->ChangeAttackable();

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CEnemyAttackState::Uninit()
{
	if (m_EnemyAttackStateMachine != nullptr)
	{
		delete m_EnemyAttackStateMachine;
		m_EnemyAttackStateMachine = nullptr;
	}

	CEnemyStateBase::Uninit();
}

//==========================
//コンボ判定を取得
//========================== 
void CEnemyAttackState::ChangeCombo()
{
	m_Combo=!m_Combo;
}

//==========================
//情報を初期化
//==========================
void CEnemyAttackState::ResetInfo()
{
	m_FlameCount = 0;
}

//==========================
//攻撃を変更
//==========================
void CEnemyAttackState::ChangeAttack(CAttackEnemyState* State)
{
	State->SetOwner(this);
	m_EnemyAttackStateMachine->ChangeState(State);
}

//==========================
//攻撃フレーム数を取得
//==========================
int CEnemyAttackState::GetFrame()
{
	return m_FlameCount;
}
