//==========================
// 
// リザルト画面の処理[result.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"result.h"
#include"manager.h"
#include"bg.h"
#include"fild.h"
#include"outgamecharactar.h"
#include"OutGameWall.h"
#include"pullup.h"
#include"punchingbag.h"
#include"benchpress.h"
#include"dark.h"
#include"knockdown.h"
#include"peoplenum.h"
#include"clear.h"
#include"GameOver.h"

//==========================
// コンストラクタ
//==========================
CResult::CResult()
{
	
}

//==========================
// デストラクタ
//==========================
CResult::~CResult()
{

}

//==========================
// 初期設定
//==========================
HRESULT CResult::Init()
{
	//CBg::Create("data\\TEXTURE\\Resurt.png");

	//背景
	Bg();

	//黒背景
	CDark::Create();

	if (CManager::GetInstance()->GetGameManager()->GetGame() == CGameManager::GAME::CLEAR)
	{
		/*CKnockDown::Create(D3DXVECTOR3(320.0f, 400.0f, 0.0f));
		CPeopleNum::Create(D3DXVECTOR3(900.0f, 400.0f, 0.0f));
		CClear::Create(D3DXVECTOR3(640.0f, 150.0f, 0.0f));*/
		CClear::Create(D3DXVECTOR3(640.0f, 340.0f, 0.0f));
	}
	else
	{
		COver::Create(D3DXVECTOR3(640.0f, 340.0f, 0.0f));
	}

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CResult::Uninit()
{
	CObject::ReleaseAll();
}

//==========================
// 更新処理
//==========================
void CResult::Update()
{
	CManager::GetInstance()->GetCamera()->OutGame(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN)
		|| CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_B))
	{//タイトル画面に遷移
		CManager::GetInstance()->GetFade()->SetFade(MODE::TITLE);
	}
}

//==========================
// 描画処理
//==========================
void CResult::Draw()
{

}

//==========================
//背景
//==========================
void CResult::Bg()
{
	//地面
	CFild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//壁
	COutGameWall::Create(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	COutGameWall::Create(D3DXVECTOR3(150.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	COutGameWall::Create(D3DXVECTOR3(0.0f, 250.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(0.0f, 1.57f, 1.57f));

	//器具
	CPullUp::Create(D3DXVECTOR3(70.0f, 0.0f, 0.0f), D3DXVECTOR3(2.5f, 1.7f, 2.0f));
	CPunchingBag::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.5f, 2.0f));
	CBenchPress::Create(D3DXVECTOR3(-80.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));

	//人
	COutGameChara::Create(D3DXVECTOR3(0.0f, 0.0f, -50.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
}