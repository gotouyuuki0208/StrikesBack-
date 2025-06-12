//==========================
// 
// ボスの状態管理[bossState.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bossState.h"
#include "boss.h"
#include "bossattackstate.h"
#include"manager.h"

//静的メンバ初期化
const int CBossDamageState::DAMEGE_FLAME = 54;//ダメージ状態を終了するまでのフレーム数
const int CBossDamageBrrowState::BRROW_FLAME = 50;//ダメージ状態を終了するまでのフレーム数
//==============================================================================
//敵の状態クラス
//==============================================================================

//==========================
//コンストラクタ
//==========================
CBossStateBase::CBossStateBase() :
	m_pBoss(nullptr)//敵の情報
{

}

//==========================
//デストラクタ
//==========================
CBossStateBase::~CBossStateBase()
{

}

//==========================
//ステートの所持者を設定
//==========================
void CBossStateBase::SetOwner(CBoss* enemy)
{
	m_pBoss = enemy;
}

//==========================
//ステートの所有者を取得
//==========================
CBoss* CBossStateBase::GetOwner()
{
	return m_pBoss;
}

//========================================================================================================
//演出状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossDirectionState::CBossDirectionState()
{
	m_count = 0;
}

//==========================
//デストラクタ
//==========================
CBossDirectionState::~CBossDirectionState()
{

}

//==========================
//開始
//==========================
void CBossDirectionState::Start()
{
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::BOSS_DIRECTION);
}

//==========================
//更新
//==========================
void CBossDirectionState::Update()
{	
	if (m_pBoss->GetMotion() == CMotionModel::MOTION_TYPE::NEUTRAL)
	{
		//モーションを設定
		m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL);
	}

	//行動可能か判定
	m_pBoss->JudgeMovable();

	if (CManager::GetInstance()->GetGameManager()->GetPlayGame()
		&& !CManager::GetInstance()->GetGameManager()->GetDirection())
	{//行動可能

		//待機状態に変更
		auto NewState = DBG_NEW CBossSmallWeaponNeutralState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CBossDirectionState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//待機状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossNeutralState::CBossNeutralState()
{

}

//==========================
//デストラクタ
//==========================
CBossNeutralState::~CBossNeutralState()
{

}

//==========================
//開始
//==========================
void CBossNeutralState::Start()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);
}

//==========================
//更新
//==========================
void CBossNeutralState::Update()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);

	if (m_pBoss->GetDamage())
	{//ダメージを受けた

		m_pBoss->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if (m_pBoss->JudgeDush())
	{//走って近づく範囲にいる

		//待機状態に変更
		auto NewState = DBG_NEW CBossDushState;
		m_pBoss->ChangeState(NewState);
		return;
	}
	else if (m_pBoss->JudgeWalk()
		|| m_pBoss->GetAttackable())
	{//歩いて近づく範囲にいるか攻撃可能のとき

		//待機状態に変更
		auto NewState = DBG_NEW CBossMoveState;
		m_pBoss->ChangeState(NewState);
		return;
	}

}

//==========================
//終了
//==========================
void CBossNeutralState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//片手武器所持待機状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossSmallWeaponNeutralState::CBossSmallWeaponNeutralState()
{

}

//==========================
//デストラクタ
//==========================
CBossSmallWeaponNeutralState::~CBossSmallWeaponNeutralState()
{

}

//==========================
//開始
//==========================
void CBossSmallWeaponNeutralState::Start()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL);
}

//==========================
//更新
//==========================
void CBossSmallWeaponNeutralState::Update()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL);

	if (m_pBoss->GetDamage())
	{//ダメージを受けた

		m_pBoss->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if (m_pBoss->JudgeWalk())
	{//歩いて近づく状態

		//待機状態に変更
		auto NewState = DBG_NEW CBossMoveState;
		m_pBoss->ChangeState(NewState);
		return;
	}
	if (m_pBoss->JudgeDush())
	{//走って近づく状態

		//待機状態に変更
		auto NewState = DBG_NEW CBossDushState;
		m_pBoss->ChangeState(NewState);
		return;
	}
	else if (m_pBoss->GetAttackable()&& !m_pBoss->JudgeAttackRange())
	{//攻撃可能かつ攻撃範囲にいる

		//攻撃状態に変更
		auto NewState = DBG_NEW CBossAttackState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CBossSmallWeaponNeutralState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//両手武器所持待機状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossBigWeaponNeutralState::CBossBigWeaponNeutralState()
{

}

//==========================
//デストラクタ
//==========================
CBossBigWeaponNeutralState::~CBossBigWeaponNeutralState()
{

}

//==========================
//開始
//==========================
void CBossBigWeaponNeutralState::Start()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::WEAPONNEUTRAL);
}

