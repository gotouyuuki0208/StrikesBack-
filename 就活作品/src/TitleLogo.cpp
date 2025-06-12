//==========================
// 
// タイトルロゴ[TitleLogo.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"TitleLogo.h"
#include"manager.h"

//静的メンバの初期化
const int CTitleLogo::PRIORITY = 4;//描画優先度
int  CTitleLogo::m_nTexIdx = 0;//テクスチャID
//========================
//コンストラクタ
//========================
CTitleLogo::CTitleLogo(int nPriority) :CObject2D(nPriority)
{

}

//========================
//デストラクタ
//========================
CTitleLogo::~CTitleLogo()
{

}

//========================
//初期設定
//========================
HRESULT CTitleLogo::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void CTitleLogo::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void CTitleLogo::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void CTitleLogo::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
CTitleLogo* CTitleLogo::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CTitleLogo* pTitleLogo = DBG_NEW CTitleLogo;

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pTitleLogo->m_nTexIdx = pTex->Regist("data\\TEXTURE\\logo.png");
	pTitleLogo->BindTexture(pTex->GetAdress(pTitleLogo->m_nTexIdx));

	//位置の設定
	pTitleLogo->SetPos(pos);

	//サイズ設定
	pTitleLogo->SetSize(150.0f,250.0f);

	//色を設定
	pTitleLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//初期設定
	pTitleLogo->Init();

	return pTitleLogo;
}