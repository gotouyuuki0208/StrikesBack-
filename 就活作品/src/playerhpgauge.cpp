//==========================
// 
// HPゲージ[playerhpgauge.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "playerhpgauge.h"
#include "texture.h"
#include "manager.h"
#include "playergaugeframe.h"

//静的メンバ初期化
const int CPlayerHPGauge::PRIORITY = 4;//描画順

//==========================
//コンストラクタ
//==========================
CPlayerHPGauge::CPlayerHPGauge(int nPriority) :
CObject2D(nPriority),//基底コンストラクタ
m_nTexIdx(0),//テクスチャの番号
m_HP(0),//hpの数値
m_MaxHP(0),//最大HPの数値
m_Targetlength(0.0f),//目的の長さ
m_length(0.0f),//長さ
m_Ratio(0.0f)//HPの割合
{

}

//==========================
//デストラクタ
//==========================
CPlayerHPGauge::~CPlayerHPGauge()
{

}

//==========================
//初期化処理
//==========================
HRESULT CPlayerHPGauge::Init()
{
	//初期設定
	CObject2D::Init();

	m_length = GetWidth() * 2;//ゲージの長さを設定

	return S_OK;
}

//==========================
//終了処理
//==========================
void CPlayerHPGauge::Uninit()
{
	//終了処理
	CObject2D::Uninit();
}

//==========================
//更新処理
//==========================
void  CPlayerHPGauge::Update()
{
	//ゲージの長さを設定
	SetLength();

	//色の変更
	SwitchCor();

	//頂点情報の設定
	SetVtx();
}

//==========================
//描画処理
//==========================
void CPlayerHPGauge::Draw()
{
	//描画処理
	CObject2D::Draw();
}

//==========================
//オブジェクト2D生成
//==========================
CPlayerHPGauge* CPlayerHPGauge::Create(D3DXVECTOR3 pos, float vertical, float width)
{
	//ゲージの枠を生成
	CPlayerHPGaugeFrame::Create(pos, vertical+1.0f, width);

	//インスタンス生成
	CPlayerHPGauge* pPlayerHPGauge = DBG_NEW CPlayerHPGauge;

	//位置の設定
	pPlayerHPGauge->SetPos(pos);

	//大きさの設定
	pPlayerHPGauge->SetSize(vertical, width);

	//色の設定
	pPlayerHPGauge->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//初期化処理
	pPlayerHPGauge->Init();

	return pPlayerHPGauge;
}

//==========================
//hpを設定
//==========================
void CPlayerHPGauge::SetHP(int hp)
{
	m_HP = hp;

	if (m_MaxHP == 0)
	{
		m_MaxHP = hp;
	}
}

//==========================
//ゲージの長さを設定
//==========================
void CPlayerHPGauge::SetLength()
{
	//HPの割合を求める
	m_Ratio = static_cast<float>(m_HP) / static_cast<float>(m_MaxHP);

	//目的の長さを設定
	m_Targetlength = ((GetWidth() * 2) * m_Ratio);

	if (m_Targetlength <= m_length)
	{//現在の長さが目的の長さより長いとき

		m_length -= 1.0f;//短くする

		if (m_Targetlength >= m_length)
		{//目的の長さより短くなったとき

			m_length = m_Targetlength;//同じ長さにする
		}
	}
	if (m_Targetlength >= m_length)
	{//現在の長さが目的の長さより長いとき
		m_length += 1.0f;//短くする

		if (m_Targetlength <= m_length)
		{//目的の長さより短くなったとき

			m_length = m_Targetlength;//同じ長さにする
		}
	}
}

//==========================
//色の変更
//==========================
void CPlayerHPGauge::SwitchCor()
{
	if (m_Ratio <= 0.2f)
	{
		SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else if (m_Ratio <= 0.5f)
	{
		SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
	}
	else
	{
		SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}
}

//==========================
//頂点情報の設定
//==========================
void CPlayerHPGauge::SetVtx()
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//頂点バッファを取得

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(GetPos().x, GetPos().y - GetVertical(), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + m_length, GetPos().y - GetVertical(), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x, GetPos().y + GetVertical(), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + m_length, GetPos().y + GetVertical(), 0.0f);

	//頂点カラーの設定
	pVtx[0].col = GetCol();
	pVtx[1].col = GetCol();
	pVtx[2].col = GetCol();
	pVtx[3].col = GetCol();

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();
}