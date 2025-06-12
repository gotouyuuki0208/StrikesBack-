//==========================
// 
// 矢印表示が指し示す位置[arrowpoint.h]
// Author Yuki Goto
//
//==========================
#ifndef _ARROWPOINT_H_
#define _ARROWPOINT_H_

//include
#include "fild.h"

//前方宣言
class CPlayer;

//クラスの定義
class CArrowPoint :public CFild
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CArrowPoint(int nPriority = PRIORITY);//コンストラクタ
	~CArrowPoint() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CArrowPoint* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//オブジェクト生成
private:
	//メンバ関数
	void GetPlayerinfo();//プレイヤーの情報を取得
	void CollisionPlayer();//プレイヤーが当たってるか判定

	//メンバ変数
	CPlayer* m_player;//プレイヤーの情報
};
#endif