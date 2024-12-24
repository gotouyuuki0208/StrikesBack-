//==========================
// 
// レンダラー[renderer.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"renderer.h"
#include"main.h"
#include"object2D.h"
#include"manager.h"

//静的メンバ初期化
const int CRenderer::NUM_EXPLANATION = 25;//デバッグ表示の最大数
///========================
//コンストラクタ
//========================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	g_pFont = nullptr;
}

//========================
//デストラクタ
//========================
CRenderer::~CRenderer()
{

}

//========================
//初期設定
//========================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//ゲーム画面サイズ(幅)

	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//ゲーム画面サイズ(高さ)

	d3dpp.BackBufferFormat = d3ddm.Format;//バックバッファの形式

	d3dpp.BackBufferCount = 1;//バックバッファの数

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//ダブルバッファの切り替え(映像信号に同期)

	d3dpp.EnableAutoDepthStencil = TRUE;//デプスバッファとステンシルバッファを作成

	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//デプスバッファとして16bitを使う

	d3dpp.Windowed = bWindow;//ウインドウモード

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//リフレッシュレート

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理はハードウェア、頂点処理はCPUで行う)
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//デバック表示用のフォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}

//========================
//終了処理
//========================
void CRenderer::Uninit(void)
{

	//Direct3Dデバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	//Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}

	//デバック表示用フォントの破棄
	if (g_pFont != nullptr)
	{
		g_pFont->Release();
		g_pFont = nullptr;
	}

}

//========================
//更新処理
//========================
void CRenderer::Update()
{
	CObject::UpdateAll();
}

//========================
//描画処理
//========================
void CRenderer::Draw()
{
	//画面クリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 170, 255, 0), 1.0f, 0);
	//m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 0), 1.0f, 0);
	
	//描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		//カメラの設定
		CManager::GetInstance()->GetCamera()->SetCamera();

		//全オブジェクト描画
		CObject::DrawAll();

#ifdef _DEBUG
		//デバッグ表示
		DrawDebug();
#endif 

		//描画の終了
		m_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//========================
//3Dデバイスの取得
//========================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

//========================
//デバッグ表示
//========================
void CRenderer::DrawDebug(void)
{
	RECT rect[NUM_EXPLANATION];
	char aStr[NUM_EXPLANATION][256];

	for (int nCnt = 0; nCnt < NUM_EXPLANATION; nCnt++)
	{
		rect[nCnt] = { 0,20 * nCnt,SCREEN_WIDTH ,SCREEN_HEIGHT };
	}

	//文字列に代入
	wsprintf(&aStr[0][0], "FPS:%d\n", GetFps());
	wsprintf(&aStr[1][0], "視点回転:Z,C\n");
	wsprintf(&aStr[2][0], "殴る:J\n");
	wsprintf(&aStr[3][0], "武器を拾う:O\n");
	wsprintf(&aStr[4][0], "武器を捨てる:P\n");
	wsprintf(&aStr[5][0], "ガード:B\n");
	wsprintf(&aStr[6][0], "プレイヤーのデバッグ:F1\n");
	wsprintf(&aStr[7][0], "ボスのデバッグ:F2\n");
	wsprintf(&aStr[8][0], "ステージ編集:F4\n");
	wsprintf(&aStr[9][0], "移動:W,A,S,D\n");
	wsprintf(&aStr[10][0], "配置:SPACE\n");
	wsprintf(&aStr[11][0], "モデルのスケール変更:1,2\n");
	wsprintf(&aStr[12][0], "前のオブジェクトに移動:3\n");
	wsprintf(&aStr[13][0], "次のオブジェクトに移動:4\n");
	wsprintf(&aStr[14][0], "最初のオブジェクトに移動:5\n");
	wsprintf(&aStr[15][0], "最後のオブジェクトに移動:6\n");
	wsprintf(&aStr[16][0], "オブジェクトを削除:7\n");
	wsprintf(&aStr[17][0], "WASDの操作を変更(位置と向き):8\n");
	wsprintf(&aStr[18][0], "カメラの位置を変更:9\n");
	wsprintf(&aStr[19][0], "WSの操作を変更(Z軸とY軸):O\n");
	wsprintf(&aStr[20][0], "保存:M\n");
	wsprintf(&aStr[21][0], "TriggerとPressを切り替え:↓\n");
	wsprintf(&aStr[22][0], "オブジェクトの種類を切り替え:←,→\n");
	wsprintf(&aStr[23][0], "編集モードを切り替え(新規配置と配置済み):↑\n");
	wsprintf(&aStr[24][0], "ステージを切り替え:V\n");

	//テキストの描画
	for (int nCnt = 0; nCnt < NUM_EXPLANATION; nCnt++)
	{
		g_pFont->DrawText(NULL, &aStr[nCnt][0], -1, &rect[nCnt], DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
	}

}