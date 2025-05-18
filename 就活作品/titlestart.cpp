//==========================
// 
// [TitleStart.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"titlestart.h"
#include"manager.h"

//静的メンバの初期化
const int CTitleStart::PRIORITY = 4;//描画優先度
int  CTitleStart::m_nTexIdx = 0;//テクスチャID
//========================
//コンストラクタ
//========================
CTitleStart::CTitleStart(int nPriority) :CObject2D(nPriority)
{

}

//========================
//デストラクタ
//========================
CTitleStart::~CTitleStart()
{

}

//========================
//初期設定
//========================
HRESULT CTitleStart::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void CTitleStart::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void CTitleStart::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void CTitleStart::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
CTitleStart* CTitleStart::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CTitleStart* pTitleStart = DBG_NEW CTitleStart;

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pTitleStart->m_nTexIdx = pTex->Regist("data\\TEXTURE\\gamestart.png");
	pTitleStart->BindTexture(pTex->GetAdress(pTitleStart->m_nTexIdx));

	//位置の設定
	pTitleStart->SetPos(pos);

	//サイズ設定
	pTitleStart->SetSize(50.0f, 200.0f);

	//色を設定
	pTitleStart->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//初期設定
	pTitleStart->Init();

	return pTitleStart;
}