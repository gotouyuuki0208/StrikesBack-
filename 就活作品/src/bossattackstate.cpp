//==========================
// 
// 攻撃の状態管理[attackstate.h]
// Author Yuki Goto
//
//==========================

//include
#include"manager.h"
#include"bossattackstate.h"
#include"bossState.h"
#include"boss.h"

//静的メンバ変数初期化
const int CBossAttackStateBase::LEFT_HAND = 5;//左手の番号
const int CBossAttackStateBase::RIGHT_HAND = 8;//右手の番号
const int CBossAttackStateBase::HITFLAME = 18;//素手攻撃の当たり判定のフレーム数
//========================================================================================================
//状態管理クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossAttackStateMachine::CBossAttackStateMachine() :
	m_State(nullptr)
{

}

//==========================
//デストラクタ
//==========================
CBossAttackStateMachine::~CBossAttackStateMachine()
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
void CBossAttackStateMachine::ChangeState(CAttackBossStateBase* NewState)
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
void CBossAttackStateMachine::Update()
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
CBossAttackStateBase::CBossAttackStateBase()
{

}

//==========================
//デストラクタ
//==========================
CBossAttackStateBase::~CBossAttackStateBase()
{

}

//==========================
//開始
//==========================
void CBossAttackStateBase::Start()
{

}

//==========================
//更新
//==========================
void CBossAttackStateBase::Update()
{

}

//==========================
//終了
//==========================
void CBossAttackStateBase::Uninit()
{
	delete this;
}

//========================================================================================================
//ボスの攻撃状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CAttackBossStateBase::CAttackBossStateBase() :
	m_OwnerState(nullptr)//ステートの所有者
{

}

//==========================
//デストラクタ
//==========================
CAttackBossStateBase::~CAttackBossStateBase()
{

}

//==========================
//ステートの所持者を設定
//==========================
void CAttackBossStateBase::SetOwner(CBossAttackState* State)
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
CBossFirstAttackState::CBossFirstAttackState()
{

}

//==========================
//デストラクタ
//==========================
CBossFirstAttackState::~CBossFirstAttackState()
{

}

//==========================
//開始
//==========================
void CBossFirstAttackState::Start()
{
	//攻撃ヒット判定を解除
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK);
}

//==========================
//更新
//==========================
void CBossFirstAttackState::Update()
{
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
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//攻撃範囲にプレイヤーがいる

		m_OwnerState->ResetInfo();//攻撃の情報を初期化
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//モーションを停止

		auto NewState = DBG_NEW CBossSecondAttackState;
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
void CBossFirstAttackState::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================2回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CBossSecondAttackState::CBossSecondAttackState()
{

}

//==========================
//デストラクタ
//==========================
CBossSecondAttackState::~CBossSecondAttackState()
{

}

//==========================
//開始
//==========================
void CBossSecondAttackState::Start()
{
	//攻撃ヒット判定を解除
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK2);
}

//==========================
//更新
//==========================
void CBossSecondAttackState::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= HITFLAME)
	{//攻撃開始から20フレーム以下

		//攻撃の当たり判定
		m_OwnerState->GetOwner()->HitPlayer(LEFT_HAND);
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//攻撃範囲にプレイヤーがいる

		m_OwnerState->ResetInfo();//攻撃の情報を初期化
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//モーションを停止

		auto NewState = DBG_NEW CBossRastAttackState;
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
void CBossSecondAttackState::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================3回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CBossRastAttackState::CBossRastAttackState()
{

}

//==========================
//デストラクタ
//==========================
CBossRastAttackState::~CBossRastAttackState()
{

}

//==========================
//開始
//==========================
void CBossRastAttackState::Start()
{
	//攻撃ヒット判定を解除
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::ATTACK3);
}

//==========================
//更新
//==========================
void CBossRastAttackState::Update()
{
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
void CBossRastAttackState::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//==============================================================================
//両手武器攻撃クラス
//==============================================================================

//=============================1回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CBossFirstBigWeaponAttack::CBossFirstBigWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CBossFirstBigWeaponAttack::~CBossFirstBigWeaponAttack()
{

}

//==========================
//開始
//==========================
void CBossFirstBigWeaponAttack::Start()
{
	//攻撃ヒット判定を解除
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK);
}

