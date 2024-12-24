//==========================
// 
// 背景処理[bg.h]
// Author Yuki Goto
//
//==========================
#ifndef _BG_H_
#define _BG_H_

//include
#include "object2D.h"

//クラスの定義
class CBg:public CObject2D
{
public:
	//定数
	static const int PRIORITY;

	//メンバ関数
	CBg(int nPriority = PRIORITY);//コンストラクタ
	~CBg()override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	static CBg* Create(const char texname[256]);//オブジェクト2D生成
private:
	static int m_nTexIdx;//テクスチャID
};

#endif 
