//==========================
// 
// 背景処理[bg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"dark.h"
#include"manager.h"

//静的メンバの初期化
const int CDark::PRIORITY = 4;//描画優先度
//========================
//コンストラクタ
//========================
CDark::CDark(int nPriority) :CObject2D(nPriority)
{

}

//========================
//デストラクタ
//========================
CDark::~CDark()
{

}

//========================
//初期設定
//========================
HRESULT CDark::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void CDark::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void CDark::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void CDark::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
CDark* CDark::Create()
{
	//インスタンス生成
	CDark* pDark = DBG_NEW CDark;

	//テクスチャ設定
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pDark->m_nTexIdx = pTex->Regist(texname);
	pDark->BindTexture(pTex->GetAdress(pDark->m_nTexIdx));*/

	//位置の設定
	pDark->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//サイズ設定
	pDark->SetSize(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);

	//色を設定
	pDark->SetCor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));

	//初期設定
	pDark->Init();

	return pDark;
}