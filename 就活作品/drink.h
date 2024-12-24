//==========================
// 
// 飲み物[drink.h]
// Author Yuki Goto
//
//==========================
#ifndef _DRINK_H_
#define _DRINK_H_

//include
#include "item.h"

//クラスの定義
class CDrink :public CItem
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CDrink(int nPriority = PRIORITY);//コンストラクタ
	~CDrink() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CDrink* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
private:
};
#endif