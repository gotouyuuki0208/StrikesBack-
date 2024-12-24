//==========================
// 
// モデルのパーツの処理[modelparts.h]
// Author Yuki Goto
//
//==========================

//include
#include"modelparts.h"
#include"manager.h"

//==========================
// コンストラクタ
//==========================
CModelParts::CModelParts(void)
{
	m_ParentParts = nullptr;
	m_modelIdx = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_motionpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_motionrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;//マテリアルへのポインタ
	m_dwNumMat = 0;//マテリアルの数
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_corDamage = false;
	D3DXMatrixIdentity(&m_mtxWorld);

	for (int i = 0; i < 100; i++)
	{
		m_Diffuse[i] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	m_Visual = nullptr;
}

//==========================
// デストラクタ
//==========================
CModelParts::~CModelParts(void)
{

}

//==========================
// 初期設定
//==========================
HRESULT CModelParts::Init(void)
{
	SetSize();
	return S_OK;
}

//==========================
// 終了処理
//==========================
void CModelParts::Uninit(void)
{

	if (m_Visual != nullptr)
	{
		m_Visual-> Uninit();
		m_Visual = nullptr;
	}

	delete this;
}

//==========================
// 更新処理
//==========================
void CModelParts::Update(void)
{
	
}

//==========================
// 描画処理
//==========================
void CModelParts::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	CreateMtx();//行列の作成

	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxTransMotion;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	D3DXMATRIX mtxParent;

	if (m_ParentParts != nullptr)
	{
		mtxParent = m_ParentParts->m_mtxWorld;
	}
	else
	{
		//スケール設定
		D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);


		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマトリックスを取得
	pDevice->GetMaterial(&matDef);

	//法線の長さを1にする
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (m_corDamage)
		{
			pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (!m_corDamage)
		{
			pMat[nCntMat].MatD3D.Diffuse = m_Diffuse[nCntMat];
		}
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	if (m_Visual != nullptr)
	{
		m_Visual->SetPos(D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43));
		m_Visual->Draw();
	}
}

//========================
//行列の生成
//========================
void CModelParts::CreateMtx()
{
	D3DXMATRIX mtxRot, mtxTrans, mtxTransMotion;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMatrixTranslation(&mtxTransMotion, m_motionpos.x, m_motionpos.y, m_motionpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransMotion);
	
}

//========================
//オブジェクト2D生成
//========================
CModelParts* CModelParts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelParts* Parent, int ModelPartsNum, D3DXVECTOR3 scale)
{
	CModelParts* pModelParts = DBG_NEW CModelParts;

	//位置設定
	pModelParts->m_pos = pos;
	pModelParts->m_rot = rot;
	pModelParts->SetParents(Parent);
	pModelParts->m_scale = scale;

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();

	//モデルの番号を保存
	pModelParts->m_modelIdx = ModelPartsNum;

	pModelParts->m_pMesh = pModel->GetMeshAdress(ModelPartsNum);
	pModelParts->m_pBuffMat = pModel->GetBuffMatAdress(ModelPartsNum);
	pModelParts->m_dwNumMat = pModel->GetNumMatAdress(ModelPartsNum);

	for (int i = 0; i < (int)pModelParts->m_dwNumMat; i++)
	{
		pModelParts->m_Diffuse[i] = pModel->GetDiffuse(ModelPartsNum, i);
	}

	//初期化処理
	if (SUCCEEDED(pModelParts->Init()))
	{

	}

	return pModelParts;
}

//========================
//親モデルの設定
//========================
void CModelParts::SetParents(CModelParts* Parent)
{
	m_ParentParts = Parent;
}

//========================
//親モデルを取得
//========================
CModelParts* CModelParts::GetParent()
{
	return m_ParentParts;
}

//========================
//位置の設定
//========================
void CModelParts::SetMotionPos(D3DXVECTOR3 pos)
{
	m_motionpos = pos;
}

