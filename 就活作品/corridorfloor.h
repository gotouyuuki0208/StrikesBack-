//==========================
// 
// 廊下の床[corridorfloor.h]
// Author Yuki Goto
//
//==========================
#ifndef _CORRIDORFLOOR_H_
#define _CORRIDORFLOOR_H_

//include
#include "building.h"

//クラスの定義
class CCorridorfloor :public CBuilding
{
public:

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CCorridorfloor(int nPriority = PRIORITY);//コンストラクタ
	~CCorridorfloor() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CCorridorfloor* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif