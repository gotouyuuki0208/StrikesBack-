//==========================
// 
// レンダラー[renderer.h]
// Author Yuki Goto
//
//==========================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//レンダラークラスの定義
class CRenderer
{
public:
	//定数
	static const int NUM_EXPLANATION;//デバッグ表示の数

	//メンバ関数
	CRenderer();//コンストラクタ
	~CRenderer();//デストラクタ
	HRESULT Init(HWND hWnd, BOOL bWindow);//初期設定
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw();//描画処理
	LPDIRECT3DDEVICE9 GetDevice();//3Dデバイスの取得
private:

	//メンバ関数
	void DrawDebug();//デバッグ表示

	//メンバ変数
	LPDIRECT3D9 m_pD3D;//Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;//Direct3Dデバイス
	LPD3DXFONT g_pFont;
};

#endif 