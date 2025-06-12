//==========================
// 
// 攻撃の状態管理[attackstate.h]
// Author Yuki Goto
//
//==========================
#ifndef ATTACKSTATE_H_
#define ATTACKSTATE_H_

//前方宣言
class CAttackState;
class CTrajectory;
//==============================================================================
//基底クラス
//==============================================================================
class CAttackStateBase
{
public:
	//定数
	static const int LEFT_HAND;//左手の番号
	static const int RIGHT_HAND;//右手の番号
	static const int WIDTH;//軌跡の横の分割数
	static const int VERTICAL;//軌跡の縦の分割数
	static const D3DXVECTOR3 TRAJECTORY_SIZE;//軌跡の大きさ
	static const int HITFLAME;//素手攻撃の当たり判定のフレーム数

	//メンバ関数
	CAttackStateBase();//コンストラクタ
	~CAttackStateBase();//デストラクタ
	virtual void Start();//開始
	virtual void Update();//更新
	virtual void Uninit();//終了
	void CreateTrajectory(D3DXVECTOR3 pos);//軌跡の生成
	void TrajectoryPos(D3DXVECTOR3 pos);//軌跡の位置を設定
private:

	//メンバ変数
	CTrajectory* m_Trajectory;//軌跡の情報
};

//==============================================================================
//攻撃の状態クラス
//==============================================================================
class CAttackPlayerStateBase :public CAttackStateBase
{
public:

	//メンバ関数
	CAttackPlayerStateBase();//コンストラクタ
	~CAttackPlayerStateBase();//デストラクタ
	void SetOwner(CAttackState* State);//ステートの所持者を設定

protected:

	//メンバ変数
	CAttackState* m_OwnerState;//ステートの所有者
};

//==============================================================================
//状態管理クラス
//==============================================================================
class CAttackStateMachine
{
public:

	//メンバ関数
	CAttackStateMachine();//コンストラクタ
	~CAttackStateMachine();//デストラクタ
	void ChangeState(CAttackPlayerStateBase* NewState);//状態の変更
	void Update();//更新

private:

	//メンバ変数
	CAttackPlayerStateBase* m_State;//プレイヤーの状態

};

//==============================================================================
//素手攻撃クラス
//==============================================================================

//1回目の攻撃
class CFirstAttackState :public CAttackPlayerStateBase
{
public:
	//メンバ関数
	CFirstAttackState();//コンストラクタ
	~CFirstAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//2回目の攻撃
class CSecondAttackState :public CAttackPlayerStateBase
{
public:
	//メンバ関数
	CSecondAttackState();//コンストラクタ
	~CSecondAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//3回目の攻撃
class CRastAttackState :public CAttackPlayerStateBase
{
public:
	//メンバ関数
	CRastAttackState();//コンストラクタ
	~CRastAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//両手武器攻撃クラス
//==============================================================================

//1回目の攻撃
class CFirstBigWeaponAttack :public CAttackPlayerStateBase
{
public:
	//メンバ関数
	CFirstBigWeaponAttack();//コンストラクタ
	~CFirstBigWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//2回目の攻撃
class CSecondBigWeaponAttack :public CAttackPlayerStateBase
{
public:
	//メンバ関数
	CSecondBigWeaponAttack();//コンストラクタ
	~CSecondBigWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//3回目の攻撃
class CRastBigWeaponAttack :public CAttackPlayerStateBase
{
public:
	//メンバ関数
	CRastBigWeaponAttack();//コンストラクタ
	~CRastBigWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//片手武器攻撃クラス
//==============================================================================

//1回目の攻撃
class CFirstSmallWeaponAttack :public CAttackPlayerStateBase
{
public:
	//メンバ関数
	CFirstSmallWeaponAttack();//コンストラクタ
	~CFirstSmallWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//2回目の攻撃
class CSecondSmallWeaponAttack :public CAttackPlayerStateBase
{
public:
	//メンバ関数
	CSecondSmallWeaponAttack();//コンストラクタ
	~CSecondSmallWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//3回目の攻撃
class CRastSmallWeaponAttack :public CAttackPlayerStateBase
{
public:
	//メンバ関数
	CRastSmallWeaponAttack();//コンストラクタ
	~CRastSmallWeaponAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

#endif