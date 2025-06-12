//==========================
// 
// 回復アイテム[item.h]
// Author Yuki Goto
//
//==========================
#ifndef _ITEM_H_
#define _ITEM_H_

//include
#include "objectX.h"

//クラスの定義
class CItem :public CObjectX
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CItem(int nPriority = PRIORITY);//コンストラクタ
	~CItem() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	int GetModelIdx();//モデルの番号を取得
	void SetModelIdx(int Idx);//モデルの番号を設定

private:

	//メンバ関数
	void ColisionPlayer();//プレイヤーとの当たり判定

	//メンバ変数
	int m_nModelIdx;//モデルの番号
};
#endif