//==========================
// 
// 自転車[bicycle.h]
// Author Yuki Goto
//
//==========================
#ifndef _CONE_H_
#define _CONE_H_

//include
#include "bigweapon.h"

//クラスの定義
class CCone :public CBigWeapon
{
public:

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CCone(int nPriority = PRIORITY);//コンストラクタ
	~CCone() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CCone* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif