//==========================
// 
// 敵の移動地点[enemymovepoint.h]
// Author Yuki Goto
//
//==========================
#ifndef _ENEMYMOVEPOINT_H_
#define _ENEMYMOVEPOINT_H_

//include
#include "fild.h"

//クラスの定義
class CEnemyMovePoint :public CFild
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CEnemyMovePoint(int nPriority = PRIORITY);//コンストラクタ
	~CEnemyMovePoint() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CEnemyMovePoint* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif