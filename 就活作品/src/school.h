//==========================
// 
// 学校[school.h]
// Author Yuki Goto
//
//==========================
#ifndef _SCHOOL_H_
#define _SCHOOL_H_

//include
#include "building.h"

//クラスの定義
class CSchool :public CBuilding
{
public:

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CSchool(int nPriority = PRIORITY);//コンストラクタ
	~CSchool() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CSchool* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif