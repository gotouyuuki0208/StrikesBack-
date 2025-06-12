//==========================
// 
// タイトルロゴ[TitleLogo.h]
// Author Yuki Goto
//
//==========================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

//include
#include "object2D.h"

//クラスの定義
class CTitleLogo :public CObject2D
{
public:
	//定数
	static const int PRIORITY;

	//メンバ関数
	CTitleLogo(int nPriority = PRIORITY);//コンストラクタ
	~CTitleLogo()override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	static CTitleLogo* Create(D3DXVECTOR3 pos);//オブジェクト2D生成
private:
	static int m_nTexIdx;//テクスチャID
};

#endif 
