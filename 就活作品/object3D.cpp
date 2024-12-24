//==========================
// 
// ポリゴンの描画処理[object3D.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"object3D.h"
#include"manager.h"

//静的メンバ初期化
const int CObject3D::PRIORITY = 2;//描画優先度

//========================
//コンストラクタ
//========================
CObject3D::CObject3D(int nPriority) :CObjectgame(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;

	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_cor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//========================
//デストラクタ
//========================
CObject3D::~CObject3D()
{

}

//========================
//初期設定
//========================
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

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
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, -m_size.y, +m_size.z);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, -m_size.y, +m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, +m_size.y, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, +m_size.y, -m_size.z);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
void CObject3D::Uninit(void)
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
void CObject3D::Update()
{
	
}

//========================
//描画処理
//========================
void CObject3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&GetMtxWorld());

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);

	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//フィールドの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================
//オブジェクト3D生成
//========================
CObject3D* CObject3D::Create(void)
{
	CObject3D* pObject3D = DBG_NEW CObject3D;

	pObject3D->Init();

	return pObject3D;
}

//========================
//テクスチャ割り当て
//========================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//========================
//大きさ設定
//========================
void CObject3D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//========================
//サイズ取得
//========================
D3DXVECTOR3& CObject3D::GetSize(void)
{
	return m_size;
}

//========================
///色の設定
//========================
void CObject3D::SetCor(D3DXCOLOR cor)
{
	m_cor = cor;
}