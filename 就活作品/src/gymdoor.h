//==========================
// 
// 体育館壁[gymdoor.h]
// Author Yuki Goto
//
//==========================
#ifndef _GYMDOOR_H_
#define _GYMDOOR_H_

//include
#include "building.h"

//クラスの定義
class CGymDoor :public CBuilding
{
public:

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CGymDoor(int nPriority = PRIORITY);//コンストラクタ
	~CGymDoor() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CGymDoor* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif