//==========================
// 
// ステージ遷移位置[stagechangepoint.h]
// Author Yuki Goto
//
//==========================
#ifndef _STAGECHANGEPOINT_H_
#define _STAGECHANGEPOINT_H_

//include
#include "fild.h"
#include "goalpoint.h"

//クラスの定義
class CStageChangePoint :public CFild
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CStageChangePoint(int nPriority = PRIORITY);//コンストラクタ
	~CStageChangePoint() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CStageChangePoint* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//オブジェクト生成
private:

	//メンバ関数
	void ColisionPlayer();//プレイヤーとの当たり判定

	//メンバ変数
	CGoalPoint* m_GoalPoint;//ステージ遷移位置の位置表示
};
#endif