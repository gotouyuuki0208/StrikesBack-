//==========================
// 
// キャラクターの状態管理[characterstate.h]
// Author Yuki Goto
//
//==========================
#ifndef _STATE_H_
#define _STATE_H_


//==============================================================================
//基底クラス
//==============================================================================
class CStateBase
{
public:
	//メンバ関数
	CStateBase();//コンストラクタ
	~CStateBase();//デストラクタ
	virtual void Start();//開始
	virtual void Update();//更新
	virtual void Uninit();//終了
};

//==============================================================================
//状態管理クラス
//==============================================================================
class CStateMachine
{
public:
	//メンバ関数
	CStateMachine();//コンストラクタ
	~CStateMachine();//デストラクタ
	void ChangeState(CStateBase* NewState);//状態の変更
	void Update();//更新
	CStateBase* GetState();//現在のステートを取得

private:

	//メンバ変数
	CStateBase* m_State = nullptr;//現在のステート
};

#endif