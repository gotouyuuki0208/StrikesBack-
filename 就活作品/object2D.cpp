//==========================
// 
// ポリゴンの描画処理[object2D.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"object2D.h"
#include"manager.h"

//静的メンバ初期化
const int CObject2D::PRIORITY = 2;//描画優先度

//========================
//コンストラクタ
//========================
CObject2D::CObject2D(int nPriority):CObjectgame(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;

	m_cor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_fAngle = 0.0f;
	m_fLength = 0.0f;//対角線の長さ
	m_fVertical = 0.0f;//縦のサイズ
	m_fWidth = 0.0f;//横のサイズ
	m_nCntAnim = 0;//テクスチャアニメーションの切り替え
	m_nPatternAnim = 0;//テクスチャアニメーションの分割数
}

//========================
//デストラクタ
//========================
CObject2D::~CObject2D()
{

}

//========================
//初期設定
//========================
HRESULT CObject2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(GetPos().x - m_fWidth, GetPos().y - m_fVertical, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + m_fWidth, GetPos().y - m_fVertical, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x - m_fWidth, GetPos().y + m_fVertical, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + m_fWidth, GetPos().y + m_fVertical, 0.0f);

	//pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[0].pos.z = 0.0f;											 
	//																 
	//pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[1].pos.z = 0.0f;

	//pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + -(D3DX_PI * 0.5f)) * m_fWidth / 2;
	//pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + -(D3DX_PI * 0.5f)) * m_fWidth / 2;
	//pVtx[2].pos.z = 0.0f;

	//pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI * 0.5f)) * m_fWidth / 2;
	//pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI * 0.5f)) * m_fWidth / 2;
	//pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CObject2D::Uninit(void)
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
void CObject2D::Update()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = m_cor;
	pVtx[1].col = m_cor;
	pVtx[2].col = m_cor;
	pVtx[3].col = m_cor;
	
	pVtx[0].pos = D3DXVECTOR3(GetPos().x - m_fWidth, GetPos().y - m_fVertical, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + m_fWidth, GetPos().y - m_fVertical, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x - m_fWidth, GetPos().y + m_fVertical, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + m_fWidth, GetPos().y + m_fVertical, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//========================
//アニメーション処理
//========================
void CObject2D::Animetion(float vertical, int width)
{
	float fvertical = 1.0f / vertical;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

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
//描画処理
//========================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//========================
//オブジェクト2D生成
//========================
CObject2D* CObject2D::Create(void)
{
	CObject2D* pObject2D = DBG_NEW CObject2D;

	pObject2D->Init();

	return pObject2D;
}

//========================
//テクスチャ割り当て
//========================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}


//========================
//対角線の長さ取得
//========================
float CObject2D::GetLength(void)
{
	return m_fLength;
}

//========================
//色の設定
//========================
void CObject2D::SetCor(D3DCOLOR cor)
{
	m_cor = cor;
}

//========================
//色の取得
//========================
D3DCOLOR CObject2D::GetCor()
{
	return m_cor;
}

//========================
//大きさ設定
//========================
void CObject2D::SetSize(float vertical, float width)
{
	m_fWidth = width;//横の長さ設定

	m_fVertical = vertical;//縦の長さ設定

	m_fAngle = atan2f(width, (vertical * 2.0f));//対角線の角度設定

	m_fLength = sqrtf(width * width + (vertical * 2.0f) * (vertical * 2.0f)) / 2;//対角線の長さ設定
}

//========================
//テクスチャの大きさ設定
//========================
void CObject2D::SetTexSize(float vertical, float width, float TexPos)
{
	float fvertical = 1.0f / vertical;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

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
//頂点バッファのポインタを取得
//========================
LPDIRECT3DVERTEXBUFFER9 CObject2D::GetVtxBuff()
{
	return m_pVtxBuff;
}

//========================
//横のサイズを取得
//========================
float CObject2D::GetWidth()
{
	return m_fWidth;
}

//========================
//縦のサイズを取得
//========================
float CObject2D::GetVertical()
{
	return m_fVertical;
}