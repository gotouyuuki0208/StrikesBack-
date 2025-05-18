//==========================
// 
// チュートリアルポップアップ表示[TutorialPopup.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "TutorialPopup.h"
#include "texture.h"
#include "manager.h"

//静的メンバ初期化
const int CTutorialPopup::PRIORITY = 3;//描画順

//==========================
//コンストラクタ
//==========================
CTutorialPopup::CTutorialPopup(int nPriority) :
	CObject2D(nPriority),//基底コンストラクタ
	m_nTexIdx(0),//テクスチャの番号
	m_transparency(0.0f),//透明度
	m_input(false)//入力判定
{

}

//==========================
//デストラクタ
//==========================
CTutorialPopup::~CTutorialPopup()
{

}

//==========================
//初期化処理
//==========================
HRESULT CTutorialPopup::Init()
{
	//初期設定
	CObject2D::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CTutorialPopup::Uninit()
{
	//終了処理
	CObject2D::Uninit();
}

//==========================
//更新処理
//==========================
void  CTutorialPopup::Update()
{
	if (!m_input)
	{//キー入力されていない

		//不透明にする
		MakeOpaque();
	}
	else
	{//キー入力されている

		//透明にする
		MakeTransparent();
	}
	

	//更新処理
	CObject2D::Update();

	if (m_transparency <= 0.0f)
	{//透明になった

		Uninit();
	}
}

//==========================
//描画処理
//==========================
void CTutorialPopup::Draw()
{
	//描画処理
	CObject2D::Draw();
}

//==========================
//オブジェクト2D生成
//==========================
CTutorialPopup* CTutorialPopup::Create()
{
	//インスタンス生成
	CTutorialPopup* pSampleObject2D = DBG_NEW CTutorialPopup;

	//位置の設定
	pSampleObject2D->SetPos({ 640.0f, 340.0f, 0.0f });

	//大きさの設定
	pSampleObject2D->SetSize(250.0f, 350.0f);

	//初期化処理
	pSampleObject2D->Init();

	//色の設定
	pSampleObject2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	//テクスチャの設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pSampleObject2D->m_nTexIdx = pTex->Regist("data\\TEXTURE\\33_Symmetry.png");
	pSampleObject2D->BindTexture(pTex->GetAdress(pSampleObject2D->m_nTexIdx));

	//テクスチャの大きさ設定
	pSampleObject2D->SetTexSize(1.0f, 1.0f, 0.0f);

	return pSampleObject2D;
}

//==========================
//不透明にする
//==========================
void CTutorialPopup::MakeOpaque()
{
	//色を取得
	D3DXCOLOR col = GetCol();
	
	if (col.a >= 1.0f)
	{//不透明になってる
		return;
	}

	//透明度を上げる
	m_transparency = col.a + 0.1f;

	//色の設定
	SetCol(D3DXCOLOR(col.r, col.g, col.b, m_transparency));
}

//==========================
//透明にする
//==========================
void CTutorialPopup::MakeTransparent()
{
	D3DXCOLOR col = GetCol();

	if (col.a <= 0.0f)
	{//透明になってる
		return;
	}

	//透明度を下げる
	m_transparency = col.a - 0.1f;

	//色の設定
	SetCol(D3DXCOLOR(col.r, col.g, col.b, m_transparency));
}

//==========================
//キー入力
//==========================
void CTutorialPopup::KeyInput()
{
	if (m_input)
	{//すでにボタンがおされている
		return;
	}

	m_input = true;
}