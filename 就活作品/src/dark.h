//==========================
// 
// 背景処理[bg.h]
// Author Yuki Goto
//
//==========================
#ifndef _DARK_H_
#define _DARK_H_

//include
#include "object2D.h"

//クラスの定義
class CDark :public CObject2D
{
public:
	//定数
	static const int PRIORITY;

	//メンバ関数
	CDark(int nPriority = PRIORITY);//コンストラクタ
	~CDark()override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	static CDark* Create();//オブジェクト2D生成
private:
};

#endif 