//==========================
//更新
//==========================
void CBossBigWeaponNeutralState::Update()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::WEAPONNEUTRAL);

	if (m_pBoss->GetDamage())
	{//ダメージを受けた

		m_pBoss->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if (m_pBoss->JudgeDush()||m_pBoss->JudgeWalk())
	{//移動範囲にいる

		//移動状態に変更
		auto NewState = DBG_NEW CBossWeaponMoveState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	else if (m_pBoss->GetAttackable() && !m_pBoss->JudgeAttackRange())
	{//攻撃可能かつ攻撃範囲にいる

		//攻撃状態に変更
		auto NewState = DBG_NEW CBossAttackState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CBossBigWeaponNeutralState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//移動状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossMoveState::CBossMoveState()
{

}

//==========================
//デストラクタ
//==========================
CBossMoveState::~CBossMoveState()
{

}

//==========================
//開始
//==========================
void CBossMoveState::Start()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::MOVE);
}

//==========================
//更新
//==========================
void CBossMoveState::Update()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::MOVE);

	//移動処理
	m_pBoss->Walk();
	m_pBoss->Move();

	if (m_pBoss->GetDamage())
	{//ダメージを受けた

		m_pBoss->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if (m_pBoss->JudgeDush() ||
		(m_pBoss->GetAttackable() && m_pBoss->GetNextAttack() && !m_pBoss->GetWeapon()))
	{//走って近づく状態か攻撃可能で次の攻撃が武器攻撃で武器を持っていない

		//待機状態に変更
		auto NewState = DBG_NEW CBossDushState;
		m_pBoss->ChangeState(NewState);
		return;
	}
	else if (m_pBoss->GetAttackable()
		&& !m_pBoss->JudgeAttackRange())
	{//攻撃可能かつ攻撃範囲にいる

		//攻撃状態に変更
		auto NewState = DBG_NEW CBossAttackState;
		m_pBoss->ChangeState(NewState);
		return;
	}
	else if (m_pBoss->JudgeStop()
		&& !m_pBoss->GetAttackable())
	{//停止する範囲にいるかつ攻撃できない

		//停止するときの行動を設定
		m_pBoss->PlayerNearAction();

		if (m_pBoss->GetGuard())
		{//ガードする

			if (m_pBoss->GetWeapon())
			{//武器所持

				//武器所持ガード状態に変更
				auto NewState = DBG_NEW CBossSmallWeaponGuardState;
				m_pBoss->ChangeState(NewState);
				return;
			}
			else
			{//武器未所持

				//ガード状態に変更
				auto NewState = DBG_NEW CBossGuardState;
				m_pBoss->ChangeState(NewState);
				return;
			}
			
		}
		else
		{
			//待機状態に変更
			auto NewState = DBG_NEW CBossNeutralState;
			m_pBoss->ChangeState(NewState);
			return;
		}

	}
}

//==========================
//終了
//==========================
void CBossMoveState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//武器持ち移動状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossWeaponMoveState::CBossWeaponMoveState()
{

}

//==========================
//デストラクタ
//==========================
CBossWeaponMoveState::~CBossWeaponMoveState()
{

}

//==========================
//開始
//==========================
void CBossWeaponMoveState::Start()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::WEAPONMOVE);
}

//==========================
//更新
//==========================
void CBossWeaponMoveState::Update()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::WEAPONMOVE);

	//移動処理
	m_pBoss->Walk();
	m_pBoss->Move();

	if (m_pBoss->JudgeStop()
		&& !m_pBoss->GetAttackable())
	{//停止する範囲にいるかつ攻撃できない


		//待機状態に変更
		auto NewState = DBG_NEW CBossBigWeaponNeutralState;
		m_pBoss->ChangeState(NewState);
		return;


	}
	else if (m_pBoss->GetAttackable() && !m_pBoss->JudgeAttackRange())
	{//攻撃可能かつ攻撃範囲にいる

		//攻撃状態に変更
		auto NewState = DBG_NEW CBossAttackState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CBossWeaponMoveState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//ガード状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossGuardState::CBossGuardState()
{

}

//==========================
//デストラクタ
//==========================
CBossGuardState::~CBossGuardState()
{

}

//==========================
//開始
//==========================
void CBossGuardState::Start()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::GUARD);
}

