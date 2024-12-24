//==========================
// 
// デバッグ表示[drawdebug.h]
// Author Yuki Goto
//
//==========================
#include"drawdebug.h"
#include"manager.h"

//==========================
//コンストラクタ
//==========================
CDrawDebug::CDrawDebug():
m_pFont(nullptr)
{

}

//==========================
//デストラクタ
//==========================
CDrawDebug::~CDrawDebug()
{

}

//==========================
//初期化処理
//==========================
HRESULT CDrawDebug::Init()
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//デバック表示用のフォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	return S_OK;
}

//==========================
//終了処理
//==========================
void CDrawDebug::Uninit()
{
	if (m_pFont != nullptr)
	{
		m_pFont = nullptr;
	}
}

//==========================
//描画処理
//==========================
void CDrawDebug::DrawDebug()
{

}