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
class CEnemyAttackStateBase
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
	CEnemyAttackStateBase();//コンストラクタ
	~CEnemyAttackStateBase();//デストラクタ
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
class CAttackEnemyState :public CEnemyAttackStateBase
{
public:

	//メンバ関数
	CAttackEnemyState();//コンストラクタ
	~CAttackEnemyState();//デストラクタ
	void SetOwner(CEnemyAttackState* State);//ステートの所持者を設定

protected:

	//メンバ変数
	CEnemyAttackState* m_OwnerState;//ステートの所有者
};

//==============================================================================
//状態管理クラス
//==============================================================================
class CEnemyAttackStateMachine
{
public:

	//メンバ関数
	CEnemyAttackStateMachine();//コンストラクタ
	~CEnemyAttackStateMachine();//デストラクタ
	void ChangeState(CEnemyAttackStateBase* NewState);//状態の変更
	void Update();//更新

private:

	//メンバ変数
	CEnemyAttackStateBase* m_State;//プレイヤーの状態

};

//==============================================================================
//素手攻撃クラス
//==============================================================================

//1回目の攻撃
class CFirstEnemyAttackState :public CAttackEnemyState
{
public:
	//メンバ関数
	CFirstEnemyAttackState();//コンストラクタ
	~CFirstEnemyAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//2回目の攻撃
class CSecondEnemyAttackState :public CAttackEnemyState
{
public:
	//メンバ関数
	CSecondEnemyAttackState();//コンストラクタ
	~CSecondEnemyAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//3回目の攻撃
class CRastEnemyAttackState :public CAttackEnemyState
{
public:
	//メンバ関数
	CRastEnemyAttackState();//コンストラクタ
	~CRastEnemyAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//片手武器攻撃クラス
//==============================================================================

//1回目の攻撃
class CFirstSmallWeaponEnemyAttack :public CAttackEnemyState
{
public:
	//メンバ関数
	CFirstSmallWeaponEnemyAttack();//コンストラクタ
	~CFirstSmallWeaponEnemyAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//2回目の攻撃
class CSecondSmallWeaponEnemyAttack :public CAttackEnemyState
{
public:
	//メンバ関数
	CSecondSmallWeaponEnemyAttack();//コンストラクタ
	~CSecondSmallWeaponEnemyAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//3回目の攻撃
class CRastSmallWeaponEnemyAttack :public CAttackEnemyState
{
public:
	//メンバ関数
	CRastSmallWeaponEnemyAttack();//コンストラクタ
	~CRastSmallWeaponEnemyAttack();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

#endif