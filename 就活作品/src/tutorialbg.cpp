//==========================
// 
// チュートリアルの背景処理[tutorialbg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"tutorialbg.h"
#include"manager.h"

//静的メンバの初期化
const int CTutorialBg::PRIORITY = 3;//描画優先度
//========================
//コンストラクタ
//========================
CTutorialBg::CTutorialBg(int nPriority):CObject2D(nPriority)
{
	
}

//========================
//デストラクタ
//========================
CTutorialBg::~CTutorialBg()
{

}

//========================
//初期設定
//========================
HRESULT CTutorialBg::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void CTutorialBg::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void CTutorialBg::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void CTutorialBg::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
CTutorialBg* CTutorialBg::Create()
{
	//インスタンス生成
	CTutorialBg* pTutorialBg = DBG_NEW CTutorialBg;

	//位置の設定
	pTutorialBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//サイズ設定
	pTutorialBg->SetSize(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);

	//色を設定
	pTutorialBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));

	//初期設定
	pTutorialBg->Init();

	return pTutorialBg;
}