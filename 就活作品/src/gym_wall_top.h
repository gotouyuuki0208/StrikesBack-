//==========================
// 
// 体育館壁上部[gym_wall_top.h]
// Author Yuki Goto
//
//==========================
#ifndef _GYM_WALL_TOP_H_
#define _GYM_WALL_TOP_H_

//include
#include "building.h"

//クラスの定義
class CGymwalltop :public CBuilding
{
public:

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CGymwalltop(int nPriority = PRIORITY);//コンストラクタ
	~CGymwalltop() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CGymwalltop* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif