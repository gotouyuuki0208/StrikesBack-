//==========================
// 
// 建物[building.h]
// Author Yuki Goto
//
//==========================
#ifndef _BUILDING_H_
#define _BUILDING_H_

//include
#include "objectX.h"

//クラスの定義
class CBuilding :public CObjectX
{
public:
	enum class BUILDING_TYPE
	{
		NONE = 0,
		BUILDING,//ビル
		APARTMENT,//アパート
		CONVENI,//コンビニ
		HOUSE,//家
		HOUSEWHITE,//白い家
		POLE,//電柱
		SHINGOKI,//信号機
		FENCE,//フェンス
		GARDEN,//庭
		CONSTRUCTION,//工事現場
		SCHOOL,//学校
		BPARKING,//駐輪場
		CORRIDORFLOOR,//廊下の床
		CORRIDORWALL,//廊下の壁
		SHOERACK,//下駄箱
		ROOMDOOR,//教室のドア
		BOARD,//掲示板
		ENTRANCE,//玄関ドア
		GYMFRONT,//体育館正面
		GYMWALL,//体育館壁
		GYMENTRANCE,//体育館入口
		GYMWALLTOP,//体育館壁上部
		BASKETGOAL,//バスケットゴール
		WALL,//壁
		GYMDOOR,//体育館ドア
		GYMCEILING,
		CEXIT,//廊下出口
		CORRIDORCEILING,//廊下天井
		ILLUMINATION,//照明
		WAVEWALL,//ウェーブで消える壁
		MAX,
	};

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CBuilding(int nPriority = PRIORITY);//コンストラクタ
	~CBuilding() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBuilding* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	BUILDING_TYPE GetBuildingType();//建物の種類を取得
	void SetBuildingType(BUILDING_TYPE type);//建物の種類を設定
	int GetModelIdx();//モデルの番号を取得
	void SetModelIdx(int Idx);//モデルの番号を設定
	void ColisionPlayer();//プレイヤーとの当たり判定
	void ColisionPlayerWide();//モデルが横向きの時の当たり判定
	void ColisionEnemy();//敵との当たり判定
	void ColisionEnemyWide();//モデルが横向きの時の敵との当たり判定
private:
	

	//メンバ変数
	int m_nModelIdx;//モデルの番号
	BUILDING_TYPE m_Building_Type;//建物の種類
};
#endif