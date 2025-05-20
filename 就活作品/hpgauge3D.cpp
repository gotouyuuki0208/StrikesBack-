//==========================
// 
// ビルボードのHPゲージ[hpgauge3D.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "hpgauge3D.h"
#include "texture.h"
#include "manager.h"

//静的メンバ初期化
const int CHPGauge3D::PRIORITY = 3;//描画順

//==========================
//コンストラクタ
//==========================
CHPGauge3D::CHPGauge3D(int nPriority) :
CBillBoard(nPriority),//基底コンストラクタ
m_nTexIdx(0),//テクスチャの番号
m_HP(0),//HPの数値
m_MaxHP(0),//最大HPの数値
m_Targetlength(0.0f),//目的の長さ
m_length(0.0f),//長さ
m_Ratio(0.0f),//HPの割合
m_Draw(true)//描画判定
{	

}

//==========================
//デストラクタ
//==========================
CHPGauge3D::~CHPGauge3D()
{

}

//==========================
//初期化処理
//==========================
HRESULT CHPGauge3D::Init()
{
	//初期設定
	CBillBoard::Init();
	
	m_length = GetSize().x * 2;//ゲージの長さを設定

	return S_OK;
}

//==========================
//終了処理
//==========================
void CHPGauge3D::Uninit()
{
	//終了処理
	CBillBoard::Uninit();
}

//==========================
//更新処理
//==========================
void  CHPGauge3D::Update()
{
	SetLength();//ゲージな長さを設定

	SwitchCor();//色の変更

	SetVtx();//頂点情報の設定
}

//==========================
//描画処理
//==========================
void CHPGauge3D::Draw()
{
	if (!m_Draw)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//描画処理
	CBillBoard::Draw();

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================
//オブジェクト2D生成
//==========================
CHPGauge3D* CHPGauge3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int hp)
{
	//インスタンス生成
	CHPGauge3D* pHPGauge3D = DBG_NEW CHPGauge3D;

	//位置の設定
	pHPGauge3D->SetPos(pos);

	//大きさの設定
	pHPGauge3D->SetSize(size);

	//初期化処理
	pHPGauge3D->Init();

	//HPの設定
	pHPGauge3D->SetHP(hp);//HPを設定
	pHPGauge3D->m_MaxHP = hp;//最大HPを設定

	return pHPGauge3D;
}

//==========================
//hpを設定
//==========================
void CHPGauge3D::SetHP(int hp)
{
	m_HP = hp;
}

//==========================
//頂点情報の設定
//==========================
void CHPGauge3D::SetVtx()
{
	if (GetVtxBuff() == nullptr)
	{
		return;
	}
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//頂点バッファを取得


	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-GetSize().x,+GetSize().y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_length - GetSize().x, +GetSize().y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-GetSize().x, -GetSize().y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_length - GetSize().x, -GetSize().y, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = GetCor();
	pVtx[1].col = GetCor();
	pVtx[2].col = GetCor();
	pVtx[3].col = GetCor();

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//==========================
//色の変更
//==========================
void CHPGauge3D::SwitchCor()
{
	if (m_Ratio <= 0.2f)
	{
		SetCor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else if (m_Ratio <= 0.5f)
	{
		SetCor(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
	}
	else
	{
		SetCor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}
}

//==========================
//ゲージの長さを設定
//==========================
void CHPGauge3D::SetLength()
{
	//HPの割合を求める
	m_Ratio = static_cast<float>(m_HP) / static_cast<float>(m_MaxHP);

	//目的の長さを設定
	m_Targetlength = ((GetSize().x * 2) * m_Ratio);

	if (m_Targetlength <= m_length)
	{//現在の長さが目的の長さより長いとき

		m_length -= 1.0f;//短くする

		if (m_Targetlength >= m_length)
		{//目的の長さより短くなったとき

			m_length = m_Targetlength;//同じ長さにする
		}
	}
}

//==========================
//表示しない
//==========================
void CHPGauge3D::EraseGauge()
{
	m_Draw = false;
}

//==========================
//表示する
//==========================
void CHPGauge3D::DrawGauge()
{
	m_Draw = true;
}