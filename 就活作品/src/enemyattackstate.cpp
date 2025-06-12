//==========================
// 
// 敵の攻撃の状態管理[enemyattackstate.h]
// Author Yuki Goto
//
//==========================

//include
#include"manager.h"
#include"enemyattackstate.h"
#include"trajectory.h"
#include"weakenemy.h"

//静的メンバ変数初期化
const int CEnemyAttackStateBase::LEFT_HAND = 5;//左手の番号
const int CEnemyAttackStateBase::RIGHT_HAND = 8;//右手の番号
//const int CAttackStateBase::WIDTH = 20;//軌跡の横の分割数
//const int CAttackStateBase::VERTICAL = 20;//軌跡の縦の分割数
//const D3DXVECTOR3 CAttackStateBase::TRAJECTORY_SIZE = { 5.0f,5.0f ,0.0f };//軌跡の大きさ
const int CEnemyAttackStateBase::HITFLAME = 18;//素手攻撃の当たり判定のフレーム数
//========================================================================================================
//状態管理クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CEnemyAttackStateMachine::CEnemyAttackStateMachine() :
	m_State(nullptr)//プレイヤーの状態
{

}

//==========================
//デストラクタ
//==========================
CEnemyAttackStateMachine::~CEnemyAttackStateMachine()
{
	if (m_State != nullptr)
	{
		delete m_State;
		m_State = nullptr;
	}
}

//==========================
//状態の変更
//==========================
void CEnemyAttackStateMachine::ChangeState(CEnemyAttackStateBase* NewState)
{
	if (m_State != nullptr)
	{
		m_State->Uninit();
		m_State = nullptr;
	}

	m_State = NewState;

	m_State->Start();
}

//==========================
//更新
//==========================
void CEnemyAttackStateMachine::Update()
{
	if (m_State != nullptr)
	{
		m_State->Update();
	}
}

//========================================================================================================
//基底クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CEnemyAttackStateBase::CEnemyAttackStateBase()
	//m_Trajectory(nullptr)//軌跡の情報
{

}

//==========================
//デストラクタ
//==========================
CEnemyAttackStateBase::~CEnemyAttackStateBase()
{

}

//==========================
//開始
//==========================
void CEnemyAttackStateBase::Start()
{

}

//==========================
//更新
//==========================
void CEnemyAttackStateBase::Update()
{

}

//==========================
//終了
//==========================
void CEnemyAttackStateBase::Uninit()
{
	/*if (m_Trajectory != nullptr)
	{
		m_Trajectory->Uninit();
		m_Trajectory = nullptr;
	}*/

	delete this;
}

////==========================
////軌跡の生成
////==========================
//void CAttackStateBase::CreateTrajectory(D3DXVECTOR3 pos)
//{
//	if (m_Trajectory != nullptr)
//	{//軌跡が生成されている
//		return;
//	}
//
//	//軌跡を生成
//	m_Trajectory = CTrajectory::Create(pos, TRAJECTORY_SIZE, WIDTH, VERTICAL);
//}
//
////==========================
////軌跡の位置を設定
////==========================
//void CAttackStateBase::TrajectoryPos(D3DXVECTOR3 pos)
//{
//	if (m_Trajectory == nullptr)
//	{//軌跡が生成されていない
//		return;
//	}
//
//	//新しい位置を設定
//	m_Trajectory->SetNewPos(pos);
//}

//========================================================================================================
//プレイヤーの攻撃状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CAttackEnemyState::CAttackEnemyState() :
	m_OwnerState(nullptr)//ステートの所有者
{

}

//==========================
//デストラクタ
//==========================
CAttackEnemyState::~CAttackEnemyState()
{

}

//==========================
//ステートの所持者を設定
//==========================
void CAttackEnemyState::SetOwner(CEnemyAttackState* State)
{
	m_OwnerState = State;
}

//==============================================================================
//素手攻撃クラス
//==============================================================================

//=============================1回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CFirstEnemyAttackState::CFirstEnemyAttackState()
{

}

//==========================
//デストラクタ
//==========================
CFirstEnemyAttackState::~CFirstEnemyAttackState()
{

}

//==========================
//開始
//==========================
void CFirstEnemyAttackState::Start()
{
	//攻撃判定を初期化
	m_OwnerState->GetOwner()->ResetAttack();
}

//==========================
//更新
//==========================
void CFirstEnemyAttackState::Update()
{
	//モーションの設定
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK);

	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() < HITFLAME)
	{//攻撃開始から20フレーム以下
		
		//攻撃の当たり判定
		m_OwnerState->GetOwner()->HitPlayer(RIGHT_HAND);
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//攻撃範囲にプレイヤーがいる

		m_OwnerState->ResetInfo();//攻撃の情報を初期化
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//モーションを停止

		auto NewState = DBG_NEW CSecondEnemyAttackState;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
	else
	{
		//攻撃終了
		m_OwnerState->ChangeCombo();

		//攻撃のクールタイムを設定
		m_OwnerState->GetOwner()->SetCoolTime(300);
	}
}

