//==========================
// 
// 敵の状態管理[enemystate.h]
// Author Yuki Goto
//
//==========================
#ifndef _ENEMYSTATE_H_
#define _ENEMYSTATE_H_

//include
#include"characterstate.h"

//前方宣言
class CWeakEnemy;
class CEenemyAttackStateMachine;
class CAttackEenemyState;

//==============================================================================
//敵の状態クラス
//==============================================================================
class CEnemyStateBase :public CStateBase
{
public:
	//メンバ関数
	CEnemyStateBase();//コンストラクタ
	~CEnemyStateBase();//デストラクタ
	void SetOwner(CWeakEnemy* enemy);//ステートの所持者を設定
	CWeakEnemy* GetOwner();//ステートの所有者を取得
protected:

	//メンバ変数
	CWeakEnemy* m_pEnemy;//敵の情報
};

//==============================================================================
//仮状態クラス
//==============================================================================
class CEnemyMovabeState :public CEnemyStateBase
{
public:
	//メンバ関数
	CEnemyMovabeState();//コンストラクタ
	~CEnemyMovabeState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};


//==============================================================================
//待機状態クラス
//==============================================================================
class CEnemyNeutralState :public CEnemyStateBase
{
public:
	//メンバ関数
	CEnemyNeutralState();//コンストラクタ
	~CEnemyNeutralState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//移動状態クラス
//==============================================================================
class CEnemyMoveState :public CEnemyStateBase
{
public:
	//メンバ関数
	CEnemyMoveState();//コンストラクタ
	~CEnemyMoveState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//ダメージ状態クラス
//==============================================================================
class CEnemyDamageState :public CEnemyStateBase
{
public:
	//定数
	static const int DAMEGE_FLAME;//ダメージ状態を終了するまでのフレーム数

	//メンバ関数
	CEnemyDamageState();//コンストラクタ
	~CEnemyDamageState();//デストラクタ
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
class CEnemyDushState :public CEnemyStateBase
{
public:
	//メンバ関数
	CEnemyDushState();//コンストラクタ
	~CEnemyDushState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
};

//==============================================================================
//吹き飛び状態クラス
//==============================================================================
class CEnemyDamageBrrowState :public CEnemyStateBase
{
public:
	//定数
	static const int BRROW_FLAME;//ダメージ状態を終了するまでのフレーム数

	//メンバ関数
	CEnemyDamageBrrowState();//コンストラクタ
	~CEnemyDamageBrrowState();//デストラクタ
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
class CEnemyAttackState :public CEnemyStateBase
{
public:
	
	//メンバ関数
	CEnemyAttackState();//コンストラクタ
	~CEnemyAttackState();//デストラクタ
	void Start()override;//開始
	void Update()override;//更新
	void Uninit()override;//終了
	void ChangeCombo();//コンボ判定を取得
	void ResetInfo();//情報を初期化
	void ChangeAttack(CAttackEenemyState* State);//攻撃を変更
	int GetFrame();//攻撃フレーム数を取得
private:

	//メンバ変数
	int m_FlameCount;//攻撃のフレーム数
	bool m_Combo;//コンボ判定
	CEenemyAttackStateMachine* m_EenemyAttackStateMachine;//攻撃の状態管理
};

#endif