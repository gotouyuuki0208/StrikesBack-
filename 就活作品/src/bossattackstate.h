//==========================
// 
// ボス攻撃の状態管理[bossattackstate.h]
// Author Yuki Goto
//
//==========================
#ifndef BOSSATTACKSTATE_H_
#define BOSSATTACKSTATE_H_

//前方宣言
class CBossAttackState;
//==============================================================================
//基底クラス
//==============================================================================
class CBossAttackStateBase
{
public:
	//定数
	static const int LEFT_HAND;//左手の番号
	static const int RIGHT_HAND;//右手の番号
	static const int HITFLAME;//素手攻撃の当たり判定のフレーム数

	//メンバ関数
	CBossAttackStateBase();//コンストラクタ
	~CBossAttackStateBase();//デストラクタ
	virtual void Start();//開始
	virtual void Update();//更新
	virtual void Uninit();//終了
};

//==============================================================================
//攻撃の状態クラス
//==============================================================================
class CAttackBossStateBase :public CBossAttackStateBase
{
public:

	//メンバ関数
	CAttackBossStateBase();//コンストラクタ
	~CAttackBossStateBase();//デストラクタ
	void SetOwner(CBossAttackState* State);//ステートの所持者を設定

protected:

	//メンバ変数
	CBossAttackState* m_OwnerState;//ステートの所有者
};

//==============================================================================
//状態管理クラス
//==============================================================================
class CBossAttackStateMachine
{
public:

	//メンバ関数
	CBossAttackStateMachine();//コンストラクタ
	~CBossAttackStateMachine();//デストラクタ
	void ChangeState(CAttackBossStateBase* NewState);//状態の変更
	void Update();//更新

private:

	//メンバ変数
	CAttackBossStateBase* m_State;//プレイヤーの状態

};

//==============================================================================
//素手攻撃クラス
//==============================================================================

//1回目の攻撃
class CBossFirstAttackState :public CAttackBossStateBase
{
public:
	//メンバ関数
	CBossFirstAttackState();//コンストラクタ
	~CBossFirstAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//2回目の攻撃
class CBossSecondAttackState :public CAttackBossStateBase
{
public:
	//メンバ関数
	CBossSecondAttackState();//コンストラクタ
	~CBossSecondAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//3回目の攻撃
class CBossRastAttackState :public CAttackBossStateBase
{
public:
	//メンバ関数
	CBossRastAttackState();//コンストラクタ
	~CBossRastAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//両手武器攻撃クラス
//==============================================================================

//1回目の攻撃
class CBossFirstBigWeaponAttack :public CAttackBossStateBase
{
public:
	//メンバ関数
	CBossFirstBigWeaponAttack();//コンストラクタ
	~CBossFirstBigWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//2回目の攻撃
class CBossSecondBigWeaponAttack :public CAttackBossStateBase
{
public:
	//メンバ関数
	CBossSecondBigWeaponAttack();//コンストラクタ
	~CBossSecondBigWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//3回目の攻撃
class CBossRastBigWeaponAttack :public CAttackBossStateBase
{
public:
	//メンバ関数
	CBossRastBigWeaponAttack();//コンストラクタ
	~CBossRastBigWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//片手武器攻撃クラス
//==============================================================================

//1回目の攻撃
class CBossFirstSmallWeaponAttack :public CAttackBossStateBase
{
public:
	//メンバ関数
	CBossFirstSmallWeaponAttack();//コンストラクタ
	~CBossFirstSmallWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//2回目の攻撃
class CBossSecondSmallWeaponAttack :public CAttackBossStateBase
{
public:
	//メンバ関数
	CBossSecondSmallWeaponAttack();//コンストラクタ
	~CBossSecondSmallWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//3回目の攻撃
class CBossRastSmallWeaponAttack :public CAttackBossStateBase
{
public:
	//メンバ関数
	CBossRastSmallWeaponAttack();//コンストラクタ
	~CBossRastSmallWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

#endif