//==========================
// 
// 攻撃の状態管理[attackstate.h]
// Author Yuki Goto
//
//==========================

//include
#include"manager.h"
#include"attackstate.h"
#include"trajectory.h"
#include "playerstate.h"

//静的メンバ変数初期化
const int CAttackStateBase::LEFT_HAND = 5;//左手の番号
const int CAttackStateBase::RIGHT_HAND = 8;//右手の番号
const int CAttackStateBase::WIDTH = 20;//軌跡の横の分割数
const int CAttackStateBase::VERTICAL = 20;//軌跡の縦の分割数
const D3DXVECTOR3 CAttackStateBase::TRAJECTORY_SIZE = { 5.0f,5.0f ,0.0f };//軌跡の大きさ
const int CAttackStateBase::HITFLAME = 18;//素手攻撃の当たり判定のフレーム数
//========================================================================================================
//状態管理クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CAttackStateMachine::CAttackStateMachine() :
	m_State(nullptr)//プレイヤーの状態
{

}

//==========================
//デストラクタ
//==========================
CAttackStateMachine::~CAttackStateMachine()
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
void CAttackStateMachine::ChangeState(CAttackPlayerStateBase* NewState)
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
void CAttackStateMachine::Update()
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
CAttackStateBase::CAttackStateBase():
m_Trajectory(nullptr)//軌跡の情報
{

}

//==========================
//デストラクタ
//==========================
CAttackStateBase::~CAttackStateBase()
{

}

//==========================
//開始
//==========================
void CAttackStateBase::Start()
{

}

//==========================
//更新
//==========================
void CAttackStateBase::Update()
{

}

//==========================
//終了
//==========================
void CAttackStateBase::Uninit()
{
	if (m_Trajectory != nullptr)
	{
		m_Trajectory->Uninit();
		m_Trajectory = nullptr;
	}

	delete this;
}

//==========================
//軌跡の生成
//==========================
void CAttackStateBase::CreateTrajectory(D3DXVECTOR3 pos)
{
	if (m_Trajectory != nullptr)
	{//軌跡が生成されている
		return;
	}

	//軌跡を生成
	m_Trajectory = CTrajectory::Create(pos, TRAJECTORY_SIZE, WIDTH, VERTICAL);
}

//==========================
//軌跡の位置を設定
//==========================
void CAttackStateBase::TrajectoryPos(D3DXVECTOR3 pos)
{
	if (m_Trajectory == nullptr)
	{//軌跡が生成されていない
		return;
	}

	//新しい位置を設定
	m_Trajectory->SetNewPos(pos);
}

//========================================================================================================
//プレイヤーの攻撃状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CAttackPlayerStateBase::CAttackPlayerStateBase():
	m_OwnerState(nullptr)//ステートの所有者
{

}

//==========================
//デストラクタ
//==========================
CAttackPlayerStateBase::~CAttackPlayerStateBase()
{

}

//==========================
//ステートの所持者を設定
//==========================
void CAttackPlayerStateBase::SetOwner(CAttackState* State)
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
CFirstAttackState::CFirstAttackState()
{

}

//==========================
//デストラクタ
//==========================
CFirstAttackState::~CFirstAttackState()
{

}

//==========================
//開始
//==========================
void CFirstAttackState::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK);
	
	//プレイヤーのパーツのマトリックスを取得
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(RIGHT_HAND)->GetMtxWorld();

	//軌跡を生成
	CreateTrajectory({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });
}

//==========================
//更新
//==========================
void CFirstAttackState::Update()
{
	//プレイヤーのパーツのマトリックスを取得
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(RIGHT_HAND)->GetMtxWorld();

	//軌跡の新しい位置を設定
	TrajectoryPos({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });

	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame()<= HITFLAME)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->HitEnemy(RIGHT_HAND);
	}

	if (m_OwnerState->GetCombo())
	{//攻撃ボタンが入力された

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CSecondAttackState;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CFirstAttackState::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================2回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CSecondAttackState::CSecondAttackState()
{

}

//==========================
//デストラクタ
//==========================
CSecondAttackState::~CSecondAttackState()
{

}

//==========================
//開始
//==========================
void CSecondAttackState::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK2);

	//プレイヤーのパーツのマトリックスを取得
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(LEFT_HAND)->GetMtxWorld();

	//軌跡を生成
	CreateTrajectory({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });
}

//==========================
//更新
//==========================
void CSecondAttackState::Update()
{
	//プレイヤーのパーツのマトリックスを取得
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(LEFT_HAND)->GetMtxWorld();

	//軌跡の新しい位置を設定
	TrajectoryPos({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });

	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= HITFLAME)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->HitEnemy(LEFT_HAND);
	}
	
	if (m_OwnerState->GetCombo())
	{//攻撃ボタンが入力された

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CRastAttackState;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CSecondAttackState::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================3回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CRastAttackState::CRastAttackState()
{

}

//==========================
//デストラクタ
//==========================
CRastAttackState::~CRastAttackState()
{

}

//==========================
//開始
//==========================
void CRastAttackState::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK3);

	//プレイヤーのパーツのマトリックスを取得
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(RIGHT_HAND)->GetMtxWorld();

	//軌跡を生成
	CreateTrajectory({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });
}

//==========================
//更新
//==========================
void CRastAttackState::Update()
{
	//プレイヤーのパーツのマトリックスを取得
	D3DXMATRIX PlayerMtx = m_OwnerState->GetOwner()->GetParts(RIGHT_HAND)->GetMtxWorld();

	//軌跡の新しい位置を設定
	TrajectoryPos({ PlayerMtx._41,PlayerMtx._42 ,PlayerMtx._43 });

	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= HITFLAME)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->HitEnemy(RIGHT_HAND);
	}
}

//==========================
//終了
//==========================
void CRastAttackState::Uninit()
{
	CAttackStateBase::Uninit();
}

//==============================================================================
//両手武器攻撃クラス
//==============================================================================

//=============================1回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CFirstBigWeaponAttack::CFirstBigWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CFirstBigWeaponAttack::~CFirstBigWeaponAttack()
{

}

//==========================
//開始
//==========================
void CFirstBigWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK);
}

//==========================
//更新
//==========================
void CFirstBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}

	if (m_OwnerState->GetCombo())
	{//攻撃ボタンが入力された

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CSecondBigWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CFirstBigWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================2回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CSecondBigWeaponAttack::CSecondBigWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CSecondBigWeaponAttack::~CSecondBigWeaponAttack()
{

}

//==========================
//開始
//==========================
void CSecondBigWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK2);
}

//==========================
//更新
//==========================
void CSecondBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}

	if (m_OwnerState->GetCombo())
	{//攻撃ボタンが入力された

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CRastBigWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CSecondBigWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================3回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CRastBigWeaponAttack::CRastBigWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CRastBigWeaponAttack::~CRastBigWeaponAttack()
{

}

//==========================
//開始
//==========================
void CRastBigWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK3);
}

//==========================
//更新
//==========================
void CRastBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}
}

//==========================
//終了
//==========================
void CRastBigWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}

//==============================================================================
//片手武器攻撃クラス
//==============================================================================

//=============================1回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CFirstSmallWeaponAttack::CFirstSmallWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CFirstSmallWeaponAttack::~CFirstSmallWeaponAttack()
{

}

//==========================
//開始
//==========================
void CFirstSmallWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK);
}

//==========================
//更新
//==========================
void CFirstSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}

	if (m_OwnerState->GetCombo())
	{//攻撃ボタンが入力された

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CSecondSmallWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CFirstSmallWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================2回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CSecondSmallWeaponAttack::CSecondSmallWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CSecondSmallWeaponAttack::~CSecondSmallWeaponAttack()
{

}

//==========================
//開始
//==========================
void CSecondSmallWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK2);
}

//==========================
//更新
//==========================
void CSecondSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}

	if (m_OwnerState->GetCombo())
	{//攻撃ボタンが入力された

		m_OwnerState->ResetInfo();

		auto NewState = DBG_NEW CRastSmallWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CSecondSmallWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}

//=============================3回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CRastSmallWeaponAttack::CRastSmallWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CRastSmallWeaponAttack::~CRastSmallWeaponAttack()
{

}

//==========================
//開始
//==========================
void CRastSmallWeaponAttack::Start()
{
	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK3);
}

//==========================
//更新
//==========================
void CRastSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->WeaponHitEnemy();
	}
}

//==========================
//終了
//==========================
void CRastSmallWeaponAttack::Uninit()
{
	CAttackStateBase::Uninit();
}