//==========================
//更新
//==========================
void CBossFirstBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//当たり判定
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//攻撃範囲にプレイヤーがいる

		m_OwnerState->ResetInfo();//攻撃の情報を初期化
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//モーションを停止

		auto NewState = DBG_NEW CBossSecondBigWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CBossFirstBigWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================2回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CBossSecondBigWeaponAttack::CBossSecondBigWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CBossSecondBigWeaponAttack::~CBossSecondBigWeaponAttack()
{

}

//==========================
//開始
//==========================
void CBossSecondBigWeaponAttack::Start()
{
	//攻撃ヒット判定を解除
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK2);
}

//==========================
//更新
//==========================
void CBossSecondBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//当たり判定
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
		
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//攻撃範囲にプレイヤーがいる

		m_OwnerState->ResetInfo();//攻撃の情報を初期化
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//モーションを停止

		auto NewState = DBG_NEW CBossRastBigWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CBossSecondBigWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================3回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CBossRastBigWeaponAttack::CBossRastBigWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CBossRastBigWeaponAttack::~CBossRastBigWeaponAttack()
{

}

//==========================
//開始
//==========================
void CBossRastBigWeaponAttack::Start()
{
	//攻撃ヒット判定を解除
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::WEAPONATTACK3);
}

//==========================
//更新
//==========================
void CBossRastBigWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//当たり判定
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
		
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
void CBossRastBigWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//==============================================================================
//片手武器攻撃クラス
//==============================================================================

//=============================1回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CBossFirstSmallWeaponAttack::CBossFirstSmallWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CBossFirstSmallWeaponAttack::~CBossFirstSmallWeaponAttack()
{

}

//==========================
//開始
//==========================
void CBossFirstSmallWeaponAttack::Start()
{
	//攻撃ヒット判定を解除
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK);
}

//==========================
//更新
//==========================
void CBossFirstSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//当たり判定
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
		
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//攻撃範囲にプレイヤーがいる

		m_OwnerState->ResetInfo();//攻撃の情報を初期化
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//モーションを停止

		auto NewState = DBG_NEW CBossSecondSmallWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CBossFirstSmallWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================2回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CBossSecondSmallWeaponAttack::CBossSecondSmallWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CBossSecondSmallWeaponAttack::~CBossSecondSmallWeaponAttack()
{

}

//==========================
//開始
//==========================
void CBossSecondSmallWeaponAttack::Start()
{
	//攻撃ヒット判定を解除
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK2);
}

//==========================
//更新
//==========================
void CBossSecondSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//当たり判定
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
		
	}
	else if (!m_OwnerState->GetOwner()->JudgeAttackRange())
	{//攻撃範囲にプレイヤーがいる

		m_OwnerState->ResetInfo();//攻撃の情報を初期化
		m_OwnerState->GetOwner()->ChangePlayMotion(false);//モーションを停止

		auto NewState = DBG_NEW CBossRastSmallWeaponAttack;
		m_OwnerState->ChangeAttack(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CBossSecondSmallWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}

//=============================3回目の攻撃======================================

//==========================
//コンストラクタ
//==========================
CBossRastSmallWeaponAttack::CBossRastSmallWeaponAttack()
{

}

//==========================
//デストラクタ
//==========================
CBossRastSmallWeaponAttack::~CBossRastSmallWeaponAttack()
{

}

//==========================
//開始
//==========================
void CBossRastSmallWeaponAttack::Start()
{
	//攻撃ヒット判定を解除
	m_OwnerState->GetOwner()->ResetAttack();

	m_OwnerState->GetOwner()->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONATTACK3);
}

//==========================
//更新
//==========================
void CBossRastSmallWeaponAttack::Update()
{
	if (m_OwnerState->GetFrame() <= 10)
	{//攻撃開始から10フレーム以下

		//攻撃時の移動
		m_OwnerState->GetOwner()->AttackMove();
		m_OwnerState->GetOwner()->Move();
	}

	if (m_OwnerState->GetFrame() <= 20)
	{//攻撃開始から20フレーム以下

		//当たり判定
		m_OwnerState->GetOwner()->ColisionWeaponAttack();

		if (m_OwnerState->GetOwner()->GetWeaponBreak())
		{
			return;
		}
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
void CBossRastSmallWeaponAttack::Uninit()
{
	CBossAttackStateBase::Uninit();
}