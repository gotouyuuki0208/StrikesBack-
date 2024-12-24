//==========================
// 
// 操作説明UIの背景[UIbg.h]
// Author Yuki Goto
//
//==========================
#ifndef _UIBG_H_
#define _UIBG_H_

//include
#include "object2D.h"

//クラスの定義
class CUIBg :public CObject2D
{
public:
	//定数
	static const int PRIORITY;

	//メンバ関数
	CUIBg(int nPriority = PRIORITY);//コンストラクタ
	~CUIBg()override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	static CUIBg* Create(D3DXVECTOR3 pos);//オブジェクト2D生成
private:
};

#endif 
