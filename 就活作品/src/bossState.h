//==========================
// 
// ボスの状態管理[bossState.h]
// Author Yuki Goto
//
//==========================
#ifndef _BOSSSTATE_H_
#define _BOSSSTATE_H_

//include
#include"characterstate.h"

//前方宣言
class CBoss;
class CBossAttackStateMachine;
class CAttackBossStateBase;
//==============================================================================
//敵の状態クラス
//==============================================================================
class CBossStateBase :public CStateBase
{
public:
	//メンバ関数
	CBossStateBase();//コンストラクタ
	~CBossStateBase();//デストラクタ
	void SetOwner(CBoss* boss);//ステートの所持者を設定
	CBoss* GetOwner();//ステートの所有者を取得
protected:

	//メンバ変数
	CBoss* m_pBoss;//敵の情報
};

//==============================================================================
//演出状態クラス
//==============================================================================
class CBossDirectionState :public CBossStateBase
{
public:
	//メンバ関数
	CBossDirectionState();//コンストラクタ
	~CBossDirectionState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
	int m_count;
};

//==============================================================================
//待機状態クラス
//==============================================================================
class CBossNeutralState :public CBossStateBase
{
public:
	//メンバ関数
	CBossNeutralState();//コンストラクタ
	~CBossNeutralState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//両手武器持ち待機状態クラス
//==============================================================================
class CBossBigWeaponNeutralState :public CBossStateBase
{
public:
	//メンバ関数
	CBossBigWeaponNeutralState();//コンストラクタ
	~CBossBigWeaponNeutralState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//片手武器持ち待機状態クラス
//==============================================================================
class CBossSmallWeaponNeutralState :public CBossStateBase
{
public:
	//メンバ関数
	CBossSmallWeaponNeutralState();//コンストラクタ
	~CBossSmallWeaponNeutralState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//両手武器持ち移動状態クラス
//==============================================================================
class CBossWeaponMoveState :public CBossStateBase
{
public:
	//メンバ関数
	CBossWeaponMoveState();//コンストラクタ
	~CBossWeaponMoveState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//移動状態クラス
//==============================================================================
class CBossMoveState :public CBossStateBase
{
public:
	//メンバ関数
	CBossMoveState();//コンストラクタ
	~CBossMoveState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//ガード状態クラス
//==============================================================================
class CBossGuardState :public CBossStateBase
{
public:
	//メンバ関数
	CBossGuardState();//コンストラクタ
	~CBossGuardState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//片手武器持ちガード状態クラス
//==============================================================================
class CBossSmallWeaponGuardState :public CBossStateBase
{
public:
	//メンバ関数
	CBossSmallWeaponGuardState();//コンストラクタ
	~CBossSmallWeaponGuardState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//ダメージ状態クラス
//==============================================================================
class CBossDamageState :public CBossStateBase
{
public:
	//定数
	static const int DAMEGE_FLAME;//ダメージ状態を終了するまでのフレーム数

	//メンバ関数
	CBossDamageState();//コンストラクタ
	~CBossDamageState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了

private:

	//メンバ変数
	int m_DmageCount;//ダメージを受けてからのフレーム数
};

//==============================================================================
//ダッシュ状態クラス
//==============================================================================
class CBossDushState :public CBossStateBase
{
public:
	//メンバ関数
	CBossDushState();//コンストラクタ
	~CBossDushState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//吹き飛び状態クラス
//==============================================================================
class CBossDamageBrrowState :public CBossStateBase
{
public:
	//定数
	static const int BRROW_FLAME;//ダメージ状態を終了するまでのフレーム数

	//メンバ関数
	CBossDamageBrrowState();//コンストラクタ
	~CBossDamageBrrowState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了

private:

	//メンバ変数
	int m_DmageCount;//ダメージを受けてからのフレーム数
};

//==============================================================================
//攻撃状態クラス
//==============================================================================
class CBossAttackState :public CBossStateBase
{
public:

	//メンバ関数
	CBossAttackState();//コンストラクタ
	~CBossAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
	void ChangeCombo();//コンボ判定を取得
	void ResetInfo();//情報を初期化
	void ChangeAttack(CAttackBossStateBase* State);//攻撃を変更
	int GetFrame();//攻撃フレーム数を取得
	bool GetCombo();//コンボ判定を取得
private:

	//メンバ変数
	int m_FlameCount;//攻撃のフレーム数
	bool m_Combo;//コンボ判定
	CBossAttackStateMachine* m_AttackStateMachine;//攻撃の状態管理
};

#endif