//==========================
// 
// 武器の位置表示[weaponpoint.h]
// Author Yuki Goto
//
//==========================
#ifndef _WEAPONPOINT_H_
#define _WEAPONPOINT_H_

//include
#include "billboard.h"

//クラスの定義
class CWeaponPoint :public CBillBoard
{
public:
	//定数
	static const int PRIORITY;//描画順
	static const float MOVE;//移動量
	static const float DISTANCE;//移動する距離

	//メンバ関数
	CWeaponPoint(int nPriority = PRIORITY);//コンストラクタ
	~CWeaponPoint() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CWeaponPoint* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//オブジェクト生成
private:
	//メンバ関数
	void Move();//移動処理

	//メンバ変数
	int m_nTexIdx;//テクスチャの番号
	bool m_MoveDirection;//移動方向切り替え判定
	float m_FirstPos;//最初の位置
};
#endif