//========================
//モーションでの位置の取得
//========================
D3DXVECTOR3& CModelParts::GetMotionPos()
{
	return m_motionpos;
}

//========================
//位置の設定
//========================
void CModelParts::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================
//向きの設定
//========================
void CModelParts::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================
//位置の取得
//========================
D3DXVECTOR3& CModelParts::GetPos()
{
	return m_pos;
}

//========================
//向きの取得
//========================
D3DXVECTOR3& CModelParts::GetRot()
{
	return m_rot;
}

//========================
//親パーツがあるかの取得
//========================
bool CModelParts::GetExistParent()
{
	if (m_ParentParts == nullptr)
	{
		return false;
	}

	return true;
}

//==========================
//マトリックス取得
//==========================
D3DXMATRIX& CModelParts::GetMtxWorld()
{
	return m_mtxWorld;
}

//==========================
//サイズの設定
//==========================
void CModelParts::SetSize()
{
	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		vtx.x *= m_scale.x;
		vtx.y *= m_scale.y;
		vtx.z *= m_scale.z;
		//最大の頂点を取得
		if (vtx.x > m_vtxMax.x)
		{
			m_vtxMax.x = floor(vtx.x);
		}
		if (vtx.y > m_vtxMax.y)
		{
			m_vtxMax.y = floor(vtx.y);
		}
		if (vtx.z > m_vtxMax.z)
		{
			m_vtxMax.z = floor(vtx.z);
		}

		//最小の頂点を取得
		if (vtx.x < m_vtxMin.x)
		{
			m_vtxMin.x = floor(vtx.x);
		}
		if (vtx.y < m_vtxMin.y)
		{
			m_vtxMin.y = floor(vtx.y);
		}

		if (vtx.z < m_vtxMin.z)
		{
			m_vtxMin.z = floor(vtx.z);
		}

		pVtxBuff += sizeFVF;
	}

	//頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();

	//サイズを設定
	/*m_vtxMax.x *= SCALIING;
	m_vtxMin.x *= SCALIING;
	m_vtxMax.y *= SCALIING;
	m_vtxMin.y *= SCALIING;
	m_vtxMax.z *= SCALIING;
	m_vtxMin.z *= SCALIING;*/

	m_Size.x = m_vtxMax.x - m_vtxMin.x;
	m_Size.y = m_vtxMax.y - m_vtxMin.y;
	m_Size.z = m_vtxMax.z - m_vtxMin.z;
}

//==========================
//頂点の最小の場所を取得
//==========================
D3DXVECTOR3& CModelParts::GetVtxMin()
{
	return m_vtxMin;
}

//==========================
//頂点の最大の場所を取得
//==========================
D3DXVECTOR3& CModelParts::GetVtxMax()
{
	return m_vtxMax;
}

//==========================
//色の設定
//==========================
void CModelParts::SetCor()
{
	m_corDamage = !m_corDamage;
}

//==========================
//モデルの番号を取得
//==========================
int CModelParts::GetModelNum()
{
	return m_modelIdx;
}

//==========================
//当たり判定を可視化するメッシュを生成
//==========================
void CModelParts::CreateVisual(D3DXVECTOR3 pos, float radius)
{
	if (m_Visual == nullptr)
	{
		m_Visual = CCollisionVisual::Create(pos, radius);
		return;
	}

	if (m_Visual->GetRadius() != radius)
	{
		m_Visual->Uninit();
		m_Visual = CCollisionVisual::Create(pos, radius);
	}
}

//==========================
//当たり判定の見た目を削除
//==========================
void CModelParts::VisualDelete()
{
	if (m_Visual != nullptr)
	{
		m_Visual->Uninit();
		m_Visual = nullptr;
	}
}

//==========================
//可視化した当たり判定の情報
//==========================
CCollisionVisual* CModelParts::GetVisual()
{
	if (m_Visual != nullptr)
	{
		return m_Visual;
	}

	return nullptr;
}