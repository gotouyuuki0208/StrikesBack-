//==========================
// 
// ライト処理[light.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "light.h"
#include"manager.h"

//========================
//コンストラクタ
//========================
CLight::CLight()
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		//ライトの情報を初期化する
		ZeroMemory(&m_aLight[i], sizeof(D3DLIGHT9));
	}
}

//========================
//デストラクタ
//========================
CLight::~CLight()
{

}

//========================
//初期設定
//========================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	D3DXVECTOR3 vecDir;//設定用方向ベクトル

	float x = 0.0f, y = 0.0f, z = 0.0f;

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{

		//ライトの種類を設定
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		switch (nCnt)
		{
		case 0:
			x = 0.0f;
			y = -1.0f;
			z = 0.0f;
			break;

		case 1:
			x = 0.0f;
			y = 1.0f;
			z = 0.0f;
			break;

		case 2:
			x = 1.5f;
			y = -1.0f;
			z = 1.0f;
			break;

		case 3:
			x = -1.5f;
			y = -1.0f;
			z = -1.0f;
			break;

		default:
			break;
		}

		//ライトの方向を設定
		vecDir = D3DXVECTOR3(x, y, z);
		D3DXVec3Normalize(&vecDir, &vecDir);
		m_aLight[nCnt].Direction = vecDir;

		//ライトを設定する
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		//ライトを有効にする
		pDevice->LightEnable(nCnt, TRUE);

	}

	return S_OK;
}

//========================
//終了処理
//========================
void CLight::Uninit(void)
{

}

//========================
//更新処理
//========================
void CLight::Update()
{

}