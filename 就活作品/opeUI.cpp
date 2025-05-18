//==========================
// 
// 背景処理[opeUI.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"opeUI.h"
#include"manager.h"

//静的メンバの初期化
const int COpeUI::PRIORITY = 4;//描画優先度
//========================
//コンストラクタ
//========================
COpeUI::COpeUI(int nPriority) :
CObject2D(nPriority),
m_nTexIdx(0)
{

}

//========================
//デストラクタ
//========================
COpeUI::~COpeUI()
{

}

//========================
//初期設定
//========================
HRESULT COpeUI::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void COpeUI::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void COpeUI::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void COpeUI::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
COpeUI* COpeUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char texname[256])
{
	//インスタンス生成
	COpeUI* pOpeUI = DBG_NEW COpeUI;

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pOpeUI->m_nTexIdx = pTex->Regist(texname);
	pOpeUI->BindTexture(pTex->GetAdress(pOpeUI->m_nTexIdx));

	//位置の設定
	pOpeUI->SetPos(pos);

	//サイズ設定
	pOpeUI->SetSize(size.y, size.x);

	//色を設定
	pOpeUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//初期設定
	pOpeUI->Init();

	return pOpeUI;
}