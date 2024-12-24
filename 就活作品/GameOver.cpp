//==========================
// 
// タイトルロゴ[Over.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"GameOver.h"
#include"manager.h"

//静的メンバの初期化
const int COver::PRIORITY = 4;//描画優先度
int  COver::m_nTexIdx = 0;//テクスチャID
//========================
//コンストラクタ
//========================
COver::COver(int nPriority) :CObject2D(nPriority)
{

}

//========================
//デストラクタ
//========================
COver::~COver()
{

}

//========================
//初期設定
//========================
HRESULT COver::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void COver::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void COver::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void COver::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
COver* COver::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	COver* pOver = DBG_NEW COver;

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pOver->m_nTexIdx = pTex->Regist("data\\TEXTURE\\GameOver.png");
	pOver->BindTexture(pTex->GetAdress(pOver->m_nTexIdx));

	//位置の設定
	pOver->SetPos(pos);

	//サイズ設定
	pOver->SetSize(100.0f, 350.0f);

	//色を設定
	pOver->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//初期設定
	pOver->Init();

	return pOver;
}