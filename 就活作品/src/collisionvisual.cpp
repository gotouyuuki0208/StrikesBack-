//==========================
// 
// 当たり判定可視化[collisionvisual.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "collisionvisual.h"
#include "manager.h"

//==========================
//コンストラクタ
//==========================
CCollisionVisual::CCollisionVisual():
m_pMesh(nullptr),//メッシュ(頂点情報)へのポインタ
m_radius(0.0f),//半径
m_pos(0.0f,0.0f,0.0f),//位置
m_rot(0.0f, 0.0f, 0.0f),//向き
m_mtxWorld()//ワールドマトリックス
{
	m_cor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//==========================
//デストラクタ
//==========================
CCollisionVisual::~CCollisionVisual()
{

}

//==========================
//初期化処理
//==========================
HRESULT CCollisionVisual::Init()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得
	D3DXCreateSphere(pDevice, m_radius, 10, 7, &m_pMesh, NULL);//球のメッシュ生成

	SetColNomal();//通常の色に設定

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CCollisionVisual::Uninit()
{
	//メッシュの破棄
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	delete this;
}

//==========================
//更新処理
//==========================
void CCollisionVisual::Update()
{

}

//==========================
//描画処理
//==========================
void CCollisionVisual::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL Mat{};//マテリアル

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマトリックスを取得
	pDevice->GetMaterial(&matDef);

	//法線の長さを1にする
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//色の設定
	Mat.MatD3D.Diffuse = m_cor;

	//マテリアルの設定
	pDevice->SetMaterial(&Mat.MatD3D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//描画
	m_pMesh->DrawSubset(0);

	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//==========================
//オブジェクト生成
//==========================
CCollisionVisual* CCollisionVisual::Create(D3DXVECTOR3 pos, float radius)
{
	//インスタンス生成
	CCollisionVisual* pVisualization = DBG_NEW CCollisionVisual;

	//位置の設定
	pVisualization->m_pos = pos;

	//半径の設定
	pVisualization->m_radius = radius;
	
	//初期化処理
	pVisualization->Init();

	return pVisualization;
}

//==========================
//位置の設定
//==========================
void CCollisionVisual::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==========================
//通常の色に設定
//==========================
void CCollisionVisual::SetColNomal()
{
	m_cor = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.3f);
}

//==========================
//衝突しているときの色に設定
//==========================
void CCollisionVisual::SetColCollision()
{
	m_cor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);
}

//==========================
//半径を取得
//==========================
float CCollisionVisual::GetRadius()
{
	return m_radius;
}

//==========================
//位置を取得
//==========================
D3DXVECTOR3& CCollisionVisual::GetPos()
{
	return m_pos;
}