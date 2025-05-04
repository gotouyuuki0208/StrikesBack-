//==========================
// 
// 敵の状態管理[enemystate.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "enemystate.h"
#include "enemy.h"
#include"enemyattackstate.h"

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
void CEnemyStateBase::SetOwner(CEnemy* enemy)
{
	m_pEnemy = enemy;
}

//==========================
//ステートの所有者を取得
//==========================
CEnemy* CEnemyStateBase::GetOwner()
{
	return m_pEnemy;
}

//========================================================================================================
//仮状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CEnemyMovabeState::CEnemyMovabeState()
{

}

//==========================
//デストラクタ
//==========================
CEnemyMovabeState::~CEnemyMovabeState()
{

}

//==========================
//開始
//==========================
void CEnemyMovabeState::Start()
{
	
}

//==========================
//更新
//==========================
void CEnemyMovabeState::Update()
{
	//行動可能か判定
	m_pEnemy->JudgeMovable();

	if (m_pEnemy->GetMovable())
	{//行動可能

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyNeutralState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CEnemyMovabeState::Uninit()
{
	CEnemyStateBase::Uninit();
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

	if (m_pEnemy->JudgeDush())
	{//走って近づく状態

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyDushState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
	else if (m_pEnemy->JudgeWalk())
	{//歩いて近づく状態

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyMoveState;
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
	m_pEnemy->Walk();
	m_pEnemy->Move();

	if (m_pEnemy->JudgeDush())
	{//走って近づく状態

		//待機状態に変更
		auto NewState = DBG_NEW CEnemyDushState;
		m_pEnemy->ChangeState(NewState);
		return;
	}
	else if (m_pEnemy->GetAttackable()
		&& !m_pEnemy->JudgeAttacKRange())
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
m_EenemyAttackStateMachine(nullptr)//攻撃の状態管理
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
	m_EenemyAttackStateMachine = DBG_NEW CEenemyAttackStateMachine;

	
	if (m_pEnemy->GetEnemyType()==CEnemy::ENEMY_TYPE::HitEnemy)
	{//素手の敵

		auto NewState = DBG_NEW CFirstEenemyAttackState;
		ChangeAttack(NewState);
	}
	else
	{//片手武器
		auto NewState = DBG_NEW CFirstSmallWeaponEenemyAttack;
		ChangeAttack(NewState);
	}
}

//==========================
//更新
//==========================
void CEnemyAttackState::Update()
{
	m_FlameCount++;
	m_EenemyAttackStateMachine->Update();	

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
	if (m_EenemyAttackStateMachine != nullptr)
	{
		delete m_EenemyAttackStateMachine;
		m_EenemyAttackStateMachine = nullptr;
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
void CEnemyAttackState::ChangeAttack(CAttackEenemyState* State)
{
	State->SetOwner(this);
	m_EenemyAttackStateMachine->ChangeState(State);
}

//==========================
//攻撃フレーム数を取得
//==========================
int CEnemyAttackState::GetFrame()
{
	return m_FlameCount;
}
