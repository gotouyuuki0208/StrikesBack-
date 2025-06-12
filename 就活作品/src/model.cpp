//==========================
// 
// モデル管理[model.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"model.h"
#include"manager.h"
#include"texture.h"

//==========================
// コンストラクタ
//==========================
CModel::CModel(void)
{
	for (int i = 0; i < NUM_MODEL; i++)
	{
		m_pBuffMat[i] = nullptr;
		m_pMesh[i] = nullptr;
		m_dwNumMat[i] = 0;
		m_aModelName[i].clear();

		for (int n = 0; n < NUM_MODEL; n++)
		{
			m_Diffuse[i][n] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			m_apTexture[i][n] = nullptr;
		}
	}

	m_numAll = 0;
}

//==========================
// デストラクタ
//==========================
CModel::~CModel(void)
{

}

//==========================
//モデルのアンロード
//==========================
void CModel::UnLoad(void)
{
	for (int i = 0; i < NUM_MODEL; i++)
	{
		if (m_pBuffMat[i] != nullptr)
		{
			m_pBuffMat[i]->Release();
			m_pBuffMat[i] = nullptr;
		}

		if (m_pMesh[i] != nullptr)
		{
			m_pMesh[i]->Release();
			m_pMesh[i] = nullptr;
		}

		for (int n = 0; n < NUM_MODEL; n++)
		{
			if (m_apTexture[i][n] != nullptr)
			{
				m_apTexture[i][n]->Release();
				m_apTexture[i][n] = nullptr;
			}
		}

		m_aModelName[i].clear();

	}
}

//==========================
//モデル登録
//==========================
int CModel::Regist(const char* pModelName)
{
	int nIdx = 0;//モデルID

	for (int i = 0; i < NUM_MODEL; i++)
	{
		if (m_dwNumMat[i] == 0)
		{//登録されてない
			LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
			pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

			//モデルの読み込み
			D3DXLoadMeshFromX(pModelName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[i], NULL, &m_dwNumMat[i], &m_pMesh[i]);
			m_aModelName[i] = pModelName;//モデルの名前を保存
			nIdx = i;//ID設定
			m_numAll++;//モデル数

			D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[i]->GetBufferPointer();//マテリアルデータへのポインタを取得

			//モデルのテクスチャ読み込み
			for (int nCntMat = 0; nCntMat < (int)m_dwNumMat[i]; nCntMat++)
			{
				//色を保存
				m_Diffuse[i][nCntMat] = pMat[nCntMat].MatD3D.Diffuse;

				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					//CTexture* pTex = CManager::GetInstance()->GetTexture();
					//m_TexIdx[i] = pTex->Regist(pMat[nCntMat].pTextureFilename);
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&m_apTexture[i][nCntMat]);

				}
			}

			break;
		}
		else if (pModelName == m_aModelName[i])
		{//既に生成したモデルと一致した

			nIdx = i;//ID設定
			break;
		}
	}

	return nIdx;
}

//==========================
//モデルのメッシュ取得
//==========================
LPD3DXMESH CModel::GetMeshAdress(int nIdx)
{
	return m_pMesh[nIdx];
}

//==========================
//モデルのマテリアル取得
//==========================
LPD3DXBUFFER CModel::GetBuffMatAdress(int nIdx)
{	
	return m_pBuffMat[nIdx];
}

//==========================
//モデルのマテリアルの数取得
//==========================
DWORD CModel::GetNumMatAdress(int nIdx)
{
	 return m_dwNumMat[nIdx];
}

//==========================
//モデルの色
//==========================
D3DCOLORVALUE CModel::GetDiffuse(int nIdx, int CorNum)
{
	return m_Diffuse[nIdx][CorNum];
}

//==========================
//テクスチャ
//==========================
LPDIRECT3DTEXTURE9* CModel::GetTexIdx(int nIdx)
{
	return &m_apTexture[nIdx][0];
}
