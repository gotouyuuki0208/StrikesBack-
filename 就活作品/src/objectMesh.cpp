//==========================
// 
// メッシュポリゴンの描画処理[objectMesh.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"objectMesh.h"
#include"manager.h"
#include"texture.h"

//静的メンバ初期化
const int CObjectMesh::PRIORITY = 0;//描画優先度

//========================
//コンストラクタ
//========================
CObjectMesh::CObjectMesh(int nPriority) :
CObjectgame(nPriority),
m_pTexture(nullptr),
m_pVtxBuff(nullptr),
m_pIdxBuff(nullptr),
m_size{},
m_WidthDiv(0),
m_VerticalDiv(0),
m_NumVtx(0),
m_NumIdx(0),
m_nTexIdx(0)
{

}

//========================
//デストラクタ
//========================
CObjectMesh::~CObjectMesh()
{

}

//========================
//初期設定
//========================
HRESULT CObjectMesh::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//頂点数の算出
	m_NumVtx = (m_WidthDiv + 1) * (m_VerticalDiv + 1);

	//インデックス数の算出
	m_NumIdx = ((m_WidthDiv + 1) * 2) * m_VerticalDiv + (2 * (m_VerticalDiv - 1));

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_NumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファへのポインタ
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_NumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	SetInit();//頂点情報の初期設定
	
	SeIdx();//インデックスバッファの設定

	return S_OK;
}

//========================
//終了処理
//========================
void CObjectMesh::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{//頂点バッファの解放
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pIdxBuff != nullptr)
	{//インデックスバッファの解放
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	if (m_pTexture != nullptr)
	{//テクスチャの解放
		m_pTexture = nullptr;
	}

	Release();
}

//========================
//更新処理
//========================
void CObjectMesh::Update()
{

}

//========================
//描画処理
//========================
void CObjectMesh::Draw()
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
	D3DXMatrixTranslation(&mtxTrans,GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	GetMtxWorld()._41 = 0.0f;
	GetMtxWorld()._42 = 0.0f;
	GetMtxWorld()._43 = 0.0f;

	//カリングをオフにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームの設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴン数
	int polygon = ((m_VerticalDiv * m_WidthDiv) * 2) + (4 * (m_VerticalDiv - 1));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumVtx, 0, polygon);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//========================
//オブジェクトMesh生成
//========================
CObjectMesh* CObjectMesh::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Width, int Vertical)
{
	CObjectMesh* pObjectMesh = DBG_NEW CObjectMesh;

	//位置の設定
	pObjectMesh->SetPos(pos);

	//サイズの設定
	pObjectMesh->SetSize(size);

	//横の分割数
	pObjectMesh->SetWidthDiv(Width);

	//縦の分割数
	pObjectMesh->SetVerticalDiv(Vertical);

	//初期設定
	pObjectMesh->Init();

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pObjectMesh->m_nTexIdx = pTex->Regist("data\\TEXTURE\\effect000.png");
	pObjectMesh->BindTexture(pTex->GetAdress(pObjectMesh->m_nTexIdx));

	return pObjectMesh;
}

//========================
//頂点バッファの設定
//========================
void CObjectMesh::SetInit()
{
	VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の横幅を算出
	float Width = (m_size.x * 2) / m_WidthDiv;

	//頂点の縦幅を算出
	float Height = (m_size.y * 2) / m_VerticalDiv;

	//頂点の縦幅を算出
	float Vertical = (m_size.z * 2) / m_VerticalDiv;
	
	//頂点の横の位置
	int WidthPos = 0;

	//頂点の縦の位置
	int VerticalPos = 0;

	//頂点座標の設定
	for (int i = 0; i < m_NumVtx; i++)
	{
		pVtx[i].pos = D3DXVECTOR3(-m_size.x + (Width * WidthPos), m_size.y + (-Height * VerticalPos), m_size.z - (Vertical * VerticalPos));
		if (WidthPos == m_WidthDiv)
		{//頂点の横幅が最後になった
			WidthPos = 0;
			VerticalPos++;
		}
		else
		{
			WidthPos++;
		}
	}

	//法線ベクトルの設定
	for (int i = 0; i < m_NumVtx; i++)
	{
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	//頂点カラーの設定
	for (int i = 0; i < m_NumVtx; i++)
	{
		pVtx[i].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f);
	}
	

	Width = 1.0f / m_WidthDiv;
	Vertical = 1.0f / m_VerticalDiv;
	WidthPos = 0;
	VerticalPos = 0;
	//テクスチャ座標の設定
	for (int i = 0; i < m_NumVtx; i++)
	{
		pVtx[i].tex = D3DXVECTOR2(0.0f + (Width * WidthPos), 0.0f + (-Vertical * VerticalPos));
		if (WidthPos == m_WidthDiv)
		{//頂点の横幅が最後になった
			WidthPos = 0;
			VerticalPos++;
		}
		else
		{
			WidthPos++;
		}
	}
	
	
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//========================
//インデックスバッファの設定
//========================
void CObjectMesh::SeIdx()
{
	//インデックスバッファのロック
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
	int IdxNum = 0;

	for (int i = 0; i < m_VerticalDiv; i++)
	{//縦の分割数

		for (int n = 0; n < m_WidthDiv+1; n++)
		{//横の分割数
			pIdx[IdxNum] = (m_WidthDiv + 1) * (i + 1) + n;
			pIdx[IdxNum + 1] = (m_WidthDiv + 1) * i + n;
			IdxNum += 2;
		}

		if (i != m_VerticalDiv - 1)
		{
			pIdx[IdxNum] = (m_WidthDiv + 1) * (1 + i) - 1;
			pIdx[IdxNum + 1] = (m_WidthDiv + 1) * (2 + i);
			IdxNum += 2;
		}
	}

	for (int i = 0; i < m_NumIdx; i++)
	{
		int a = pIdx[i];
		a = 0;
	}

	//インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();
}

//========================
//縦の分割数を設定
//========================
void CObjectMesh::SetVerticalDiv(int vertical)
{
	m_VerticalDiv = vertical;
}

//========================
//縦の分割数を取得
//========================
int CObjectMesh::GetVerticalDiv()
{
	return m_VerticalDiv;
}

//========================
//横の分割数を設定
//========================
void CObjectMesh::SetWidthDiv(int width)
{
	m_WidthDiv = width;
}

//========================
//横の分割数を設定
//========================
int CObjectMesh::GetWidthDiv()
{
	return m_WidthDiv;
}

//========================
//サイズを設定
//========================
void CObjectMesh::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//========================
//サイズを取得
//========================
D3DXVECTOR3& CObjectMesh::GetSize()
{
	return m_size;
}

//========================
//頂点バッファを取得
//========================
LPDIRECT3DVERTEXBUFFER9& CObjectMesh::GetVtxBuff()
{
	return m_pVtxBuff;
}

//========================
//頂点数の取得
//========================
int CObjectMesh::GetNumVtx()
{
	return m_NumVtx;
}

//========================
//テクスチャ割り当て
//========================
void CObjectMesh::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}