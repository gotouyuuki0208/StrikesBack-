//==========================
// 
// プレイヤーの状態管理[playerstate.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "playerstate.h"
#include "manager.h"
#include "player.h"
#include "attackstate.h"

//静的メンバ初期化
const int CDamageState::DAMEGE_FLAME = 54;//ダメージ状態を終了するまでのフレーム数
const int CAttackState::INPUT_START_FLAME = 24;//入力受付開始フレーム数
const int CAttackState::INPUT_FINISH_FLAME = 60;//入力受付終了フレーム数
const int CAttackState::RESET_FLAME = 54;//コンボの情報リセットフレーム数
const int CAvoidanceState::AVOIDANCE_FLAME = 6;//回避フレーム数
const int CDamageBrrowState::BRROW_FLAME = 50;//ダメージ状態を終了するまでのフレーム数

//========================================================================================================
//プレイヤーの状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CPlayerStateBase::CPlayerStateBase():
	m_pPlayer(nullptr)//プレイヤーの情報
{

}

//==========================
//デストラクタ
//==========================
CPlayerStateBase::~CPlayerStateBase()
{

}

//==========================
//ステートの所持者を設定
//==========================
void CPlayerStateBase::SetOwner(CPlayer* player)
{
	m_pPlayer = player;
}

//==========================
//ステートの所有者を取得
//==========================
CPlayer* CPlayerStateBase::GetOwner()
{
	return m_pPlayer;
}

//========================================================================================================
//待機状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CNeutralState::CNeutralState()
{

}

//==========================
//デストラクタ
//==========================
CNeutralState::~CNeutralState()
{

}

//==========================
//開始
//==========================
void CNeutralState::Start()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);
}

//==========================
//更新
//==========================
void CNeutralState::Update()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::NEUTRAL);

	//パッドの情報を取得
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamage())
	{//ダメージを受けた

		m_pPlayer->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetLeftStick())
	{//左スティックを入力されている

		//移動状態に変更
		auto NewState = DBG_NEW CMoveState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetLeftStick()
		&& pJoypad->GetTriggerPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
	{//左スティックを入力されているかつLTが押されている

		//ダッシュ状態に変更
		auto NewState = DBG_NEW CDushState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_X))
	{//Xボタンがおされた

		//ガード状態に変更
		auto NewState = DBG_NEW CGuardState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_Y))
	{//Yボタンを入力

		//攻撃状態に変更
		auto NewState = DBG_NEW CAttackState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_A))
	{//左スティックを入力されている

		//移動状態に変更
		auto NewState = DBG_NEW CAvoidanceState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//左スティックを入力されている

		//武器を持つ
		m_pPlayer->PickUpWeapon();

		if (!m_pPlayer->GetHaveWeapon())
		{//武器を持っていない
			return;
		}

		if(!m_pPlayer->GetWeaponType())
		{//大きい武器を持ってるとき

			//待機状態に変更
			auto NewState = DBG_NEW CBigWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
		}
		else
		{//小さい武器を持ってるとき

			//待機状態に変更
			auto NewState = DBG_NEW CSmallWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
		}
		return;
	}
}

//==========================
//終了
//==========================
void CNeutralState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//両手武器所持待機状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBigWeaponNeutralState::CBigWeaponNeutralState()
{

}

//==========================
//デストラクタ
//==========================
CBigWeaponNeutralState::~CBigWeaponNeutralState()
{

}

//==========================
//開始
//==========================
void CBigWeaponNeutralState::Start()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::WEAPONNEUTRAL);
}

//==========================
//更新
//==========================
void CBigWeaponNeutralState::Update()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::WEAPONNEUTRAL);

	//パッドの情報を取得
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamage())
	{//ダメージを受けた

		m_pPlayer->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetLeftStick())
	{//左スティックを入力されている

		//移動状態に変更
		auto NewState = DBG_NEW CBigWeaponMoveState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//左スティックを入力されている

		//武器を捨てる
		m_pPlayer->ReleaseWeapon();

		//待機状態に変更
		auto NewState = DBG_NEW CNeutralState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_Y))
	{//左スティックを入力されている

		//攻撃状態に変更
		auto NewState = DBG_NEW CAttackState;
		m_pPlayer->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CBigWeaponNeutralState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//片手武器所持待機状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CSmallWeaponNeutralState::CSmallWeaponNeutralState()
{

}

//==========================
//デストラクタ
//==========================
CSmallWeaponNeutralState::~CSmallWeaponNeutralState()
{

}

//==========================
//開始
//==========================
void CSmallWeaponNeutralState::Start()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL);
}

//==========================
//更新
//==========================
void CSmallWeaponNeutralState::Update()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONNEUTRAL);

	//パッドの情報を取得
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamage())
	{//ダメージを受けた

		m_pPlayer->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetLeftStick())
	{//左スティックを入力されている

		//移動状態に変更
		auto NewState = DBG_NEW CMoveState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_X))
	{//Xボタンがおされた

		//ガード状態に変更
		auto NewState = DBG_NEW CSmallWeaponGuardState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//左スティックを入力されている

		//武器を捨てる
		m_pPlayer->ReleaseWeapon();

		//待機状態に変更
		auto NewState = DBG_NEW CNeutralState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_Y))
	{//左スティックを入力されている

		//待機状態に変更
		auto NewState = DBG_NEW CAttackState;
		m_pPlayer->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CSmallWeaponNeutralState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//移動状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CMoveState::CMoveState()
{

}

//==========================
//デストラクタ
//==========================
CMoveState::~CMoveState()
{

}

//==========================
//開始
//==========================
void CMoveState::Start()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::MOVE);
}

//==========================
//更新
//==========================
void CMoveState::Update()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::MOVE);

	//パッドの情報を取得
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamage())
	{//ダメージを受けた

		m_pPlayer->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (!pJoypad->Connection())
	{//パッドが接続されていない
		return;
	}

	if (!pJoypad->GetLeftStick())
	{//左スティックを入力されていない

		if (m_pPlayer->GetHaveWeapon())
		{
			//待機状態に変更
			auto NewState = DBG_NEW CSmallWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
		else
		{
			//待機状態に変更
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
		
	}

	if (pJoypad->GetLeftStick()
		&& pJoypad->GetTriggerPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
	{//左スティックを入力されているかつLTが押されている

		//ダッシュ状態に変更
		auto NewState = DBG_NEW CDushState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//左スティックを入力されている

		//武器を捨てる
		auto NewState = DBG_NEW CWeaponThrowState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	//移動処理
	m_pPlayer->InputMove();
	m_pPlayer->Move();
}

//==========================
//終了
//==========================
void CMoveState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//武器持ち移動状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CBigWeaponMoveState::CBigWeaponMoveState()
{

}

//==========================
//デストラクタ
//==========================
CBigWeaponMoveState::~CBigWeaponMoveState()
{

}

//==========================
//開始
//==========================
void CBigWeaponMoveState::Start()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::MOVE);
}

//==========================
//更新
//==========================
void CBigWeaponMoveState::Update()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::WEAPONMOVE);

	//パッドの情報を取得
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	//移動処理
	m_pPlayer->InputMove();
	m_pPlayer->Move();

	if (m_pPlayer->GetDamage())
	{//ダメージを受けた

		m_pPlayer->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->Connection())
	{//パッドが接続されているとき

		if (!pJoypad->GetLeftStick())
		{//左スティックを入力されている

			//待機状態に変更
			auto NewState = DBG_NEW CBigWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//左スティックを入力されている

		//武器を捨てる
		auto NewState = DBG_NEW CWeaponThrowState;
		m_pPlayer->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CBigWeaponMoveState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//ダッシュ状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CDushState::CDushState()
{

}

//==========================
//デストラクタ
//==========================
CDushState::~CDushState()
{

}

//==========================
//開始
//==========================
void CDushState::Start()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::DUSH);
}

//==========================
//更新
//==========================
void CDushState::Update()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::DUSH);

	//パッドの情報を取得
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamage())
	{//ダメージを受けた

		m_pPlayer->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->Connection())
	{//パッドが接続されているとき

		if (pJoypad->GetLeftStick()
			&& !pJoypad->GetTriggerPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
		{//左スティックを入力されている

			//移動状態に変更
			auto NewState = DBG_NEW CMoveState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}

	if (pJoypad->Connection())
	{//パッドが接続されているとき

		if (!pJoypad->GetLeftStick())
		{//左スティックを入力されている

			//待機状態に変更
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
	{//左スティックを入力されている

		//武器を捨てる
		m_pPlayer->ThrowWeapon();
	}

	//移動処理
	m_pPlayer->InputMove();
	m_pPlayer->Move();
}

//==========================
//終了
//==========================
void CDushState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//ガード状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CGuardState::CGuardState()
{

}

//==========================
//デストラクタ
//==========================
CGuardState::~CGuardState()
{

}

//==========================
//開始
//==========================
void CGuardState::Start()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::GUARD);
}

//==========================
//更新
//==========================
void CGuardState::Update()
{

	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::GUARD);

	//パッドの情報を取得
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (m_pPlayer->GetDamageNum() >= 3)
	{//連続で3回被弾した
		m_pPlayer->ResetDamageNum();//被弾回数を初期化
	}

	if (pJoypad->Connection())
	{//パッドが接続されているとき

		if (pJoypad->GetRelease(CInputJoypad::JOYKEY_X))
		{//Xボタンが放された

			//移動状態に変更
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}
}

//==========================
//終了
//==========================
void CGuardState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//片手武器持ちガード状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CSmallWeaponGuardState::CSmallWeaponGuardState()
{

}

//==========================
//デストラクタ
//==========================
CSmallWeaponGuardState::~CSmallWeaponGuardState()
{

}

//==========================
//開始
//==========================
void CSmallWeaponGuardState::Start()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONGUARD);
}

//==========================
//更新
//==========================
void CSmallWeaponGuardState::Update()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::SMALLWEAPONGUARD);

	if (m_pPlayer->GetDamageNum() >= 3)
	{//連続で3回被弾した
		m_pPlayer->ResetDamageNum();//被弾回数を初期化
	}

	//パッドの情報を取得
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	if (pJoypad->Connection())
	{//パッドが接続されているとき

		if (pJoypad->GetRelease(CInputJoypad::JOYKEY_X))
		{//Xボタンが放された

			//移動状態に変更
			auto NewState = DBG_NEW CSmallWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}
}

//==========================
//終了
//==========================
void CSmallWeaponGuardState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//攻撃状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CAttackState::CAttackState():
	m_FlameCount(0),//フレーム数
	m_AttackStateMachine(nullptr),//攻撃の状態管理
	m_Combo(false)//コンボ判定
{

}

//==========================
//デストラクタ
//==========================
CAttackState::~CAttackState()
{

}

//==========================
//開始
//==========================
void CAttackState::Start()
{
	m_AttackStateMachine = DBG_NEW CAttackStateMachine;

	if (!m_pPlayer->GetHaveWeapon())
	{//プレイヤーが武器を所持していない

		auto NewState = DBG_NEW CFirstAttackState;
		ChangeAttack(NewState);
	}
	else if (!m_pPlayer->GetWeaponType())
	{//両手武器所持

		auto NewState = DBG_NEW CFirstBigWeaponAttack;
		ChangeAttack(NewState);
	}
	else if (m_pPlayer->GetWeaponType())
	{//片手武器
		auto NewState = DBG_NEW CFirstSmallWeaponAttack;
		ChangeAttack(NewState);
	}
}

//==========================
//更新
//==========================
void CAttackState::Update()
{
	//パッドの情報を取得
	CInputJoypad* pJoypad = CManager::GetInstance()->GetJoypad();

	m_FlameCount++;

	if (m_pPlayer->GetDamage())
	{//ダメージを受けた

		m_pPlayer->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_Y))
	{
		if (m_FlameCount > INPUT_START_FLAME)
		{//入力受付時間中に入力
			m_Combo = true;
			
			//角度を補正
			m_pPlayer->CorrectionAngle();
			return;
		}
	}

	if (m_FlameCount > INPUT_FINISH_FLAME)
	{//入力受付時間を超えた

		if (!m_pPlayer->GetHaveWeapon())
		{//プレイヤーが武器を所持していない
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
		else if (!m_pPlayer->GetWeaponType())
		{//両手武器所持
			auto NewState = DBG_NEW CBigWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
		else if (m_pPlayer->GetWeaponType())
		{//片手武器所持
			auto NewState = DBG_NEW CSmallWeaponNeutralState;
			m_pPlayer->ChangeState(NewState);
			return;
		}
	}

	if (m_AttackStateMachine != nullptr)
	{
		m_AttackStateMachine->Update();
	}

	if (m_pPlayer->GetWeaponBreak())
	{//武器が壊れた

		//武器破壊判定をリセット
		m_pPlayer->BreakReset();

		auto NewState = DBG_NEW CNeutralState;
		m_pPlayer->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CAttackState::Uninit()
{
	if (m_AttackStateMachine != nullptr)
	{
		delete m_AttackStateMachine;
		m_AttackStateMachine = nullptr;
	}

	CPlayerStateBase::Uninit();
}

//==========================
//コンボ判定を取得
//==========================
bool CAttackState::GetCombo()
{
	return m_Combo;
}

//==========================
//情報を初期化
//==========================
void CAttackState::ResetInfo()
{
	m_FlameCount = 0;
	m_Combo = false;
}

//==========================
//攻撃を変更
//==========================
void CAttackState::ChangeAttack(CAttackPlayerStateBase* State)
{
	State->SetOwner(this);
	m_AttackStateMachine->ChangeState(State);
}

//==========================
//攻撃フレーム数を取得
//==========================
int CAttackState::GetFrame()
{
	return m_FlameCount;
}

//========================================================================================================
//ダメージ状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CDamageState::CDamageState():
	m_DmageCount(0)//ダメージを受けてからのフレーム数
{

}

//==========================
//デストラクタ
//==========================
CDamageState::~CDamageState()
{

}

//==========================
//開始
//==========================
void CDamageState::Start()
{
	
}

//==========================
//更新
//==========================
void CDamageState::Update()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::DAMAGE);

	m_DmageCount++;
	if (m_DmageCount >= DAMEGE_FLAME)
	{
		m_DmageCount = 0;
		m_pPlayer->ResetDamageNum();//被弾回数を初期化
		
		//待機状態に変更
		if (m_pPlayer->GetHaveWeapon())
		{//武器を持ってる

			if (m_pPlayer->GetWeaponType())
			{//片手
				auto NewState = DBG_NEW CSmallWeaponNeutralState;
				m_pPlayer->ChangeState(NewState);
			}
			else
			{//両手
				auto NewState = DBG_NEW CBigWeaponNeutralState;
				m_pPlayer->ChangeState(NewState);
			}
		}
		else
		{//武器を持っない
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
		}
		
		return;
	}

	if (m_pPlayer->GetDamageNum() >= 3)
	{//連続で3回被弾した

		m_pPlayer->SetDamage(false);

		//吹き飛び状態に変更
		auto NewState = DBG_NEW CDamageBrrowState;
		m_pPlayer->ChangeState(NewState);
		return;
	}

	if (m_pPlayer->GetDamage())
	{//ダメージを受けた

		m_pPlayer->SetDamage(false);

		//ダメージ状態に変更
		auto NewState = DBG_NEW CDamageState;
		m_pPlayer->ChangeState(NewState);
		return;
	}
}

//==========================
//終了
//==========================
void CDamageState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//回避状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CAvoidanceState::CAvoidanceState():
	m_AvoidanceCount(0)//回避してからのフレーム数
{

}

//==========================
//デストラクタ
//==========================
CAvoidanceState::~CAvoidanceState()
{

}

//==========================
//開始
//==========================
void CAvoidanceState::Start()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::AVOIDANCE_BACK);
}

//==========================
//更新
//==========================
void CAvoidanceState::Update()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::AVOIDANCE_BACK);

	//ダメージを受けていな状態に変更
	m_pPlayer->SetDamage(false);

	//移動処理
	m_pPlayer->Avoidance();

	m_AvoidanceCount++;

	if (m_AvoidanceCount > AVOIDANCE_FLAME)
	{
		m_AvoidanceCount = 0;
		m_pPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		//移動状態に変更
		auto NewState = DBG_NEW CNeutralState;
		m_pPlayer->ChangeState(NewState);

		return;
	}

}

//==========================
//終了
//==========================
void CAvoidanceState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//========================================================================================================
//吹き飛び状態クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CDamageBrrowState::CDamageBrrowState() :
	m_DmageCount(0)//ダメージを受けてからのフレーム数
{

}

//==========================
//デストラクタ
//==========================
CDamageBrrowState::~CDamageBrrowState()
{

}

//==========================
//開始
//==========================
void CDamageBrrowState::Start()
{
	//モーションを設定
	m_pPlayer->SetMotion(CMotionModel::MOTION_TYPE::DAMAGEBLOW);

}

//==========================
//更新
//==========================
void CDamageBrrowState::Update()
{
	//移動処理
	m_pPlayer->Move();

	m_DmageCount++;
	if (m_DmageCount >= BRROW_FLAME)
	{
		m_DmageCount = 0;
		m_pPlayer->ResetDamageNum();//被弾回数を初期化

		//待機状態に変更
		if (m_pPlayer->GetHaveWeapon())
		{//武器を持ってる

			if (m_pPlayer->GetWeaponType())
			{//片手
				auto NewState = DBG_NEW CSmallWeaponNeutralState;
				m_pPlayer->ChangeState(NewState);
			}
			else
			{//両手
				auto NewState = DBG_NEW CBigWeaponNeutralState;
				m_pPlayer->ChangeState(NewState);
			}
		}
		else
		{//武器を持っない
			auto NewState = DBG_NEW CNeutralState;
			m_pPlayer->ChangeState(NewState);
		}

		return;
	}
}

//==========================
//終了
//==========================
void CDamageBrrowState::Uninit()
{
	CPlayerStateBase::Uninit();
}

//==============================================================================
//武器投げ状態クラス
//==============================================================================

//==========================
//コンストラクタ
//==========================
CWeaponThrowState::CWeaponThrowState()
{

}

//==========================
//デストラクタ
//==========================
CWeaponThrowState::~CWeaponThrowState()
{

}

//==========================
//開始
//==========================
void CWeaponThrowState::Start()
{
	m_pPlayer->ThrowWeapon();
}

//==========================
//更新
//==========================
void CWeaponThrowState::Update()
{
	//移動状態に変更
	auto NewState = DBG_NEW CMoveState;
	m_pPlayer->ChangeState(NewState);
	return;
}

//==========================
//終了
//==========================
void CWeaponThrowState::Uninit()
{
	CPlayerStateBase::Uninit();
}