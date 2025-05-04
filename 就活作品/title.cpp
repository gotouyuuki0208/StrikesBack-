//==========================
// 
// タイトル画面の処理[taitle.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"title.h"
#include"manager.h"
#include"bg.h"
#include"fild.h"
#include"outgamecharactar.h"
#include"OutGameWall.h"
#include"pullup.h"
#include"punchingbag.h"
#include"benchpress.h"
#include"TitleLogo.h"
#include"titlestart.h"

//==========================
// コンストラクタ
//==========================
CTitle::CTitle()
{

}

//==========================
// デストラクタ
//==========================
CTitle::~CTitle()
{

}

//==========================
// 初期設定
//==========================
HRESULT CTitle::Init()
{
	//CBg::Create("data\\TEXTURE\\title.png");

	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_TITLE);

	//背景
	Bg();

	//タイトルロゴ
	CTitleLogo::Create(D3DXVECTOR3(350.0f, 200.0f, 0.0f));

	//タイトルロゴ
	CTitleStart::Create(D3DXVECTOR3(640.0f, 600.0f, 0.0f));

	return S_OK;

}

//==========================
// 終了処理
//==========================
void CTitle::Uninit()
{
	CObject::ReleaseAll();

	CManager::GetInstance()->GetSound()->Stop();
}

//==========================
// 更新処理
//==========================
void CTitle::Update()
{
	CManager::GetInstance()->GetCamera()->OutGame(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN)
		|| CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_B))
	{//ゲーム画面に遷移

		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_START);
		CManager::GetInstance()->GetFade()->SetFade(MODE::GAME);
	}
}

//==========================
// 描画処理
//==========================
void CTitle::Draw()
{

}

//==========================
//背景
//==========================
void CTitle::Bg()
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
	COutGameChara::Create(D3DXVECTOR3(75.0f, 22.0f, -3.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
}