//==========================
//終了
//==========================
void CFirstEnemyAttackState::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}

//=============================2回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CSecondEnemyAttackState::CSecondEnemyAttackState()
{

}

//==========================
//デストラクタ
//==========================
CSecondEnemyAttackState::~CSecondEnemyAttackState()
{

}

//==========================
//開始
//==========================
void CSecondEnemyAttackState::Start()
{
	//攻撃判定を初期化
	m_OwnerState->GetOwner()->ResetAttack();

	//向きを変更
	m_OwnerState->GetOwner()->ChangeDirection();

	//モーションを再生
	m_OwnerState->GetOwner()->ChangePlayMotion(true);
}

//==========================
//更新
//==========================
void CSecondEnemyAttackState::Update()
{
	//モーション変更
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK2);

	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() < HITFLAME)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->HitPlayer(LEFT_HAND);
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//攻撃範囲にプレイヤーがいる

		m_OwnerState->ResetInfo();//攻撃の情報を初期化
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//モーションを停止

		auto NewState = DBG_NEW CRastEnemyAttackState;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
	else
	{
		//攻撃終了
		m_OwnerState->ChangeCombo();

		//攻撃のクールタイムを設定
		m_OwnerState->GetOwner()->SetCoolTime(300);
	}
}

//==========================
//終了
//==========================
void CSecondEnemyAttackState::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}

//=============================3回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CRastEnemyAttackState::CRastEnemyAttackState()
{

}

//==========================
//デストラクタ
//==========================
CRastEnemyAttackState::~CRastEnemyAttackState()
{

}

//==========================
//開始
//==========================
void CRastEnemyAttackState::Start()
{
	//攻撃判定を初期化
	m_OwnerState->GetOwner()->ResetAttack();

	//向きを変更
	m_OwnerState->GetOwner()->ChangeDirection();

	//モーションを再生
	m_OwnerState->GetOwner()->ChangePlayMotion(true);
}

//==========================
//更新
//==========================
void CRastEnemyAttackState::Update()
{
	//モーションの変更
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK3);

	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= HITFLAME)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->HitPlayer(RIGHT_HAND);
	}
	else
	{
		//攻撃終了
		m_OwnerState->ChangeCombo();

		//攻撃のクールタイムを設定
		m_OwnerState->GetOwner()->SetCoolTime(300);
	}
}

//==========================
//終了
//==========================
void CRastEnemyAttackState::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}

//==============================================================================
//片手武器攻撃クラス
//==============================================================================

//=============================1回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CFirstSmallWeaponEnemyAttack::CFirstSmallWeaponEnemyAttack()
{

}

//==========================
//デストラクタ
//==========================
CFirstSmallWeaponEnemyAttack::~CFirstSmallWeaponEnemyAttack()
{

}

//==========================
//開始
//==========================
void CFirstSmallWeaponEnemyAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK);
}

//==========================
//更新
//==========================
void CFirstSmallWeaponEnemyAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		//m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		//m_OwnerState->GetOwner()->WeaponHitEnemy();
	}
}

//==========================
//終了
//==========================
void CFirstSmallWeaponEnemyAttack::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}

//=============================2回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CSecondSmallWeaponEnemyAttack::CSecondSmallWeaponEnemyAttack()
{

}

//==========================
//デストラクタ
//==========================
CSecondSmallWeaponEnemyAttack::~CSecondSmallWeaponEnemyAttack()
{

}

//==========================
//開始
//==========================
void CSecondSmallWeaponEnemyAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK2);
}

//==========================
//更新
//==========================
void CSecondSmallWeaponEnemyAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		//m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		//m_OwnerState->GetOwner()->WeaponHitEnemy();
	}
}

//==========================
//終了
//==========================
void CSecondSmallWeaponEnemyAttack::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}

//=============================3回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CRastSmallWeaponEnemyAttack::CRastSmallWeaponEnemyAttack()
{

}

//==========================
//デストラクタ
//==========================
CRastSmallWeaponEnemyAttack::~CRastSmallWeaponEnemyAttack()
{

}

//==========================
//開始
//==========================
void CRastSmallWeaponEnemyAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK3);
}

//==========================
//更新
//==========================
void CRastSmallWeaponEnemyAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		//m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		//m_OwnerState->GetOwner()->WeaponHitEnemy();
	}
}

//==========================
//終了
//==========================
void CRastSmallWeaponEnemyAttack::Uninit()
{
	CEnemyAttackStateBase::Uninit();
}