//==========================
//更新
//==========================
void CBossGuardState::Update()
{

	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::GUARD);

	if (m_pBoss->GetDamageNum() >= 3)
	{//連続で3回被弾した
		m_pBoss->ResetDamageNum();//被弾回数を初期化
	}

	if (!m_pBoss->JudgeGuard())
	{//ガードする範囲にいない

		//ガードの情報をリセット
		m_pBoss->GuardReset();

		//待機状態に変更
		auto NewState = DBG_NEW CBossNeutralState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CBossGuardState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//片手武器持ちガード状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossSmallWeaponGuardState::CBossSmallWeaponGuardState()
{

}

//==========================
//デストラクタ
//==========================
CBossSmallWeaponGuardState::~CBossSmallWeaponGuardState()
{

}

//==========================
//開始
//==========================
void CBossSmallWeaponGuardState::Start()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONGUARD);
}

//==========================
//更新
//==========================
void CBossSmallWeaponGuardState::Update()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONGUARD);

	if (!m_pBoss->JudgeGuard())
	{//ガードする範囲にいない

		//ガードの情報をリセット
		m_pBoss->GuardReset();

		//片手武器持ち待機状態に変更
		auto NewState = DBG_NEW CBossSmallWeaponNeutralState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CBossSmallWeaponGuardState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//ダメージ状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossDamageState::CBossDamageState() :
	m_DmageCount(0)//ダメージを受けてからのフレーム数
{

}

//==========================
//デストラクタ
//==========================
CBossDamageState::~CBossDamageState()
{

}

//==========================
//開始
//==========================
void CBossDamageState::Start()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::DAMAGE);
}

//==========================
//更新
//==========================
void CBossDamageState::Update()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::DAMAGE);

	//ダメージを受けてからのフレーム数を数える
	m_DmageCount++;

	if (m_DmageCount >= DAMEGE_FLAME)
	{
		m_DmageCount = 0;
		m_pBoss->ResetDamageNum();//被弾回数を初期化
		m_pBoss->SetDamage(false);

		//移動状態に変更
		auto NewState = DBG_NEW CBossNeutralState;
		m_pBoss->ChangeState(NewState);

		return;
	}

	if (m_pBoss->GetDamageNum() >= 3)
	{//連続で3回被弾した

		m_pBoss->SetDamage(false);

		//吹き飛び状態に変更
		auto NewState = DBG_NEW CBossDamageBrrowState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if (m_pBoss->GetDamage())
	{//ダメージを受けた

		m_pBoss->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CBossDamageState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//ダッシュ状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossDushState::CBossDushState()
{

}

//==========================
//デストラクタ
//==========================
CBossDushState::~CBossDushState()
{

}

//==========================
//開始
//==========================
void CBossDushState::Start()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::DUSH);
}

//==========================
//更新
//==========================
void CBossDushState::Update()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::DUSH);

	if (m_pBoss->GetDamage())
	{//ダメージを受けた

		m_pBoss->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	if(m_pBoss->GetAttackable() && m_pBoss->GetNextAttack() && !m_pBoss->GetWeapon())
	{//攻撃可能で次の攻撃が武器攻撃で武器を持っていない

		//武器の方向に移動
		m_pBoss->WeaponMove();

		if (m_pBoss->GetWeapon())
		{//武器を持っている
			
			if (!m_pBoss->GetWeaponType())
			{//片手武器

				//片手武器持ち待機状態に変更
				auto NewState = DBG_NEW CBossSmallWeaponNeutralState;
					m_pBoss->ChangeState(NewState);
					return;
			}
			else if (m_pBoss->GetWeaponType())
			{//両手武器

				//両手武器持ち待機状態に変更
				auto NewState = DBG_NEW CBossBigWeaponNeutralState;
				m_pBoss->ChangeState(NewState);
				return;
			}
		}
	}
	else
	{
		if (m_pBoss->JudgeWalk())
		{//歩いて近づく状態

			//待機状態に変更
			auto NewState = DBG_NEW CBossMoveState;
			m_pBoss->ChangeState(NewState);
			return;
		}
		else if (m_pBoss->JudgeStop())
		{//停止する範囲にいるかつ攻撃できない

			//待機状態に変更
			auto NewState = DBG_NEW CBossNeutralState;
			m_pBoss->ChangeState(NewState);
			return;
		}

		//プレイヤーに移動
		m_pBoss->Dush();
	}

	//値を変更
	m_pBoss->Move();
	
}

//==========================
//終了
//==========================
void CBossDushState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//吹き飛び状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossDamageBrrowState::CBossDamageBrrowState() :
	m_DmageCount(0)//ダメージを受けてからのフレーム数
{

}

//==========================
//デストラクタ
//==========================
CBossDamageBrrowState::~CBossDamageBrrowState()
{

}

//==========================
//開始
//==========================
void CBossDamageBrrowState::Start()
{
	//モーションを設定
	m_pBoss->SetMotion(CMotionModel::MOTION_TYPE::DAMAGEBLOW);
}

//==========================
//更新
//==========================
void CBossDamageBrrowState::Update()
{
	//移動処理
	m_pBoss->Move();

	m_DmageCount++;

	if (m_pBoss->GetLife() <= 0)
	{//ライフが0

		if (m_DmageCount >= 30)
		{
			m_pBoss->ChangePlayMotion(false);//モーションを停止
			//m_pBoss->SubPartsCol();//色を薄くする
		}
	}
	else if (m_DmageCount >= BRROW_FLAME)
	{
		m_DmageCount = 0;
		m_pBoss->ResetDamageNum();//被弾回数を初期化
		m_pBoss->SetDamage(false);

		//待機状態に変更
		auto NewState = DBG_NEW CBossNeutralState;
		m_pBoss->ChangeState(NewState);

		return;
	}
}

//==========================
//終了
//==========================
void CBossDamageBrrowState::Uninit()
{
	CBossStateBase::Uninit();
}

//========================================================================================================
//攻撃状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBossAttackState::CBossAttackState() :
	m_FlameCount(0),//攻撃のフレーム数
	m_Combo(true),//コンボ判定
	m_AttackStateMachine(nullptr)//攻撃の状態管理
{

}

//==========================
//デストラクタ
//==========================
CBossAttackState::~CBossAttackState()
{

}

//==========================
//開始
//==========================
void CBossAttackState::Start()
{
	m_AttackStateMachine = DBG_NEW CBossAttackStateMachine;

	if (!m_pBoss->GetNextAttack())
	{//素手攻撃

		auto NewState = DBG_NEW CBossFirstAttackState;
		ChangeAttack(NewState);
	}
	else
	{//武器攻撃

		if (m_pBoss->GetWeaponType())
		{//両手武器

			auto NewState = DBG_NEW CBossFirstBigWeaponAttack;
			ChangeAttack(NewState);
		}
		else
		{//片手武器

			auto NewState = DBG_NEW CBossFirstSmallWeaponAttack;
			ChangeAttack(NewState);
		}
	}
}

//==========================
//更新
//==========================
void CBossAttackState::Update()
{
	if (m_pBoss->GetDamage())
	{//ダメージを受けた

		//攻撃出来ない状態に変更
		m_pBoss->ChangeAttackable();

		//攻撃のクールタイムを設定
		m_pBoss->SetCoolTime(300);

		m_pBoss->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CBossDamageState;
		m_pBoss->ChangeState(NewState);
		return;
	}

	m_FlameCount++;

	if (m_AttackStateMachine != nullptr)
	{
		m_AttackStateMachine->Update();
	}

	if (m_pBoss->GetWeaponBreak())
	{
		//待機状態に変更
		auto NewState = DBG_NEW CBossNeutralState;
		m_pBoss->ChangeState(NewState);
	}

	if (m_Combo)
	{//攻撃中は終了
		return;
	}

	//攻撃出来ない状態に変更
	m_pBoss->ChangeAttackable();

	//待機状態に変更
	auto NewState = DBG_NEW CBossNeutralState;
	m_pBoss->ChangeState(NewState);
	return;
}

//==========================
//終了
//==========================
void CBossAttackState::Uninit()
{
	if (m_AttackStateMachine != nullptr)
	{
		delete m_AttackStateMachine;
		m_AttackStateMachine = nullptr;
	}

	CBossStateBase::Uninit();
}

//==========================
//コンボ判定を取得
//========================== 
void CBossAttackState::ChangeCombo()
{
	m_Combo = !m_Combo;
}

//==========================
//情報を初期化
//==========================
void CBossAttackState::ResetInfo()
{
	m_FlameCount = 0;
}

//==========================
//攻撃を変更
//==========================
void CBossAttackState::ChangeAttack(CAttackBossStateBase* State)
{
	State->SetOwner(this);
	m_AttackStateMachine->ChangeState(State);
}

//==========================
//攻撃フレーム数を取得
//==========================
int CBossAttackState::GetFrame()
{
	return m_FlameCount;
}

//==========================
//コンボ判定を取得
//==========================
bool CBossAttackState::GetCombo()
{
	return m_Combo;
}