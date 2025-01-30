//==========================
//
// ビルボードの描画処理[billboard.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"billboard.h"
#include"manager.h"

//静的メンバ初期化
const int CBillBoard::PRIORITY = 1;//描画優先度

//========================
//コンストラクタ
//========================
CBillBoard::CBillBoard(int nPriority) :CObjectgame(nPriority)
{
	m_pTexture = nullptr;//テクスチャへのポインタ
	m_pVtxBuff = nullptr;//頂点バッファへのポインタ
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//大きさ
	m_cor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//色の設定
	m_nCntAnim = 0;//アニメーションカウンター
	m_nPatternAnim = 0;//テクスチャアニメーションの分割数
	m_aPosTexV = 0.0f;
}

//========================
//デストラクタ
//========================
CBillBoard::~CBillBoard()
{

}

//========================
//初期設定
//========================
HRESULT CBillBoard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\block000.jpg", &m_pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = m_cor;
	pVtx[1].col = m_cor;
	pVtx[2].col = m_cor;
	pVtx[3].col = m_cor;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//========================
//終了処理
//========================
void CBillBoard::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}

	Release();
}

//========================
//更新処理
//========================
void CBillBoard::Update()
{
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = m_cor;
	pVtx[1].col = m_cor;
	pVtx[2].col = m_cor;
	pVtx[3].col = m_cor;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//========================
//描画処理
//========================
void CBillBoard::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	D3DXMATRIX mtxTrans,a;//計算用マトリックス
	D3DXMATRIX mtxView;//ビューマトリックス取得用

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&GetMtxWorld());
	
	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	
	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&GetMtxWorld(), NULL, &mtxView);//逆行列を求める
	GetMtxWorld()._41 = 0.0f;
	GetMtxWorld()._42 = 0.0f;
	GetMtxWorld()._43 = 0.0f;
	
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ビルボードの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//========================
//テクスチャ割り当て
//========================
void CBillBoard::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//========================
//オブジェクト3D生成
//========================
CBillBoard* CBillBoard::Create(D3DXVECTOR3 pos)
{
	CBillBoard* pBillBoard = DBG_NEW CBillBoard;

	pBillBoard->SetPos(pos);
	pBillBoard->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	pBillBoard->Init();

	return pBillBoard;
}

//========================
//大きさ設定
//========================
void CBillBoard::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//========================
//大きさを取得
//========================
D3DXVECTOR3& CBillBoard::GetSize()
{
	return m_size;
}

//========================
//色の設定
//========================
void CBillBoard::SetCor(D3DXCOLOR cor)
{
	m_cor = cor;
}

//========================
//色の取得
//========================
D3DXCOLOR& CBillBoard::GetCor()
{
	return m_cor;
}

//========================
//アニメーション処理
//========================
void CBillBoard::Animetion(float vertical, int width)
{
	float fvertical = 1.0f / vertical;

	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_nCntAnim++;
	if (m_nCntAnim >= 5)
	{
		m_nPatternAnim++;
		if (m_nPatternAnim >= width)
		{
			m_nPatternAnim = 0;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((1.0f / width) * m_nPatternAnim, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((1.0f / width) * (m_nPatternAnim + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((1.0f / width) * m_nPatternAnim, fvertical);
		pVtx[3].tex = D3DXVECTOR2((1.0f / width) * (m_nPatternAnim + 1), fvertical);

		m_nCntAnim = 0;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//========================
//テクスチャのサイズ設定
//========================
void CBillBoard::Move()
{

	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の開始位置の更新
	m_aPosTexV += 0.0005f;

	//テクスチャ座標の更新	
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_aPosTexV, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + m_aPosTexV, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_aPosTexV, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + m_aPosTexV, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//========================
//テクスチャのサイズ設定
//========================
void CBillBoard::SetTexSize(float vertical, float width, float TexPos)
{
	float fvertical = 1.0f / vertical;

	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + TexPos * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(((1 / width) + TexPos * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + TexPos * 0.1f, fvertical);
	pVtx[3].tex = D3DXVECTOR2(((1 / width) + TexPos * 0.1f), fvertical);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//========================
//頂点バッファの取得
//========================
LPDIRECT3DVERTEXBUFFER9& CBillBoard::GetVtxBuff()
{
	return m_pVtxBuff;
}

//========================
//テクスチャの取得
//========================
LPDIRECT3DTEXTURE9& CBillBoard::GetTex()
{
	return m_pTexture;
}