//==========================
// 
// 体育館天井[corridorfloor.h]
// Author Yuki Goto
//
//==========================
#ifndef _GYMCEILING_H_
#define _GYMCEILING_H_

//include
#include "building.h"

//クラスの定義
class CGymCeiling :public CBuilding
{
public:

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CGymCeiling(int nPriority = PRIORITY);//コンストラクタ
	~CGymCeiling() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CGymCeiling* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif