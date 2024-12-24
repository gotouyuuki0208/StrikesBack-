//==========================
// 
// テクスチャ管理[texture.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"texture.h"
#include"manager.h"

//==========================
// コンストラクタ
//==========================
CTexture::CTexture(void)
{
	for (int i = 0; i < NUM_TEX; i++)
	{
		m_apTexture[i] = nullptr;
		m_aTextureName[i].clear();
	}
	
	m_numAll = 0;
}

//==========================
// デストラクタ
//==========================
CTexture::~CTexture(void)
{

}

//==========================
//テクスチャのアンロード
//==========================
void CTexture::UnLoad(void)
{
	for (int i = 0; i < NUM_TEX; i++)
	{
		if (m_apTexture[i] != nullptr)
		{
			m_apTexture[i]->Release();
			m_apTexture[i] = nullptr;
		}

		m_aTextureName[i].clear();
	}
}

//==========================
//テクスチャ登録
//==========================
int CTexture::Regist(const char* pTextureName)
{
	int nIdx = 0;//テクスチャID

	for (int i = 0; i < NUM_TEX; i++)
	{
		if (m_apTexture[i] == nullptr)
		{//登録されてない
			LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
			pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pTextureName, &m_apTexture[i]);
			m_aTextureName[i] = pTextureName;//テクスチャの名前を保存
			nIdx = i;//ID設定
			m_numAll++;//テクスチャ数
			break;
		}
		else if (pTextureName == m_aTextureName[i])
		{//既に生成したテクスチャと一致した

			nIdx = i;//ID設定
			break;
		}
	}

	return nIdx;
}

//==========================
//テクスチャ取得
//==========================
LPDIRECT3DTEXTURE9 CTexture::GetAdress(int nIdx)
{
	return m_apTexture[nIdx];
}