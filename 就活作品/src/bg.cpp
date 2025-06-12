//==========================
// 
// 背景処理[bg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"bg.h"
#include"manager.h"

//静的メンバの初期化
const int CBg::PRIORITY = 4;//描画優先度
int  CBg::m_nTexIdx = 0;//テクスチャID
//========================
//コンストラクタ
//========================
CBg::CBg(int nPriority):CObject2D(nPriority)
{
	
}

//========================
//デストラクタ
//========================
CBg::~CBg()
{

}

//========================
//初期設定
//========================
HRESULT CBg::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void CBg::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void CBg::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void CBg::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
CBg* CBg::Create(const char texname[256])
{
	//インスタンス生成
	CBg* pBg = DBG_NEW CBg;

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pBg->m_nTexIdx = pTex->Regist(texname);
	pBg->BindTexture(pTex->GetAdress(pBg->m_nTexIdx));

	//位置の設定
	pBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//サイズ設定
	pBg->SetSize(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);

	//色を設定
	pBg->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//初期設定
	pBg->Init();

	return pBg;
}