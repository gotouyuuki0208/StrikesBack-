//==========================
// 
// 操作説明UIの背景[UIbg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"UIbg.h"


//静的メンバの初期化
const int CUIBg::PRIORITY = 4;//描画優先度

//========================
//コンストラクタ
//========================
CUIBg::CUIBg(int nPriority) :CObject2D(nPriority)
{

}

//========================
//デストラクタ
//========================
CUIBg::~CUIBg()
{

}

//========================
//初期設定
//========================
HRESULT CUIBg::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void CUIBg::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void CUIBg::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void CUIBg::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
CUIBg* CUIBg::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CUIBg* pUIBg = DBG_NEW CUIBg;

	//位置の設定
	pUIBg->SetPos(pos);

	//サイズ設定
	pUIBg->SetSize(20.0f,150.0f);

	//色を設定
	pUIBg->SetCor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

	//初期設定
	pUIBg->Init();

	return pUIBg;
}