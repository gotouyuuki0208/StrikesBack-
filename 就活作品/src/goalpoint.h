//==========================
// 
// ステージ遷移位置の位置表示[goalpoint.h]
// Author Yuki Goto
//
//==========================
#ifndef _GOALPOINT_H_
#define _GOALPOINT_H_

//include
#include "billboard.h"

//クラスの定義
class CGoalPoint :public CBillBoard
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CGoalPoint(int nPriority = PRIORITY);//コンストラクタ
	~CGoalPoint() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CGoalPoint* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//オブジェクト生成
private:
	int m_nTexIdx;//テクスチャの番号
};
#endif