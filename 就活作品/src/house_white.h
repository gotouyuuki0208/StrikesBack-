//==========================
// 
// 白い家[house_white.h]
// Author Yuki Goto
//
//==========================
#ifndef _HOUSE_WHITE_H_
#define _HOUSE_WHITE_H_

//include
#include "building.h"

//クラスの定義
class CHouseWhite :public CBuilding
{
public:

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CHouseWhite(int nPriority = PRIORITY);//コンストラクタ
	~CHouseWhite() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CHouseWhite* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif