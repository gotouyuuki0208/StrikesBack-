//==========================
// 
// 自転車[bicycle.h]
// Author Yuki Goto
//
//==========================
#ifndef _BICYCLE_H_
#define _BICYCLE_H_

//include
#include "bigweapon.h"

//クラスの定義
class CBicycle :public CBigWeapon
{
public:
	
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CBicycle(int nPriority = PRIORITY);//コンストラクタ
	~CBicycle() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBicycle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif