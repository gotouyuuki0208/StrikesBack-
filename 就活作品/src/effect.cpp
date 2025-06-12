//==========================
// 
// エフェクト処理[effect.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"effect.h"
#include"manager.h"

//静的メンバの初期化
const int CEffect::PRIORITY = 3;//描画優先度
int CEffect::m_nTexIdx = 0;//テクスチャID

//==========================
// コンストラクタ
//==========================
CEffect::CEffect(int Priority):
CBillBoard(Priority),//基底コンストラクタ
m_nLife(30),//寿命
cor(1.0f),//色
m_Vertical(0.0f),//縦の長さ
m_Width(0.0f)//横の長さ
{

}

//==========================
// デストラクタ
//==========================
CEffect::~CEffect(void)
{

}

//==========================
// 初期設定
//==========================
HRESULT CEffect::Init(void)
{
	//初期化処理
	CBillBoard::Init();

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CEffect::Uninit(void)
{
	//終了処理
	CBillBoard::Uninit();
}

//==========================
// 更新処理
//==========================
void CEffect::Update(void)
{
	m_nLife--;//寿命を減らす

	//小さくする
	m_Vertical -= 0.2f;
	m_Width -= 0.2f;
	SetSize(D3DXVECTOR3(m_Width, m_Vertical, 0.0f));

	cor -= 0.01f;//透明度を減らす
	
	SetCol(D3DXCOLOR(GetCol().r, GetCol().g, GetCol().b, cor));//色の設定

	if (m_nLife <= 0 || m_Vertical <= 0)
	{
		Uninit();
		return;
	}

	//更新処理
	CBillBoard::Update();
}

//==========================
// 描画処理
//==========================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画処理
	CBillBoard::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//========================
//オブジェクト2D生成
//========================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR cor, float Vertical, float Width)
{
	CEffect* pEffect = DBG_NEW CEffect;

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	m_nTexIdx = pTex->Regist("data\\TEXTURE\\effect000.jpg");
	pEffect->BindTexture(pTex->GetAdress(m_nTexIdx));

	//位置の設定
	pEffect->SetPos(pos);

	//色の設定
	pEffect->SetCol(cor);

	//サイズの設定
	pEffect->m_Width = Width;
	pEffect->m_Vertical = Vertical;
	pEffect->SetSize(D3DXVECTOR3(Width, Vertical, 0.0f));

	//初期化処理
	pEffect->Init();

	return pEffect;
}