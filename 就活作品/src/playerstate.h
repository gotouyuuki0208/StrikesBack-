//==========================
// 
// プレイヤーの状態管理[playerstate.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYERSTATE_H_
#define _PLAYERSTATE_H_

//include
#include"characterstate.h"

//前方宣言
class CPlayer;
class CAttackStateMachine;
class CAttackPlayerStateBase;

//==============================================================================
//プレイヤーの状態クラス
//==============================================================================
class CPlayerStateBase :public CStateBase
{
public:
	//メンバ関数
	CPlayerStateBase();//コンストラクタ
	~CPlayerStateBase();//デストラクタ
	void SetOwner(CPlayer* player);//ステートの所持者を設定
	CPlayer* GetOwner();//ステートの所有者を取得
protected:

	//メンバ変数
	CPlayer* m_pPlayer;//プレイヤーの情報
};

//==============================================================================
//待機状態クラス
//==============================================================================
class CNeutralState :public CPlayerStateBase
{
public:
	//メンバ関数
	CNeutralState();//コンストラクタ
	~CNeutralState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//両手武器持ち待機状態クラス
//==============================================================================
class CBigWeaponNeutralState :public CPlayerStateBase
{
public:
	//メンバ関数
	CBigWeaponNeutralState();//コンストラクタ
	~CBigWeaponNeutralState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//片手武器持ち待機状態クラス
//==============================================================================
class CSmallWeaponNeutralState :public CPlayerStateBase
{
public:
	//メンバ関数
	CSmallWeaponNeutralState();//コンストラクタ
	~CSmallWeaponNeutralState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//両手武器持ち移動状態クラス
//==============================================================================
class CBigWeaponMoveState :public CPlayerStateBase
{
public:
	//メンバ関数
	CBigWeaponMoveState();//コンストラクタ
	~CBigWeaponMoveState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//移動状態クラス
//==============================================================================
class CMoveState :public CPlayerStateBase
{
public:
	//メンバ関数
	CMoveState();//コンストラクタ
	~CMoveState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//ダッシュ状態クラス
//==============================================================================
class CDushState :public CPlayerStateBase
{
public:
	//メンバ関数
	CDushState();//コンストラクタ
	~CDushState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//ガード状態クラス
//==============================================================================
class CGuardState :public CPlayerStateBase
{
public:
	//メンバ関数
	CGuardState();//コンストラクタ
	~CGuardState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//片手武器持ちガード状態クラス
//==============================================================================
class CSmallWeaponGuardState :public CPlayerStateBase
{
public:
	//メンバ関数
	CSmallWeaponGuardState();//コンストラクタ
	~CSmallWeaponGuardState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//攻撃状態クラス
//==============================================================================
class CAttackState :public CPlayerStateBase
{
public:

	//定数
	static const int INPUT_START_FLAME;//入力受付開始フレーム数
	static const int INPUT_FINISH_FLAME;//入力受付終了フレーム数
	static const int RESET_FLAME;//コンボの情報リセットフレーム数
	
	//メンバ関数
	CAttackState();//コンストラクタ
	~CAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
	bool GetCombo();//コンボ判定を取得
	void ResetInfo();//情報を初期化
	void ChangeAttack(CAttackPlayerStateBase* State);//攻撃を変更
	int GetFrame();//攻撃フレーム数を取得
private:

	//メンバ変数
	int m_FlameCount;//攻撃のフレーム数
	bool m_Combo;//コンボ判定
	CAttackStateMachine* m_AttackStateMachine;//攻撃の状態管理
};

//==============================================================================
//ダメージ状態クラス
//==============================================================================
class CDamageState :public CPlayerStateBase
{
public:
	//定数
	static const int DAMEGE_FLAME;//ダメージ状態を終了するまでのフレーム数

	//メンバ関数
	CDamageState();//コンストラクタ
	~CDamageState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了

private:

	//メンバ変数
	int m_DmageCount;//ダメージを受けてからのフレーム数
};

//==============================================================================
//吹き飛び状態クラス
//==============================================================================
class CDamageBrrowState :public CPlayerStateBase
{
public:
	//定数
	static const int BRROW_FLAME;//ダメージ状態を終了するまでのフレーム数

	//メンバ関数
	CDamageBrrowState();//コンストラクタ
	~CDamageBrrowState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了

private:

	//メンバ変数
	int m_DmageCount;//ダメージを受けてからのフレーム数
};

//==============================================================================
//武器投げ状態クラス
//==============================================================================
class CWeaponThrowState :public CPlayerStateBase
{
public:
	
	//メンバ関数
	CWeaponThrowState();//コンストラクタ
	~CWeaponThrowState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//回避状態クラス
//==============================================================================
class CAvoidanceState :public CPlayerStateBase
{
public:
	//定数
	static const int AVOIDANCE_FLAME;//回避フレーム数

	//メンバ関数
	CAvoidanceState();//コンストラクタ
	~CAvoidanceState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了

private:

	//メンバ変数
	int m_AvoidanceCount;//回避してからのフレーム数
};
#endif