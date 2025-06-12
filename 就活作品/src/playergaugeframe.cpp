//==========================
// 
// プレイヤーのHPゲージの枠[playergaugeframe.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "playergaugeframe.h"
#include "texture.h"
#include "manager.h"

//静的メンバ初期化
const int CPlayerHPGaugeFrame::PRIORITY = 4;//描画順

//==========================
//コンストラクタ
//==========================
CPlayerHPGaugeFrame::CPlayerHPGaugeFrame(int nPriority) :
CObject2D(nPriority),//基底コンストラクタ
m_nTexIdx(0)//テクスチャの番号
{

}

//==========================
//デストラクタ
//==========================
CPlayerHPGaugeFrame::~CPlayerHPGaugeFrame()
{

}

//==========================
//初期化処理
//==========================
HRESULT CPlayerHPGaugeFrame::Init()
{
	//初期設定
	CObject2D::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CPlayerHPGaugeFrame::Uninit()
{
	//終了処理
	CObject2D::Uninit();
}

//==========================
//更新処理
//==========================
void  CPlayerHPGaugeFrame::Update()
{
	//頂点情報の設定
	SetVtx();
}

//==========================
//描画処理
//==========================
void CPlayerHPGaugeFrame::Draw()
{
	//描画処理
	CObject2D::Draw();
}

//==========================
//オブジェクト2D生成
//==========================
CPlayerHPGaugeFrame* CPlayerHPGaugeFrame::Create(D3DXVECTOR3 pos, float vertical, float width)
{
	//インスタンス生成
	CPlayerHPGaugeFrame* pPlayerHPGauge = DBG_NEW CPlayerHPGaugeFrame;

	//位置の設定
	pPlayerHPGauge->SetPos(pos);

	//大きさの設定
	pPlayerHPGauge->SetSize(vertical, width);

	//色の設定
	pPlayerHPGauge->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//初期化処理
	pPlayerHPGauge->Init();

	return pPlayerHPGauge;
}

//==========================
//頂点情報の設定
//==========================
void CPlayerHPGaugeFrame::SetVtx()
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//頂点バッファを取得

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(GetPos().x - 1.0f, GetPos().y - GetVertical(), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + (GetWidth() * 2) + 1.0f, GetPos().y - GetVertical(), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x - 1.0f, GetPos().y + GetVertical(), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + (GetWidth() * 2) + 1.0f, GetPos().y + GetVertical(), 0.0f);

	//頂点カラーの設定
	pVtx[0].col = GetCol();
	pVtx[1].col = GetCol();
	pVtx[2].col = GetCol();
	pVtx[3].col = GetCol();

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();
}