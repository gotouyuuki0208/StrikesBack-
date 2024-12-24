//==========================
// 
// タイトルロゴ[Clear.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"clear.h"
#include"manager.h"

//静的メンバの初期化
const int CClear::PRIORITY = 4;//描画優先度
int  CClear::m_nTexIdx = 0;//テクスチャID
//========================
//コンストラクタ
//========================
CClear::CClear(int nPriority) :CObject2D(nPriority)
{

}

//========================
//デストラクタ
//========================
CClear::~CClear()
{

}

//========================
//初期設定
//========================
HRESULT CClear::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void CClear::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void CClear::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void CClear::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
CClear* CClear::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CClear* pClear = DBG_NEW CClear;

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pClear->m_nTexIdx = pTex->Regist("data\\TEXTURE\\GameClear.png");
	pClear->BindTexture(pTex->GetAdress(pClear->m_nTexIdx));

	//位置の設定
	pClear->SetPos(pos);

	//サイズ設定
	pClear->SetSize(100.0f, 350.0f);

	//色を設定
	pClear->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//初期設定
	pClear->Init();

	return pClear;
}