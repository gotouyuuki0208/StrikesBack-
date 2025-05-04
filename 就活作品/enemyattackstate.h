//==========================
// 
// 敵の攻撃の状態管理[enemyattackstate.h]
// Author Yuki Goto
//
//==========================
#ifndef ENEMYATTACKSTATE_H_
#define ENEMYATTACKSTATE_H_

//include
#include "enemystate.h"

//前方宣言
class CEnemyAttackState;
//class CTrajectory;
//==============================================================================
//基底クラス
//==============================================================================
class CEenemyAttackStateBase
{
public:
	//定数
	static const int LEFT_HAND;//左手の番号
	static const int RIGHT_HAND;//右手の番号
	static const int HITFLAME;//素手攻撃の当たり判定のフレーム数
	//static const int WIDTH;//軌跡の横の分割数
	//static const int VERTICAL;//軌跡の縦の分割数
	//static const D3DXVECTOR3 TRAJECTORY_SIZE;//軌跡の大きさ

	//メンバ関数
	CEenemyAttackStateBase();//コンストラクタ
	~CEenemyAttackStateBase();//デストラクタ
	virtual void Start();//開始
	virtual void Update();//更新
	virtual void Uninit();//終了
	//void CreateTrajectory(D3DXVECTOR3 pos);//軌跡の生成
	//void TrajectoryPos(D3DXVECTOR3 pos);//軌跡の位置を設定
private:

	//メンバ変数
	//CTrajectory* m_Trajectory;//軌跡の情報
};

//==============================================================================
//攻撃の状態クラス
//==============================================================================
class CAttackEenemyState :public CEenemyAttackStateBase
{
public:

	//メンバ関数
	CAttackEenemyState();//コンストラクタ
	~CAttackEenemyState();//デストラクタ
	void SetOwner(CEnemyAttackState* State);//ステートの所持者を設定

protected:

	//メンバ変数
	CEnemyAttackState* m_OwnerState;//ステートの所有者
};

//==============================================================================
//状態管理クラス
//==============================================================================
class CEenemyAttackStateMachine
{
public:

	//メンバ関数
	CEenemyAttackStateMachine();//コンストラクタ
	~CEenemyAttackStateMachine();//デストラクタ
	void ChangeState(CEenemyAttackStateBase* NewState);//状態の変更
	void Update();//更新

private:

	//メンバ変数
	CEenemyAttackStateBase* m_State;//プレイヤーの状態

};

//==============================================================================
//素手攻撃クラス
//==============================================================================

//1回目の攻撃
class CFirstEenemyAttackState :public CAttackEenemyState
{
public:
	//メンバ関数
	CFirstEenemyAttackState();//コンストラクタ
	~CFirstEenemyAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//2回目の攻撃
class CSecondEenemyAttackState :public CAttackEenemyState
{
public:
	//メンバ関数
	CSecondEenemyAttackState();//コンストラクタ
	~CSecondEenemyAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//3回目の攻撃
class CRastEenemyAttackState :public CAttackEenemyState
{
public:
	//メンバ関数
	CRastEenemyAttackState();//コンストラクタ
	~CRastEenemyAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//片手武器攻撃クラス
//==============================================================================

//1回目の攻撃
class CFirstSmallWeaponEenemyAttack :public CAttackEenemyState
{
public:
	//メンバ関数
	CFirstSmallWeaponEenemyAttack();//コンストラクタ
	~CFirstSmallWeaponEenemyAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//2回目の攻撃
class CSecondSmallWeaponEenemyAttack :public CAttackEenemyState
{
public:
	//メンバ関数
	CSecondSmallWeaponEenemyAttack();//コンストラクタ
	~CSecondSmallWeaponEenemyAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//3回目の攻撃
class CRastSmallWeaponEenemyAttack :public CAttackEenemyState
{
public:
	//メンバ関数
	CRastSmallWeaponEenemyAttack();//コンストラクタ
	~CRastSmallWeaponEenemyAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

#endif