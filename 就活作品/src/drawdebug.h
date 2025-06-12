//==========================
// 
// デバッグ表示[drawdebug.h]
// Author Yuki Goto
//
//==========================
#ifndef _DRAWDEBUG_H_
#define _DRAWDEBUG_H_

//クラスの定義
class CDrawDebug
{
public:

	//メンバ関数
	CDrawDebug();//コンストラクタ
	~CDrawDebug();//デストラクタ
	HRESULT Init();//初期化処理
	void Uninit();//終了処理
	static void DrawDebug();//描画処理
private:

	//メンバ変数
	LPD3DXFONT m_pFont;
};

#endif