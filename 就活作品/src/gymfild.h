//==========================
// 
// 縁石[curb.h]
// Author Yuki Goto
//
//==========================
#ifndef _GYMFILD_H_
#define _GYMFILD_H_

//include
#include "fild.h"

//クラスの定義
class CGymFild :public CFild
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CGymFild(int nPriority = PRIORITY);//コンストラクタ
	~CGymFild() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CGymFild* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif