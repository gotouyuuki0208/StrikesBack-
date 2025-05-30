//==========================
// 
// キャラクターの状態管理[characterstate.cpp]
// Author Yuki Goto
//
//==========================
#include"characterstate.h"

//========================================================================================================
//状態管理クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CStateMachine::CStateMachine() :
	m_State(nullptr)//キャラクターの状態
{

}

//==========================
//デストラクタ
//==========================
CStateMachine::~CStateMachine()
{
	if (m_State != nullptr)
	{//ステートがある

		//現在のステートの終了
		m_State->Uninit();
		m_State = nullptr;
	}
}

//==========================
//状態の変更
//==========================
void CStateMachine::ChangeState(CStateBase* NewState)
{
	if (m_State != nullptr)
	{//ステートがある

		//現在のステートの終了
		m_State->Uninit();
		m_State = nullptr;
	}

	//新しいステートを保存
	m_State = NewState;

	//初期設定
	m_State->Start();
}

//==========================
//更新
//==========================
void CStateMachine::Update()
{
	if (m_State != nullptr)
	{//ステートがある

		//ステートの更新
		m_State->Update();
	}
}

//==========================
//現在のステートを取得
//==========================
CStateBase* CStateMachine::GetState()
{
	return m_State;
}

//========================================================================================================
//基底クラス
//========================================================================================================

//==========================
//コンストラクタ
//==========================
CStateBase::CStateBase()
{

}

//==========================
//デストラクタ
//==========================
CStateBase::~CStateBase()
{

}

//==========================
//開始
//==========================
void CStateBase::Start()
{

}

//==========================
//更新
//==========================
void CStateBase::Update()
{

}

//==========================
//終了
//==========================
void CStateBase::Uninit()
{
	delete this;
}
